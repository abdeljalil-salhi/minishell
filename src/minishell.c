/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:44:18 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/27 01:47:06 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argc;
	(void)argv;
	init_builtins();
	g_data.env = ft_tabdup(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		input = readline(GREEN "minishell-3.2$ " RESET);
		if (empty(input))
			continue ;
		add_history(input);
		parsing(input);
		if (g_data.errors)
			continue ;
		if (DEBUG)
			printf_struct();
		supervisor();
		clear();
	}
}
