#include "seela.h"

char	**copy_map(char **original_map)
{
	char	**new_map;
    int     i;

    i = 0;
    while (original_map[i])
        i++;
	new_map = malloc(sizeof(char *) * (i + 1));
	if (!new_map)
		return (NULL);
    i = 0;
	while (original_map[i])
	{
		new_map[i] = ft_strdup(original_map[i]);
		if (!new_map[i])
		{
			ft_free_map(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

void    initialize_struct(char **envp)
{
    t_ms ms;

    ms.exit_status = 0;
    ms.envp = copy_map(envp);
    ms.exported = copy_map(envp);
}   
