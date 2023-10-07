/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 12:35:46 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/26 20:41:06 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_infile(t_parsing *parsing, size_t i, size_t c, int first_pipe)
{
	if (parsing->infiles[c] >= 0)
	{
		if (parsing->infiles[c] > 0)
			close(parsing->infiles[c]);
		if (parsing->tokens[i] == 'H')
		{
			signal(SIGINT, here_doc_controller);
			parsing->infiles[c] = open_here_doc(parsing->prompt[i + 1],
					first_pipe);
			if (g_gb.hsig)
			{
				dup2(g_gb.stdin, 0);
				return ;
			}
			signal(SIGINT, ctrl_c_handler);
		}
		else
			parsing->infiles[c] = open(parsing->prompt[i + 1], O_RDONLY);
	}
	if (parsing->infiles[c] < 0)
	{
		printf("minishell: no such file or directory: %s\n", parsing->prompt[i
			+ 1]);
		g_gb.status_code = 1;
	}
}

void	check_outfile(t_parsing *parsing, size_t i, size_t c)
{
	if (parsing->outfiles[c] >= 0)
	{
		if (parsing->outfiles[c] > 2)
			close(parsing->outfiles[c]);
		if (parsing->tokens[i] == '>')
			parsing->outfiles[c] = open(parsing->prompt[i + 1], O_CREAT
					| O_WRONLY, 0664);
		else
			parsing->outfiles[c] = open(parsing->prompt[i + 1], O_CREAT
					| O_APPEND | O_RDWR, 0664);
	}
	if (parsing->outfiles[c] < 0)
		printf("permission denied: %s\n", parsing->prompt[i + 1]);
}

void	check_io_helper(size_t *i, size_t *c, int *first_pipe)
{
	*first_pipe = 0;
	*i = 0;
	*c = 0;
}

void	check_io(t_parsing *parsing)
{
	size_t	i;
	size_t	c;
	int		first_pipe;

	check_io_helper(&i, &c, &first_pipe);
	commands_size(parsing);
	parsing->infiles = (int *)ft_calloc(sizeof(int), parsing->cmd_size);
	parsing->outfiles = (int *)ft_calloc(sizeof(int), parsing->cmd_size);
	while (parsing->tokens[i])
	{
		if (parsing->tokens[i] == '<' || parsing->tokens[i] == 'H')
		{
			check_infile(parsing, i, c, first_pipe);
			if (g_gb.hsig)
				return ;
		}
		else if (parsing->tokens[i] == '>' || parsing->tokens[i] == 'A')
			check_outfile(parsing, i, c);
		if (parsing->tokens[i] == '|')
		{
			first_pipe = 1;
			c++;
		}
		i++;
	}
}

int	open_here_doc(char *delimiter, int first_pipe)
{
	int		fd[2];
	char	*line;
	size_t	i;

	pipe(fd);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strcmp(delimiter, line))
			break ;
		i = 0;
		while (line[i])
		{
			if (line[i] == '$' && !ft_strchr(delimiter, '\"')
				&& !ft_strchr(delimiter, '\'') && !ft_strchr(delimiter, '$'))
				expand_var(&line, i, first_pipe);
			if (line[i])
				i++;
		}
		(write(fd[1], line, ft_strlen(line)), write(fd[1], "\n", 1), free(line));
	}
	close(fd[1]);
	if (line)
		free(line);
	return (fd[0]);
}
