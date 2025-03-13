/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/13 12:32:13 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
#include <sys/wait.h>

typedef struct s_pipex
{
	int		argc;
	char    **cmds;
	char	**envp;
    int     cmd_count;
    char    *infile;
    char    *outfile;
}	t_pipex;

typedef struct s_child
{
	int		index;
	char    *cmd;
    int     pid;
	struct s_child *next;
}	t_child;

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_first_child(t_pipex *pipex, int next_pipe[], int **pipefd);
void	ft_last_child(t_pipex *pipex, int prev_pipe[], int **pipefd);
void	ft_execute(char *cmd, char *envp[]);
int	    ft_fork(t_pipex *pipex, int **pipefd);
void	ft_deallocate_pipes(int **pipefd, int i);
void	ft_middle_child(t_pipex *pipex, int prev_pipe[], int next_pipe[], int forks, int **pipefd);
int	 **ft_create_arr_pipes(t_pipex *pipex);

#endif
