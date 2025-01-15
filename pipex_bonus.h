/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/01/15 14:59:48 by cbuzzini         ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_first_child (char *argv[], char *envp[], int pipefd[]);
int	    ft_first_fork (char *argv[], char *envp[], int pipefd[]);
void	ft_second_child (char *argv[], char *envp[], int pipefd[]);
int	    ft_second_fork (char *argv[], char *envp[], int pipefd[], int id1);


#endif
