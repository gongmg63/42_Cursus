/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:48:19 by mkong             #+#    #+#             */
/*   Updated: 2023/10/15 16:34:56 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*result;

	s_len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (result == 0 || start + len - 1 > s_len)
		return (0);
	ft_strlcpy(result, s + start, len);
	return (result);
}
