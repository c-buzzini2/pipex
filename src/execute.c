/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:19:24 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 17:24:37 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "pipex_bonus.h"
#else
# include "pipex.h"
#endif

void	ft_execute(char *cmd, char *envp[])
{
	char	*args[4];

	args[0] = "/bin/zsh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/zsh", args, envp);
}
