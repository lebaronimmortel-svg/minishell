#include "../../header/header.h"

static char **my_realloc(char **split, int old_size, int new_size)
{
	char **new_split;
	int i;
	
	if (!split)
		return (NULL);
	new_split = malloc(new_size * sizeof(char *) + 1);	
	if (!new_split)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_split[i] = ft_strdup(split[i]);
		free(split[i]);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}

void	export(char **split, t_data *data)
{
	//to be completed
	return ;
}
