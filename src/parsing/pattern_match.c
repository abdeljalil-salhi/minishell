/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 09:17:57 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 12:54:51 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incream(int *i, int *j)
{
	(*i)++;
	(*j)++;
}

void	reset_str_index(int i, int j, int *x, int *y)
{
	*x = i;
	*y = j;
}

void	reset_index(int *i, int *j, int x, int y)
{
	*j = x + 1;
	*i = y + 1;
}

int	pattern_match(char *filename, char *pattern, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!ft_strlen(filename))
		return (!ft_strlen(pattern));
	while (i < ft_strlen(filename))
	{
		if (j < ft_strlen(pattern) && filename[i] == pattern[j])
			incream(&i, &j);
		else if (j < ft_strlen(pattern) && pattern[j] == ASTERISK)
			reset_str_index(i, j++, &x, &y);
		else if (y != -1)
			reset_index(&i, &j, y, x++);
		else
			return (0);
	}
	while (j < ft_strlen(pattern) && pattern[j] == ASTERISK)
		j++;
	if (j == ft_strlen(pattern))
		return (1);
	return (0);
}
