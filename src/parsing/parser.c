/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:45:36 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 13:09:27 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cmd_path(void)
{
	t_proc	*tmp;

	tmp = g_data.head;
	while (tmp)
	{
		if (!tmp->args)
			tmp->cmd = ft_strdup("");
		else
			tmp->cmd = absolute_path(tmp->args[0]);
		tmp = tmp->next;
	}
}

char	*del_quote(char *str)
{
	char	*buffer;
	char	quote;
	int		i;

	i = 0;
	buffer = NULL;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
		{
			quote = str[i++];
			while (str[i] != quote)
				buffer = str_concate(buffer, str[i++]);
			i++;
		}
		if (str[i] && str[i] != SINGLE_QUOTE && str[i] != DOUBLE_QUOTE)
			buffer = str_concate(buffer, str[i++]);
	}
	if (!buffer)
		buffer = ft_strdup("");
	free(str);
	return (buffer);
}

void	quote_expand(t_proc *proc)
{
	int		i;

	i = 0;
	while (proc->args && proc->args[i])
	{
		proc->args[i] = expand(proc->args[i], 1);
		if (ft_strchr(proc->args[i], '\'') || ft_strchr(proc->args[i], '"'))
			proc->args[i] = del_quote(proc->args[i]);
		i++;
	}
}

void	parser(char **lx)
{
	t_proc	*tmp;

	init_list(lx);
	init_rd();
	tmp = g_data.head;
	while (tmp)
	{
		wildcard(tmp);
		quote_expand(tmp);
		tmp = tmp->next;
	}
	get_cmd_path();
}
