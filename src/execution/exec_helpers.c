/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:54:22 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/05 00:30:12 by absalhi          ###   ########.fr       */
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

void	check_if_dots(t_proc **proc)
{
	if (!(*proc)->args)
		return ;
	if (ft_strcmp((*proc)->args[0], ".") == 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: .: filename argument required\n");
		ft_dprintf(STDERR_FILENO, ".: usage: . filename [arguments]\n");
		g_data.exit_status = 2;
		(*proc)->error = 1;
	}
	else if (ft_strcmp((*proc)->args[0], "..") == 0)
	{
		ft_dprintf(STDERR_FILENO, ERR_CMD_NOT_FOUND, (*proc)->args[0]);
		g_data.exit_status = 127;
		(*proc)->error = 1;
	}
}

void	check_if_directory(t_proc **proc)
{
	DIR	*dir;

	dir = opendir((*proc)->cmd);
	if (dir && !(*proc)->error)
	{
		ft_dprintf(2, CUSTOM, (*proc)->args[0], "is a directory");
		(*proc)->error = 1;
		g_data.exit_status = 126;
		closedir(dir);
	}
}

int	is_path(void)
{
	int	i;

	if (!g_data.env)
		return (0);
	i = -1;
	while (g_data.env[++i])
		if (ft_strncmp(g_data.env[i], "PATH=", 5) == 0)
			return (1);
	return (0);
}
