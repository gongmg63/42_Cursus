/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:00:39 by mkong             #+#    #+#             */
/*   Updated: 2023/10/09 19:25:40 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	unsigned char	*dst_start;
	unsigned char	*src_start;

	dst_start = dst;
	src_start = src;
	while (n > 0)
	{
		*dst_start = *src_start;
		dst_start++;
		src_start++;
		n--;
	}
	return (dst);
}
