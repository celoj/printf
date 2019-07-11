/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 23:01:03 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:56:52 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					get_padding_char(t_flags *flags)
{
	if (!flags || !is_flag_enabled('0', flags))
		return (' ');
	return ('0');
}

int					enable_flag(char flag, t_flags *flags)
{
	int				i;

	if (flags)
	{
		i = -1;
		while (GLOBAL_FLAGS[++i])
			if (GLOBAL_FLAGS[i] == flag)
				return (flags->global_flags[i] += 1);
		i = -1;
		while (VALID_CONV_FLAGS[++i])
			if (VALID_CONV_FLAGS[i] == flag)
				return (flags->key_flags[i] += 1);
	}
	return (0);
}
