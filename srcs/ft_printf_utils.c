/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alopez-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 00:05:23 by alopez-g          #+#    #+#             */
/*   Updated: 2020/07/28 04:53:51 by alopez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "Libft/includes/libft.h"

/*
** Function: process_in
** ---------------------
** Reads input string (only if % was found) and apply format depending on mod
**
** const char *pos: input string
** t_info *si:      info structure
** t_flags *sf:     flag structure
*/

void	process_in(const char *pos, t_info *si, t_flags *sf)
{
	char	mod;

	mod = mod_finder(pos, si);
	init_flags_struct(sf);
	if (mod)
		check_flag_struct(pos, si, sf);
	if (mod == 'c')
		apply_c_flags(si, sf, va_arg(si->ap, int));
	else if (mod == 's')
		apply_s_flags(si, sf, va_arg(si->ap, char*));
	else if (mod == 'd' || mod == 'i')
		apply_d_flags(si, sf, ft_itoa(va_arg(si->ap, int)));
	else if (mod == 'u')
		apply_u_flags(si, sf,
		ft_uitoa((unsigned int)va_arg(si->ap, unsigned int)));
	else if (mod == 'p')
		apply_p_flags(si, sf,
		ft_itoab(va_arg(si->ap, size_t), "0123456789abcdef"));
	else if (mod == 'x' || mod == 'X')
		apply_d_flags(si, sf, ft_itoab(va_arg(si->ap, size_t),
		mod == 'x' ? "0123456789abcdef" : "0123456789ABCDEF"));
	else if (mod == '%')
		apply_perc(pos, si, sf);
}

/*
** Function: mod_finder
** ---------------------
** Look for the moddifier currently being used, also fills using *
**
** const char *pos: input string
** t_info *si:      info structure
** t_flags *sf:     flag structure
**
** returns:         char of found modifier
*/

char	mod_finder(const char *pos, t_info *si)
{
	int	aux;

	aux = 0;
	while (ft_strchr(si->flags, *(pos + aux)) && *(pos + aux) != 0)
		aux++;
	if (ft_strchr(si->mods, *(pos + aux)) && *(pos + aux) != 0)
		return (*(pos + aux));
	return (0);
}
