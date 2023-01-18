/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_concate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:16:17 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/14 15:00:45 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_concate(char **tab, char *str)
{
	char	**arr;
	int		i;

	if (!tab)
	{
		tab = malloc(sizeof(char *));
		tab[0] = NULL;
	}
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
