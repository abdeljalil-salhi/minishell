/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_piped.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:54:22 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/03 03:04:05 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin_pipe(t_proc *proc, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		exec_piped(proc, _pipe, prev_pipe);
	else if (pid > 0)
		wait_for_child(pid, _pipe, prev_pipe, &status);
	else
		ft_dprintf(2, FAIL_FORK, strerror(errno));
	return (exit_status(status));
}

void	exec_piped(t_proc *proc, int _pipe[2], int prev_pipe[2])
{
	t_redir	*current;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (proc->previous && proc->previous->separator == PIPE_TOKEN)
		dup_and_close(prev_pipe[0], STDIN_FILENO);
	if (proc->separator == PIPE_TOKEN)
		dup_and_close(_pipe[1], STDOUT_FILENO);
	current = proc->head;
	while (current)
	{
		dup_or_error(current);
		current = current->next;
	}
	exit(exec_builtin(proc->cmd, proc->args));
}
