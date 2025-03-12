/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/17 16:25:55 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
#include <sys/wait.h>

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_first_child(char *argv[], char *envp[], int pipefd[]);
void	ft_first_fork(char *argv[], char *envp[], int pipefd[]);
void	ft_last_child(char *argv[], char *envp[], int pipefd[], int exctd_cmds);
int	    ft_last_fork(char *argv[], char *envp[], int *pipes[], int exctd_cmds);
void	ft_middle_children(char *argv[], char *envp[], int *pipes[], int exctd_cmds);
int	    ft_middle_fork(char *argv[], char *envp[], int *pipes[], int exctd_cmds);
void	ft_execute(char *cmd, char *envp[]);
void	ft_create_pipe(int *pipes[], int i);
int	    **ft_allocate_pipes(int total_pipes);
void	ft_close_and_free(int *pipes[], int total_pipes);


#endif
