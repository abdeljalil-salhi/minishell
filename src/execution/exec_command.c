/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:38:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/05 02:06:28 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
}

int	exec_empty_cmd(t_proc *proc)
{
	t_redir	*current;

	current = proc->head;
	while (current)
	{
		init_redirections(&current);
		if (current->fd == -1)
			return (ft_dprintf(2, ERR_PERMISSION, current->file),
				EXIT_FAILURE);
		if (current->fd == -2)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

void	dup_or_error(t_redir *current)
{
	init_redirections(&current);
	if (current->fd == -1)
	{
		ft_dprintf(STDERR_FILENO, ERR_PERMISSION, current->file);
		exit(EXIT_FAILURE);
	}
	if (current->fd == -2)
	{
		ft_dprintf(STDERR_FILENO, ERR_NO_SUCH_FILE, current->file);
		exit(EXIT_FAILURE);
	}
	if (current->type == INPUT)
		dup_and_close(current->fd, STDIN_FILENO);
	else if (current->type == OUTPUT || current->type == APPEND)
		dup_and_close(current->fd, STDOUT_FILENO);
	else if (current->type == HEREDOC)
	{
		current->fd = open(HERE_DOC, O_RDONLY, 0644);
		dup_and_close(current->fd, STDIN_FILENO);
	}
}

void	exec_cmd(t_proc *proc, int _pipe[2], int prev_pipe[2])
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
	if (execve(proc->cmd, proc->args, g_data.env) == -1 && !proc->error)
	{
		ft_dprintf(STDERR_FILENO, CUSTOM, proc->cmd, strerror(errno));
		exit(126);
	}
	exit(g_data.exit_status);
}

void	wait_for_child(pid_t pid, int _pipe[2], int prev_pipe[2], int *status)
{
	close(_pipe[1]);
	close(prev_pipe[0]);
	signal(SIGINT, SIG_IGN);
	if (waitpid(pid, status, 0) == -1)
	{
		ft_dprintf(STDERR_FILENO, FAIL_WAITPID, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGQUIT)
		ft_dprintf(STDERR_FILENO, "Quit: %d\n", WTERMSIG(*status));
	signal(SIGINT, sig_handler);
}
