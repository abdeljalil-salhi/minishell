/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:45:36 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/29 08:32:51 by absalhi          ###   ########.fr       */
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

void	open_files(void)
{
	t_proc	*tmp1;
	t_redir	*tmp2;

	tmp1 = g_data.head;
	while (tmp1)
	{
		tmp2 = tmp1->head;
		while (tmp2)
		{
			if (tmp2->type == INPUT)
				tmp2->fd = open(tmp2->file, O_RDONLY, 0644);
			else if (tmp2->type == OUTPUT)
				tmp2->fd = open(tmp2->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (tmp2->type == APPEND)
				tmp2->fd = open(tmp2->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (tmp2->type == HEREDOC)
				tmp2->fd = -3;
			if (tmp2->fd == -1)
				if (access(tmp2->file, F_OK) == -1)
					tmp2->fd = -2;
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
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
		proc->args[i] = expand(proc->args[i]);
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
	get_cmd_path();
	open_files();
	tmp = g_data.head;
	while (tmp)
	{
		quote_expand(tmp);
		tmp = tmp->next;
	}
}
