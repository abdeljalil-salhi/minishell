/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 07:48:27 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/31 04:52:52 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	exec_heredoc(t_redir *current)
{
	char	*line;

	current->fd = open(HERE_DOC, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (current->fd == -1)
		return ;
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
		ft_putendl_fd(line, current->fd);
		free(line);
	}
	close(current->fd);
}

void	look_for_heredocs(void)
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
