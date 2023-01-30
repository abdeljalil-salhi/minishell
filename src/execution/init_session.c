/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_session.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:19:43 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/30 18:35:32 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("    ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n\n");
	printf(RESET);
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
