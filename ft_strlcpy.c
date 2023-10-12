/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:37:37 by mkong             #+#    #+#             */
/*   Updated: 2023/10/12 19:54:03 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	while (dstsize > 1 && src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
		dstsize--;
	}
	if (dstsize != 0)
		dst[index] = '\0';
	index = 0;
	while (src[index] != 0)
		index++;
	return (index);
}
