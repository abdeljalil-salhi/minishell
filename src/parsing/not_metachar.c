/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_metachar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:45:35 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/29 22:45:14 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_metachar(char c)
{
	if (c != RIGHT_ARROW && c != LEFT_ARROW
		&& c != PIPE && c != SPACE && c != TAB
		&& c != AMPERSAND && c != OPEN_PARENTHESE
		&& c != CLOSE_PARENTHESE)
		return (1);
	return (0);
}
