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
	ft_putstr_fd("zsh: ", 2);
	if (cmd[0] == '/' || c == 2)
		ft_putstr_fd("No such file or directory: ", 2);
	else if (cmd[0] == '.')
		ft_putstr_fd("Permission denied: ", 2);
	else
		ft_putstr_fd("command not found: ", 2);
    if (!err_out)
        exit(1);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}
