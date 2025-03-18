/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 17:34:18 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		argc;
	char	**cmds;
	char	**envp;
	int		cmd_count;
	char	*infile;
	char	*outfile;
	int		**fd;
}	t_pipex;

void	ft_putstr_fd(char *s, int fd);
void	ft_first_child(t_pipex *pipex);
void	ft_last_child(t_pipex *pipex, int prev_pipe[]);
void	ft_execute(char *cmd, char *envp[]);
int		ft_fork(t_pipex *pipex);
void	ft_deallocate_pipes(int **pipefd);
void	ft_create_arr_pipes(t_pipex *pipex);
int		ft_strcmp(const char *s1, const char *s2);

#endif
