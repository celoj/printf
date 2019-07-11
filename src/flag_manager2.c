/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_manager2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:38:47 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:47:19 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					enforce_width_specifier(char c, int n)
{
	int				i;

	i = -1;
	while (++i < n)
		write(1, &c, 1);
	return (n < 0 ? 0 : n);
}

int					initialize_flags(t_flags *flags)
{
	int				size;

	size = ft_strlen(VALID_CONV_FLAGS) * sizeof(int);
	if (!(flags->key_flags = (int *)malloc(size)))
		return (0);
	ft_bzero(flags->key_flags, size);
	size = ft_strlen(GLOBAL_FLAGS) * sizeof(int);
	if (!(flags->global_flags = (int *)malloc(size)))
		return (0);
	ft_bzero(flags->global_flags, size);
	return (1);
}

int					read_precision(t_flags *flags,
		const char *format, int i)
{
	int				j;

	j = 1;
	check_flag(flags, '.');
	flags->precision = 0;
	while (ft_isdigit(format[i + j]))
	{
		flags->precision = flags->precision * 10
			+ (format[i + j] - '0');
		j++;
	}
	return (j);
}
