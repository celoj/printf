/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:51:49 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:55:40 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			perform_function_for_key(char key, t_flags *flags, void *data)
{
	int				j;

	j = -1;
	while (++j < FUNC_MAP_SIZE)
	{
		if (((char *)g_func_map[j][0])[0] == key)
		{
			return
			((int (*)(t_flags *, void *))g_func_map[j][1])(flags, data);
		}
	}
	return (0);
}

int			is_key(char c)
{
	int		i;

	i = -1;
	while (++i < FUNC_MAP_SIZE)
	{
		if ((char)((char *)g_func_map[i][0])[0] == c)
		{
			return (1);
		}
	}
	return (0);
}

int			invalid_key_char(char c)
{
	int		i;

	i = -1;
	while (GLOBAL_FLAGS[++i])
		if (c == GLOBAL_FLAGS[i])
			return (0);
	i = -1;
	while (VALID_CONV_FLAGS[++i])
		if (c == VALID_CONV_FLAGS[i])
			return (0);
	return (!is_key(c) && !ft_isdigit(c));
}
