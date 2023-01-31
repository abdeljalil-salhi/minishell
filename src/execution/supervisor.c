/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:38:16 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/31 04:58:38 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_proc *proc, int _pipe[2], int prev_pipe[2])
{
	pid_t	pid;
	int		status;
	t_redir	*current;
	int		pipe_stdout;
	int		pipe_stdin;

	pipe_stdin = dup(0);
	pipe_stdout = dup(1);
	if (!proc->cmd)
	{
		close(_pipe[1]);
		close(prev_pipe[0]);
		return (127);
	}
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sig_handler);
	}
	else
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("minishell: fork: %s\n", strerror(errno));
		dup2(STDOUT_FILENO, STDERR_FILENO);
	}
	return (exit_status(status));
}

void	inspector(void)
{
	t_proc	*current;
	int		_pipe[2];
	int		prev_pipe[2];
	int		i;
	int		level;

	i = -1;
	current = g_data.head;
	while (current)
	{
		if (i % 2)
		{
			pipe(prev_pipe);
			g_data.exit_status = executor(current, prev_pipe, _pipe);
		}
		else
		{
			pipe(_pipe);
			g_data.exit_status = executor(current, _pipe, prev_pipe);
		}
		if (g_data.exit_status && current->separator == AND_TOKEN)
		{
			level = current->level;
			while (current && (current->separator == AND_TOKEN
				|| current->separator == PIPE_TOKEN) && current->level >= level)
				current = current->next;
		}
		else if (g_data.exit_status == 0 && current->separator == OR_TOKEN)
		{
			level = current->level;
			while (current && ((current->separator == OR_TOKEN
				|| current->separator == PIPE_TOKEN) || (current->separator == AND_TOKEN
				&& current->level > level)) && current->level >= level)
			{
				if (current->separator == AND_TOKEN)
					level = current->level;
				current = current->next;
			}
		}
		i++;
		if (current->separator != PIPE_TOKEN)
			i = -1;
		current = current->next;
	}
	close(_pipe[0]), close(_pipe[1]);
	close(prev_pipe[0]), close(prev_pipe[1]);
}

void	supervisor(void)
{
	t_proc	*current;
	t_redir	*redir;

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
				else if (redir->type == INPUT && (!current->cmd || !(*current->cmd))
					&& !current->no_such_file)
				{
					current->no_such_file = 1;
					dup2(STDERR_FILENO, STDOUT_FILENO);
					printf("minishell: %s: No such file or directory\n", redir->file);
					dup2(STDOUT_FILENO, STDERR_FILENO);
				}
				redir = redir->next;
			}
		}
		current = current->next;
	}
	current = g_data.head;
	while (current)
	{
		if (!current->cmd && !(current->head && current->head->type == INPUT)
			&& !current->no_such_file)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: %s: command not found\n", current->args[0]);
			dup2(STDOUT_FILENO, STDERR_FILENO);
		}
		current = current->next;
	}
	inspector();
	close_heredocs();
}
