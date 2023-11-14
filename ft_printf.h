/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkong <mkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:20:52 by mkong             #+#    #+#             */
/*   Updated: 2023/11/14 16:50:34 by mkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

void	ft_putchar_va(char c);
size_t	ft_strlen(const char *s);
char	*ft_itohex(int n, char c);
void	ft_putstr_va(char *s);
void	ft_putnbr_va(int n, char c);
void	ft_puthex_va(int n, char c);
void	ft_putadd_va(unsigned long long add);
int		ft_printf(const char *format, ...);

#endif
