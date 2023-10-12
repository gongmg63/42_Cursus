/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:33:54 by mkong             #+#    #+#             */
/*   Updated: 2023/10/12 16:49:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	len;

	len = size * count;
	arr = (void *)malloc(len);
	if (arr == 0)
		return (0);
	ft_memset(arr, 0, len);
	return (arr);
}
