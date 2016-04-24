
// UCLA CS 111 Lab 1 command reading
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
#include <stdlib.h> // malloc, free, realloc, calloc
#include <string.h> // strstr, strlen, strcat
#include <stdio.h> // printf, fprintf
#include <ctype.h> // isalnum, isalpha,tolower, toupper
#include <error.h> 

// struct command_stream
// {
  // size_t m_num;
  // size_t m_iter;
  // command_t m_command;
  // command_stream_t m_next;
  // command_stream_t m_prev;
// };

struct command_stream
{
	command_t cmd;
	command_stream_t next;
	size_t already_checked;
};

struct token
{
  enum token_type m_token_type;
  char * m_script;
  size_t m_line;
  token_t m_prev_token;
  token_t m_next_token;
};

// HELPER FUNCTIONS IN make_command_stream(): DECLARATIONS
// Returns 1 if the ch is a valid word char.
// Fulfills criteria: A-Z, a-z, 0-9, and !%+,-./:@^_
size_t is_word_char(char ch);

// Initialize a token with proper settings.
token_t create_token(enum token_type type, char * script, size_t line, token_t prev);

// Initialize a token with proper settings.
token_stream_t create_token_stream(token_t head, token_stream_t next);

// Separate the buffer characters into tokens indicating the word/command/special characters
// involved and organizes it into a linked list of tokens that is pointed to by a
// token_stream.
token_stream_t separate_into_tokens(char *buf, size_t size);

// Separate token list into proper token streams based on rules.
token_stream_t split_tstream(token_stream_t stream);

// Print all tokens. This is for debugging purposes.
void print_tokens(token_stream_t stream);

// Free all the allocated words in tokens, tokens, and token stream involved.
void free_token_stream(token_stream_t token_stream);

// Initialize input and output of a command to NULL.
command_t nullifyIO (command_t c);

// Checks for bad grammar
size_t check_grammar (token_stream_t ts);

// Adjust certain newlines to semicolons and account for "cat if done" case
void adjust_tokens(token_stream_t ts);

// MAJOR FUNCTION DEFINITIONS

