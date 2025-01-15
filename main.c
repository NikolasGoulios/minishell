/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoulios <ngoulios@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:32:18 by ngoulios          #+#    #+#             */
/*   Updated: 2025/01/15 11:48:19 by ngoulios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	
	while(1)
	{
		char *promt = readline("Enter Command: ");
		printf("Fuck your,%s!\n", promt);
		free(promt);
		promt = NULL;
	}
}