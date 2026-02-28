#include "../header/header.h"

static void token_convert(char *raw, char **token)
{
	if (!(*raw))
		return ;
	if (!ft_strncmp(raw, "Unknown : ", 10))
	{
		*token = malloc(66);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : IGN CMD\n█		Unknown command\n█		(to be ignored)\n█", 66);
	}
	else if (!ft_strncmp(raw, "||", 2) || !ft_strncmp(raw, "&&", 2))
	{
		*token = malloc(50);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : IGN OPERATOR\n█		(to be ignored)\n█", 50);
	}
	else if (raw[0] == '|' && !raw[1])
	{
		*token = malloc(67);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : OPERATOR\n█		Redirection of the\n█		output stream\n█", 68);
	}
	else if (raw[0] == '>' && !raw[1])
	{
		*token = malloc(61);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : OPERATOR\n█		Redirection of the\n█		output\n█", 61);
	}
	else if (raw[0] == '<' && !raw[1])
	{
		*token = malloc(60);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : OPERATOR\n█		Redirection of the\n█		input\n█", 60);
	}
	else if (raw[0] == '>' && raw[1] == '>' && !raw[2])
	{
		*token = malloc(82);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : OPERATOR\n█		Redirection of \n█		the output\n█		in append mode\n█", 82);
	}
	else if (raw[0] == '<' && raw[1] == '<' && !raw[2])
	{
		*token = malloc(38);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : OPERATOR\n█		Heredoc\n█", 38);
	}
	else if (raw[0] == 'F' && raw[1] && raw[1] == 'L')
	{
		*token = malloc(67);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : FLAG\n█		Execute previous cmd\n█		with this flag\n█", 67);
	}
	else
	{
		*token = malloc(30) + ft_strlen(raw);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "█		TYPE : CMD\n█		Execute ", 30);
		*token = ft_strjoin(*token, raw);
		*token = ft_strjoin(*token, "\n█");
	}
}

static void	lex_token(char ***lexer)
{
	char **split;
	char **token;
	int i;

	split = lexer[0];
	token = lexer[1];
	i = 0;
	while (split[i])
	{
		token_convert(split[i], &token[i]);
		i++;
	}
	return ;
}

int ft_memlen(char **split)
{
	int i;
	
	i = 0;
	if (!split || !(*split))
		return (0);
	while (split[i])
		i++;
	return (i);
}

static int	is_alpha(char *str)
{
	int i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < 'a' || str[i] > 'z')
		{
			if (str[i] < 'A' || str[i] > 'Z')
				return (0);
		}
		i++;
	}
	return (1);
}

static void	lex_convert(char **split, char **envp)
{
	int i;
	int flag;
	char *tmp;

	i = 0;
	flag = 0;
	while (split[i])
	{
		if (split[i][0] == '|' && !split[i][1])
			flag = 1;
		else if (split[i][0] == '&' && split[i][1] == '&' && !split[i][2])
			flag = 1;
		else if (split[i][0] == '>' && split[i][1] == '>' && !split[i][2])
			flag = 1;
		else if (split[i][0] == '<' && split[i][1] == '<' && !split[i][2])
			flag = 1;
		else if (split[i][0] == '>' && !split[i][1])
			flag = 1;
		else if (split[i][0] == '<' && !split[i][1])
			flag = 1;
		else if (split[i][0] == '|' && split[i][1] == '|' && !split[i][2])
			flag = 1;
		else if (split[i][0] == '-' && is_alpha(&split[i][1]))
		{
			tmp = split[i];
			split[i] = ft_strjoin("FL", split[i]);
			free(tmp);
		}
		else if (!exists(split[i], envp))
		{
			tmp = split[i];
			split[i] = ft_strdup("Unknown : ");
			split[i] = ft_strjoin(split[i], tmp);
			free(tmp);
		}
		i++;
	}
}

char ***lexer(char *str, char **envp)
{
	char **split;
	char **token;
	char ***tuple;

	tuple = malloc(2 * sizeof(char **));
	if (!tuple)
		return (NULL);
	split = ft_split(str, ' ');
	token = malloc(ft_memlen(split) * sizeof(char *));
	if (!token)
	{
		free(tuple);
		return (NULL);
	}
	tuple[0] = split;
	tuple[1] = token;
	lex_convert(split, envp);
	lex_token(tuple);
	return (tuple);
}
