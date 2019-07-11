/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:38:48 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 00:32:10 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*check_infinity(long double f, int capitalize)
{
	if (f == INFINITY)
		return (ft_strdup(capitalize ? "INF" : "inf"));
	else if (f == -INFINITY)
		return (ft_strdup(capitalize ? "-INF" : "-inf"));
	return (NULL);
}

static long double	ft_round(long double f, int precision)
{
	long double		r;

	r = 1;
	while (precision--)
		r /= 10;
	return (f + (5 * r));
}

static void			write_int(long double f, char *data, int *i)
{
	long double	int_pos;
	long double	n;

	int_pos = 1;
	n = f;
	while ((long long)(n /= 10) != 0)
		int_pos *= 10;
	while (int_pos >= 1)
	{
		data[++(*i)] = (long long)(f / int_pos) + '0';
		f -= int_pos * (long long)(f / int_pos);
		int_pos /= 10;
	}
}

static void			write_float(long double f, char *data, int *i,
		unsigned int precision)
{
	data[++(*i)] = '.';
	while (precision)
	{
		f = (f - (long long)f) * 10;
		data[++(*i)] = (long long)f + '0';
		precision--;
	}
}

char				*ft_ldtoa(long double f, unsigned int precision,
		int capitalize)
{
	char		*data;
	int			i;
	int			size;

	data = f != f ? ft_strdup("nan") : check_infinity(f, capitalize);
	if (data)
		return (data);
	size = 1000;
	if (!(data = ft_strnew(size)))
		return (NULL);
	ft_bzero(data, size);
	i = -1;
	if (f < 0)
	{
		data[++i] = '-';
		f *= -1;
	}
	f = ft_round(f, precision + 1);
	write_int(f, data, &i);
	if (precision != 0)
		write_float(f, data, &i, precision);
	data[++i] = '\0';
	return (data);
}