command_t 
parse_command (token_t tp, command_t cpA)
{	
	
	if (tp != NULL)
	  {
	    switch (tp->m_token_type) 
	      {
		case NEWLINE:
		  {
			if (tp->m_next_token != NULL)
			  {
			    cpA = parse_command(tp->m_next_token, cpA);
			    return cpA;
			  }
			else
			  {
			    
			    /* if (tp->m_next_token == WORD && tp->m_prev_token != NULL && (tp ->m_prev_token->m_token_type == DONE || tp->m_prev_token->m_token_type == FI || tp->m_prev_token == WORD))
			      {
				tp->m_token_type = SEMICOLON;
				cpA = parse_command(tp, cpA);
			      }
			    */
			    return cpA;
			  }
			break;
		  }
		case WORD:
		  {
		    // if the command is the first one passed, dynamically allocate one
		    if (cpA == NULL)
		      {
			cpA = (command_t) checked_malloc(sizeof(struct command));
			cpA->status = -1;
		      }
		    
		    cpA->type = SIMPLE_COMMAND;
		   
      		    size_t i = 0;			
		    size_t count = 0;
		    token_t temp = tp;
		    // First count how many words to add to simple_command; 
		    while (temp != NULL && temp->m_token_type == WORD)
		      {
			temp = temp->m_next_token;	
			count++;
		      }
		    
			
		    cpA->u.word = (char**)checked_malloc(sizeof(char*)*(count+1));
		    while (i < count)
		      {
			cpA->u.word[i] = tp->m_script;
			tp = tp->m_next_token;
			i++;
		      }

		    // set last word to NULL
		    cpA->u.word[i] = NULL;
			
		    if (tp == NULL)
		      {
			cpA->type = SIMPLE_COMMAND;
			cpA = nullifyIO(cpA);
			return cpA;
		      }
		    
		    if (tp->m_token_type == LEFT_REDIR)
		      {
			cpA->type = SIMPLE_COMMAND;
			// if <
			if (tp->m_next_token != NULL)
			  {
			    tp = tp->m_next_token;
			    // if < bad
			    if (tp->m_token_type != WORD)
			      {
				// Syntax error: < bad
				exit(1);
		      }
			    // if < word
			    else
			      {
				cpA->input = tp->m_script;
				cpA->output = NULL;
				if (tp->m_next_token != NULL)
				  {
				    tp = tp->m_next_token;
				    // if < word >
				    if (tp->m_token_type == RIGHT_REDIR)
				      {
					if (tp->m_next_token != NULL)
					  {
					    tp = tp->m_next_token;
					    // if < word > word
					    if (tp->m_token_type == WORD)
					      {
						cpA->output = tp->m_script;
					      }
					    else
					      {
						// Syntax error: < word > bad
						exit(1);
					      }
					  }
				      }
				    else
				      {
					tp = tp->m_prev_token;
				      }
				  }
			      }
			  }
			
			// If there are no more tokens and this is the last command
			if (tp->m_next_token == NULL)
			  {
			    return cpA;
			  }
			// If there are more tokens left, make a new command and
			// check the other tokens
			else
			  {
			    cpA = parse_command(tp->m_next_token, cpA);
			    return cpA;
			  }
			
			
		      }
		    else if (tp->m_token_type == RIGHT_REDIR)
		      {
			cpA->type = SIMPLE_COMMAND;
			cpA->input = NULL;
			cpA->output = NULL;
			if (tp->m_next_token != NULL)
			  {
			    tp = tp->m_next_token;
			    // if > bad
			    if (tp->m_token_type != WORD)
			      {
				// Syntax error: > bad
				exit(1);
			      }
			    else
			      {
				cpA->output = tp->m_script;
			      }
			  }
			
			// If there are no more tokens and this is the last command
			if (tp->m_next_token == NULL)
			  {
			    
			    return cpA;
			  }
			else
			  {
			    cpA = parse_command(tp->m_next_token, cpA);
			    return cpA;
			  }
		      }
		    // Word is not immediately followed by a < or >
		    else
		      {
			cpA = parse_command(tp, cpA);
			return cpA;
		      }
		    break;
		  }
		case PIPE:
		case SEMICOLON:
		  {
		    // check for a;a;, then a;, etc.
		    if (tp->m_next_token == NULL || tp->m_next_token->m_token_type == DO || tp->m_next_token->m_token_type == FI || tp->m_next_token->m_token_type == ELSE ||
			tp->m_next_token->m_token_type == DONE || tp->m_next_token->m_token_type == THEN)
		      {
			return cpA;
		      }
			command_t pscp = (command_t)checked_malloc(sizeof(struct command));
			pscp->status = -1;
		       
			if (tp->m_token_type == PIPE)
			  {
				pscp->type = PIPE_COMMAND;
			  }
			else
			  {
				pscp->type = SEQUENCE_COMMAND;
			  }
			
			pscp->u.command[0] = cpA;
			pscp = nullifyIO(pscp);
			
			command_t cpB = (command_t)checked_malloc(sizeof(struct command));
			cpB->status = -1;
			pscp->u.command[1] = parse_command(tp->m_next_token, cpB);

			return pscp;
			
			break;
		  }
	      case OPEN_PAREN:
		  {
			command_t shcp = (command_t)checked_malloc(sizeof(struct command));
			shcp->status = -1;
			shcp->type = SUBSHELL_COMMAND;
			shcp->u.command[0] = parse_command(tp->m_next_token, cpA);
			shcp = nullifyIO(shcp);
			
			while (tp != NULL && tp->m_token_type != CLOSED_PAREN)
			  {
				tp = tp->m_next_token;
			  }
			
			if (tp->m_token_type == CLOSED_PAREN)
			  {
				tp = tp->m_next_token;
				// // while (tp != NULL && tp->m_token_type != PIPE && tp->m_token_type != SEMICOLON && tp->m_token_type != THEN && tp->m_token_type != ELSE && tp->m_token_type != FI && tp->m_token_type != DO && tp->m_token_type != DONE) 	
				// // {
					// // tp = tp->m_next_token;
				// // }
				
				if (tp == NULL)
				  {
					return shcp;
				  }
				else
				  {
					shcp = parse_command(tp, shcp);
					return shcp;
				  }
			  }
			else
			  {
			 abort();
			  }
			break;
		  }
		case IF:
		case WHILE:
		case UNTIL:
		  {
		    size_t if_count = 0;
		    size_t uw_count = 0;
		    if (cpA == NULL)
		      {
			cpA = (command_t) checked_malloc(sizeof(struct command));
			cpA->status = -1;
			cpA = nullifyIO(cpA);
		      }
		    if (tp->m_token_type == IF)
		      {
			cpA->type = IF_COMMAND;
		      }
		    else if (tp->m_token_type == WHILE)
		      {
			cpA->type = WHILE_COMMAND;
		      }
		    else 
		      {
			cpA->type = UNTIL_COMMAND;
		      }

		    cpA->u.command[0] = NULL;
		    cpA->u.command[1] = NULL;
		    cpA->u.command[2] = NULL;
		       
		    // Handle A arguments: if A, while A, until A
		    command_t cAcp = (command_t)checked_malloc(sizeof(struct command));
		    cAcp = nullifyIO(cAcp);
		    cAcp->status = -1;
		    cpA->u.command[0] = parse_command(tp->m_next_token, cAcp);

		    // Handle B arguments if A then B
		    command_t cBcp = (command_t)checked_malloc(sizeof(struct command));
		    cBcp->status = -1;
		    cBcp = nullifyIO(cBcp);
		    
   		    if (tp->m_token_type == IF)
		      {
			while (tp != NULL)
			  {
			    if (tp->m_token_type == IF)
			      {
				if_count++;
			      }
			    else if (tp->m_token_type == FI)
			      {
				if_count--;
			      }
			    else if (tp->m_token_type == THEN && if_count == 1)
			      {
				break;
			      }
			    tp = tp->m_next_token;
			  }
			if (tp == NULL)
			  {
			    // Syntax error, no THEN
			    exit(1);
			  }
			// After finding THEN or NULL
			cpA->u.command[1] = parse_command(tp->m_next_token, cBcp);
			
			/* Handle nested here too */
			while (tp != NULL && tp->m_token_type != ELSE && tp->m_token_type != FI)
			  {
			    tp = tp->m_next_token;
			  }
			// After finding ELSE or FI or NULL
			if (tp == NULL)
			  {
			    // Possible syntax error maybe?
			    exit(1);
			  }
			else if (tp->m_token_type == ELSE)
			  {
			    command_t cCcp = (command_t) checked_malloc(sizeof(struct command));
			    cCcp = nullifyIO(cCcp);
			    cCcp->status = -1;
			    cpA->u.command[2] = parse_command(tp->m_next_token, cCcp);
			
			  }
			else if (tp->m_token_type == FI)
			  {
			    cpA = parse_command(tp->m_next_token, cpA);
			    return cpA;
			  }
			// What if it's FI?
		      }
		    else if (tp->m_token_type == WHILE || tp->m_token_type == UNTIL)
		      {
			/* Handle nested here too */
			while (tp != NULL)
			  {
			    if (tp->m_token_type == WHILE || tp->m_token_type == UNTIL)
			      {
				uw_count++;
			      }
			    else if (tp->m_token_type == DONE)
			      {
				uw_count--;
			      }
			    else if (tp->m_token_type == DO && uw_count == 1)
			      {
				break;
			      }
			    tp = tp->m_next_token;
			  }
			// After finding DO or NULL
			cpA->u.command[1] = parse_command(tp->m_next_token, cBcp);

			while (tp != NULL && tp->m_token_type != DONE)
			  {
			    tp = tp->m_next_token;
			  }
			// After finding DONE
			if (tp == NULL)
			  {
			    
			    exit(1);
			  }
			else
			  {
			    if (tp->m_next_token != NULL && tp->m_next_token->m_token_type == NEWLINE && tp->m_next_token->m_next_token != NULL && tp->m_next_token->m_next_token->m_token_type == WORD)
			      {
				tp->m_next_token->m_token_type = SEMICOLON;
				cpA = parse_command(tp->m_next_token, cpA);
				return cpA;
						    
			      }
			    cpA = parse_command(tp->m_next_token, cpA);
			    return cpA;
			  }
		      }
		    
		    break;
		  }
	      case THEN:
	      case ELSE:
	      case FI:
	      case DO:
	      case DONE:
		{
		  return cpA;
		  break;
		}
	      case LEFT_REDIR:
	      case RIGHT_REDIR:
		{
		  if (tp->m_next_token != NULL && tp->m_token_type == LEFT_REDIR)
		    {
		      cpA->input = tp->m_next_token->m_script;
		    }
		  else if (tp->m_next_token != NULL && tp->m_token_type == RIGHT_REDIR)
		    {
		      cpA->output = tp->m_next_token->m_script;
		    }
		  return cpA;
		}
	      }
	  }
	// If there are no more tokens in token stream, return the command.
	return cpA;
}

