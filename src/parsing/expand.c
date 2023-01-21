/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:24:04 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/21 07:13:59 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_variable(char *str, char **env)
{
	char	*ptr;
	int		i;

	i = 0;
	while (env[i])
	{
		ptr = ft_strstr(env[i], str);
		if (ptr)
		{
			if (*(ptr + ft_strlen(str)) == '=' && *str == *env[i])
			{
				ptr = ft_strdup(env[i] + (ft_strlen(str) + 1));
				free(str);
				return (ptr);
			}
		}
		i++;
	}
	if (!ft_strcmp(str, "?"))
		ptr = ft_itoa(g_exit_status);
	else
		ptr = ft_strdup("");
	free(str);
	return (ptr);
}

void	get_env_value(char **buffer, char *str, int *i, char **env)
{
	char	*ptr1;
	char	*ptr2;
	int		j;

	(*i)++;
	j = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != ' '
		&& str[*i] != SINGLE_QUOTE && str[*i] != DOUBLE_QUOTE)
		(*i)++;
	ptr1 = ft_substr(str, j, *i - j);
	ptr1 = get_env_variable(ptr1, env);
	ptr2 = *buffer;
	*buffer = ft_strjoin(*buffer, ptr1);
	free(ptr2);
	free(ptr1);
}

void	set_quotes(char *str, int i, int *s_quote, int *d_quote)
{
	if (str[i] == SINGLE_QUOTE)
		(*s_quote)++;
	else if (str[i] == DOUBLE_QUOTE)
		(*d_quote)++;
}

char	*expand(char *str, char **env)
{
	int		s_quote;
	int		d_quote;
	char	*buffer;
	int		i;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	buffer = NULL;
	while (str[i])
	{
		set_quotes(str, i, &s_quote, &d_quote);
		if (str[i] == '$' && (d_quote % 2
			|| (d_quote % 2 == 0 && s_quote % 2 == 0)))
		 	 	get_env_value(&buffer, str, &i, env);
		else
			buffer = str_concate(buffer, str[i++]);
	}	
	free(str);
	return (buffer);
}
