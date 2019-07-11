/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imttoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:47:21 by dcelojev          #+#    #+#             */
/*   Updated: 2019/06/08 15:59:36 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	imttoa_base_get_length(intmax_t n, int base)
{
	size_t		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_imttoa_base(intmax_t n, int base, int capitalize)
{
	const char	*digits = "0123456789abcdef";
	size_t		length;
	char		*data;
	int			negative;

	length = imttoa_base_get_length(n, base);
	negative = n < 0;
	if ((n < 0 && base != 10) || !(data = ft_strnew(length += negative)))
		return (NULL);
	if (negative)
		n *= -1;
	data[0] = negative ? '-' : '0';
	while (n > 0)
	{
		data[--length] = capitalize ?
			ft_toupper(digits[n % base]) : digits[n % base];
		n /= base;
	}
	return (data);
}
