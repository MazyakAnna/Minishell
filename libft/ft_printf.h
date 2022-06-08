/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserwyn <fserwyn@student.21-school.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:06:47 by fserwyn           #+#    #+#             */
/*   Updated: 2021/01/30 09:47:47 by fserwyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	int	width;
	int	accuracy;
	int	flag;
	int	argument;
	int	result;
	int	minus;
	int	star;
	int	arg_star;
	int	up_x;
	int	p_null;
	int	accuracy_0;
}				t_list;

int				ft_printf(const char *str, ...);

size_t			ft_strlen(const char *s);

void			ft_printf_c(int c, t_list *spec);
void			ft_printf_s(char *str, t_list *spec);
void			ft_printf_u(unsigned int u, t_list *spec);
void			ft_printf_x(unsigned int x, t_list *spec);
void			ft_printf_p(unsigned long long x, t_list *spec);
void			ft_printf_d(int d, t_list *spec);

void			ft_putchar_mod(char c, t_list *spec);
void			ft_putstr_mod(char *s, t_list *spec, int len);
void			ft_putnbr_mod(unsigned int n, t_list *spec);
void			ft_putnbr_mod_16(unsigned long long n, t_list *spec);
int				ft_putnbr_len(unsigned long long n);
int				ft_putnbr_len_p(unsigned long long n);
int				ft_putnbr_len_16(unsigned long long n);

void			spec_null(t_list *spec);
void			serch_flag(int *i, const char *str, t_list *spec, int vaarg);
int				f_10_16(unsigned long long x);

void			print_if_flag_1_2(int c, t_list *spec);
void			print_str_if_flag_1_2(char *str, t_list *spec, int len);
void			f_if_width_minus(t_list *spec);

void			f_if_strar_1(int *i, t_list *spec, va_list arg);
void			f_parse(va_list arg, char *str, t_list *spec);
void			f_while_str_num(int *i, char *str, t_list *spec);
void			f_while_str_num_acy(int *i, char *str, t_list *spec);
void			f_if_str_flag(int *i, char *str, t_list *spec, va_list arg);
void			f_if_str_accuracy(int *i, char *str, t_list *spec, va_list arg);
void			f_if_str_cspdiux(int *i, char *str, t_list *spec, va_list arg);

void			f_width_put__(t_list *spec);
void			f_while_len_len_put_0(unsigned int *u, int *len, t_list *spec);
void			print_u_if_flag1(unsigned int *u, int *len, \
						int *len_tmp, t_list *spec);
void			print_u_if_flag2(unsigned int *u, int *len, t_list *spec);
void			f_while_width_len_put_0(int *len, t_list *spec);
void			f_if_accuracy_len(int *len, int *len_tmp, t_list *spec);
void			print_x_if_flag1(unsigned int *x, int *len_tmp, t_list *spec);
void			print_x_if_flag1_1(int *len, int *len_tmp2, t_list *spec);
void			len_status_x(unsigned int *x, int *len, int *len_tmp, \
								int *len_tmp2);
void			f_connect(unsigned int *x, int *len, \
							int *len_tmp, t_list *spec);
void			print_x_if_flag2(unsigned int *x, int *len, \
						int *len_tmp, t_list *spec);
void			f_if_accuracy_m1(unsigned int *x, int *len, t_list *spec);
void			f_while_width_len_put__(int *len, t_list *spec);
void			f_while_len_f(unsigned int *x, int *len, t_list *spec);
void			f_if_x_0(unsigned int *x, t_list *spec);
void			f_if_p_0(unsigned long long *x, t_list *spec);
void			print_p_if_flag1(unsigned long long *x, \
						int *len_tmp, t_list *spec);
void			print_p_if_flag1_1(int *len, int *len_tmp, \
						int *len_tmp2, t_list *spec);
void			f_connect_2(unsigned long long *x, int *len, \
							int *len_tmp, t_list *spec);
void			f_if_x_0_and_accuracy_n0(unsigned long long *x, t_list *spec);
void			print_p_if_flag2(unsigned long long *x, int *len, \
							int *len_tmp, t_list *spec);
void			f_while_fwidth_len_2(int *len, t_list *spec);
void			f_if_accuracy_and_p_0(unsigned long long *x, t_list *spec);
void			f_if_accuracy__m1(unsigned long long *x, \
						int *len, t_list *spec);
void			len_status(unsigned long long *x, int *len, int *len_tmp, \
								int *len_tmp2);
void			f_if_px_0(unsigned long long *x, int *len);

void			f_if_width_and_d_m0(int *d, t_list *spec);
void			print_d_if_flag1(int *d, int *len, t_list *spec);
void			print_d_if_flag2(int *d, int *len, t_list *spec);
void			f_while_width_and_more(unsigned long long *x, int *len, \
								t_list *spec);
void			print_d_if_accuracy_m1_ang_b1(int *len, t_list *spec);
void			print_d_if_accuracy_m1(int *d, t_list *spec);
void			print_d_while_width_len(int *d, int *len, t_list *spec);

#endif
