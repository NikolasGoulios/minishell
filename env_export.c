/*
HANDLES THESE CASES:
env                 = prints out envp stored in ms->envp
export              = prints out exported variables stored in ms->exported
export KEY          = adds KEY to exported without value, if it already exists with or without VALUE, do nothing
export KEY=         = changes KEY's value to empty in exported and envp, creates it with this empty value if it don't already exist
export KEY=VALUE    = changes KEY's value to VALUE in exported and envp, creates it with this value if it don't already exist

and export always prints in alphabetical order, with declare -x before KEY and VALUE is in double quotes ""

KEY contains only alphabets or numbers or _ and the first character cant be a number
*/
/*
in env handlind, call handle_envp(t_ms *ms) function with the ms struct
in export handling, call handle_exported(char **args, t_ms *ms) function
with args and the ms struct
args are for example args[0]="export" args[1]="HEY=hi" args[2]=NULL
*/
#include "seela.h"

void    update_exported(char *arg, t_ms *ms)
{
    char    **temp;
    int     i;
    int     len;
    int     check;

    temp = NULL;
    i = 0;
    check = 0;
	if (arg[0] >= '0' && arg[0] <= '9')
		return (print_error3(ms, arg));
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (print_error3(ms, arg));
		i++;
	}
	i = 0;
    len = (int)ft_strlen(arg);
    while (ms->exported[i])
        i++;
    temp = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (ms->exported[i])
    {
        if (ft_strncmp(arg, ms->exported[i], len) == 0)
        {
            if (ms->exported[i][len] == '\0' || ms->exported[i][len] == '=')
                check = 1;
        }
        temp[i] = ft_strdup(ms->exported[i]);
        i++;
    }
    if (check == 0)
    {
        temp[i] = ft_strdup(arg);
        i++;
    }
    temp[i] = NULL;
    ms->exported = copy_map(temp);
    free(temp);
}

void    add_to_exported(char *arg, t_ms *ms, char *name, int len)
{
    int     i;
    char    **temp;
    int     check;

    i = 0;
    check = 0;
    while (ms->exported[i])
        i++;
    temp = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (ms->exported[i])
    {
        if (ft_strncmp(ms->exported[i], name, len) == 0)
        {
            if (ms->envp[i][len] && ms->envp[i][len] == '=')
            {
                temp[i] = ft_strdup(arg);
                check = 1;
            }
            else
                temp[i] = ft_strdup(ms->exported[i]);
        }
        else
            temp[i] = ft_strdup(ms->exported[i]);
        i++;
    }
    if (check == 0)
    {
        temp[i] = ft_strdup(arg);
        i++;
    }
    temp[i] = NULL;
    ms->exported = copy_map(temp);
    free(temp);
}

void    add_to_env(char *arg, t_ms *ms, char *name, int len)
{
    int     i;
    int     check;
    char    **temp;

    i = 0;
    check = 0;
    while (ms->envp[i])
        i++;
    temp = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (ms->envp[i])
    {
        if (ft_strncmp(ms->envp[i], name, len) == 0)
        {
            if (ms->envp[i][len] && ms->envp[i][len] == '=')
            {
                temp[i] = ft_strdup(arg);
                check = 1;
            }
            else
                temp[i] = ft_strdup(ms->envp[i]);
        }
        else
            temp[i] = ft_strdup(ms->envp[i]);
        i++;
    }
    if (check == 0)
    {
        temp[i] = ft_strdup(arg);
        i++;
    }
    temp[i] = NULL;
    ms->envp = copy_map(temp);
    free(temp);
}

void    add_to_exported_env(char *arg, t_ms *ms)
{
    int     len;
	int		i;
    char    *name;

    len = 0;
	i = 0;
    while (arg[len] && arg[len] != '=')
        len++;
	if (len == 0)
		return;
	name = malloc(sizeof(char) * (len + 1));
	name = ft_strncpy(name, arg, len);
	if (name[0] >= '0' && name[0] <= '9')
	{
		free(name);
		return (print_error3(ms, arg));
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			free(name);
			return (print_error3(ms, arg));
		}
		i++;
	}
    add_to_exported(arg, ms, name, len);
    add_to_env(arg, ms, name, len);
	free(name);
}

void    handle_export(char **args, t_ms *ms) /// args are for exapmle args[0]="export" args[1]="HEY=hi" args[2]=NULL
{
    int     arg_count;

    ms->exit_status = 0;
    arg_count = 0;
    if (!args)
        return;
    while (args[arg_count])
        arg_count++;
    if (arg_count == 1)
    {
        sort_exported_alphaorder(ms);
        print_exported(ms);
    }
    else
    {
        if (ft_strchr(args[1], '=') == 0) // if there is no =, then we just add value to export if dont exist already
        {
            update_exported(args[1], ms);
            sort_exported_alphaorder(ms);
        }
        else //add value to envp and exported
        {
            add_to_exported_env(args[1], ms);
            sort_exported_alphaorder(ms);
        }
    }
}
