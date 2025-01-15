/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoulios <ngoulios@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:33:17 by ngoulios          #+#    #+#             */
/*   Updated: 2025/01/15 20:17:59 by ngoulios         ###   ########.fr       */
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

/**
 * @enum TokenType
 * @brief Represents the different types of tokens in a lexical analyzer.
 *
 * This enumeration defines all possible categories a token can fall into
 * during lexical analysis. It is used to identify and classify pieces of
 * input text, improving readability and facilitating further parsing or
 * processing.
 *
 * @var TOKEN_KEYWORD
 *      A reserved word in the language (e.g., "int", "return").
 *
 * @var TOKEN_IDENTIFIER
 *      A name defined by the user (e.g., variable or function names).
 *
 * @var TOKEN_NUMBER
 *      A numeric literal (e.g., "10", "3.14").
 *
 * @var TOKEN_OPERATOR
 *      An operator used in expressions (e.g., "+", "-", "=").
 *
 * @var TOKEN_SEPARATOR
 *      A symbol that separates statements or elements (e.g., ";", ",").
 */
typedef enum
{
	TOKEN_WORD, // 0
    TOKEN_PIPE, // 1
    TOKEN_REDIRECT_IN, //2
    TOKEN_REDIRECT_OUT, //3
    TOKEN_APPEND, //4
    TOKEN_HEREDOC,// 5
    TOKEN_SEPARATOR, //6 
	TOKEN_COMMAND, // 7 The command (e.g., "ls")
	TOKEN_ARGUMENT, // 8 Arguments (e.g., "-la")
    TOKEN_UNRECOGNIZED // 9 For anything unexpected
}					TokenType;

typedef struct	t_token
{
	TokenType		type;
	char			*value;
	struct t_token	*prev;
	struct t_token	*next;
}					s_token;

#endif
