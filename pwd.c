/*
 prints out pwd path stored in ms->envp
prnts it out even if pwd 1 etc. many args, bs des this in bash 
*/


#include "seela.h"

char *get_env_value(char *key, char **envp)
{
    int		i;
    size_t	len;

	i = 0;
	len = ft_strlen(key);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1); // Return value after "KEY="
        i++;
    }
    return (NULL); // Key not found
}

void	check_pwd(t_ms *ms, char **array)
{
	char	*pwd;

	if (!array || !*array)
		return;
	if (ft_strcmp(array[0], "pwd") != 0)
		return;
	pwd = get_env_value("PWD", ms->envp);
	if (pwd)
		printf("%s\n", pwd);
	else
		perror("pwd"); // Fallback if PWD isn't set
}

