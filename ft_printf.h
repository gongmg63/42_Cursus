/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gongmingu <gongmingu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:20:52 by mkong             #+#    #+#             */
/*   Updated: 2023/11/13 16:57:17 by gongmingu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

void	ft_putchar_va(char c);
size_t	ft_strlen(const char *s);
int		ft_intlen(int n,int base);
char    *ft_itohex(int n, char c);
void	ft_putstr_va(char *s);
void	ft_putnbr_va(int n);
void	ft_putunnbr_va(unsigned int n);
void    ft_puthex_va(int n, char c);
void    ft_putadd_va(unsigned long long add);

#endif
