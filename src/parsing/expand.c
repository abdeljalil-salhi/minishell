/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:24:04 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/16 09:34:32 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valuelen(char *str, char **env)
{
	char	*ptr;
	int		i;

	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '$'
		&& str[i] != DOUBLE_QUOTE)
		i++;
	ptr = ft_substr(str, 1, i - 1);
	ptr = get_env_values(ptr, env);
	i = ft_strlen(ptr);
	free(ptr);
	return (i);
}

int	newsize(char *str, char **env)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != '$')
		{
			i++;
			size++;
		}
		else
		{
			size += valuelen(str + i++, env);
			while (str[i] && str[i] != ' ' && str[i] != '$'
				&& str[i] != DOUBLE_QUOTE)
				i++;
		}
	}
	return (size);
}

char	*g_value(char *str, char **env)
{
	char	*ptr;
	int		i;

	i = 1;
	while (str[i] && str[i] != ' ' && str[i] != '$'
		&& str[i] != DOUBLE_QUOTE)
		i++;
	ptr = ft_substr(str, 1, i - 1);
	ptr = get_env_values(ptr, env);
	return (ptr);
}

void	getvalue(char *str, char *s, int *j, char **env)
{
	char	*ptr;
	int		x;

	x = 0;
	ptr = g_value(str, env);
	while (ptr[x])
		s[(*j)++] = ptr[x++];
	free(ptr);
}

char	*expand(char *str, char **env)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc(sizeof(char) * (newsize(str, env) + 1));
	if (!s)
		exit(EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] != '$')
			s[j++] = str[i++];
		else
		{
			getvalue(str + i++, s, &j, env);
			while (str[i] && str[i] != ' ' && str[i] != '$'
				&& str[i] != DOUBLE_QUOTE)
				i++;
		}
	}
	s[j] = '\0';
	free(str);
	return (s);
}
