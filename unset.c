/*
unset

works like this unset KEY
KEY is made of alphabets, numbers and _, number cannot be the first character
rms the KEY and its value from envp and export
if you send unset KEY= or unset KEY=VALUE, prnts ut error message and changes exit status accordingly

handle_unset(char **args, t_ms *ms)
gve args which are unset and all the KEYS needed to be removed.
for example args[0]="unset", args[1]="USER" args[2]="LOGNAME" args[3]=NULL
if one KEY s invalid like "USER=", it will cahnge exit status to 1 but still would remove the LOGNAME
and the t_ms *ms is the struct which holds the envp and exported
*/

#include "seela.h"

static void	rm_from_export(t_ms *ms, char *name, int len)
{
	int		i;
	int		x;
	char	**temp;

	i = 0;
	x = 0;
	while (ms->exported[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ms->exported[i])
    {
        if (ft_strncmp(name, ms->exported[i], len) == 0)
        {
            if (ms->exported[i][len] == '\0' || ms->exported[i][len] == '=')
				i++;
        }
		temp[x] = ft_strdup(ms->exported[i]);
        x++;
		i++;
    }
	temp[x] = NULL;
    ms->exported = copy_map(temp);
    free(temp);
}

static void	rm_from_env(t_ms *ms, char *name, int len)
{
	int		i;
	int		x;
	char	**temp;

	i = 0;
	x = 0;
	while (ms->envp[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (ms->envp[i])
    {
        if (ft_strncmp(name, ms->envp[i], len) == 0)
        {
            if (ms->envp[i] && ms->envp[i][len] == '=')
				i++;
        }
		temp[x] = ft_strdup(ms->envp[i]);
        x++;
		i++;
    }
	temp[x] = NULL;
    ms->envp = copy_map(temp);
    free(temp);
}

static void	print_unset_error(char **args, int i, t_ms *ms)
{
	char	*err_out;
	char	*err_out2;

	err_out = ft_strjoin("bash: unset: '", args[i]);
	err_out2 = ft_strjoin(err_out, "': not a valid indentifier\n");
	ft_putstr_fd(err_out2, 2);
	ms->exit_status = 1;
	free(err_out2);
	free(err_out);
}

static int		check_if_valid_key(char *name, char **args, int i, t_ms *ms)
{
	int		x;

	x = 0;
	if (name[0] >= '0' && name[0] <= '9')
	{
		free(name);
		print_unset_error(args, i, ms);
		return (1);
	}
	while (name[x])
	{
		if (!ft_isalnum(name[x]) && name[x] != '_')
		{
			free(name);
			print_unset_error(args, i, ms);
			return (1);
		}
		x++;
	}
	return (0);
}

void	handle_unset(char **args, t_ms *ms)
{
	int		len;
	char	*name;
	int		i;

	len = 0;
	i = 1;
	ms->exit_status = 0;
	while (args[i])
	{
		while (args[i][len] && args[i][len] != '=')
			len++;
		if (len == 0)
			return;
		if (ft_strchr(args[i], '=') != 0)
			print_unset_error(args, i, ms);
		else
		{
			name = malloc(sizeof(char) * (len + 1));
			name = ft_strncpy(name, args[i], len);
			if (check_if_valid_key(name, args, i, ms) == 0)
			{
				rm_from_export(ms, name, len);
				rm_from_env(ms, name, len);
				free(name);
			}
		}
		i++;
		len = 0;
	}
}
