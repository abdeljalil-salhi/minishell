/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:34:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/03 10:35:14 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;

	if (!(*little))
		return ((char *)big);
	while (*big && len--)
	{
		i = 0;
		while (little[i] == big[i] && i <= len)
		{
			if (!little[i + 1])
				return ((char *)big);
			i++;
		}
		big++;
	}
	return (0);
}
