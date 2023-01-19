/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:55:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 12:37:45 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("minishell: error retrieving current directory\n");
	printf("%s\n", pwd);
	free(pwd);
}
