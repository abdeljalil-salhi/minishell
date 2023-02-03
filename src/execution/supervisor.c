/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:38:16 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/03 03:54:54 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_proc *proc, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;

	if (!proc->cmd)
	{
		close(_pipe[1]);
		close(prev_pipe[0]);
		return (127);
	}
	if (proc->cmd[0] == '\0')
		return (exec_empty_cmd(proc));
	if (is_builtin(proc->cmd))
		return (exec_builtin_cmd(proc, _pipe, prev_pipe));
	status = 0;
	pid = fork();
	if (pid == 0)
		exec_cmd(proc, _pipe, prev_pipe);
	else if (pid > 0)
		wait_for_child(pid, _pipe, prev_pipe, &status);
	else
		ft_dprintf(2, FAIL_FORK, strerror(errno));
	return (exit_status(status));
}

typedef struct s_inspector
{
	t_proc	*current;
	int		_pipe[2];
	int		prev_pipe[2];
	int		i;
	int		level;
}	t_inspector;

void	inspector(void)
{
	t_inspector	s;

	look_for_cmd_not_found();
	s.i = -1;
	s.current = g_data.head;
	while (s.current)
	{
		check_if_dots(&s.current);
		check_if_directory(&s.current);
		init_inspector_and_exec(s.current, s._pipe, s.prev_pipe, s.i);
		apply_priorities(&s.current, &s.level);
		s.i++;
		if (s.current->separator != PIPE_TOKEN)
			s.i = -1;
		s.current = s.current->next;
	}
	close(s._pipe[0]);
	close(s._pipe[1]);
	close(s.prev_pipe[0]);
	close(s.prev_pipe[1]);
	close_heredocs();
}

typedef struct s_supervisor
{
	t_proc	*cr;
	t_redir	*rd;
	pid_t	pid;
	int		status;
}	t_supervisor;

void	supervisor(void)
{
	t_supervisor	s;

	s.cr = g_data.head;
	while (s.cr)
	{
		if (s.cr->head)
		{
			s.rd = s.cr->head;
			while (s.rd)
			{
				if (s.rd->type == HEREDOC
					&& heredoc_and_errors(&s.rd, &s.status, &s.pid))
					return ;
				else if (s.rd->type == INPUT && (!s.cr->cmd || !(*s.cr->cmd))
					&& !s.cr->error && access(s.rd->file, F_OK) == -1)
				{
					s.cr->error = 1;
					ft_dprintf(2, CUSTOM, s.rd->file, strerror(errno));
				}
				s.rd = s.rd->next;
			}
		}
		s.cr = s.cr->next;
	}
	inspector();
}
