/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:24:29 by mkong             #+#    #+#             */
/*   Updated: 2023/10/13 18:21:23 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *str, char c)
{
	int	cnt;

	cnt = 0;
	while (str)
	{
		if (str != ft_strchr(str, c))
			str++;
		else
		{
			cnt++;
			str = ft_strchr(str, c);
		}
	}
	return (cnt);
}

int	count_one_word(char *str, char c)
{
	int	cnt;

	cnt = 0;
	while (str)
	{
		while (str == ft_strchr(str, c))
			str++;
		cnt++;
		str = ft_strchr(str, c);
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	s_len;
	size_t	one_word_len;

	words = (char **)malloc(sizeof(char *) * (count_words(s,c)));
	s_len = ft_strlen(s);
	if (words == 0)
		return (0);
	while (str)
	{
		if (s == ft_strchr(s, c))
			str++;
		else
		{
			if (ft_strchr(s, c) == 0)
				*word = ft_strdup(s);
			else
			{
				one_word_len = ft_strchr(s, c) - str;
				*word = ft_strdup(ft_substr(s, 0, one_word_len));
			}
			word++;
		}
	}
}
