/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:26:02 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:19:36 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*perform_function_for_flag(char flag, void *data)
{
	char	*oct;

	oct = NULL;
	if (flag == 'h' || flag == 'l')
	{
		oct = ft_ulltoa_base((unsigned long long)data, 8, 0);
	}
	else if (flag == 'j')
	{
		oct = ft_uimttoa_base((intmax_t)data, 8, 0);
	}
	else if (flag == 'z')
	{
		oct = ft_sttoa_base((size_t)data, 8, 0);
	}
	else if (flag == 't')
	{
		oct = ft_pdttoa_base((ptrdiff_t)data, 8, 0);
	}
	return (oct);
}

static int		handle_flags(t_flags *flags, int data_length,
			int resolve_pound)
{
	int			chars_printed;

	if (!flags)
		return (0);
	chars_printed = 0;
	if (flags->width_specifier > 0)
		chars_printed += enforce_width_specifier(
		is_flag_enabled('0', flags) && flags->precision == 0 ? '0' : ' ',
		flags->width_specifier - (flags->precision > data_length ?
		flags->precision - resolve_pound : data_length) - resolve_pound);
	if (resolve_pound)
		chars_printed += write(1, "0", 1);
	if (is_flag_enabled('.', flags) && flags->precision > 0
			&& flags->precision > data_length)
		chars_printed += enforce_width_specifier('0',
			flags->precision - data_length - resolve_pound);
	return (chars_printed);
}

int				o(t_flags *flags, void *data)
{
	int			i;
	int			chars_printed;
	char		*oct;

	oct = NULL;
	chars_printed = 0;
	if (!flags)
		oct = ft_ulltoa_base((unsigned long long)data, 8, 0);
	else
	{
		i = -1;
		while (!oct && VALID_CONV_FLAGS[++i])
			if (flags->key_flags[i] > 0)
				oct = perform_function_for_flag(VALID_CONV_FLAGS[i], data);
		if (!oct)
			oct = ft_ulltoa_base((unsigned long long)data, 8, 0);
	}
	if (is_flag_enabled('.', flags) && flags->precision == 0)
	{
		free(oct);
		oct = "";
	}
	return (handle_flags(flags, ft_strlen(oct), is_flag_enabled('#',
	flags) && ((int)data != 0 || ft_strlen(oct) == 0)) + ft_putstr_ret(oct));
}
