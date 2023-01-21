/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/21 02:47:03 by mtellami         ###   ########.fr       */
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
	t_proc	*tmp = data->head;
	while (tmp)
	{
		for(int i =0;tmp->args[i];i++)
			printf("%s\n", tmp->args[i]);
		tmp = tmp->next;
	}
	ft_freearr(ps);
	free(input);
}
