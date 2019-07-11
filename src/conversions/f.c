/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:26:02 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:15:49 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_decimal(char *s)
{
	int		i;

	i = -1;
	if (s[0] == '-')
		i++;
	while (s[++i])
		if (s[i] != '.' && !ft_isdigit(s[i]))
			return (0);
	return (1);
}

static int	flag_checks(t_flags *flags, char *s, int sign, int *chars_printed)
{
	int zero_padding;
	int is_dec;

	is_dec = is_decimal(s);
	if (is_flag_enabled('-', flags) && flags->width_specifier > 0)
		flags->width_specifier *= -1;
	if (s[0] != '-' && (is_dec || (s && (s[0] == 'i' || s[0] == 'I'
			|| ft_strcmp(s, "-inf") == 0 || ft_strcmp(s, "-INF") == 0))))
	{
		if (is_flag_enabled('+', flags))
			sign = '+';
		else if (is_flag_enabled(' ', flags))
			sign = ' ';
	}
	zero_padding = is_flag_enabled('0', flags)
		&& is_dec && flags->width_specifier > 0;
	if (zero_padding && sign != 0)
		*chars_printed += write(1, &sign, 1);
	if (flags->width_specifier > 0)
		*chars_printed += enforce_width_specifier(zero_padding ? '0' : ' ',
			flags->width_specifier - (sign != 0 && s[0] != '-')
				- ft_strlen(s)) - (sign == '-' && zero_padding);
	if (!zero_padding)
		*chars_printed += sign != 0 && s[0] != '-' ? write(1, &sign, 1) : 0;
	return (zero_padding);
}

static int	print_decimal(t_flags *flags, char *s)
{
	int		chars_printed;
	int		is_dec;
	int		sign;
	int		zero_padding;

	chars_printed = 0;
	zero_padding = 0;
	sign = s[0] == '-' ? '-' : 0;
	is_dec = is_decimal(s);
	if (flags)
		zero_padding = flag_checks(flags, s, sign, &chars_printed);
	chars_printed += ft_putstr_ret(zero_padding && sign == '-' ? s + 1 : s)
		+ (zero_padding && sign == '-');
	if (is_flag_enabled('#', flags) && !ft_strchr(s, '.'))
		chars_printed += write(1, ".", 1);
	if (flags && flags->width_specifier < 0)
		chars_printed += enforce_width_specifier(' ',
				ABS(flags->width_specifier) - chars_printed);
	return (chars_printed);
}

int			lf(t_flags *flags, long double data)
{
	char	*s;
	int		chars_printed;

	if (!(s = ft_ldtoa(data, flags ? flags->precision : 6, 0)))
		return (0);
	chars_printed = s ? print_decimal(flags, s) : 0;
	free(s);
	return (chars_printed);
}

int			f(t_flags *flags, double data)
{
	char	*s;
	int		chars_printed;

	if (!(s = ft_dtoa(data, flags ? flags->precision : 6, 0)))
		return (0);
	chars_printed = s ? print_decimal(flags, s) : 0;
	free(s);
	return (chars_printed);
}
