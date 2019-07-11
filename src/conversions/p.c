/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:33:28 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:28:01 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		handle_width_specifier(t_flags *flags, int data_length)
{
	int chars_printed;
	int precision_pad;

	chars_printed = 0;
	precision_pad = flags ? flags->precision : 0;
	if (flags && flags->width_specifier > 0)
	{
		if (is_flag_enabled('0', flags))
			chars_printed += write(1, "0x", 2) +
				enforce_width_specifier('0', flags->width_specifier
						- data_length - 2 + precision_pad);
		else
		{
			chars_printed += enforce_width_specifier(' ',
			flags->width_specifier - data_length - 2 - (data_length >
				precision_pad ? 0 : precision_pad)) + ft_putstr_ret("0x");
			chars_printed += enforce_width_specifier('0', precision_pad
					- chars_printed - data_length + 2);
		}
	}
	else
		chars_printed += write(1, "0x", 2);
	return (chars_printed + (precision_pad > 0 && flags->width_specifier < 1 ?
			enforce_width_specifier('0', precision_pad - chars_printed
				- data_length + 2) : 0));
}

int				p(t_flags *flags, void *data)
{
	int			i;
	int			chars_printed;
	char		*addr;

	addr = ft_ulltoa_base((unsigned long long)data, 16, 0);
	chars_printed = handle_width_specifier(flags, ft_strlen(addr));
	if (flags && flags->precision == 0 && is_flag_enabled('.', flags))
		return (chars_printed);
	i = -1;
	while (addr[++i])
		ft_putchar(addr[i]);
	free(addr);
	return (chars_printed + i);
}