command_stream_t
make_command_stream (int (*get_next_byte) (void *),
		     void *get_next_byte_argument)
{
  // First, read in all characters of input file into a buffer.
  char ch;
  size_t index = 0;
  size_t buf_size = 1024;
  char * buf = (char *) checked_malloc(sizeof(char) * buf_size);
  token_stream_t tstream;
  token_stream_t tstream_list;
  
  // Place one char at a time into buffer, reallocating if necessary.
  while ((ch = get_next_byte(get_next_byte_argument)) != EOF)
    {
      if (index+1 == buf_size)
	  buf = (char *) checked_grow_alloc(buf, &buf_size);
      if (ch == '&')
	exit(-1);
      
      buf[index] = ch;
      index++;
    }

    if (index == buf_size)
	buf = (char *) checked_grow_alloc(buf, &buf_size);

    // Make sure the buffer ends in a null byte.  
    buf[index] = '\0';

    tstream = (token_stream_t) separate_into_tokens(buf, index);

    adjust_tokens(tstream);
    
    size_t good_grammar = 0;
    good_grammar =  check_grammar(tstream);
    
    tstream_list = (token_stream_t) split_tstream(tstream);

    
    // print_tokens(tstream_list);

    command_stream_t cstream_head;
    command_stream_t add_cstream;
    command_stream_t cur_cstream;
    if (tstream_list != NULL)
      {
	command_stream_t add_cstream = (command_stream_t)checked_malloc(sizeof(struct command_stream));
	add_cstream->next = NULL;
	add_cstream->cmd = NULL;
	cur_cstream = add_cstream;
	cur_cstream->already_checked = 0;
	cstream_head = cur_cstream;
	token_stream_t tstreamtemp = tstream_list;
	    
	while(tstreamtemp != NULL)
	  {
	    cur_cstream->cmd = NULL;
	    cur_cstream->cmd = parse_command(tstreamtemp->m_head, cur_cstream->cmd);
	    tstreamtemp = tstreamtemp->m_next_token_stream;
		  
	    if (tstreamtemp != NULL)
	      {
		add_cstream = (command_stream_t) checked_malloc(sizeof(struct command_stream));
		add_cstream->next = NULL;
		add_cstream->cmd = NULL;
		cur_cstream->next = add_cstream;
		cur_cstream = add_cstream;
		cur_cstream->already_checked = 0;
	      }
	  }

		/*  Not necessary anymore 
		if (tstreamtemp == NULL)
		{
			cstream->next = NULL;
		}
		*/
      }
    else
      {
	cstream_head = NULL;
      }

    /*
  // Deallocate memory from buffer.
    free(buf);
    free_token_stream(tstream);
    */
  // free_command_stream(cstream);

    return cstream_head;

}

