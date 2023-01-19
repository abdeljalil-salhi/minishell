/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/19 15:23:46 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(char *input, t_data *data)
{
	char	**ps;

	data->errors = 0;
	ps = lexer(input);
	if (syntax_error(ps))
	{
		data->errors = 1;
		free(input);
		ft_freearr(ps);
		return ;
	}
	parser(ps, data);
	ft_freearr(ps);
	free(input);
}
