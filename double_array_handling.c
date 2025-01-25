#include "seela.h"

void    print_array(char **m)
{
    int     i;

    i = 0;
    while (m[i])
    {
        printf("%s\n", m[i]);
        i++;
    }
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

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
