/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:39:11 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/26 21:19:57 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	find_equal(char *env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	return (i);
}

void	setup_lenv(char **env)
{
	t_env	*var;
	size_t	del;
	size_t	i;

	g_gb.env = NULL;
	if (!*env)
		return ;
	var = malloc(sizeof(t_env));
	g_gb.env = var;
	i = 0;
	while (env && env[i])
	{
		del = find_equal(env[i]);
		env[i][del] = 0;
		var->key = ft_strdup(env[i]);
		var->value = ft_strdup(&env[i][del + 1]);
		var->next = 0;
		if (env[i + 1])
			var->next = malloc(sizeof(t_env));
		var = var->next;
		i++;
	}
}

void	commands_size(t_parsing *parsing)
{
	size_t	i;

	i = 0;
	parsing->cmd_size = 0;
	while (parsing->tokens[i])
	{
		if (parsing->tokens[i] == '|')
			(parsing->cmd_size)++;
		i++;
	}
	if (i > 0)
		(parsing->cmd_size)++;
}

size_t	remove_quote(char **line, size_t start, size_t end, t_utils *utils)
{
	char	*new_line;
	char	*inside;
	char	*temp;
	size_t	i;

	inside = ft_substr(*line, start + 1, end - start - 1);
	i = 0;
	while ((*line)[start] == '"' && inside[i])
	{
		if (inside[i] == '$' && utils->prev_token != 'H')
			expand_var(&inside, i, utils->first_pipe);
		else
			i++;
	}
	(*line)[start] = 0;
	temp = ft_strjoin(*line, inside);
	new_line = ft_strjoin(temp, &(*line)[end + 1]);
	i = start + ft_strlen(inside);
	free(inside);
	free(temp);
	free(*line);
	*line = new_line;
	return (i);
}

void	setup_args_utils(t_parsing *parsing, size_t cmd_index, size_t *i)
{
	size_t	j;

	j = 0;
	while (j < cmd_index)
	{
		if (parsing->tokens[*i] == '|')
			j++;
		(*i)++;
	}
}
