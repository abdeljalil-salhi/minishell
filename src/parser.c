/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:45:36 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 18:34:46 by mtellami         ###   ########.fr       */
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

void	init_list(char **lx, t_data *data)
{
	t_proc	*node;
	char	**buffer;
	int		lvl;
	int	i;

	lvl = 0;
	i = 0;
	data->head = NULL;
	while (lx[i])
	{
		while (lx[i] && !ft_strcmp(lx[i], "("))
		{
			lvl++;
			i++;
		}
		buffer = NULL;
		while (lx[i] && (ft_strcmp(lx[i], ")") && ft_strcmp(lx[i], "&&")
			&& ft_strcmp(lx[i], "|") && ft_strcmp(lx[i], "||")))
			buffer = arr_concate(buffer, lx[i++]);
		node = pc_new_node(buffer, get_separator(lx, i), lvl);
		pc_addback(&data->head, node);
		while (lx[i] && !ft_strcmp(lx[i], ")"))
		{
			lvl--;
			i++;
		}
		if (lx[i])
			i++;
	}
}

int	is_arrow(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (!ft_strcmp(str, "<"))
		return (INPUT);
	else if (!ft_strcmp(str, "<<"))
		return (APPEND);
	return (-1);
}

int	check_redir(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_arrow(args[i]) != -1)
			return (1);
		i++;
	}
	return (0);
}

void	init_rd(t_data *data)
{
	t_proc	*tmp;
	t_redir	*node;
	int		i;
	char	**buffer;

	tmp = data->head;
	while (tmp)
	{
		buffer = NULL;
		if (check_redir(tmp->args))
		{
			i = 0;
			while (tmp->args[i])
			{
				if (is_arrow(tmp->args[i]) != -1)
				{
					node = rd_new_node(tmp->args[i + 1], is_arrow(tmp->args[i]));
					rd_addback(&tmp->head, node);
					i++;
				}
				else
					buffer = arr_concate(buffer, tmp->args[i]);
				i++;
			}
			ft_freearr(tmp->args);
			tmp->args = buffer;
		}
		else
			tmp->head = NULL;
		tmp = tmp->next;
	}
}

void	open_files(t_data *data)
{
	t_proc	*tmp1;
	t_redir	*tmp2;

	tmp1 = data->head;
	while (tmp1)
	{
		tmp2 = tmp1->head;
		while (tmp2)
		{
			if (tmp2->type == INPUT)
				tmp2->fd = open(tmp2->file, O_RDONLY);
			else if (tmp2->type == OUTPUT)
				tmp2->fd = open(tmp2->file, O_WRONLY);
			else if (tmp2->type == APPEND)
				tmp2->fd = open(tmp2->file, O_WRONLY);
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

void	get_cmd_path(t_data *data)
{
	t_proc	*tmp;

	tmp = data->head;
	while (tmp)
	{
		if (!tmp->args)
			tmp->cmd = ft_strdup("");
		else
			tmp->cmd = absolute_path(tmp->args[0], data->env);
		tmp = tmp->next;
	}
}

char	*del_in_quote(char *str)
{
	int		i;
	char	quote;
	char	*s;

	i = 0;
	s = NULL;
	while (str[i])
	{
		if (str[i] != SINGLE_QUOTE && str[i] != DOUBLE_QUOTE)
			s = str_concate(s, str[i++]);
		else
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				s = str_concate(s, str[i++]);
			i++;
		}
	}
	free(str);
	return (s);
}

void	quote_expand(t_proc *proc, char **env)
{
	char	*ptr;
	int		i;

	i = 0;
	while (proc->args && proc->args[i])
	{
		if (proc->args[i][0] != SINGLE_QUOTE)
			proc->args[i] = expand(proc->args[i], env);
		if (proc->args[i][0] == SINGLE_QUOTE
			|| proc->args[i][0] == DOUBLE_QUOTE)
		{
			ptr = proc->args[i];
			proc->args[i] = ft_substr(proc->args[i], 1,
					ft_strlen(proc->args[i]) - 2);
			free(ptr);
		}
		if (proc->args[i][0] != SINGLE_QUOTE
			&& proc->args[i][0] != DOUBLE_QUOTE)
		proc->args[i] = del_in_quote(proc->args[i]);
		i++;
	}
}

void	parser(char **lx, t_data *data)
{
	t_proc	*tmp;

	init_list(lx, data);
	init_rd(data);
	get_cmd_path(data);
	open_files(data);
	tmp = data->head;
	while (tmp)
	{
		quote_expand(tmp, data->env);
		tmp = tmp->next;
	}
}
