/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capital_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 23:22:31 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 13:38:35 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				capital_c(t_flags *flags, void *data)
{
	int			chars_printed;
	wchar_t		c;

	chars_printed = 0;
	c = (wchar_t)data;
	if (flags && flags->width_specifier > 0)
		chars_printed += enforce_width_specifier(
				(is_flag_enabled('0', flags) ? '0' : ' '),
							flags->width_specifier - 1);
	write(1, &c, sizeof(wchar_t));
	return (1 + chars_printed);
}
