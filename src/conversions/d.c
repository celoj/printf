/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:26:02 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:16:11 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*perform_function_for_flag(char flag, int count,
		void *data)
{
	char	*dec;

	dec = NULL;
	if (flag == 'l')
		dec = ft_lltoa_base((long long)data, 10, 0);
	else if (flag == 'h')
	{
		if (count % 2 == 1)
			dec = ft_stoa_base((short)data, 10, 0);
		else
			dec = ft_itoa_base((signed char)data, 10, 0);
	}
	else if (flag == 'j')
		dec = ft_imttoa_base((intmax_t)data, 10, 0);
	else if (flag == 'z')
		dec = ft_sttoa_base((size_t)data, 10, 0);
	else if (flag == 't')
		dec = ft_pdttoa_base((ptrdiff_t)data, 10, 0);
	return (dec);
}

static int		check_sign_flags(t_flags *flags, int current_sign)
{
	if (is_flag_enabled('+', flags))
		return ('+');
	else if (is_flag_enabled(' ', flags))
		return (' ');
	return (current_sign);
}

static int		handle_flags(t_flags *flags, char *data, int *handled_sign)
{
	int			chars_printed;
	char		sign;

	if (!flags)
		return (0);
	chars_printed = 0;
	sign = data[0] == '-' ? '-' : 0;
	if (ft_isdigit(data[0]))
		sign = check_sign_flags(flags, sign);
	if (sign != 0 && is_flag_enabled('0', flags) && flags->precision == 0)
		chars_printed += write(1, &sign, (*handled_sign = 1));
	if (flags->width_specifier > 0)
		chars_printed += enforce_width_specifier((
		is_flag_enabled('0', flags) && flags->precision == 0 ? '0' : ' '),
		flags->width_specifier - (sign != 0 && sign != '-') - ((
		flags->precision == 0 || (int)ft_strlen(data) > flags->precision)
		&& !(sign != 0 && flags->precision == 0 && is_flag_enabled('.',
		flags)) ? ft_strlen(data) : (flags->precision + (data[0] == '-'))));
	if (sign != 0 && !*handled_sign)
		chars_printed += write(1, &sign, (*handled_sign = 1));
	if (flags->precision > 0)
		chars_printed += enforce_width_specifier('0',
				flags->precision - ft_strlen(data) + (sign == '-'));
	return (chars_printed);
}

static int		put_number(char *dec, t_flags *flags)
{
	int			chars_printed;
	int			handled_sign;

	handled_sign = 0;
	chars_printed = handle_flags(flags, dec, &handled_sign);
	if (is_flag_enabled('.', flags) && flags->precision == 0)
		return ((chars_printed) + (handled_sign
			|| flags->width_specifier == 0 ?
			0 : enforce_width_specifier(' ', ft_strlen(dec))));
	else
		return (chars_printed + ft_putstr_ret(handled_sign
				&& dec[0] == '-' ? (dec + 1) : dec));
}

int				d(t_flags *flags, void *data)
{
	int			i;
	char		*dec;

	dec = NULL;
	if (!flags)
		dec = ft_lltoa_base((int)data, 10, 0);
	else
	{
		i = -1;
		while (VALID_CONV_FLAGS[++i])
		{
			if (flags->key_flags[i] > 0)
			{
				dec = perform_function_for_flag(VALID_CONV_FLAGS[i],
						flags->key_flags[i], data);
			}
		}
		if (!dec)
			dec = ft_lltoa_base((int)data, 10, 0);
	}
	return (put_number(dec, flags));
}
