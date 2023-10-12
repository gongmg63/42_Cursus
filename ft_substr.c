/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:48:19 by mkong             #+#    #+#             */
/*   Updated: 2023/10/12 16:06:23 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		index;

	result = (char *)malloc(sizeof(char) * len + 1);
	index = 0;
	if (result == NULL)
		return (0);
	while (len > 0)
	{
		result[index] = s[start + index];
		index++;
		len--;
	}
	result[index] = '\0';
	return (result);
}
