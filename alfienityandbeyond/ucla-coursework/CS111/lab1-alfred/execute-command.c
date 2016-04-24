// UCLA CS 111 Lab 1 command execution

// Copyright 2012-2014 Paul Eggert.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "command.h"
#include "command-internals.h"
#include "alloc.h" // checked_malloc, checked_grow_alloc

#include <error.h> 
#include <errno.h>
#include <unistd.h> // execvp for sys calls, fork, dup2, write, open, read
#include <sys/types.h> // pid_t
#include <sys/wait.h> // waitpid(), WEXITSTATUS
#include <fcntl.h> // file control options: O_RDONLY, O_RDWR, O_WRONLY, 0_CREAT
#include <stdlib.h> // malloc, realloc
#include <stdio.h> // printf, fprintf
#include <string.h> // strstr, strlen
#include <sys/time.h> // getrusage
#include <time.h>  // clock_getres, clock_gettime
#include <sys/resource.h>


void
add_log(double * cur, double * real, double * ucpu,
	double * scpu, int profiling, command_t c)
{
  // Cmd string is 992 for 1024-33 (991 + null byte); this is the char limit for cmd
  // after taking into account the size of the formatting of times.
  // log is 1025 to hold 1024 characters plus null byte at end.
  char cmd[992];
  char log[1025];
  int status;
  int word_count = 0;
  int size = 0;
  int i = 0;
  char * word;

  // Reformat the command string to the proper way before passing to snprintf.
  while(c->u.word[word_count] != NULL && i < 991)
    {
      char * word = c->u.word[word_count];
      size = strlen(word);
      if ((i+size+1) < 991)
	{
	  int j;
	  for (j = 0; j < size; j++)
	    {
	      if (word[j] != '\n')
		cmd[i] = word[j];
	      else
		cmd[i] = ' ';
	      i++;
	    }
	  
	  // Add space to the end.
	  if (i < 991)
	    {
	      cmd[i] = ' ';
	      i++;
	    }
	}
      else
	{
	  int start = i;
	  int j;
	  for (j = 0; (start + j) < 991; j++)
	    {
	      if (word[j] != '\n')
		cmd[i] = word[j];
	      else
		cmd[i] = ' ';
	      i++;
	    }
	}
      word_count++;
    }
  // Terminate cmd with null byte.
  cmd[i] = '\0';
  
  // Format the time values and command accordingly before printing out.
  status = snprintf(log, 1025, "%.2f %.3f %.3f %.3f %s\n",
   *cur, *real, *ucpu, *scpu, cmd);

  // for debugging purposes
  // printf ("%s", log);
  
  // Return error if it wasn't allocated properly; otherwise, return
  // the number of bytes in the log.
  if (status < -1)
    error(1, 0, "Error in allocating/writing to log");

  // Write it out to file
  write(profiling, log, strlen(log));
}

