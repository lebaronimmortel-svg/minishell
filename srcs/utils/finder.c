#include "../header/header.h"

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

int	exists(char *str, char **envp)
{
	int i;
	int ind;
	char **path;
	char	buf[4096];

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	ft_memmove(str, &str[i], i);
	
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
			break;
		}
		i++;
	}
	if (!ind)
		return(0);
	free_path(path);
	return (1);
}
