/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:10:56 by mkong             #+#    #+#             */
/*   Updated: 2023/10/05 17:01:19 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	length;
	int		index;

	length = 0;
	index = 0;
	while (s[index])
	{
		index++;
		lenght++;
	}
	return (length);
}
