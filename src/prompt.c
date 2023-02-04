/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:48:57 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 14:34:54 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		s.path = ft_getenv("PWD");
	s.user = ft_strdup("$USER");
	s.user = expand(s.user, 1);
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