int
prepare_profiling (char const *name)
{
  // Open the file or create one if file doesn't already exist
  // to add time profiling data into per shell/subshell processes.
  int fd = open(name, O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

  // If it failed to open/create a file return error (-1); otherwise, return
  // the file descriptor number.
  if (fd < 0)
    return -1;
  else
    return fd;
}

int
command_status (command_t c)
{
  return c->status;
}

void
handle_io(command_t c)
{
  int fd_status;
  // Handle input if present.
  if (c->input != NULL)
    {
      int fd_input = open(c->input, O_RDONLY);
      if (fd_input < 0)
	error(1, 0, "Error in opening input file: %s", c->input);

      fd_status = dup2(fd_input, 0);
      if (fd_status < 0)
	error(1, 0, "Error in duplicating input file descriptor");

      fd_status = close(fd_input);
      if (fd_status < 0)
	error(1, 0, "Error in closing input file: %s", c->input);
    }

  // Handle output if present; create a new file if necessary.
  if (c->output != NULL)
    {
      // If a new file is created, set proper permissions to match shell standards.
      int fd_output = open(c->output, O_CREAT | O_WRONLY | O_TRUNC,
			   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
      if (fd_output < 0)
	error(1, 0, "Error in opening/creating output file: %s", c->output);

      fd_status = dup2(fd_output, 1);
      if (fd_status < 0)
	error(1, 0, "Error in duplicating output file descriptor");

      fd_status = close(fd_output);
      if (fd_status < 0)
	error(1, 0, "Error in closing output file: %s", c->output);
    }  
}

void
execute_simple_command(command_t c, int profiling)
{
  int size;
  double cur_time, real_time, ucpu_time, scpu_time;
  
  struct timespec cur;
  struct timespec r_start, r_end;
  struct rusage ru_self, ru_children;
  struct rusage ru_self_start, ru_children_start;
  
  clock_gettime(CLOCK_MONOTONIC, &r_start);

  // Get start user CPU and system CPU times from parent process and child/children processes.
  getrusage(RUSAGE_SELF, &ru_self_start);
  getrusage(RUSAGE_CHILDREN, &ru_children_start);
  
  // Create a child process.
  pid_t pid = fork();
  
  // Execute the simple commmand in the child process.
  if(pid == 0)
    {
      // Handle input/output file redirections
      handle_io(c);

      // If exec command is found, the following command is executed
      if (strcmp("exec", c->u.word[0]) == 0)
	{
	  char ** w = c->u.word;
	  ++w;

	  execvp(c->u.word[1], w);
	}
      else
	{
	  // Executes command in word[0] with args following after.
	  execvp(c->u.word[0], c->u.word);
	}
	  error(1,0, "%s: command not found", c->u.word[0]);
    }
  else if (pid > 0)
    {
      int status;
      // Parent process waits for child process to execute and stores the status.
      waitpid(pid, &status, 0);
      c->status = WEXITSTATUS(status);

      // End of child process or overall simple command.
      clock_gettime(CLOCK_MONOTONIC, &r_end);

      // Get user CPU and system CPU times from parent process and child/children processes.
      getrusage(RUSAGE_SELF, &ru_self);
      getrusage(RUSAGE_CHILDREN, &ru_children);
    }
  else
    {
      error(1, 0, "Error in forking a child process");
    }

  // Compute user CPU and system CPU time by adding up times from parent and child.
  ucpu_time = (ru_self.ru_utime.tv_sec + ru_children.ru_utime.tv_sec -
	       ru_children_start.ru_utime.tv_sec - ru_self_start.ru_utime.tv_sec) +
    (double)(ru_self.ru_utime.tv_usec + ru_children.ru_utime.tv_usec -
	     ru_self_start.ru_utime.tv_usec - ru_children_start.ru_utime.tv_usec)
    / 1000000;
  scpu_time = (ru_self.ru_stime.tv_sec + ru_children.ru_stime.tv_sec -
	       ru_children_start.ru_stime.tv_sec - ru_self_start.ru_stime.tv_sec) +
    (double)(ru_self.ru_stime.tv_usec + ru_children.ru_stime.tv_usec -
	     ru_self_start.ru_stime.tv_usec - ru_children_start.ru_stime.tv_usec)
    / 1000000;
  
    
  // Compute real execution time.
  real_time = (double)(r_end.tv_sec - r_start.tv_sec) + (double)(r_end.tv_nsec - r_start.tv_nsec)/1000000000;
  //printf("%f CLOCK_EXECTIME\n", real_time);
   
  // Compute current time since Epoch.
  clock_gettime(CLOCK_REALTIME, &cur);
  cur_time = cur.tv_sec + (double)(cur.tv_nsec) / 1000000000;
  //printf("%f CLOCK_CURTIME\n", cur_time);

  if(profiling >= 0)
    {
      // Create log line and add it to profiling file.
      add_log(&cur_time, &real_time, &ucpu_time, &scpu_time, profiling, c);
    }
}

void
execute_if_command(command_t c, int profiling)
{
  // Copy stdin and stdout file descriptors just in case to replace
  // if c->output/input changes.
  int cfdin = dup(0);
  int cfdout = dup(1);
  
  // Handle IO for after compound commands
  handle_io(c);
 
  // Execute for if A
  execute_command(c->u.command[0], profiling);

  // Status is nonzero if false, so if the if-statement returned false,
  // run the else part if there is one.
  if ((c->u.command[0]->status))
    {
      // If the else exists for the format if A then B else C fi
      if (c->u.command[2] != NULL)
	{
	  execute_command(c->u.command[2], profiling);
	  c->status = c->u.command[2]->status;
	}
      else
	{
	  // Nothing executed so exit status is 0.
	  c->status = 0;
	}
    }
  else // Status is 0, meaning true, so do B for the format: if A then B ...
    {
      execute_command(c->u.command[1], profiling);

      // Set status of last command executed
      c->status = c->u.command[1]->status;
    }

  if (c->output != NULL)
    {
      dup2(cfdout, 1);
    }
  if (c->input != NULL)
    {
      dup2(cfdin, 0);
    }
}

void
execute_until_command(command_t c, int profiling)
{  
  // Copy stdin and stdout file descriptors just in case to replace
  // if c->output/input changes.
  int cfdin = dup(0);
  int cfdout = dup(1);
  
  // Handle IO for after the until command
  handle_io(c);

  // Run A command for the format: until A
  execute_command(c->u.command[0], profiling);

  // If no body commands executed, set exit status of until command to 0.
  c->status = 0;
    
  // Until the condition is true or the status of the execute command is no longer a nonzero number,
  // do B for the format: until A do B done
  while ((c->u.command[0]->status))
    {
      // Do B until A is true.
      execute_command(c->u.command[1], profiling);

      // Set exit status to status of final body command executed.
      c->status = c->u.command[1]->status;

      // Run command A again to get a new status to be checked.
      execute_command(c->u.command[0], profiling);
    }
  
  if (c->output != NULL)
    {
      dup2(cfdout, 1);
    }
  if (c->input != NULL)
    {
      dup2(cfdin, 0);
    }
}

void
execute_while_command(command_t c, int profiling)
{  
  // Copy stdin and stdout file descriptors just in case to replace
  // if c->output/input changes.
  int cfdin = dup(0);
  int cfdout = dup(1);
  
  // Handle IO for after the while command
  handle_io(c);
  
  // Run A command for the format: while A
  execute_command(c->u.command[0], profiling);

  // If no body commands executed, set exit status to 0.
  c->status = 0;
  
  // While the condition is true or the status of the execute command is zero,
  // do B for the format: while A do B done
  while (!(c->u.command[0]->status))
    {
      // Do B while A is true.
      execute_command(c->u.command[1], profiling);
      // Set status to exit status of last body command.
      c->status = c->u.command[1]->status;
      
      // Run command A again to get a new status to be checked.
      execute_command(c->u.command[0], profiling);
    }

  if (c->output != NULL)
    {
      dup2(cfdout, 1);
    }
  if (c->input != NULL)
    {
      dup2(cfdin, 0);
    }

}

void
execute_sequence_command(command_t c, int profiling)
{
  // Handle IO for after the sequence command
  handle_io(c);

  // For sequence commands, simply execute A then B for the format: A;B
  execute_command(c->u.command[0], profiling);
  execute_command(c->u.command[1], profiling);

  // Set exit status to status of final command executed in sequence.
  c->status = c->u.command[1]->status;
}

void
execute_pipe_command(command_t c, int profiling)
{
  int pfd[2];
  int ppid, size;
  pid_t pid;
  double cur_time, real_time, ucpu_time, scpu_time;

  struct timespec cur;
  struct timespec r_start, r_end;
  struct rusage ru_self, ru_children;
  struct rusage ru_self_start, ru_children_start;
  
  // Create a pipe with file descriptors going into pfd[0] for read end and
  // pfd[1] for write end.
  pipe(pfd);

  clock_gettime(CLOCK_MONOTONIC, &r_start);
  // Get start user CPU and system CPU times from parent process and child/children proces\ses.
  getrusage(RUSAGE_SELF, &ru_self_start);
  getrusage(RUSAGE_CHILDREN, &ru_children_start);
  
  // Create a child process to handle B, it should exit first
  ppid = fork();

  // Handle child's process, handling A for the format: A|B
  if (ppid == 0)
    {
      // Replace stdout with write end of pipe.
      dup2(pfd[1], 1);

      // Close unused read end of pipe
      close(pfd[0]);

      // Run A.
      execute_command(c->u.command[0], profiling);
      _exit(c->u.command[0]->status);
    }
  else // Handle parent's process, handling B for the format: A|B
    {
      // Replace stdin with read end of pipe
      dup2(pfd[0], 0);

      // Close unused write end of pipe
      close(pfd[1]);

      // Wait for child process
      waitpid(ppid, &(c->status), 0);

      // Run B
      execute_command(c->u.command[1], profiling);

      // The exit status of B should be the exit status of overall pipe.
      c->status = c->u.command[1]->status;
    }

  // End of child processes for overall pipe command.
  clock_gettime(CLOCK_MONOTONIC, &r_end);

  // Get user CPU and system CPU times from parent process and child/children processes.
  getrusage(RUSAGE_SELF, &ru_self);
  getrusage(RUSAGE_CHILDREN, &ru_children);


  // Compute user CPU and system CPU time by adding up times from parent and child.
  ucpu_time = (ru_self.ru_utime.tv_sec + ru_children.ru_utime.tv_sec -
	       ru_children_start.ru_utime.tv_sec - ru_self_start.ru_utime.tv_sec) +
    (double)(ru_self.ru_utime.tv_usec + ru_children.ru_utime.tv_usec -
	     ru_self_start.ru_utime.tv_usec - ru_children_start.ru_utime.tv_usec)
    / 1000000;
  scpu_time = (ru_self.ru_stime.tv_sec + ru_children.ru_stime.tv_sec -
	       ru_children_start.ru_stime.tv_sec - ru_self_start.ru_stime.tv_sec) +
    (double)(ru_self.ru_stime.tv_usec + ru_children.ru_stime.tv_usec -
	     ru_self_start.ru_stime.tv_usec - ru_children_start.ru_stime.tv_usec)
    / 1000000;
  //printf("%f UCPU_TIME %f SCPU_TIME\n", ucpu_time, scpu_time);

  // Compute real execution time.
  real_time = (double)(r_end.tv_sec - r_start.tv_sec) +
    (double)(r_end.tv_nsec - r_start.tv_nsec)/1000000000;
  //printf("%f CLOCK_EXECTIME\n", real_time);

  // Compute current time since Epoch.
  clock_gettime(CLOCK_REALTIME, &cur);
  cur_time = cur.tv_sec + (double)(cur.tv_nsec) / 1000000000;
  //printf("%f CLOCK_CURTIME\n", cur_time);

  if (profiling >= 0)
    {
      // Add shell log to profiling file.
      pid = getpid();
      // Allocate cstring of 1024 characters
      char log[1025];
      int status;

      // Dynamically allocate a process log based on its size, and format the
      // time values accordingly with pid number at the end.
      status = snprintf(log, 1025, "%.2f %.3f %.3f %.3f [%d]\n",
			cur_time, real_time, ucpu_time, scpu_time, pid);
      
      // Return error if it wasn't allocated properly; otherwise, return
      // the number of bytes in the log.
      if (status < -1)
	error(1, 0, "Error in allocating/writing to log");
      
      write(profiling, log, strlen(log));
    }
 
}

void
execute_subshell_command(command_t c, int profiling)
{
  // Copy stdin and stdout file descriptors just in case to replace
  // if c->output/input changes.
  int cfdin = dup(0);
  int cfdout = dup(1);
  
  // Handle IO for after the subshell command
  handle_io(c);
  
  // Simply run the command within subshell (A)
  execute_command(c->u.command[0], profiling);

  // The exit status of A should be the exit status of subshell command
  c->status = c->u.command[0]->status;

  // Possibly reset to original IO values.
  if (c->output != NULL)
    {
      dup2(cfdout, 1);
    }
  if (c->input != NULL)
    {
      dup2(cfdin, 0);
    }
}

void
execute_command (command_t c, int profiling)
{
  switch (c->type)
    {
    case SIMPLE_COMMAND:
      execute_simple_command(c, profiling);
      break;
    case IF_COMMAND:
      execute_if_command(c, profiling);
      break;
    case UNTIL_COMMAND:
      execute_until_command(c, profiling);
      break;
    case WHILE_COMMAND:
      execute_while_command(c, profiling);
      break;
    case SEQUENCE_COMMAND:
      execute_sequence_command(c, profiling);
      break;
    case PIPE_COMMAND:
      execute_pipe_command(c, profiling);
      break;
    case SUBSHELL_COMMAND:
      execute_subshell_command(c, profiling);
      break;
    default:
      error(1, 0, "Command type not found.");
    }
  return ;
}
