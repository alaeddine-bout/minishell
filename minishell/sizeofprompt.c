/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizeofprompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:05:40 by oryadi            #+#    #+#             */
/*   Updated: 2023/06/16 16:44:25 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_checkiprompt(char *line, size_t i)
{
	if (line[i] == '<' || line[i] == '|' || line[i] == '>')
	{
		ft_checkingdupp(line, &i);
		i++;
	}
	else
	{
		while (line[i] && line[i] != '<' && line[i] != '|'
			&& line[i] != '>' && line[i] != ' ' && line[i] != '\t')
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

size_t	sizeofprompt(char *line)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			continue ;
		}
		i = ft_checkiprompt(line, i);
		count++;
	}
	return (count);
}
