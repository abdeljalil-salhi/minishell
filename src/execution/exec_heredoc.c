/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 07:48:27 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/05 02:06:46 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_heredoc(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_FAILURE);
}

void	exec_heredoc(t_redir *current)
{
	char	*line;

	current->fd = open(HERE_DOC, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (current->fd == -1)
		return ;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_heredoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, current->file) == 0)
		{
			free(line);
			break ;
		}
		line = expand(line, 0);
		if (!line)
			line = ft_strdup("");
		ft_dprintf(current->fd, "%s\n", line);
		free(line);
	}
	close(current->fd);
	exit(EXIT_SUCCESS);
}

void	close_heredocs(void)
{
	t_proc	*current;
	t_redir	*redir;
	char	*line;

	current = g_data.head;
	while (current)
	{
		redir = current->head;
		while (redir)
		{
			if (redir->type == HEREDOC)
				if (!(read(redir->fd, &line, 0) < 0 && errno == EBADF))
					close(redir->fd);
			redir = redir->next;
		}
		current = current->next;
	}
}

int	handle_heredoc(pid_t pid, int *status)
{
	g_data.here_doc = 1;
	if (waitpid(pid, status, 0) == -1)
	{
		ft_dprintf(STDERR_FILENO, FAIL_WAITPID, strerror(errno));
		return (EXIT_FAILURE);
	}
	g_data.here_doc = 0;
	if (WIFEXITED(*status))
	{
		g_data.exit_status = EXIT_SUCCESS;
		if (WEXITSTATUS(*status))
		{
			g_data.exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
