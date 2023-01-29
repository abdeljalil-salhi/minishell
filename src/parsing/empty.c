/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:49:05 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/29 22:44:02 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty(char *input)
{
	int	i;

	i = -1;
	if (!input)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	while (input[++i])
		if (input[i] != SPACE && input[i] != TAB)
			return (0);
	free(input);
	return (1);
}
