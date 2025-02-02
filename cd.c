/*
	Handles cd
	cd = goes to home
	cd .. = goes to one directory up
	cd - = goes to the oldpwd directory so the one where we were before
	cd dir = goes to dir if it exists

	handle_cd(t_ms *ms, char **args)
	takes the struct as argument and
	args that are for example
	args[0]="cd", args[1]="-", args[2]=NULL
*/

#include "seela.h"

static void	update_env_var(t_ms *ms, char *key, char *new_value)
{
	int		i;
	int		len;
	char	*new_env_entry;

	i = 0;
	len = ft_strlen(key);
	new_env_entry = malloc(len + ft_strlen(new_value) + 1);
	if (!new_env_entry)
		return;
	ft_strcpy(new_env_entry, key);
	ft_strcat(new_env_entry, new_value);
	while (ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], key, len) == 0)
		{
			free(ms->envp[i]);
			ms->envp[i] = new_env_entry;
			return;
		}
		i++;
	}
	ms->envp[i] = new_env_entry;
	ms->envp[i + 1] = NULL;
}

static char	*get_cd_target(t_ms *ms, char **args)
{
	char	*target;

	if (!args[1])
	{
		target = get_env_value("HOME", ms->envp);
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			ms->exit_status = 1;
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value("OLDPWD", ms->envp);
		if (!target)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			ms->exit_status = 1;
		}
		else
			printf("%s\n", target);
	}
	else
		target = args[1];
	return (target);
}

static void	update_cd_env(t_ms *ms, char *old_pwd)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("cd: getcwd failed");
		ms->exit_status = 1;
		return;
	}
	update_env_var(ms, "PWD=", cwd);
	update_env_var(ms, "OLDPWD=", old_pwd);
	ms->exit_status = 0;
}

void	handle_cd(t_ms *ms, char **args)
{
	char	old_pwd[1024];
	char	*target_dir;

	if (ft_strcmp(args[0], "cd") != 0)
		return;
	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("cd: getcwd failed");
		ms->exit_status = 1;
		return;
	}
	target_dir = get_cd_target(ms, args);
	if (!target_dir || ms->exit_status == 1)
		return;
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(target_dir, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
		ms->exit_status = 1;
		return;
	}
	update_cd_env(ms, old_pwd);
}
