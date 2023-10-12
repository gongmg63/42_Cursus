/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:39:54 by mkong             #+#    #+#             */
/*   Updated: 2023/10/11 17:50:23 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"ft_strlen.c"

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	char	*arr;

	s1_len = ft_strlen(s1);
	arr = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (arr == NULL)
		return (0);
	while (*s1)
	{
		*arr = *s1;
		arr++;
		s1++;
	}
	*arr = '\0';
	return (arr - s1_len);
}
