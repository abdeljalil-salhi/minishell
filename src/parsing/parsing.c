/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/26 22:48:05 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**clean_parenthese(char **ps)
{
	(void)ps;
	return (NULL);
}

void	parsing(char *input)
{
	char	**ps;

	g_data.errors = 0;
	ps = lexer(input);
 	// ps = clean_parenthese(ps);
	// unneccesery parenthese and doubled parenthese(maybe should exit as syntax error)
	if (syntax_error(ps))
	{
		g_data.errors = 1;
		free(input);
		ft_freearr(ps);
		return ;
	}
	parser(ps);
	ft_freearr(ps);
	free(input);
}
