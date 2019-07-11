/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ull.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:04:22 by dcelojev          #+#    #+#             */
/*   Updated: 2019/05/30 15:11:29 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnbr_ull(unsigned long long n)
{
	char	d;
	int		chars_printed;

	chars_printed = 0;
	if (n >= 10)
	{
		chars_printed += ft_putnbr_ull(n / 10);
		chars_printed += ft_putnbr_ull(n % 10);
	}
	else if (n < 10)
	{
		d = n + '0';
		write(1, &d, 1);
		return (1);
	}
	return (chars_printed);
}
