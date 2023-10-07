/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:15:19 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/26 17:22:53 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd_lines	*cmd_lines;

	(void)argv;
	(void)argc;
	setup_lenv(env);
	g_gb.status_code = 0;
	cmd_lines = NULL;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	g_gb.hsig = 0;
	g_gb.stdin = dup(0);
	while (1)
	{
		cmd_lines = ft_parsing(cmd_lines);
		if (cmd_lines == NULL)
			continue ;
		execute_cmd(cmd_lines);
		free_nodes(cmd_lines);
	}
}

void	ctrl_c_handler(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_gb.status_code = 1;
}

t_cmd_lines	*ft_parsing(t_cmd_lines *cmd_lines)
{
	t_parsing	parsing;
	char		*line;

	initialpars(&parsing);
	line = readline("[minishell][:)]~> ");
	if (line == NULL)
		(write(2, "exit\n", 5), exit(g_gb.status_code));
	if (!(*line))
		return (free(line), NULL);
	if (ft_strlen(line) > 0)
		add_history(line);
	(ft_spliting(line, &parsing), free(line));
	if (!parsing.prompt[0])
		return (0);
	tokening(&parsing);
	if (checkerrors(&parsing))
		return (0);
	(expand(&parsing), check_io(&parsing));
	if (g_gb.hsig)
	{
		g_gb.hsig = 0;
		return (freeparsing(&parsing), NULL);
	}
	cmd_lines = addtostruct(&parsing);
	return (freeparsing(&parsing), cmd_lines);
}
