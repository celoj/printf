/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:26:02 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:45:08 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*perform_function_for_flag(char flag, void *data)
{
	char	*hex;

	hex = NULL;
	if (flag == 'h' || flag == 'l')
	{
		hex = ft_ulltoa_base((unsigned long long)data, 16, 0);
	}
	else if (flag == 'j')
	{
		hex = ft_uimttoa_base((intmax_t)data, 16, 0);
	}
	else if (flag == 'z')
	{
		hex = ft_sttoa_base((size_t)data, 16, 0);
	}
	else if (flag == 't')
	{
		hex = ft_pdttoa_base((ptrdiff_t)data, 16, 0);
	}
	return (hex);
}

static int		can_print_hex_prefix(t_flags *flags)
{
	return (is_flag_enabled('#', flags) && !(is_flag_enabled('.', flags)
				&& flags->precision == 0));
}

static void		do_width_specifier(t_flags *flags, int data_length,
		int *chars_printed, int print_prefix)
{
	if (is_flag_enabled('0', flags) && !(is_flag_enabled('.', flags)
		&& flags->precision > 0))
		*chars_printed += (print_prefix ? ft_putstr_ret("0x") : 0)
		+ enforce_width_specifier('0', flags->width_specifier
		- (flags->precision > data_length ? flags->precision :
			data_length) - (print_prefix * 2));
	else
		*chars_printed += enforce_width_specifier(' ',
		flags->width_specifier - (flags->precision > data_length
			? flags->precision : data_length) - (print_prefix * 2))
		+ (print_prefix ? ft_putstr_ret("0x") : 0);
}

static int		handle_global_flags(t_flags *flags, int data_length,
		int is_zero)
{
	int			chars_printed;
	int			print_prefix;

	chars_printed = 0;
	print_prefix = !is_zero && can_print_hex_prefix(flags);
	if (!flags)
		return (0);
	if (flags->width_specifier > 0)
		do_width_specifier(flags, data_length, &chars_printed,
				print_prefix);
	else if (print_prefix)
		chars_printed += ft_putstr_ret("0x");
	if (is_flag_enabled('.', flags) && flags->precision > 0)
		chars_printed += enforce_width_specifier('0',
				flags->precision - data_length);
	return (chars_printed);
}

int				x(t_flags *flags, void *data)
{
	int			i;
	char		*hex;

	hex = NULL;
	if (!flags)
		hex = ft_ulltoa_base((unsigned long long)data, 16, 0);
	else
	{
		i = -1;
		while (!hex && VALID_CONV_FLAGS[++i])
			if (flags->key_flags[i] > 0)
				hex = perform_function_for_flag(VALID_CONV_FLAGS[i],
						data);
		if (!hex)
			hex = ft_ulltoa_base((unsigned long long)data, 16, 0);
	}
	if (is_flag_enabled('.', flags) && flags->precision == 0)
	{
		free(hex);
		hex = "";
	}
	return (handle_global_flags(flags, ft_strlen(hex), (int)data == 0)
			+ ft_putstr_ret(hex));
}
