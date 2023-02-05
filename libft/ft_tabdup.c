/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:23:38 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/05 00:40:56 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabdup(char **tab)
{
	char	**dup;
	int		i;

	dup = malloc(sizeof(char *) * (ft_tabsize(tab) + 1));
	if (!dup)
		exit(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
