/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 07:31:40 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/07/29 16:26:07 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_signal.h"

void	new_prompt(int sig)
{
	(void)sig;
	g_var = 1;
	printf(BHMAG "\n" RESET);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	kill_here_doc(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}
