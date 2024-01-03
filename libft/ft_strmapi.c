/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:36:20 by mkong             #+#    #+#             */
/*   Updated: 2024/01/03 15:42:24 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	size_t			s_len;
	unsigned int	idx;

	s_len = ft_strlen(s);
	idx = 0;
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (result == 0)
		return (0);
	while (idx < s_len)
	{
		*(result + idx) = (*f)(idx, *(s + idx));
		idx++;
	}
	*(result + idx) = '\0';
	return (result);
}
