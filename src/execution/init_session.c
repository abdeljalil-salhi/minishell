/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:19:43 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/06 11:42:13 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirections(t_redir **redir)
{
	if (((*redir))->type == INPUT)
		((*redir))->fd = open(((*redir))->file, O_RDONLY, 0644);
	else if (((*redir))->type == OUTPUT)
		((*redir))->fd = open(((*redir))->file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (((*redir))->type == APPEND)
		((*redir))->fd = open(((*redir))->file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (((*redir))->type == HEREDOC)
		((*redir))->fd = -3;
	if (((*redir))->fd == -1 && access(((*redir))->file, F_OK) == -1)
		((*redir))->fd = -2;
}

static void	print_banner(void)
{
	printf(RED);
	printf("\t ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ");
	printf("██████  ██░ ██ ▓█████  ██▓     ██▓    \n");
	printf("\t▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒█");
	printf("█    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n");
	printf("\t▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ");
	printf("▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n");
	printf("\t▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ");
	printf("▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n");
	printf("\t▒██▒   ░██▒░██░▒██░   ▓██░░██░▒█");
	printf("█████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n");
	printf("\t░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ");
	printf("▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n");
	printf("\t░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ");
	printf("░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n");
	printf("\t░      ░    ▒ ░   ░   ░ ░  ▒ ░░ ");
	printf(" ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n");
	printf("\t       ░    ░           ░  ░    ");
	printf("    ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n");
	printf("%s\n", RESET);
}

/*
** This function is called at the beginning of the program.
** It initializes the global struct g_data and the builtins.
** It also clears the terminal and displays the minishell banner.
*/
void	init_session(int argc, char **argv, char **env)
{
	(void) argc, (void) argv;
	ft_bzero(&g_data, sizeof(t_data));
	init_builtins();
	g_data.env = ft_tabdup(env);
	printf("\033[2J");
	printf("\033[0;0H");
	print_banner();
}

void	dup_and_close(int fd, int new_fd)
{
	dup2(fd, new_fd);
	close(fd);
}
