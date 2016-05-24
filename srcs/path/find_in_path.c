/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblet <mblet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 19:02:39 by mblet             #+#    #+#             */
/*   Updated: 2016/05/22 19:46:14 by mblet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

#include <libft.h>

static int	s_check_if_access(char *exe_path)
{
	if (access(exe_path, X_OK) == -1)
		return (0);
	return (1);
}

static int	s_in_path_env(char **aexe)
{
	char	**list_path;
	char	*tmp;
	size_t	i;
	int		ret;

	list_path = ft_strsplit(sh_getenv(sgt_sh()->env, "PATH"), ':');
	if (list_path == NULL)
		return (0);
	ret = 0;
	i = 0;
	tmp = NULL;
	while (list_path[i])
	{
		ft_asprintf(&tmp, "%s/%s", list_path[i], *aexe);
		if (s_check_if_access(tmp))
		{
			ft_asprintf(aexe, "%s", tmp);
			ret = 1;
			break ;
		}
		++i;
	}
	ft_strtable_clear(&list_path);
	ft_strdel(&tmp);
	return (ret);
}

int			find_in_path(char **aexe)
{
	int		ret;

	if (sgt_sh()->env == NULL || aexe == NULL || *aexe == NULL)
		return (-1);
	if ((*aexe)[0] == '/' || (*aexe)[0] == '.')
		ret = s_check_if_access(*aexe);
	else
		ret = s_in_path_env(aexe);
	return (ret);
}
