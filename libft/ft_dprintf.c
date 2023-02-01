/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 23:48:33 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/01 23:25:19 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		ret;
	char	c;

	ret = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		ret += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ret += ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	ret += write(fd, &c, 1);
	return (ret);
}

int	ft_putstr_fd(char *s, int fd)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (s[++i])
		ret += write(fd, &s[i], 1);
	return (ret);
}

int	ft_vdprintf(int fd, const char *s, va_list ap)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 'd')
				ret += ft_putnbr_fd(va_arg(ap, int), fd);
			else if (s[i] == 's')
				ret += ft_putstr_fd(va_arg(ap, char *), fd);
			else if (s[i] == '%')
				ret += write(fd, "%", 1);
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