// Iterate through command_stream_t nodes until one finds proper one that hasn't
// been used yet and return its command_t member.
command_t
read_command_stream (command_stream_t s)
{
  command_stream_t temp = s;
  if (temp == NULL)
    return NULL;
  
  while (temp != NULL)
    {
      if (temp->already_checked != 1)
	{
	  temp->already_checked = 1;
	  return temp->cmd;
	}
      else
	{
	  temp = temp->next;
	}
    };
  
  return NULL;
}

// HELPER FUNCTION DEFINITIONS

size_t
is_word_char(char ch)
{
  if ((isalnum(ch)) || (strchr("!%+,-./:@^_", ch) != NULL))
    return 1;
  else
    return 0;
}

token_t
create_token(enum token_type type, char * script, size_t line, token_t prev)
{
  token_t new_token = (token_t)checked_malloc(sizeof(struct token));
  new_token->m_prev_token = prev;
  new_token->m_script = script;
  new_token->m_line = line;
  new_token->m_token_type = type;
  new_token->m_next_token = NULL;

  return new_token;				  
}

token_stream_t
create_token_stream(token_t head, token_stream_t next)
{
  token_stream_t stream = (token_stream_t) checked_malloc(sizeof(struct token_stream));
  stream->m_head = head;
  stream->m_next_token_stream = next;
  
  return stream;
}

    
token_stream_t
separate_into_tokens(char *buf, size_t size)
{
  token_stream_t head_token_stream = NULL;
  token_stream_t cur_token_stream = NULL;
  token_stream_t add_token_stream = NULL;

  token_t cur_token = NULL;
  token_t add_token = NULL;

  size_t word_size= 0;;
  size_t buf_index = 0;
  size_t word_index = 0;
  size_t line_num = 0;
  char ch;
    
  while (buf_index < size)
    {
      ch = buf[buf_index];

      switch (ch)
	{
	case '<':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(LEFT_REDIR, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }
		
		cur_token = add_token;
	      }
	    else
	      {
		add_token = (token_t)create_token(LEFT_REDIR,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
	      }
	    break;
	  }
	case '>':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(RIGHT_REDIR, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }
		
		cur_token = add_token;
      	      }
	    else
	      {
		add_token = (token_t)create_token(RIGHT_REDIR,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
	      }
	    break;
	  }
       	case '(':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(OPEN_PAREN, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }
		
		cur_token = add_token;
       	      }
	    else
	      {
		add_token = (token_t)create_token(OPEN_PAREN,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
	      }
	    break;
	  }
       	case ')':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(CLOSED_PAREN, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }
		
		cur_token = add_token;
		
	      }
	    else
	      {
		add_token = (token_t)create_token(CLOSED_PAREN,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
		
	      }
	    break;
	  }
	case ';':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(SEMICOLON, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }
		
		cur_token = add_token;
		
	      }
	    else
	      {
		add_token = (token_t)create_token(SEMICOLON,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
	      }
	    break;
	  }
	case '|':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(PIPE, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }
		
		cur_token = add_token;
		
	      }
	    else
	      {
		add_token = (token_t)create_token(PIPE,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
	      }
      	    break;
	  }
	case '#':
	  {
	    char commented_out_char;

	    buf_index++;
	    while (buf_index < size)
	      {
		commented_out_char = buf[buf_index];
		if (commented_out_char == '\n')
		  break;

		buf_index++;
	      }
	    
	    if (buf_index < size)
	      buf_index--;
	    
	    break;
	  }
	case '\n':
	  {
	    if (cur_token == NULL)
	      {
		add_token = (token_t)create_token(NEWLINE, (buf+buf_index), line_num, NULL);
		if (head_token_stream == NULL)
		  {
		    add_token_stream = (token_stream_t) create_token_stream(add_token, NULL)\
		      ;
		    head_token_stream = add_token_stream;
		    cur_token_stream = add_token_stream;
		  }
		else // handle if added another stream to set beginning of new token list
		  {
		    cur_token_stream->m_head = add_token;
		  }

		cur_token = add_token;

	      }
	    else
	      {
		add_token = (token_t)create_token(NEWLINE,(buf+buf_index), line_num, cur_token);
		cur_token->m_next_token = add_token;
		cur_token = add_token;
	      }
	    break;
	  }
	}
	    /*
	    if (ch == '\n')
	      {
		if (buf_index+1 < size)
		  {
		    buf_index++;
       		    ch = buf[buf_index];
		    if (ch == '\n')
		      {
			if (cur_token != NULL)
			  {
			    if (cur_token->m_token_type == WORD || cur_token->m_token_type == FI || cur_token->m_token_type == DONE
				|| cur_token->m_token_type == CLOSED_PAREN)
			      {
				line_num++;
				add_token_stream = (token_stream_t) create_token_stream(NULL, NULL);
				cur_token_stream->m_next_token_stream = add_token_stream;
				cur_token_stream = add_token_stream;
				cur_token = NULL;
			      }
			    
			    else if (cur_token->m_token_type == THEN || cur_token->m_token_type == ELSE || cur_token->m_token_type == DO
				     || cur_token->m_token_type == WHILE || cur_token->m_token_type == IF || cur_token->m_token_type == UNTIL)
			      {
				add_token = (token_t)create_token(SEMICOLON,(buf+buf_index), line_num, cur_token);
				cur_token->m_next_token = add_token;
				cur_token = add_token;
			      }
			    else
			      break;
			    
			  }
      		      }
		    else
		      {
			buf_index--;
		      }
		  }
		line_num++;
	      }
*/
		  
      // If it is a word char, retrieve the rest of the word; Otherwise, return
      // error as other characters are not allowed.
      if (is_word_char(ch))
	{
      	  word_size = 8;
	  word_index = 0;
	  char * word = (char *) checked_malloc(word_size);
	  word[word_index] = ch;
	  word_index++;
	  buf_index++;
	  
	  while (buf_index < size)
	    {
	      ch = buf[buf_index];
	      if (is_word_char(ch))
		{
		  word[word_index] = ch;
		  word_index++;
		  if (word_index == word_size)
		    {
		      word = (char *)checked_grow_alloc(word, &word_size);
		    }
		}
	      else
		break;
	      buf_index++;
	    }	  

	  // End words with null-byte, crucial for printf
	  if (word_index == word_size)
	    word = (char *)checked_grow_alloc(word, &word_size);
	  
	  word[word_index] = '\0';

	  if (cur_token == NULL)
	    {
	      add_token = (token_t)create_token(WORD, word, line_num, NULL);
	      if (head_token_stream == NULL)
		{
		  add_token_stream = (token_stream_t) create_token_stream(add_token, NULL);
		  head_token_stream = add_token_stream;
		  cur_token_stream = add_token_stream;
		}
	      else // handle if added another stream to set beginning of new token list
		{
		  cur_token_stream->m_head = add_token;
		}
	      
	      cur_token = add_token;
	    }
	  else
	    {
	      add_token = (token_t)create_token(WORD, word, line_num, cur_token);
	      cur_token->m_next_token = add_token;
	      cur_token = add_token;
	    }

	  // Now check if the word is a special command word such as if, fi, while, until, etc. and set accordingly.
	  // The special commands are of size 2, 4, and 5 so break it down further and check using strstr.
	  // strstr returns null if word is not the same as special one.
	  char * result = NULL;
	  if (word_index == 2)
	    {
	      if ((result = strstr(word, "if")) != NULL)
		{
		  cur_token->m_token_type = IF;
		}
	      else if ((result = strstr(word, "fi")) != NULL)
		{
		  cur_token->m_token_type = FI;
		}
	      else if ((result = strstr(word, "do")) != NULL)
		{
		  cur_token->m_token_type = DO;
		}
	    }
	  else if (word_index == 4)
	    {
	      if ((result = strstr(word, "then")) != NULL)
		{
		  cur_token->m_token_type = THEN;
		}
	      else if ((result = strstr(word, "else")) != NULL)
		{
		  cur_token->m_token_type = ELSE;
		}
	      else if ((result = strstr(word, "done")) != NULL)
		{
		  cur_token->m_token_type = DONE;
		}
	    }
	  else if (word_index == 5)
	    {
	      if ((result = strstr(word, "until")) != NULL)
		{
		  cur_token->m_token_type = UNTIL;
		}
	      else if ((result = strstr(word, "while")) != NULL)
		{
		  cur_token->m_token_type = WHILE;
		}
	    }
	  
	  
	  // If the word is retrieved but the buffer is still not yet fully traversed,
	  // decrement the buf_index because the char that it encountered may be a special token.
	  if (buf_index < size)
	    {
	      buf_index--;
	    }
	  else
	   {
	     exit(-1);
	   }
       	}
      buf_index++;
    }
  
  return head_token_stream;
}

