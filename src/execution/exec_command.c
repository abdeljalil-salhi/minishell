/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:38:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/01 23:26:37 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_close(int fd, int new_fd)
{
	dup2(fd, new_fd);
	close(fd);
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
}

void	dup_or_error(t_redir *current)
{
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
	if (execve(proc->cmd, proc->args, g_data.env) == -1)
	{
		ft_dprintf(STDERR_FILENO, ERR_PERMISSION, proc->cmd);
		exit(126);
	}
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
