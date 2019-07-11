/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:34:06 by dcelojev          #+#    #+#             */
/*   Updated: 2019/06/06 15:51:59 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printbits(void *data, size_t size)
{
	char	*bytes;
	size_t	i;
	size_t	j;
	size_t	total;
	char	b[(size * 8) + 1];

	i = 0;
	total = size * 8;
	bytes = (char *)data;
	b[size] = 0;
	while (i < size)
	{
		j = 0;
		while (j < 8)
		{
			b[total--] = ((int)(bytes[i] >> j) & 1) + '0';
			j++;
		}
		i++;
	}
	i = 0;
	while (b[i])
		ft_putchar(b[i++]);
	ft_putchar('\n');
}