token_stream_t
split_tstream(token_stream_t stream)
{
  token_stream_t head = stream;
  token_stream_t add_token_stream = NULL;

  token_t cur = head->m_head;
  token_t next = NULL;
  token_t prev = NULL;
  size_t compound_count = 0;
 
  if (stream == NULL)
    return NULL;

  while (cur != NULL)
    {
            
      if (cur->m_token_type == IF || cur->m_token_type == WHILE || cur->m_token_type == UNTIL)
	{
	  compound_count++;
	}
      else if (cur->m_token_type == FI || cur->m_token_type == DONE)
	{
	  compound_count--;
	}
      else if (cur->m_token_type == NEWLINE)
	{
	  next = cur->m_next_token;
	  if (next != NULL && next->m_token_type == NEWLINE && compound_count == 0)
	    {
	      prev = cur->m_prev_token;
	      if (prev != NULL && prev->m_token_type != NEWLINE)
		{
		  // Add a token stream after a complete command; the next next token is the start of the
		  // new stream or it can be NULL.
		  cur = next->m_next_token;
		  cur->m_prev_token = NULL;
		  add_token_stream = (token_stream_t) create_token_stream(next->m_next_token, NULL);
		  stream->m_next_token_stream = add_token_stream;
		  stream = add_token_stream;
		  
		  // Set the next's m_next_token to NULL signifying end of token stream.
		  next->m_next_token = NULL;

		  // Continue because current is now pointing to proper node two away, whether another token or NULL
		  continue;
		}
	    }
	}
      cur = cur->m_next_token;
    }
  
  return head;
}


