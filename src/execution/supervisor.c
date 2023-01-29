/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:38:16 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/29 12:48:50 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_proc *proc, int level, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;
	t_redir	*current;
	int		pipe_stdout = dup(1);
	int		pipe_stdin = dup(0);

	(void) level;
	if (!proc->cmd)
		return (127);
	if (proc->cmd[0] == '\0')
		return (0);
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
		current = proc->head;
		while (current)
		{
			if (current->fd == -1)
			{
				dup2(STDERR_FILENO, STDOUT_FILENO);
				printf("minishell: %s: Permission denied\n", current->file);
				dup2(STDOUT_FILENO, STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (current->fd == -2)
			{
				dup2(STDERR_FILENO, STDOUT_FILENO);
				printf("minishell: %s: No such file or directory\n", current->file);
				dup2(STDOUT_FILENO, STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (current->type == INPUT)
			{
				dup2(current->fd, 0);
				close(current->fd);
			}
			else if (current->type == OUTPUT || current->type == APPEND)
			{
				dup2(current->fd, 1);
				close(current->fd);
			}
			else if (current->type == HEREDOC)
			{
				current->fd = open(HERE_DOC, O_RDONLY, 0644);
				dup2(current->fd, 0);
				close(current->fd);
			}
			current = current->next;
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
		current = proc->head;
		while (current)
		{
			if (current->fd == -1)
			{
				dup2(STDERR_FILENO, STDOUT_FILENO);
				printf("minishell: %s: Permission denied\n", current->file);
				exit(EXIT_FAILURE);
			}
			if (current->fd == -2)
			{
				dup2(STDERR_FILENO, STDOUT_FILENO);
				printf("minishell: %s: No such file or directory\n", current->file);
				exit(EXIT_FAILURE);
			}
			if (current->type == INPUT)
			{
				dup2(current->fd, 0);
				close(current->fd);
			}
			else if (current->type == OUTPUT || current->type == APPEND)
			{
				dup2(current->fd, 1);
				close(current->fd);
			}
			else if (current->type == HEREDOC)
			{
				current->fd = open(HERE_DOC, O_RDONLY, 0644);
				dup2(current->fd, 0);
				close(current->fd);
			}
			current = current->next;
		}
		if (execve(proc->cmd, proc->args, g_data.env) == -1)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: %s: Permission denied\n", proc->cmd);
			exit(126);
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

void	inspector(void)
{
	t_proc	*current;
	int		_pipe[2];
	int		prev_pipe[2];
	int		i;

	i = -1;
	current = g_data.head;
	while (current)
	{
		pipe(i % 2 ? prev_pipe : _pipe);
		g_data.exit_status = executor(current, current->level,
				i % 2 ? prev_pipe : _pipe, i % 2 ? _pipe : prev_pipe);
		current = current->next;
		i++;
	}
	close(_pipe[0]), close(_pipe[1]);
	close(prev_pipe[0]), close(prev_pipe[1]);
}

void	supervisor(void)
{
	t_proc	*current;
	t_redir	*redir;
	int		i;

	current = g_data.head;
	while (current)
	{
		if (current->head)
		{
			redir = current->head;
			while (redir)
			{
				if (redir->type == HEREDOC)
					exec_heredoc(redir);
				redir = redir->next;
			}
		}
		current = current->next;
	}
	current = g_data.head;
	while (current)
	{
		if (!current->cmd)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: %s: command not found\n", current->args[0]);
			dup2(STDOUT_FILENO, STDERR_FILENO);
		}
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
		// pipe(i % 2 ? prev_pipe : _pipe);
		// g_data.exit_status = executor(current, current->level,
		// 		i % 2 ? prev_pipe : _pipe, i % 2 ? _pipe : prev_pipe);
		current = current->next;
		i++;
	}
	inspector();
	
	// refactor this later v
	int		res;
	char	*line;
	
	current = g_data.head;
	while (current)
	{
		redir = current->head;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				res = read(redir->fd, &line, 0);
				if (!(res < 0 && errno == EBADF))
					close(redir->fd);
			}
			redir = redir->next;
		}
		current = current->next;
	}
}
