/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:06:53 by about             #+#    #+#             */
/*   Updated: 2023/07/25 00:15:25 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_someputstr_fd(char *key, char *value, int outfile)
{
	ft_putstr_fd(key, outfile);
	ft_putstr_fd("=", outfile);
	ft_putstr_fd(value, outfile);
	ft_putstr_fd("\n", outfile);
}

int	ft_env(int flag, int outfile)
{
	t_env	*tmp;

	tmp = g_gb.env;
	while (tmp)
	{
		if (flag)
		{
			ft_putstr_fd("declare -x ", outfile);
			ft_putstr_fd(tmp->key, outfile);
			if (tmp->value)
			{
				ft_putstr_fd("=\"", outfile);
				ft_putstr_fd(tmp->value, outfile);
				ft_putstr_fd("\"", outfile);
			}
			ft_putstr_fd("\n", outfile);
		}
		else if (tmp->value)
			ft_someputstr_fd(tmp->key, tmp->value, outfile);
		tmp = tmp->next;
	}
	return (0);
}
