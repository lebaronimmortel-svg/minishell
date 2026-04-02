#include "../../header/header.h"

void	unset(char **split, char **envp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (split[i])
	{
		str = getenv(split[i]);
		if (str)
		{
			j = 0;
			while (ft_strncmp(split[i], envp[j], ft_strlen(split[i])))
				j++;
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = envp[j + 1];
		}
		i++;
	}
}

void	pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");
}

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}
