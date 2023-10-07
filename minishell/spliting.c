/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:41:55 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/15 09:15:22 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_checks(char *line, size_t i)
{
	if (line[i] == '<' || line[i] == '|' || line[i] == '>')
	{
		ft_checkingdupp(line, &i);
		i++;
	}
	else
	{
		while (line[i] && line[i] != '<' && line[i] != '|' && line[i] != '>'
			&& line[i] != ' ' && line[i] != '\t')
		{
			if (line[i] == '\"' || line[i] == '\'')
			{
				i++;
				i = dquoting(line, line[i - 1], i);
				i++;
			}
			else
				i++;
		}
	}
	return (i);
}

t_parsing	*initialsplit(t_parsing *parsing, char *line, size_t *i,
		size_t *start)
{
	*i = 0;
	*start = 0;
	parsing->size = sizeofprompt(line);
	parsing->prompt = malloc((parsing->size + 1) * sizeof(char **));
	parsing->tokens = malloc(parsing->size + 1);
	return (parsing);
}

void	ft_spliting(char *line, t_parsing *parsing)
{
	size_t	i;
	size_t	start;
	int		x;
	size_t	len;

	parsing = initialsplit(parsing, line, &i, &start);
	x = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			start++;
			continue ;
		}
		i = ft_checks(line, i);
		len = i - start;
		parsing->prompt[x] = ft_substr(line, start, len);
		x++;
		if (!line[i])
			break ;
		start = i;
	}
	parsing->prompt[x] = NULL;
}
