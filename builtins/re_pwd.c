/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:55:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/27 01:55:19 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_pwd(char **args, char **env)
{
	char	*pwd;

	(void) args;
	(void) env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("minishell: error retrieving current directory\n");
	printf("%s\n", pwd);
	free(pwd);
}
