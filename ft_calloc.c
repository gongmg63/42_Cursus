/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:33:54 by mkong             #+#    #+#             */
/*   Updated: 2023/10/11 18:40:33 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	len;

	len = size * count;
	arr = (void *)malloc(len);
	if (arr == NULL)
			return (0);
	while (len > 0)
	{
		arr[len - 1] = 0;
		len--;
	}
	return (arr);
}
