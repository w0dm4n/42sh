/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 04:08:29 by jguyet            #+#    #+#             */
/*   Updated: 2016/05/23 01:28:27 by mblet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline.h>
#include <sh.h>
#include <signal.h>

void	resize(int sig)
{
	if (sig != SIGWINCH)
		return ;
	readline_signal_resize();
}

void	ctrlc(int sig)
{
	if (sig != SIGINT)
		return ;
	if (!g_signal_ctrlc)
		readline_signal_ctrl_c();
	else if (sgt_sh()->in_current_process)
		sgt_sh()->in_current_process = 0;
	else
		readline_signal_ctrl_c();
}

void	ctrlz(int sig)
{
	//static t_bool	in = false;

	if (sig != SIGTSTP)
		return ;
	//if (in == false)
	//{
		//kill(sgt_sh()->lastexepid, SIGTSTP);//Sending to the whole group
		//in = true;
	//}
	//else
	//{/
		//kill(sgt_sh()->lastexepid, SIGCONT);
		//in = false;
	//}
}
