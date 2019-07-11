/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:20:11 by dcelojev          #+#    #+#             */
/*   Updated: 2019/06/17 19:35:37 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*perform_function_for_flag(char flag, void *data)
{
	char *dec;

	dec = NULL;
	if (flag == 'h' || flag == 'l')
	{
		dec = ft_ulltoa_base((unsigned long long)data, 10, 0);
	}
	else if (flag == 'j')
	{
		dec = ft_uimttoa_base((uintmax_t)data, 10, 0);
	}
	else if (flag == 'z')
	{
		dec = ft_sttoa_base((size_t)data, 10, 0);
	}
	else if (flag == 't')
	{
		dec = ft_pdttoa_base((ptrdiff_t)data, 10, 0);
	}
	return (dec);
}

static int		print_udec(char *dec, t_flags *flags, int data_length)
{
	int			chars_printed;

	chars_printed = 0;
	if (flags && flags->width_specifier > 0)
		chars_printed += enforce_width_specifier(
		(is_flag_enabled('0', flags) && flags->precision == 0 ? '0'
		: ' '), flags->width_specifier - (flags->precision >
			data_length ? flags->precision : data_length));
	if (is_flag_enabled('.', flags) && flags->precision)
		chars_printed += enforce_width_specifier('0',
				flags->precision - data_length);
	chars_printed += ft_putstr_ret(dec);
	if (flags && flags->width_specifier < 0)
		chars_printed += enforce_width_specifier(' ',
				ABS(flags->width_specifier) - chars_printed);
	return (chars_printed);
}

int				u(t_flags *flags, void *data)
{
	int			i;
	char		*dec;

	dec = NULL;
	if (!flags)
		dec = ft_ulltoa_base((unsigned long long)data, 10, 0);
	else
	{
		i = -1;
		while (VALID_CONV_FLAGS[++i])
			if (flags->key_flags[i] > 0)
				dec = perform_function_for_flag(VALID_CONV_FLAGS[i],
						data);
		if (!dec)
			dec = ft_ulltoa_base((unsigned long long)data, 10, 0);
	}
	if (is_flag_enabled('.', flags) && flags->precision == 0)
	{
		free(dec);
		dec = "";
	}
	if (is_flag_enabled('-', flags) && flags->width_specifier > 0)
		flags->width_specifier *= -1;
	return (print_udec(dec, flags, ft_strlen(dec)));
}
