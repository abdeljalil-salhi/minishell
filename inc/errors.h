/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:28:37 by absalhi           #+#    #+#             */
/*   Updated: 2023/02/02 12:31:29 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_PERMISSION "minishell: %s: Permission denied\n"
# define ERR_NO_SUCH_FILE "minishell: %s: No such file or directory\n"
# define ERR_CMD_NOT_FOUND "minishell: %s: command not found\n"

# define FAIL_FORK "minishell: fork: %s\n"
# define FAIL_WAITPID "minishell: waitpid: %s\n"
# define FAIL_PIPE "minishell: pipe: %s\n"

# define CUSTOM "minishell: %s: %s\n"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `%s'\n"

#endif