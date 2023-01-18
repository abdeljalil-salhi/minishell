/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:23:18 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 15:23:20 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arrsize(const char *str, char c)
{
	int	size;

	size = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			size++;
		while (*str && *str != c)
			str++;
	}
	return (size);
}

int	ft_wordlen(const char *str, char c)
{
	int	len;

	len = 0;
	while (*str && *str == c)
		str++;
	while (*str && *str != c)
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_word(const char *str, char c)
{
	char	*word;
	int		i;
	int		len;

	len = ft_wordlen(str, c);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (ft_arrsize(s, c) + 1));
	if (!tab)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			tab[i] = ft_word(s, c);
			if (!tab[i])
				return (0);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	tab[i] = 0;
	return (tab);
}
