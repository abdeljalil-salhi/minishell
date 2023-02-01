/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:16:17 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/01 21:21:56 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_special(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_' || c == '?');
}

char	**alloc_one(void)
{
	char	**buffer;

	buffer = malloc(sizeof(char *));
	*buffer = NULL;
	return (buffer);
}

void	buffer_reset(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
}

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

char	**arr_concate(char **tab, char *str)
{
	char	**arr;
	int		i;

	if (!tab)
		tab = alloc_one();
	arr = malloc(sizeof(char *) * (ft_tabsize(tab) + 2));
	if (!arr)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		arr[i] = ft_strdup(tab[i]);
		i++;
	}
	arr[i++] = ft_strdup(str);
	arr[i] = NULL;
	ft_freearr(tab);
	return (arr);
}
