/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:42:18 by mkong             #+#    #+#             */
/*   Updated: 2023/10/13 16:07:36 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	while (ft_strchr(set, *s1))
	{
		s1++;
		s1_len--;
	}
	while (ft_strrchr(set, s1[s1_len]))
		s1_len--;
	result = (char *)malloc(s1_len + 2);
	ft_strlcpy(result, s1, s1_len + 2);
	return (result);
}
