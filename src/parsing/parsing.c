/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/23 17:02:45 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**clean_parenthese(char **ps)
{
	(void)ps;
	return (NULL);
}

void	parsing(char *input, t_data *data)
{
	char	**ps;

	data->errors = 0;
	ps = lexer(input);
 	// ps = clean_parenthese(ps);
	// unneccesery parenthese and doubled parenthese(maybe should exit as syntax error)
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
