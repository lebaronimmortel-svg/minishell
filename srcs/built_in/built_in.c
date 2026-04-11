#include "../../header/header.h"

int	is_built_in(char *input)
{
	if (!input)
		return (0);
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		return (1);
	if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		return (1);
	if (!ft_strncmp(input, "unset ", 6))
		return (1);
	if (!ft_strncmp(input, "echo ", 5))
		return (1);
	if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
		return (1);
	if (!ft_strncmp(input, "exit ", 5))
		return (1);
	if (!ft_strncmp(input, "cd ", 3))
		return (1);
	if (!ft_strncmp(input, "cd", 2) && ft_strlen(input) == 2)
		return (1);
	if (!ft_strncmp(input, "export", 6) && ft_strlen(input) == 6)
		return (1);
	if (!ft_strncmp(input, "export ", 7))
		return (1);
	return (0);
}

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
			//free(envp[j]);
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
