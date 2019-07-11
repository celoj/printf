/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pdttoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:47:21 by dcelojev          #+#    #+#             */
/*   Updated: 2019/06/09 00:31:37 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	pdttoa_base_get_length(ptrdiff_t n, int base)
{
	size_t		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_pdttoa_base(ptrdiff_t n, int base, int capitalize)
{
	const char	*digits = "0123456789abcdef";
	size_t		length;
	char		*data;
	int			negative;

	length = pdttoa_base_get_length(n, base);
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
