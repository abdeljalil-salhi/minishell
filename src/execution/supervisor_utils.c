/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 21:06:19 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/03 04:36:23 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_inspector_and_exec(t_proc *proc, int prev_pipe[2], int _pipe[2],
		int i)
{
	if (i % 2)
	{
		if (pipe(prev_pipe) == -1)
		{
			ft_dprintf(STDERR_FILENO, FAIL_PIPE, strerror(errno));
			exit(EXIT_FAILURE);
		}
		g_data.exit_status = executor(proc, prev_pipe, _pipe);
	}
	else
	{
		if (pipe(_pipe) == -1)
		{
			ft_dprintf(STDERR_FILENO, FAIL_PIPE, strerror(errno));
			exit(EXIT_FAILURE);
		}
		g_data.exit_status = executor(proc, _pipe, prev_pipe);
	}
}

int	priority_condition(t_proc *proc, int level, int token)
{
	if (token == AND_TOKEN)
		return (proc && (proc->separator == AND_TOKEN
				|| proc->separator == PIPE_TOKEN) && proc->level >= level);
	else if (token == OR_TOKEN)
		return (proc && ((proc->separator == OR_TOKEN
					|| proc->separator == PIPE_TOKEN)
				|| (proc->separator == AND_TOKEN
					&& proc->level > level)) && proc->level >= level);
	return (EXIT_SUCCESS);
}

void	apply_priorities(t_proc **proc, int *level)
{
	if (g_data.exit_status && (*proc)->separator == AND_TOKEN)
	{
		*level = (*proc)->level;
		while (priority_condition(*proc, *level, AND_TOKEN))
			*proc = (*proc)->next;
	}
	else if (g_data.exit_status == 0 && (*proc)->separator == OR_TOKEN)
	{
		*level = (*proc)->level;
		while (priority_condition(*proc, *level, OR_TOKEN))
		{
			if ((*proc)->separator == AND_TOKEN)
				*level = (*proc)->level;
			*proc = (*proc)->next;
		}
	}
}

int	heredoc_and_errors(t_redir **redir, int *status, pid_t *pid)
{
	*pid = fork();
	if (*pid == 0)
		exec_heredoc(*redir);
	else if (*pid > 0)
	{
		if (handle_heredoc(*pid, status))
			return (EXIT_FAILURE);
	}
	else
		ft_dprintf(STDERR_FILENO, FAIL_FORK, strerror(errno));
	return (EXIT_SUCCESS);
}

void	look_for_cmd_not_found(void)
{
	t_proc	*current;

	current = g_data.head;
	while (current)
	{
		if (!current->cmd && !(current->head && current->head->type == INPUT)
			&& !current->error)
		{
			if (ft_strchr(current->args[0], '/'))
				ft_dprintf(2, ERR_NO_SUCH_FILE, current->args[0]);
			else if (!is_path())
				ft_dprintf(2, ERR_NO_SUCH_FILE, current->args[0]);
			else
				ft_dprintf(2, ERR_CMD_NOT_FOUND, current->args[0]);
		}
		current = current->next;
	}
}
