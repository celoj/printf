/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:58:55 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:28:56 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	wchar_t_s(void *data, t_flags *flags)
{
	int		i;
	int		length;
	int		max_chars;
	int		padding;
	wchar_t	*s;

	i = -1;
	padding = 0;
	s = data ? (wchar_t *)data : L"(null)";
	length = ft_wstrlen(s);
	if (is_flag_enabled('.', flags) && flags->precision < length)
		length = flags->precision;
	max_chars = flags && is_flag_enabled('.', flags) ?
		flags->precision : length;
	if (flags && flags->width_specifier > 0)
		padding = enforce_width_specifier(
				get_padding_char(flags), flags->width_specifier - length);
	while (s[++i] && i < max_chars)
		write(1, &s[i], sizeof(wchar_t));
	if (flags && flags->width_specifier < 0 && i < ABS(flags->width_specifier))
		i += enforce_width_specifier(' ', ABS(flags->width_specifier) - i - 1);
	return (padding + i);
}

static int	char_s(void *data, t_flags *flags)
{
	int		i;
	int		length;
	int		max_chars;
	int		padding;
	char	*s;

	i = -1;
	padding = 0;
	s = data ? (char *)data : "(null)";
	length = ft_strlen(s);
	if (is_flag_enabled('.', flags) && flags->precision < length)
		length = flags->precision;
	max_chars = flags && is_flag_enabled('.', flags) ?
		flags->precision : length;
	if (flags && flags->width_specifier > 0)
		padding = enforce_width_specifier(
				get_padding_char(flags), flags->width_specifier - length);
	while (s[++i] && i < max_chars)
		write(1, &s[i], sizeof(char));
	if (flags && flags->width_specifier < 0 &&
			i < ABS(flags->width_specifier))
		i += enforce_width_specifier(' ',
				ABS(flags->width_specifier) - i - 1);
	return (padding + i);
}

int			s(t_flags *flags, void *data)
{
	int		chars_printed;

	chars_printed = 0;
	if (is_flag_enabled('-', flags) && flags->width_specifier > 0)
		flags->width_specifier *= -1;
	if (is_flag_enabled('l', flags))
		chars_printed += wchar_t_s(data, flags);
	else
		chars_printed += char_s(data, flags);
	return (chars_printed);
}
