/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:49:05 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/15 12:42:05 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty(char *input)
{
	int	i;

	i = 0;
	if (!input)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	while (input[i])
		if (input[i++] != SPACE)
			return (0);	
	free(input);
	return (1);
}
