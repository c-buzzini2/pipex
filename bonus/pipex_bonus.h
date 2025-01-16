/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/16 14:09:35 by cbuzzini         ###   ########.fr       */
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
void	ft_last_child(char *argv[], char *envp[], int pipefd[]);
int	    ft_second_fork(char *argv[], char *envp[], int pipefd[]);//, int commands);
void	ft_execute(char *cmd, char *envp[]);

#endif
