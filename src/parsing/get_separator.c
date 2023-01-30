/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_separator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 06:35:56 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 06:36:16 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_separator(char **lx, int i)
{
	int	sep;

	sep = -1;
	if (!lx[i])
		sep = LAST_CMD;
	else if (!ft_strcmp(lx[i], "&&"))
		sep = AND_TOKEN;
	else if (!ft_strcmp(lx[i], "||"))
		sep = OR_TOKEN;
	else if (!ft_strcmp(lx[i], "|"))
		sep = PIPE_TOKEN;
	else
	{
		while (lx[i] && !ft_strcmp(lx[i], ")"))
			i++;
		sep = get_separator(lx, i);
	}
	return (sep);
}
