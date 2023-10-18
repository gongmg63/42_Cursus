/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:24:29 by mkong             #+#    #+#             */
/*   Updated: 2023/10/18 16:31:20 by mkong            ###   ########.fr       */
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
	char	*s_substr;

	if (ft_strchr(s, c) == 0)
		word = ft_strdup(s);
	else
	{
		s_substr = ft_substr(s, 0, ft_strchr(s, c) - s);
		if (s_substr == 0)
			return (0);
		word = ft_strdup(s_substr);
		free(s_substr);
	}
	return (word);
}

static void	two_dimension_free(char **words, int idx)
{
	while (idx >= 0)
	{
		free(words[idx]);
		idx--;
	}
	free(words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	idx;

	words = (char **)malloc(sizeof(char *) * ((count_words(s, c) + 1)));
	idx = 0;
	if (words == 0)
		return (0);
	while (s && *s)
	{
		if (s == ft_strchr(s, c))
			s++;
		else
		{
			words[idx] = add_word(words[idx], s, c);
			if (!words[idx])
			{
				two_dimension_free(words, idx);
				return (0);
			}
			s = ft_strchr(s, c);
			idx++;
		}
	}
	words[idx] = 0;
	return (words);
}
