/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 06:44:34 by lukrodri          #+#    #+#             */
/*   Updated: 2026/02/17 06:44:36 by lukrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/header.h"

static void	handler0(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	inject_missing_vars(t_data *data, int i, int has_path, int has_pwd)
{
	char	buf[1024];
	char	*pwd_entry;

	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
			has_path = 1;
		if (!ft_strncmp(data->env[i], "PWD=", 4))
			has_pwd = 1;
		i++;
	}
	if (!has_path)
		add_var("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin",
			data);
	if (!has_pwd)
	{
		if (!getcwd(buf, sizeof(buf)))
			return (0);
		pwd_entry = ft_strjoin("PWD=", buf);
		if (!pwd_entry)
			return (0);
		add_var(pwd_entry, data);
		free(pwd_entry);
	}
	return (1);
}

static int	init(t_data *data, char **envp)
{
	data->error_code = 0;
	data->env = split_dup(envp);
	if (!data->env)
	{
		data->env = ft_calloc(1, sizeof(char *));
		if (!data->env)
			return (0);
	}
	data->env_bis = split_dup(data->env);
	if (!data->env_bis)
	{
		data->env_bis = ft_calloc(1, sizeof(char *));
		if (!data->env_bis)
		{
			free_split(data->env, 0);
			return (0);
		}
	}
	if (!inject_missing_vars(data, 0, 0, 0))
	{
		free_split(data->env, 0);
		free_split(data->env_bis, 0);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*lex;
	char	**split;
	t_data	*data;

	signal(SIGINT, handler0);
	signal(SIGQUIT, SIG_IGN);
	(void) argv;
	if (argc != 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (139);
	if (!init(data, envp))
		return (139);
	lex = NULL;
	split = NULL;
	main_loop(split, lex, data);
	return (0);
}
