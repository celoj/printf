/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:11:45 by dcelojev          #+#    #+#             */
/*   Updated: 2019/07/09 14:57:04 by dcelojev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Frees passed (non-NULL) parameters.
*/

t_flags				*printf_free(t_flags *flags)
{
	if (flags)
	{
		if (flags->key_flags)
		{
			free(flags->key_flags);
		}
		if (flags->global_flags)
		{
			free(flags->global_flags);
		}
		free(flags);
	}
	return (NULL);
}
