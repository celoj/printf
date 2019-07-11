/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_intmax_t.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:28:52 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/29 22:12:43 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_intmax_t(intmax_t n)
{
	char	d;
	int		chars_printed;

	chars_printed = 0;
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
		chars_printed += 1 + ft_putnbr_intmax_t(n);
	}
	else if (n >= 10)
	{
		chars_printed += ft_putnbr_intmax_t(n / 10);
		chars_printed += ft_putnbr_intmax_t(n % 10);
	}
	else if (n < 10)
	{
		d = n + '0';
		write(1, &d, 1);
		return (1);
	}
	return (chars_printed);
}
