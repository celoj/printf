/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:52:59 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 15:12:45 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"
# define FLAG_MAP_SIZE 12
# define FUNC_MAP_SIZE 16
# define GLOBAL_FLAGS " 0+-#."
# define VALID_CONV_FLAGS "lLhjzt"

typedef struct		s_flags
{
	char			key;
	int				width_specifier;
	int				precision;
	int				*key_flags;
	int				*global_flags;
}					t_flags;

int					ft_printf(const char *format, ...);
t_flags				*get_flags_for_key(const char *format, int i,
		char key, int key_length);
int					is_flag_enabled(char flag, t_flags *flags);
int					enforce_width_specifier(char c, int n);
int					get_padding_char(t_flags *flags);
int					enable_flag(char flag, t_flags *flags);
t_flags				*printf_free(t_flags *flags);
int					s(t_flags *flags, void *data);
int					capital_s(t_flags *flags, void *data);
int					c(t_flags *flags, void *data);
int					capital_c(t_flags *flags, void *data);
int					p(t_flags *flags, void *data);
int					d(t_flags *flags, void *data);
int					u(t_flags *flags, void *data);
int					x(t_flags *flags, void *data);
int					capital_x(t_flags *flags, void *data);
int					o(t_flags *flags, void *data);
int					f(t_flags *flags, double data);
int					lf(t_flags *flags, long double data);
int					enforce_width_specifier(char c, int n);
int					initialize_flags(t_flags *flags);
int					read_precision(t_flags *flags, const char *format, int i);
void				check_flag(t_flags *flags, char flag);
int					perform_function_for_key(char key, t_flags *flags,
		void *data);
int					is_key(char c);
int					invalid_key_char(char c);

const static void	*g_func_map[FUNC_MAP_SIZE][2] =
{
	{"s", &s}, {"S", &capital_s},
	{"c", &c}, {"C", &capital_c},
	{"p", &p},
	{"d", &d}, {"D", &d},
	{"i", &d},
	{"u", &u}, {"U", &u},
	{"x", &x}, {"X", &capital_x},
	{"o", &o},
	{"f", &f}, {"F", &f},
	{"%", &c}
};

#endif
