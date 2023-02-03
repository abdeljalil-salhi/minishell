/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:19:59 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/03 04:51:41 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(void)
{
	g_data.builtins[0].name = "echo";
	g_data.builtins[0].func = &re_echo;
	g_data.builtins[1].name = "cd";
	g_data.builtins[1].func = &re_cd;
	g_data.builtins[2].name = "pwd";
	g_data.builtins[2].func = &re_pwd;
	g_data.builtins[3].name = "export";
	g_data.builtins[3].func = &re_export;
	g_data.builtins[4].name = "unset";
	g_data.builtins[4].func = &re_unset;
	g_data.builtins[5].name = "env";
	g_data.builtins[5].func = &re_env;
	g_data.builtins[6].name = "exit";
	g_data.builtins[6].func = &re_exit;
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	exec_builtin(char *cmd, char **args)
{
	int	i;

	i = -1;
	g_data.exit_status = 0;
	while (++i < 7)
	{
		if (ft_strcmp(cmd, g_data.builtins[i].name) == 0)
		{
			g_data.builtins[i].func(args);
			return (g_data.exit_status);
		}
	}
	return (1);
}

int	dup_or_error_builtin(t_redir *current)
{
	init_redirections(&current);
	if (current->fd == -1)
		return (ft_dprintf(2, ERR_PERMISSION, current->file),
			EXIT_FAILURE);
	if (current->fd == -2)
		return (ft_dprintf(2, ERR_NO_SUCH_FILE, current->file),
			EXIT_FAILURE);
	if (current->type == INPUT)
		dup_and_close(current->fd, STDIN_FILENO);
	else if (current->type == OUTPUT || current->type == APPEND)
		dup_and_close(current->fd, STDOUT_FILENO);
	else if (current->type == HEREDOC)
	{
		current->fd = open(HERE_DOC, O_RDONLY, 0644);
		dup_and_close(current->fd, STDIN_FILENO);
	}
	return (EXIT_SUCCESS);
}

typedef struct s_exec_builtin
{
	int		pipe_stdout;
	int		pipe_stdin;
	int		status;
	t_redir	*current;
}	t_exec_builtin;

int	exec_builtin_cmd(t_proc *proc, int _pipe[2], int prev_pipe[2])
{
	t_exec_builtin	s;

	if ((proc->previous && proc->previous->separator == PIPE_TOKEN)
		|| proc->separator == PIPE_TOKEN)
		return (exec_builtin_pipe(proc, _pipe, prev_pipe));
	s.pipe_stdin = dup(STDIN_FILENO);
	s.pipe_stdout = dup(STDOUT_FILENO);
	if (proc->previous && proc->previous->separator == PIPE_TOKEN)
		dup_and_close(prev_pipe[0], 0);
	if (proc->separator == PIPE_TOKEN)
		dup_and_close(_pipe[1], 1);
	s.current = proc->head;
	while (s.current)
	{
		if (dup_or_error_builtin(s.current) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		s.current = s.current->next;
	}
	s.status = exec_builtin(proc->cmd, proc->args);
	dup_and_close(s.pipe_stdout, STDOUT_FILENO);
	dup_and_close(s.pipe_stdin, STDIN_FILENO);
	return (s.status);
}
