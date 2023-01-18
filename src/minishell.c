/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:44:18 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 18:39:58 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*input;

	(void)argc;
	(void)argv;
	(void)env;
	data.env = ft_tabdup(env);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		input = readline(GREEN "minishell-3.2$ " RESET);
		if (empty(input))
			continue ;
		add_history(input);
		parsing(input, &data);
		if (data.errors)
			continue ;
		clear(&data);
	}
}
