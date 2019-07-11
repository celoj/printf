/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 23:34:45 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 15:13:05 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char			*g_flag_map[FLAG_MAP_SIZE][2] =
{
	{"s", "l"},
	{"c", "l"},
	{"d", "lhjzt"},
	{"D", "lhjzt"},
	{"i", "lhjzt"},
	{"u", "lhjzt"},
	{"U", "lhjzt"},
	{"x", "lhjzt"},
	{"X", "lhjzt"},
	{"o", "lhjzt"},
	{"f", "L"},
	{"F", "L"}
};

void				check_flag(t_flags *flags, char flag)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (VALID_CONV_FLAGS[i] || GLOBAL_FLAGS[j])
	{
		if (VALID_CONV_FLAGS[i])
		{
			if (flag == VALID_CONV_FLAGS[i])
			{
				flags->key_flags[i] += 1;
			}
			i++;
		}
		if (GLOBAL_FLAGS[j])
		{
			if (flag == GLOBAL_FLAGS[j])
			{
				flags->global_flags[j] += 1;
			}
			j++;
		}
	}
}

static int			read_width_specifier(t_flags *flags,
		const char *format, int i)
{
	int				j;

	j = 0;
	flags->width_specifier = 0;
	while (ft_isdigit(format[i + j]))
	{
		flags->width_specifier = flags->width_specifier * 10
			+ (format[i + j] - '0');
		j++;
	}
	if (i > 0 && format[i - 1] == '-')
		flags->width_specifier *= -1;
	return (j);
}

static int			get_key_flags(t_flags *flags, const char *format,
		int i, int key_length)
{
	int				j;
	int				reading_number;

	j = 0;
	reading_number = 0;
	if (!initialize_flags(flags))
		return (0);
	while (++j < key_length)
	{
		if (format[i + j] == '.')
			j += read_precision(flags, format, i + j) - 1;
		else if (format[i + j] > '0' && format[i + j] <= '9')
			j += read_width_specifier(flags, format, i + j) - 1;
		else
			check_flag(flags, format[i + j]);
	}
	return (1);
}

int					is_flag_enabled(char flag, t_flags *flags)
{
	int				i;

	if (flags)
	{
		i = -1;
		while (GLOBAL_FLAGS[++i])
			if (GLOBAL_FLAGS[i] == flag
					&& flags->global_flags[i] > 0)
				return (1);
		i = -1;
		while (VALID_CONV_FLAGS[++i])
			if (VALID_CONV_FLAGS[i] == flag
					&& flags->key_flags[i] > 0)
				return (1);
	}
	return (0);
}

t_flags				*get_flags_for_key(const char *format, int i,
		char key, int key_length)
{
	int				j;
	int				flag_map_index;
	t_flags			*flags;

	j = -1;
	flag_map_index = -1;
	flags = NULL;
	if (!(flags = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	flags->key_flags = NULL;
	flags->global_flags = NULL;
	flags->key = key;
	flags->width_specifier = 0;
	flags->precision = key == 'f' ? 6 : 0;
	while (flag_map_index == -1 && ++j < FLAG_MAP_SIZE)
		if (g_flag_map[j][0][0] == key)
			flag_map_index = j;
	if (!get_key_flags(flags, format, i, key_length))
		return (printf_free(flags));
	return (flags);
}
