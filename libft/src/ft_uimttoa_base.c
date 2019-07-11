/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimttoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:47:21 by dcelojev          #+#    #+#             */
/*   Updated: 2019/06/08 16:27:07 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	uimttoa_base_get_length(uintmax_t n, int base)
{
	size_t		i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*ft_uimttoa_base(uintmax_t n, int base, int capitalize)
{
	const char	*digits = "0123456789abcdef";
	size_t		length;
	char		*data;

	length = uimttoa_base_get_length(n, base);
	if (!(data = ft_strnew(length)))
		return (NULL);
	data[0] = '0';
	while (n > 0)
	{
		data[--length] = capitalize ?
			ft_toupper(digits[n % base]) : digits[n % base];
		n /= base;
	}
	return (data);
}
