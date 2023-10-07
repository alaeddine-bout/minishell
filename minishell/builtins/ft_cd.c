/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: about <about@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:06:29 by about             #+#    #+#             */
/*   Updated: 2023/07/24 23:14:10 by about            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*current_env(char *str)
{
	t_env	*env;
	char	*var;

	env = g_gb.env;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			var = ft_strdup(env->value);
			return (var);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_cd(char **av)
{
	char	*path;
	char	*home;

	if (!av[1] || ft_strcmp(av[1], "~") == 0)
	{
		home = current_env("HOME");
		if (chdir(home) == -1)
			write(2, "cd: HOME not set\n", 17);
		free(home);
		return (g_gb.status_code = 0);
	}
	else if (av[1])
	{
		path = av[1];
		if (chdir(path) == -1)
			printf("cd: No such file or directory : %s\n", path);
		return (g_gb.status_code = 1);
	}
	return (g_gb.status_code = 0);
}
