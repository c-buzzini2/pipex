/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuzzini <cbuzzini@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:33:53 by cbuzzini          #+#    #+#             */
/*   Updated: 2025/03/18 15:54:11 by cbuzzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

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
	char	*heredoc;
	char	*limiter;
	int		**fd;
}	t_pipex;

void			ft_putstr_fd(char *s, int fd);
void			ft_first_child(t_pipex *pipex);
void			ft_last_child(t_pipex *pipex, int prev_pipe[]);
void			ft_execute(char *cmd, char *envp[]);
int				ft_fork(t_pipex *pipex);
void			ft_deallocate_pipes(int **pipefd);
void			ft_middle_child(t_pipex *pipex, int prev_pipe[],
					int next_pipe[], int forks);
void			ft_create_arr_pipes(t_pipex *pipex);
char			*get_next_line(int fd);
size_t			ft_len_till_eol(char *s, char c);
unsigned int	ft_strlcat_gnl(char *dst, char *src, unsigned int size);
char			*ft_strdup_gnl(char *s, int fr);
char			*ft_strjoin_gnl(char *s1, char *s2);
void			ft_strlcpy(char *dst, char *src, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_heredoc(t_pipex *pipex, int argc, char **argv);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *s);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
void			ft_bzero(void *s, size_t n);
char			*ft_strdup(const char *s);
void			ft_delete_heredoc(t_pipex *pipex);

#endif
