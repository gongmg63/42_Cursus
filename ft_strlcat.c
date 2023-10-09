/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:00:03 by mkong             #+#    #+#             */
/*   Updated: 2023/10/09 20:07:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;

	len_dst = 0;
	len_src = 0;
	while (*dst != '\0')
	{
		dst++;
		len_dst++;
	}
	while (src[len_src] != '\0')
		len_src++;
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (size - 1 > len_dst && *src != '\0')
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (len_dst + len_src);
}
