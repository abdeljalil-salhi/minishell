/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/29 00:20:57 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input)
{
	char	**ps;

	g_data.errors = 0;
	ps = lexer(input);
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
