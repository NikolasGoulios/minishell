/*
 can change later but now just takes an array like array0] = "exit", array[1] = 1, array[2] = NULL

Handles the exit command, including support for:
No argument (defaults to exit 127). (exit)
Valid numeric argument (exits with that code). (exit 1)
if exit is bigger than 255, exits with %module 256
for example exit 300 would exit with 44

Too many arguments (prints an error). (exit 1 1)
Non-numeric argument (prints an error). (exit 1x)
*/

/*
 SHOULD ADD THIS ,SYNTAX ERROR THINGS
 if
 exit (1)
 The error bash: syntax error near unexpected token '1' happens because of the wrong syntax.
 */

#include "seela.h"

void	exit_shell(char *array)
{
	int	exit_nbr;
	
	exit_nbr = (ft_atoi(array));
	if (exit_nbr > 255)
		exit(exit_nbr % 256);
	exit(exit_nbr);
}

void	check_exit(char	**array)
{
	int		i;

	i = 0;
	if (!array || !*array)
		return;
	if (ft_strcmp(array[0], "exit") != 0)
		return;
	if (array[1])
	{
		if (array[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			return;
		}
		while (array[1][i])
		{
			if (ft_isdigit(array[1][i]) != 1)
			{
				ft_putstr_fd("bash: exit: numeric argument required\n", 2);
				return;
			}
			i++;
		}
		exit_shell(array[1]);
	}
	exit(127);
}
