/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoulios <ngoulios@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:33:17 by ngoulios          #+#    #+#             */
/*   Updated: 2025/01/24 19:24:56 by ngoulios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lib/RevisedLibft/libft.h"
# include <stdio.h>
# include <stdlib.h>

/*Provides functions for reading and editing user input from the command line,
with features like line editing, auto-completion, and custom keybindings.
The readline function allows input with a customizable prompt.
*/
# include <readline/readline.h>

/*Manages command history by enabling adding, retrieving, saving, and loading
user inputs from a history list. It supports navigating through input
history and persisting it across sessions*/
# include <readline/history.h>


typedef enum token_type
{
	NONE = 0,
	CMD = 1,
	PIPE = 2,
	OR = 3,
	AND = 4,
	BR_OPEN = 5,
	BR_CLOSE = 6,
}	t_token_type;

typedef enum redirect_type
{
	RD_IN = 0,
	RD_OUT = 1,
	RD_HEREDOC = 2,
	RD_APPEND = 3,
}	t_redirect_type;

typedef enum e_error
{
	ERR_NONE = 0,
	ERR_SYNTAX = 1,
	ERR_MALLOC = 2,
	ERR_FORK = 3,
	ERR_PIPE = 4
}	t_error;

typedef enum e_syntax
{
	SYN_NONE = 0,
	SYN_QUOTE = 1,
	SYN_RD = 2,
	SYN_LOGIC = 3,
	SYN_BR = 4,
	SYN_NORMAL = 5
}	t_syntax;

//----------------------------------------------------
// TOKEN 
//-----------------------------------------------------

typedef struct s_redir
{
	int					fd; // File Descriptor for redirection
	int					no_exp; // Flag indicating expansion is off (heredocs)
	t_redirect_type		type; // Type of redirection
	char				*orig_path; // Original path in the command
	char				*path; // Processed or resolved file path for the redirection
	struct s_redir		*next; // Pointer to the next redirection in a linked list
}	t_redir;

typedef struct s_token
{
	t_token_type		type; // Type of token
	char				*cmd; // The actual command or token string
	char				**args; // Arguments for the command
	t_redir				*redir; // Pointer to the list of redirections 
}	t_token;

typedef struct s_token_list
{
	t_token				*array; // Array of tokens
	size_t				size; // Total size of the token array
	size_t				cur_pos; // Current position
	size_t				to_add; // Number of tokens to be added
	int					br_open; // Count of currently open brackets
	int					has_heredoc; // Flag indicating if the command contains a heredoc
	int					has_pipe; // Flag indicating if the command contains a pipe
	char				*last_cmd; // Stores the result of the last executed command
	t_syntax			syntax_err; // Stores syntax error
}	t_token_list;

#endif
