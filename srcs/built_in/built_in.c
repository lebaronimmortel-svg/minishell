/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfuen <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:51:24 by alexfuen          #+#    #+#             */
/*   Updated: 2026/04/09 02:51:26 by alexfuen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static void	pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		printf("%s\n", buffer);
	else
		perror("getcwd");
}

static void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
}

static int	status_code(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != ' ')
		i++;
	if (!input[i])
		return (data->error_code);
	return (ft_atoi(&input[i]));
}

void	exec_built_in(char *input, t_data *data)
{
	if (!ft_strncmp(input, "pwd", 3) && ft_strlen(input) == 3)
		pwd();
	else if (!ft_strncmp(input, "unset ", 6))
		unset(&ft_split(input, ' ')[1], data);
	else if (!ft_strncmp(input, "env", 3) && ft_strlen(input) == 3)
		env(data->env);
	else if ((!ft_strncmp(input, "exit", 4)
			&& ft_strlen(input) == 4)
		|| (!ft_strncmp(input, "exit ", 5)))
		exit(status_code(input, data));
	else if ((!ft_strncmp(input, "echo ", 5)))
		echo(input);
	else if ((!ft_strncmp(input, "export", 6)) && ft_strlen(input) == 6)
		export_single(data);
	else if ((!ft_strncmp(input, "export ", 7)))
		ft_export(input, data);
}
