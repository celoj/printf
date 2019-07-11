/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:47:21 by dcelojev          #+#    #+#             */
/*   Updated: 2019/06/13 19:33:56 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	stoa_base_get_length(short n, int base)
{
	size_t		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_stoa_base(short n, int base, int capitalize)
{
	const char	*digits = "0123456789abcdef";
	size_t		length;
	char		*data;
	int			negative;

	length = stoa_base_get_length(n, base);
	negative = n < 0;
	if ((n < 0 && base != 10) || !(data = ft_strnew(length += negative)))
		return (NULL);
	if (negative)
	{
		if (n == SHRT_MIN)
			data[--length] = '8';
		n = (n / (n == SHRT_MIN ? 10 : 1)) * -1;
	}
	data[0] = negative ? '-' : '0';
	while (n > 0)
	{
		data[--length] = capitalize ?
			ft_toupper(digits[n % base]) : digits[n % base];
		n /= base;
	}
	return (data);
}
