/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:20:52 by mkong             #+#    #+#             */
/*   Updated: 2023/11/10 19:54:39 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>

void	ft_putchar_va(char c);
size_t	ft_strlen(const char *s);
int		ft_intlen(int n);
void	ft_putstr_va(char *s);
void	ft_putnbr_va(int n);

#endif
