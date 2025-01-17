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

	err_msg = "zsh: ";
    err_out = NULL;
	if (cmd[0] == '/' || c == 2)
		err_out = ft_strjoin(err_msg, "No such file or directory: ");
	else if (cmd[0] == '.')
		err_out = ft_strjoin(err_msg, "Permission denied: ");
	else
		err_out = ft_strjoin(err_msg, "command not found: ");
    if (!err_out)
        exit(1);
	temp = ft_strjoin(err_out, cmd);
    free(err_out);
    if (!temp)
        exit(1);
    err_out = ft_strjoin(temp, "\n");
	free(temp);
    if (err_out)
	{
		ft_putstr_fd(err_out, STDERR_FILENO);
		free(err_out);
	}
}
