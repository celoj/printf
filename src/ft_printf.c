/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 13:57:15 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:56:28 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			get_key_length(const char *format, int i)
{
	int				length;

	length = 0;
	while (format[++i] && !invalid_key_char(format[i]))
	{
		if (is_key(format[i]))
			return (length + 1);
		length++;
	}
	return (length);
}

static int			verify_width(int chars_printed_for_key, int width)
{
	if (width < 0 && ABS(width) > chars_printed_for_key)
		return (enforce_width_specifier(' ', ABS(width
						+ chars_printed_for_key)));
	else
		return (0);
}

static int			decode(const char *format, int i, void *data,
		int *chars_printed)
{
	char			key;
	t_flags			*flags;
	int				key_length;
	int				chars_printed_for_key;

	flags = NULL;
	key_length = get_key_length(format, i);
	key = format[i + key_length];
	if (key_length > 1)
	{
		flags = get_flags_for_key(format, i, key, key_length);
		chars_printed_for_key = perform_function_for_key(key, flags, data);
		chars_printed_for_key += verify_width(
		chars_printed_for_key, flags->width_specifier *
		(is_flag_enabled('-', flags) &&
		flags->width_specifier > 0 ? -1 : 1));
		free(flags);
	}
	else
		chars_printed_for_key = perform_function_for_key(key, NULL, data);
	*chars_printed += chars_printed_for_key;
	return (key_length);
}

static int			decode_float(const char *format, int i,
		int *chars_printed, va_list args)
{
	t_flags			*flags;
	int				key_length;
	int				chars_printed_for_key;

	flags = NULL;
	key_length = get_key_length(format, i);
	if (key_length > 1)
	{
		flags = get_flags_for_key(format, i, 'f', key_length);
		chars_printed_for_key = (is_flag_enabled('L', flags)
				? lf(flags, va_arg(args, long double))
					: f(flags, va_arg(args, double)));
		chars_printed_for_key += verify_width(
				chars_printed_for_key, flags->width_specifier);
		free(flags);
	}
	else
		chars_printed_for_key = f(NULL, va_arg(args, double));
	*chars_printed += chars_printed_for_key;
	return (key_length);
}

int					ft_printf(const char *format, ...)
{
	int				i;
	int				chars_printed;
	va_list			args;
	int				key_length;

	i = -1;
	chars_printed = 0;
	va_start(args, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			key_length = get_key_length(format, i);
			if (format[i + key_length] == 'f')
				i += decode_float(format, i, &chars_printed, args);
			else
				i += decode(format, i, (format[i + key_length] == '%' ?
					(void *)'%' : va_arg(args, void *)), &chars_printed);
		}
		else
			chars_printed += write(1, &format[i], 1);
	}
	va_end(args);
	return (chars_printed);
}
