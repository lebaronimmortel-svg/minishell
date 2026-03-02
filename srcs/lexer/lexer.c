#include "../header/header.h"

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

static void token_convert(char *raw, char **token)
{

	if (!(*raw))
		return ;
	if (!ft_strncmp(raw, "Unknown : ", 10))
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "UNK", 4);
	}
	else if (!ft_strncmp(raw, "||", 2) || !ft_strncmp(raw, "&&", 2))
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "UNK", 4);
	}
	else if (raw[0] == '|' && !raw[1])
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "PIP", 4);
	}
	else if (raw[0] == '>' && !raw[1])
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "RDR", 4);
	}
	else if (raw[0] == '<' && !raw[1])
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "RDR", 4);
	}
	else if (raw[0] == '>' && raw[1] == '>' && !raw[2])
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "RDR", 4);
	}
	else if (raw[0] == '<' && raw[1] == '<' && !raw[2])
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "RDR", 4);
	}
	else if (raw[0] == '-' && is_alpha(&raw[1]))
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "FLG", 4);
	}
	else if (raw[0] == '-' && raw[1] == '-' && is_alpha(&raw[2]))
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "FLG", 4);
	}
	else if (raw[0] == '$' && raw[1])
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "VAR", 4);
	}
	else
	{
		*token = malloc(4);
		if (!(*token))
			return ;
		ft_strlcpy(*token, "CMD", 4);
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
	token[i] = NULL;
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

static int	is_built(char *str)
{
	if (!ft_strncmp(str, "cd", 10))
		return (1);
	if (!ft_strncmp(str, "export", 10))
		return (1);
	if (!ft_strncmp(str, "unset", 10))
		return (1);
	if (!ft_strncmp(str, "exit", 10))
		return (1);
	return (0);
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
		else if (split[i][0] == '$' && split[i][1])
			flag = 1;
		else if (split[i][0] == '<' && split[i][1] == '<' && !split[i][2])
			flag = 1;
		else if (split[i][0] == '>' && !split[i][1])
			flag = 1;
		else if (split[i][0] == '<' && !split[i][1])
			flag = 1;
		else if (split[i][0] == '|' && split[i][1] == '|' && !split[i][2])
			flag = 1;
		else if (split[i][0] == '.' && split[i][1] == '/' && split[i][2])
			flag = 1;
		else if ((split[i][0] == '-' && is_alpha(&split[i][1])) || (split[i][0] == '-' && split[i][1] && split[i][1] == '-' && is_alpha(&split[i][2])))
			flag = 1;
		else if ((!exists(split[i], envp) || split[i][0] == '.' || split[i][0] == '/') && !is_built(split[i]))
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
	token = malloc((ft_memlen(split) + 1) * sizeof(char *));
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
