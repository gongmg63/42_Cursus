/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:24:29 by mkong             #+#    #+#             */
/*   Updated: 2023/10/16 18:23:23 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
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

static char	*add_word(char *word, const char *s, char c)
{
	if (ft_strchr(s, c) == 0)
		word = ft_strdup(s);
	else
		word = ft_strdup(ft_substr(s, 0, ft_strchr(s, c) - s));
	return (word);
}

static void	two_dimension_free(char **words, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(*(words + i));
		i++;
	}
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
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
			words[index] = add_word(words[index], s, c);
			if (!words[index])
			{
				two_dimension_free(words, count_words(s, c));
				return (0);
			}
			s = ft_strchr(s, c);
			index++;
		}
	}
	words[index] = 0;
	return (words);
}
