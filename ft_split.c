/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:24:29 by mkong             #+#    #+#             */
/*   Updated: 2023/10/13 20:40:37 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
int	count_words(const char *s, char c)
{
	int	cnt;

	cnt = 0;
	while (s && *s)
	{
		if (s == ft_strchr(s, c))
			s++;
		else
		{
			cnt++;
			s = ft_strchr(s, c);
		}
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	one_word_len;
	size_t	index;

	words = (char **)malloc(sizeof(char *) * ((count_words(s, c) + 1)));
	index = 0;
	if (words == 0)
		return (0);
	while (s && *s)
	{
		if (s == ft_strchr(s, c))
			s++;
		else
		{
			if (ft_strchr(s, c) == 0)
				words[index] = ft_strdup(s);
			else
			{
				one_word_len = ft_strchr(s, c) - s;
				words[index] = ft_strdup(ft_substr(s, 0, one_word_len + 1));
			}
			s = ft_strchr(s, c);
			index++;
		}
	}
	words[index] = 0;
	return (words);
}