void
free_token_stream(token_stream_t token_stream)
{
  token_stream_t temp_token_stream;
  token_t temp_token;
  enum token_type type;

  // Free first the inner token linked list (script and token itself) before
  // freeing the outer token stream.
  while (token_stream != NULL)
   {
     while (token_stream->m_head != NULL)
       {
	 temp_token = token_stream->m_head->m_next_token;
	 type = token_stream->m_head->m_token_type;

     if (type == WORD || type == IF || type == FI || type == DO ||
	 type == THEN || type == ELSE || type == DONE || type == WHILE ||
	 type == UNTIL)
       {
	      free(token_stream->m_head->m_script);
       }

     free(token_stream->m_head);
     token_stream->m_head = temp_token;
       }
     // Handle outer token stream.
     temp_token_stream = token_stream->m_next_token_stream;
     free(token_stream);
     token_stream = temp_token_stream;
   }
}

void
print_tokens(token_stream_t stream)
{
  token_stream_t cur_stream;
  token_t cur;
  
  cur_stream = stream;
  while (cur_stream != NULL)
    {
      cur = cur_stream->m_head;
      while (cur != NULL)
	{
	  printf("%c %d\n", *(cur->m_script), cur->m_token_type);
	  cur = cur->m_next_token;
	}
      cur_stream = cur_stream->m_next_token_stream;
      printf("x\n");
    }  
}

command_t
nullifyIO (command_t c)
{
	c->input = NULL;
	c->output = NULL;
	return c;
}

