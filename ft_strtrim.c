/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:42:18 by mkong             #+#    #+#             */
/*   Updated: 2023/10/18 16:52:06 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1))
	{
		s1++;
		s1_len--;
	}
	while (*s1 && ft_strrchr(set, *(s1 + s1_len - 1)))
		s1_len--;
	if (s1_len == 0)
	{
		result = (char *)malloc(sizeof(char) * 1);
		if (result == 0)
			return (0);
		*result = '\0';
		return (result);
	}
	result = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (result == 0)
		return (0);
	ft_strlcpy(result, s1, s1_len + 1);
	return (result);
}
