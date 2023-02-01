/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:48:57 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/01 21:27:11 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd_env(void)
{
	char	*cwd;
	int		i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "PWD=", 4))
			cwd = ft_strdup(g_data.env[i] + 4);
		i++;
	}
	return (cwd);
}

typedef struct s_prompt
{
	char	*path;
	char	*folder;
	char	*user;
	char	*color;
}	t_prompt;

char	*prompt(void)
{
	t_prompt	s;

	s.path = getcwd(NULL, 0);
	if (!s.path)
		s.path = get_cwd_env();
	s.user = ft_strdup("$USER");
	s.user = expand(s.user);
	if (g_data.exit_status == 0)
		s.color = GREEN_ARROW;
	else
		s.color = RED_ARROW;
	if (ft_strlen(s.path) != ft_strlen(ft_strrchr(s.path, '/')))
	{
		if (!ft_strcmp(s.user, ft_strrchr(s.path, '/') + 1))
			s.folder = ft_strjoin(s.color, "~");
		else
			s.folder = ft_strjoin(s.color, ft_strrchr(s.path, '/') + 1);
	}
	else
		s.folder = ft_strjoin(s.color, ft_strrchr(s.path, '/'));
	free(s.path);
	s.path = ft_strjoin(s.folder, RESET);
	free(s.folder);
	free(s.user);
	return (s.path);
}
