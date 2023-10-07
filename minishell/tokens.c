/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:33:21 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/24 23:55:19 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokening(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->prompt[i])
	{
		if (parsing->prompt[i][0] == '|')
			parsing->tokens[i] = '|';
		else if (parsing->prompt[i][0] == '<' && !parsing->prompt[i][1])
			parsing->tokens[i] = '<';
		else if (parsing->prompt[i][0] == '<' && parsing->prompt[i][1])
			parsing->tokens[i] = 'H';
		else if (parsing->prompt[i][0] == '>' && !parsing->prompt[i][1])
			parsing->tokens[i] = '>';
		else if (parsing->prompt[i][0] == '>' && parsing->prompt[i][1])
			parsing->tokens[i] = 'A';
		else
			parsing->tokens[i] = 'S';
		i++;
	}
	parsing->tokens[i] = '\0';
}
