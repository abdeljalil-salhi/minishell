/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_concate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:09:19 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/14 15:06:49 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_concate(char *s, char c)
{
	char	*str;
	int		i;

	if (!s)
		s = ft_strdup("");
	str = malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i++] = c;
	str[i] = '\0';
	free(s);
	return (str);
}
