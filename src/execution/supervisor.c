/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:38:16 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/28 14:15:43 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_proc *proc, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;
	int		pipe_stdout = dup(1);
	int		pipe_stdin = dup(0);

	if (!proc->cmd)
		return (127);
	if (is_builtin(proc->cmd))
	{
		if (proc->previous && proc->previous->separator == PIPE_TOKEN)
		{
			dup2(prev_pipe[0], 0);
			close(prev_pipe[0]);
		}
		if (proc->separator == PIPE_TOKEN)
		{
			dup2(_pipe[1], 1);
			close(_pipe[1]);
		}
		status = exec_builtin(proc->cmd, proc->args);
		dup2(pipe_stdout, 1);
		close(pipe_stdout);
		dup2(pipe_stdin, 0);
		close(pipe_stdin);
		return (status);
	}
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (proc->previous && proc->previous->separator == PIPE_TOKEN)
		{
			dup2(prev_pipe[0], 0);
			close(prev_pipe[0]);
		}
		if (proc->separator == PIPE_TOKEN)
		{
			dup2(_pipe[1], 1);
			close(_pipe[1]);
		}
		if (execve(proc->cmd, proc->args, g_data.env) == -1)
		{
			printf("errno %d\n", (*__error()));
			printf("Error: command not found or failed to execute\n");
			printf("   ~ path: %s\n", proc->cmd);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		close(_pipe[1]);
		close(prev_pipe[0]);
		waitpid(pid, &status, 0);
	}
	else
		printf("   ~ fork failed\n");
	return (exit_status(status));
}

void	supervisor(void)
{
	t_proc	*current;
	int		_pipe[2];
	int		prev_pipe[2];
	int		i;

	current = g_data.head;
	while (current)
	{
		if (!current->cmd)
			printf("minishell: %s: command not found\n", current->args[0]);
		current = current->next;
	}
	i = -1;
	current = g_data.head;
	while (current)
	{
		if (DEBUG)
		{
			printf("   ~ current->cmd = %s\n", current->cmd);
			printf("   ~ current->separator = %d\n", current->separator);
			printf("   ~ current->level = %d\n", current->level);
			printf("   ~ current->next = %p\n", current->next);
		}
		pipe(i % 2 ? prev_pipe : _pipe);
		g_data.exit_status = executor(current, i % 2 ? prev_pipe : _pipe, i % 2 ? _pipe : prev_pipe);
		current = current->next;
		i++;
	}
	close(_pipe[0]), close(_pipe[1]);
	close(prev_pipe[0]), close(prev_pipe[1]);
}
