/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoulios <ngoulios@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:32:18 by ngoulios          #+#    #+#             */
/*   Updated: 2025/01/15 20:13:47 by ngoulios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

s_token *createToken(TokenType type, const char *value);
s_token *tokenizeCommand(const char *command);
TokenType classifyToken(const char *word);


int main(int argc, char **argv, char **env)
{
	// I dont know what i am doing , send help WHAT THE FUCK WHAT THE FUCCCK
	(void)argc;
	(void)argv;
	(void)env;
	
	while(1)
	{
		char *promt = readline("minishell> ");
		if (!promt)
		{
			printf("EXITING...\n");
			break;
		}
		if (*promt == '\0')
		{
			free(promt);
			continue;
		}
		add_history(promt);
		s_token *tokens = tokenizeCommand(promt);
		printf("Parsed Tokens: \n");
		s_token *current = tokens;
		while (current)
		{
			printf("Type: %d, Value: %s\n", current->type, current->value);
			current = current->next;
		}
		current = tokens;
		while (current)
		{
			s_token *next = current->next;
			free(current->value);
			free(current);
			current = next;
		}
		free(promt);
		//promt = NULL;
	}
	return 0;
}


s_token *createToken(TokenType type, const char *value)
{
    s_token *token = malloc(sizeof(s_token));
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

s_token *tokenizeCommand(const char *command)
{
    s_token *head = NULL, *current = NULL;
    char *copy = strdup(command);
    char *word = strtok(copy, " ");

    while (word != NULL) 
	{
        s_token *newToken = createToken(classifyToken(word), word);

        if (!head) 
            head = newToken;
		else 
            current->next = newToken;
        current = newToken;
        word = strtok(NULL, " ");
    }

    free(copy);
    return head;
}

TokenType classifyToken(const char *word)
{
	if (word[0] == '-')
		return TOKEN_ARGUMENT;
	return TOKEN_COMMAND;
}
