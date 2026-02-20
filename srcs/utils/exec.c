#include "../header/header.h"

void	do_thing(char *path)
{
	////
	(void) path;
	write(1, "Commande trouvee !\n", 19);
	////
	
	/*
	
	insert code here 
	
	*/
	
	return ;
}

void free_path(char **path)
{
	int i;
	
	if (!path)
		return;
	if (!(*path))
	{
		free(path);
		return;
	}
	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
#include <string.h>
void	exec(char *str, char **envp)
{
	int i;
	int ind;
	char **path;
	char	buf[4096];

	//enlever les whitespace du debut
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	ft_memmove(str, &str[i], i);
	//
	
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			break;
		i++;
	}
	path = ft_split(&envp[i][5], ':');
	i = 0;
	ind = 0;
	while (path[i])
	{
		ft_bzero(buf, sizeof(buf));
		strcat(buf, path[i]);
		strcat(buf, "/");
		strcat(buf, str);
		if (access(buf, X_OK) == 0)
		{
			ind = 1;
			do_thing(path[i]);
			break;
		}
		i++;
	}
	if (!ind)
		write(1, "Unknown command\n", 16);
	free_path(path);
}
