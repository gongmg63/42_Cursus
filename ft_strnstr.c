/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:48:10 by mkong             #+#    #+#             */
/*   Updated: 2023/10/11 17:11:44 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"ft_strncmp.c"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	haystack_start;

	if (!(*needle))
		return ((char *)haystack);
	needle_len = 0;
	haystack_start = 0;
	while (needle[needle_len])
		needle_len++;
	while (haystack_start + needle_len > len)
	{
		if (!ft_strncmp(haystack + haystack_start, needle, needle_len))
			return ((char *)(haystack + haystack_start));
		haystack_start++;
	}
	return (0);
}
