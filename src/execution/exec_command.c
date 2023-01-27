/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:38:52 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/27 02:55:31 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (status);
}

int	executor(t_proc *proc)
{
	pid_t	pid;
	int		status;

	if (!proc->cmd)
	{
		printf("minishell: %s: command not found\n", proc->args[0]);
		return (127);
	}
	if (is_builtin(proc->cmd))
		return (exec_builtin(proc->cmd, proc->args));
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		execve(proc->cmd, proc->args, g_data.env);
		printf("Error: command not found or failed to execute\n");
		printf("   ~ path: %s\n", proc->cmd);
        exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		printf("   ~ fork failed\n");
	return (exit_status(status));
}
