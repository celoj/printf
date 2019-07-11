/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:54:02 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 13:38:06 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	wchar_t_c(void *data)
{
	int		i;
	wchar_t	c;

	i = -1;
	c = (wchar_t)data;
	return (write(1, &c, sizeof(wchar_t)));
}

static int	char_c(void *data)
{
	int		i;
	char	c;

	i = -1;
	c = (char)data;
	return (write(1, &c, sizeof(char)));
}

int			c(t_flags *flags, void *data)
{
	int		chars_printed;

	chars_printed = 0;
	if (flags && flags->width_specifier > 0 && !is_flag_enabled('-', flags))
		chars_printed += enforce_width_specifier(
				(is_flag_enabled('0', flags) ? '0' : ' '),
							flags->width_specifier - 1);
	if (flags && flags->key_flags[0] > 0)
		chars_printed += wchar_t_c(data);
	else
		chars_printed += char_c(data);
	return (chars_printed);
}
