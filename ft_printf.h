/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:20:52 by mkong             #+#    #+#             */
/*   Updated: 2023/11/15 15:37:29 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

void	ft_putchar_va(char c, int *len);
size_t	ft_strlen(const char *s);
char	*ft_tohex(unsigned long long n, char c);
void	ft_putstr_va(char *s, int *len);
void	ft_putnbr_va(int n, char c, int *len);
void	ft_puthex_va(unsigned long long n, char c, int *len);
void	ft_putadd_va(unsigned long long add, int *len);
int		ft_printf(const char *format, ...);

#endif
