/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:48:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/01 12:26:27 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_vdprintf(int fd, const char *s, va_list ap)
{
	int		i;
	int		ret;
	char	*str;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			str = va_arg(ap, char *);
			ret += write(fd, str, ft_strlen(str));
			i++;
		}
		else
			ret += write(fd, &s[i], 1);
		i++;
	}
	return (ret);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, s);
	ret = ft_vdprintf(fd, s, ap);
	va_end(ap);
	return (ret);
}
