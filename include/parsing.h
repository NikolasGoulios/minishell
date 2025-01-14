/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoulios <ngoulios@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:33:17 by ngoulios          #+#    #+#             */
/*   Updated: 2025/01/14 21:47:02 by ngoulios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>

/*Provides functions for reading and editing user input from the command line, 
with features like line editing, auto-completion, and custom keybindings. 
The readline function allows input with a customizable prompt.
*/
#include <readline/readline.h>

/*Manages command history by enabling adding, retrieving, saving, and loading 
user inputs from a history list. It supports navigating through input 
history and persisting it across sessions*/
#include <readline/history.h>

// There will be 2 steps
// Lexical analysis / tokenization
// 		In Lexical analysis the user input will be splited into tokens
// Syntax analysis / Parsing
//		In syntax analysis scanning the stream of tokens according to a specific 
//		grammar and then deciding what to do with them (e.g. generating an AST — Abstract Syntax Tree).


#endif


