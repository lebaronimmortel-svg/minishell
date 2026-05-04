#include "../../header/header.h"

long long	calculation_atoll(const char *str, int i, int signe, long long *result)
{
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			*result = *result * 10 + str[i] - '0';
		else
			return (*result * signe);
		i++;
	}
	return (*result * signe);
}

long long	ft_atoll(const char *nptr, long long *result)
{
	int	i;
	int	signe;

	i = 0;
	signe = 1;
	while (check_space(nptr, i))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	if (!calculation_atoll(nptr, i, signe, result))
		return (0);
	*result = *result * signe;
	return (1);
}

char	*get_user(t_data *data)
{
	int		i;
	char	*result;
	char	**split;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "USER=", 5))
		{
			split = ft_split(data->env[i], '=');
			if (!split)
				return (NULL);
			result = ft_strdup(split[1]);
			if (!result)
				return (NULL);
			free_split(split, 0);
			return (result);
		}
		i++;
	}
	return (NULL);
}

int	get_home_path(char *path, t_data *data)
{
	char	*user;

	user = get_user(data);
	if (!user)
		return (1);
	path = ft_strjoin("cd /home/", user);
	if (!path)
		return (1);
	free(user);
	cd(path, data);
	free(path);
	return (0);
}

int	display_cd_error_msg(int flag)
{
	if (flag == 1)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (flag == 2)
		ft_putstr_fd("cd: no such file or directory\n", 2);
	else if (flag == 3)
		ft_putstr_fd("cd: permission denied\n", 2);
	else if (flag == 4)
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
	return (1);
}

int	cd(char *input, t_data *data)
{
	char		*path;
	char		buffer[1024];
	struct stat	info;

	path = &input[3];
	unmask_spaces(path);
	if (ft_strchr(path, ' '))
		return (display_cd_error_msg(1));
	if (!(*path) || (ft_strlen(path) == 1 && path[0] == '~'))
		return (get_home_path(path, data));
	if (stat(path, &info) != 0)
		return (display_cd_error_msg(2));
	if (access(path, X_OK) != 0)
		return (display_cd_error_msg(3));
	if (!getcwd(buffer, sizeof(buffer)))
		buffer[0] = '\0';
	change_path(0, buffer, data);
	if (chdir(path))
		return (1);
	if (!getcwd(buffer, sizeof(buffer)))
		return (display_cd_error_msg(4));
	change_path(1, buffer, data);
	return (0);
}