size_t
check_grammar (token_stream_t ts)
{
  if (ts == NULL || ts->m_head == NULL)
    {
      exit(-1);
    }
  
  token_t temp_tokenp = ts->m_head;
  
  // Checks if first token isn't WORD, OPEN_PAREN, IF, WHILE, or UNTIL 
  if (temp_tokenp->m_prev_token == NULL && temp_tokenp->m_token_type != WORD && temp_tokenp->m_token_type != OPEN_PAREN && temp_tokenp->m_token_type != IF && temp_tokenp->m_token_type != UNTIL && temp_tokenp->m_token_type != WHILE)
    {
      exit(-1);
    }

  if (temp_tokenp->m_prev_token == NULL && (temp_tokenp->m_token_type == DONE || temp_tokenp->m_token_type == FI))
    {
      exit (-1);
    }
  
  // 0 for when no ifs checked yet, 1 when if checked and passed tests
  size_t if_passed = 0;
  // same as above, but for parentheses
  size_t paren_passed = 0;
  // same as above, but for while and until
  size_t while_until_passed = 0;
  
  while(temp_tokenp != NULL)
    {
      switch (temp_tokenp->m_token_type)
	{
	case WORD:
	  {
	    if (temp_tokenp->m_prev_token != NULL)
	      {
		if (temp_tokenp->m_prev_token->m_token_type == DONE || temp_tokenp->m_prev_token->m_token_type == FI)
		  {
		    exit(-1);
		  }
	      }

	    break;
	  }
	case SEMICOLON:
	  {
	    if (temp_tokenp->m_next_token != NULL)
	      {
		if (temp_tokenp->m_next_token->m_token_type != WORD && temp_tokenp->m_next_token->m_token_type != OPEN_PAREN && temp_tokenp->m_next_token->m_token_type != ELSE &&
		    temp_tokenp->m_next_token->m_token_type != THEN && temp_tokenp->m_next_token->m_token_type != DO && temp_tokenp->m_next_token->m_token_type != DONE &&
		    temp_tokenp->m_next_token->m_token_type != FI && temp_tokenp->m_next_token->m_token_type != IF && temp_tokenp->m_next_token->m_token_type != WHILE &&
		    temp_tokenp->m_next_token->m_token_type != UNTIL)	
		  {
		    exit(-1);
		  }
	      }

	    /*
	    if (temp_tokenp->m_prev_token->m_token_type != WORD && (temp_tokenp->m_next_token->m_token_type != CLOSED_PAREN &&)
	      {
		exit(-1);
	      }
	    */
	    break;
	  }
	  
	case PIPE:
	  {
	    if (temp_tokenp->m_next_token != NULL)
	      {
		if (temp_tokenp->m_next_token->m_token_type != WORD && temp_tokenp->m_next_token->m_token_type != OPEN_PAREN)
		  {
		    exit(-1);
		  }
	      }
	    
	    if (temp_tokenp->m_prev_token != NULL && temp_tokenp->m_prev_token->m_token_type != WORD && temp_tokenp->m_next_token->m_token_type != CLOSED_PAREN)
	      {
		exit(-1);
	      }

	    break;
	  }
	  
	case RIGHT_REDIR:
	  {
	    if (temp_tokenp->m_next_token != NULL)
	      {
		if (temp_tokenp->m_next_token->m_token_type != WORD)
		  {
		    exit(-1);
		  }
	      }
	    else if (temp_tokenp->m_next_token == NULL)
	      {
		exit(-1);
	      }
	    
	    break;
	  }
	  
	case LEFT_REDIR:
	  {      
	    if (temp_tokenp->m_next_token == NULL)
	      {
		exit(-1);
	      }
	    else
	      {
		if (temp_tokenp->m_next_token->m_token_type != WORD)
		  {
		    exit(-1);
		  }
	      }
	    
	    break;
	  }
	  
	case OPEN_PAREN:
	  {
	    if (paren_passed == 0)
	      {
		if (temp_tokenp->m_next_token != NULL)
		  {
		    if (temp_tokenp->m_next_token->m_token_type == CLOSED_PAREN)
		      {
			exit(-1);
		      }
		    
		    token_t iterator = temp_tokenp->m_next_token;
		    
		    size_t pair_counter = 1;
		    while (iterator != NULL)
		      {
			if (iterator->m_token_type == OPEN_PAREN)
			  {
			    pair_counter++;
			  }
			else if (iterator->m_token_type == CLOSED_PAREN)
			  {
			    pair_counter--;
			  }
			iterator = iterator->m_next_token;
		      }
		    
		    if (pair_counter != 0)
		      {
			exit(-1);
		      }
		    
		    paren_passed = 1;
		    break;
		  }
		else if (temp_tokenp->m_next_token == NULL)
		  {
		    exit(-1);
		  }
	      }
	    
	    break;
	  }
	  
	case CLOSED_PAREN:
	  {
	    if (paren_passed == 0)
	      {
		exit(-1);
	      }
	    
	    break;
	  }
	  
	case IF:
	  {
	    if (if_passed == 0)
	      {
		if (temp_tokenp->m_next_token != NULL)
		  {
		    token_t iterator = temp_tokenp->m_next_token;
		    
		    size_t if_counter = 1;
		    size_t then_counter = 0;
		    size_t else_counter = 0;
		    size_t fi_counter = 0;
		    
		    while (iterator != NULL)
		      {
			if (iterator->m_token_type == IF)
			  {
			    if_counter++;
			  }
			else if (iterator->m_token_type == THEN)
			  {
			    then_counter++;
			    
			    if (then_counter > if_counter)
			      {
				exit(-1);
			      }
			  }
			else if (iterator->m_token_type == ELSE)
			  {
			    else_counter++;
			    
			    if (else_counter > then_counter || else_counter > if_counter)
			      {
				exit(-1);
			      }
			  }
			else if (iterator->m_token_type == FI)
			  {
			    fi_counter++;
			  }

			iterator = iterator->m_next_token;
		      }
		    
		    if (if_counter != fi_counter || if_counter != then_counter)
		      {
			exit(-1);
		      }
		    
		    if_passed = 1;
		    break;
		  }
		else if (temp_tokenp->m_next_token == NULL)
		  {
		    exit(-1);
		  }
	      }
	    
	    break;
	  }
	  
	case THEN:
	case ELSE:
	case FI:
	  {
	    if (if_passed == 0)
	      {
		exit(-1);
	      }

	    if (temp_tokenp->m_token_type == FI)
	      {
		if (temp_tokenp->m_prev_token != NULL && (temp_tokenp->m_prev_token->m_token_type == THEN || temp_tokenp->m_prev_token->m_token_type == ELSE))
		  {
		    exit(-1);
		  }
	      }
	    
	    break;
	  }
	  
	case WHILE:
	case UNTIL:
	  {
	    if (while_until_passed == 0)
	      {
		if (temp_tokenp->m_next_token != NULL)
		  {
		    token_t iterator = temp_tokenp->m_next_token;
		    
		    size_t while_counter = 0;
		    size_t until_counter = 0;
		    size_t do_counter = 0;
		    size_t done_counter = 0;
		    
		    if (temp_tokenp->m_token_type == WHILE)
		      {
			while_counter++;
		      }
		    else
		      {
			until_counter++;
		      }
		    
		    while (iterator != NULL)
		      {
			if (iterator->m_token_type == WHILE)
			  {
			    while_counter++;
			  }
			else if (iterator->m_token_type == UNTIL)
			  {
			    until_counter++;
			  }
			else if (iterator->m_token_type == DO)
			  {
			    do_counter++;
			    
			    if (do_counter > (while_counter + until_counter))
			      {
				exit(-1);
			      }
			  }
			else if (iterator->m_token_type == DONE)
			  {
			    done_counter++;
			    
			    if (done_counter > do_counter || done_counter > (while_counter + until_counter))
			      {
				exit(-1);
			      }
			  }

			iterator = iterator->m_next_token;
		      }
		    
		    if ((while_counter + until_counter) != done_counter || (while_counter + until_counter) != do_counter)
		      {
			exit(-1);
		      }
		    
		    while_until_passed = 1;
		    break;
		  }
		else if (temp_tokenp->m_next_token == NULL)
		  {
		    exit(-1);
		  }
	      }
	    
	    break;
	  }
	  
	case DO:
	case DONE:
	  {
	    if (while_until_passed == 0)
	      {
		exit(-1);
	      }
	    
	    break;
	  }
	}
      
      temp_tokenp = temp_tokenp->m_next_token;
    }
  
  // Breaking out of while loop means all grammar checks were passed
  return 1;
}

void adjust_tokens(token_stream_t ts)
{
  token_t cur = ts->m_head;
  while (cur != NULL)
    {
      if (cur->m_token_type == NEWLINE)
	{
	  if (cur->m_prev_token != NULL && (cur->m_prev_token->m_token_type == WORD || cur->m_prev_token->m_token_type == CLOSED_PAREN || cur->m_prev_token->m_token_type == DONE || cur->m_prev_token->m_token_type == FI || cur->m_prev_token->m_token_type == SEMICOLON) && cur->m_next_token != NULL && (cur->m_next_token->m_token_type == WORD || cur->m_next_token->m_token_type == OPEN_PAREN || cur->m_next_token->m_token_type == IF || cur->m_next_token->m_token_type == WHILE || cur->m_next_token->m_token_type == UNTIL || cur->m_next_token->m_token_type == SEMICOLON))
	    {
	      cur->m_token_type = SEMICOLON;
	    }
	}
      
      cur = cur->m_next_token;
    }
}
