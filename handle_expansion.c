/*
handles $USER, so enviroment variable expansion
args has all the arrays need to bee expanded
for example args[0] = "My home directory is $HOME", args[1]="$USER$LOGNAME" args[2]=NULL
if the KEY dont exists replace the $HOME with "", else replace $HOME with the VALUE

KEY only contains numbers, alphabets or _ and the first character cant be a number
*/

#include "seela.h"


char	*expand_key(char **envp, char *key, int len)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0)
		{
			if (envp[i][len] == '=')
				return (ft_strdup(envp[i] + len + 1));
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*handle_expansion(char *args, t_ms *ms)
{
	int		i;
	int		x;
	char	*key = NULL;
	char	*s;
	char	*temp;
	char	*string;

	string = ft_strdup("");;
	i = 0;
	x = 0;
	while (args[i])
	{
		if (args[i] == '$' && args[i + 1])
		{
			i++;
			x = 0;
			while (args[i + x] && (ft_isalnum(args[i + x]) || args[i + x] == '_'))
				x++;
			key = ft_substr(args, i, x);
			s = expand_key(ms->envp, key, x);
			temp = ft_strjoin(string, s);
			free(string);
			string = temp;
			free(s);
			free(key);
			i = i + x;
		}
		else
		{
			temp = ft_strjoin(string, ft_substr(args, i, 1));
			free(string);
			string = temp;
			i++;
		}
	}
	return (string);
}
