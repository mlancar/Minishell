/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_close.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malancar <malancar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:22:15 by malancar          #+#    #+#             */
/*   Updated: 2023/11/23 22:40:07 by malancar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error_exec(t_struct_data *s, t_cmd *cmd, int exit_code)
{
	close_all_fd(cmd);
	free_and_exit(s, cmd, exit_code);
}

void	error_cmd(t_struct_data *s, t_cmd *cmd,
	int exit_code)
{
	int	i;

	i = 0;
	if (cmd->name[0])
		print_error(cmd);
	close_all_fd(cmd);
	free_and_exit(s, cmd, exit_code);
}
