// UCLA CS 111 Lab 1 main program

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

#include <errno.h>
#include <error.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/resource.h>
#include "command.h"

static char const *program_name;
static char const *script_name;

static void
usage (void)
{
  error (1, 0, "usage: %s [-p PROF-FILE | -t] SCRIPT-FILE", program_name);
}

static int
get_next_byte (void *stream)
{
  return getc (stream);
}

int
main (int argc, char **argv)
{
  double cur_time, real_time, ucpu_time, scpu_time;
  struct timespec cur;
  struct timespec r_start, r_end;
  struct rusage ru_self, ru_children;
  struct rusage ru_self_start, ru_children_start;

  int command_number = 1;
  bool print_tree = false;
  char const *profile_name = 0;
  program_name = argv[0];

  clock_gettime(CLOCK_MONOTONIC, &r_start);

  // Get start user CPU and system CPU times from parent process and child/children processes.
  getrusage(RUSAGE_SELF, &ru_self_start);
  getrusage(RUSAGE_CHILDREN, &ru_children_start);
  
  for (;;)
    switch (getopt (argc, argv, "p:t"))
      {
      case 'p': profile_name = optarg; break;
      case 't': print_tree = true; break;
      default: usage (); break;
      case -1: goto options_exhausted;
      }
 options_exhausted:;

  // There must be exactly one file argument.
  if (optind != argc - 1)
    usage ();

  script_name = argv[optind];
  FILE *script_stream = fopen (script_name, "r");
  if (! script_stream)
    error (1, errno, "%s: cannot open", script_name);
  command_stream_t command_stream =
    make_command_stream (get_next_byte, script_stream);
  int profiling = -1;
  if (profile_name)
    {
      profiling = prepare_profiling (profile_name);
      if (profiling < 0)
	error (1, errno, "%s: cannot open", profile_name);
    }

  command_t last_command = NULL;
  command_t command;
  while ((command = read_command_stream (command_stream)))
    {
      if (print_tree)
	{
	  printf ("# %d\n", command_number++);
	  print_command (command);
	}
      else
	{
	  last_command = command;
	  execute_command (command, profiling);
	}
    }

  // End time of overall shell process in main
  clock_gettime(CLOCK_MONOTONIC, &r_end);
  
  // Get user CPU and system CPU times from parent process and child/children processes.
  getrusage(RUSAGE_SELF, &ru_self);
  getrusage(RUSAGE_CHILDREN, &ru_children);

  //Compute user CPU and system CPU time by adding up times from parent and child.
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

  // Compute current time since Epoch.
  clock_gettime(CLOCK_REALTIME, &cur);
  cur_time = cur.tv_sec + (double)(cur.tv_nsec) / 1000000000;
  
  if (profiling >= 0)
    {
      // Add shell log to profiling file.
      pid_t pid = getpid();
      // Allocate cstring of 1024 characters
      char log[1025];
      int status;

      // allocate a process log based on its size, and format the
      // time values accordingly with pid number at the end.
      status = snprintf(log, 1025, "%.2f %.3f %.3f %.3f [%d]\n",
                        cur_time, real_time, ucpu_time, scpu_time, pid);

      // Return error if it wasn't allocated properly; otherwise, return
      // the number of bytes in the log.
      if (status < -1)
        error(1, 0, "Error in allocating/owriting to log");

      write(profiling, log, strlen(log));
    } 
  
  return print_tree || !last_command ? 0 : command_status (last_command);
}
