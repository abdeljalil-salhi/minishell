/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:55:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 13:03:31 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_chdir(char *path)
{
	int	i;

	set_oldpwd();
	i = chdir(path);
	if (i)
	{
		ft_dprintf(STDERR_FILENO, ERR_NO_SUCH_FILE_2, "cd", path);
		g_data.exit_status = EXIT_FAILURE;
		return ;
	}
	printf("%s\n", path);
	set_pwd();
	free(path);
}

void	cd_oldpwd(void)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "OLDPWD=", 7))
		{
			path = ft_strdup(g_data.env[i] + 7);
			break ;
		}
		i++;
	}
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, ERR_UNSET, "OLDPWD");
		g_data.exit_status = EXIT_FAILURE;
	}
	else
		ft_chdir(path);
}

void	re_pwd(char **args)
{
	char	*pwd;

	(void) args;
	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	free(pwd);
}
