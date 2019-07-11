/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uintmax_t.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:24:27 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/30 15:29:39 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_uintmax_t(uintmax_t n)
{
	char	d;
	int		chars_printed;

	chars_printed = 0;
	if (n >= 10)
	{
		chars_printed += ft_putnbr_uintmax_t(n / 10);
		chars_printed += ft_putnbr_uintmax_t(n % 10);
	}
	else if (n < 10)
	{
		d = n + '0';
		write(1, &d, 1);
		return (1);
	}
	return (chars_printed);
}
