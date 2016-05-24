/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_method_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 22:25:52 by jguyet            #+#    #+#             */
/*   Updated: 2016/05/23 01:07:54 by mblet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

short	exec_all_method(t_tree *node)
{
	char	test[255];
	char	**env;
	int ret = 0;

	redir_in(node);
	env = (sgt_sh()->tmp_env == NULL) ? sgt_sh()->env : sgt_sh()->tmp_env;
	DEBUGLINE;
	if (node->sub != -1)
	{
		if (node->full_path && !check_if_in_builtin(node->args))
		{
			free(node->args[0]);
			node->args[0] = ft_strdup(node->full_path);
		}
		if (exec_sub_default(node, node->sub) <= 0)
			node->error = 1;
	}
	else if ((ret = execve(node->full_path, node->args, env)) <= 0)
	{
		ERR("42sh: %s %i", ft_strerror(), ret);
		node->error = 1;
	}
	if (!node->error && node->sub == -1)
	{
		if (read(2, test, 254) != 0)
			node->error = 1;
	}
	redir_out(node);
	return (1);
}

short	exec_method_default(t_tree *node)
{
	int		error;

	ft_strtable_clear(&sgt_sh()->tmp_env);
	if (node->sub == -1 && check_builtin(node->args)
		&& if_env_valid(&node->args) == false)
		return (1);
	else if (((error = find_in_path(&node->args[0])) > 0
			&& (node->full_path = ft_strdup(node->args[0]))
			&& (node->pid = fork()) == 0))
	{
		exec_all_method(node);
		exit(0);
	}
	g_signal_ctrlc = 1;
	sgt_sh()->lastexepid = node->pid;
	waitpid(node->pid, &(node->status), WUNTRACED);
	DEBUGLINE;
	if (WIFSIGNALED(node->status))
	{
		ERR("%s", ft_strerr(WTERMSIG(node->status)));
		//ft_printf("42sh segmentation fault  %s\n", \
				//node->pid, node->full_path);
	}
	if (WIFEXITED(node->status))
		DEBUG("%i", WEXITSTATUS(node->status));
	DEBUGLINE;
	g_signal_ctrlc = 0;
	return ((short)error);
}
