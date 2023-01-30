/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 07:48:27 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/30 19:12:20 by absalhi          ###   ########.fr       */
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
	g_data.here_doc = 1;
	while (g_data.here_doc)
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
	g_data.here_doc = 0;
	close(current->fd);
}
