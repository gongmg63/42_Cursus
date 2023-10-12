/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:26:52 by mkong             #+#    #+#             */
/*   Updated: 2023/10/12 16:53:46 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_start;
	unsigned char	*src_start;

	dst_start = (unsigned char *)dst;
	src_start = (unsigned char *)src;
	while (len > 0)
	{
		*dst_start = *src_start;
		dst_start++;
		src_start++;
		len--;
	}
	return (dst);
}
