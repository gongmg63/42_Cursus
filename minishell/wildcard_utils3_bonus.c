/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:47:15 by jgoo              #+#    #+#             */
/*   Updated: 2024/03/14 13:34:31 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

void	move_str(char **str, int len)
{
	char	*s;

	s = *str;
	while (len--)
		s++;
	*str = s;
}
