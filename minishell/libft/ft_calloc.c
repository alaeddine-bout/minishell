/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oryadi <oryadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:24:35 by oryadi            #+#    #+#             */
/*   Updated: 2023/07/26 20:24:50 by oryadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (0);
	ft_bzero (str, (count * size));
	return (str);
}
