/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:44:18 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 08:50:35 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	char	*name;

	(void)argc, (void)argv;
	ft_bzero(&g_data, sizeof(t_data));
	init_builtins();
	g_data.env = ft_tabdup(env);
	while (1)
	{
		name = prompt();
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		input = readline(name);
		free(name);
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
