/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalorin <ssalorin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 15:37:31 by ssalorin          #+#    #+#             */
/*   Updated: 2025/01/15 15:39:39 by ssalorin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "seela.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_print_err(char *cmd, int c)
{
	char	*err_msg;
	char	*err_out;
	char	*temp;

	err_msg = "./pipex: ";
	err_out = ft_strjoin(err_msg, cmd);
	if (cmd[0] == '/' || c == 2)
		temp = ft_strjoin(err_out, ": No such file or directory\n");
	else if (cmd[0] == '.')
		temp = ft_strjoin(err_out, ": Permission denied\n");
	else
		temp = ft_strjoin(err_out, ": command not found\n");
	free(err_out);
	err_out = temp;
	if (err_out)
	{
		ft_putstr_fd(err_out, STDERR_FILENO);
		free(err_out);
	}
}
