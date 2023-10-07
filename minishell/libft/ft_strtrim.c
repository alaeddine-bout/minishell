/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:26:12 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/26 20:28:51 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_check(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	len = ft_strlen(s1) - 1;
	if (s1[start] == '\0')
		return (ft_strdup(""));
	while (s1[start] != '\0' && ft_check(set, s1[start]) == 1)
		start++;
	while (start < len && ft_check(set, s1[len]) == 1)
		len--;
	str = ft_substr(s1, start, (len - start) + 1);
	return (str);
}
