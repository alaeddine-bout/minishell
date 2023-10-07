/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:11:22 by about             #+#    #+#             */
/*   Updated: 2023/07/25 23:13:57 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(int outfile)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("%s\n", current_env("OLDPWD"));
		return (0);
	}
	ft_putstr_fd(pwd, outfile);
	ft_putstr_fd("\n", outfile);
	free(pwd);
	return (0);
}
