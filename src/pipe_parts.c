/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:49:29 by bmaegan           #+#    #+#             */
/*   Updated: 2021/09/26 18:49:32 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//by default fd_in = 0
//void	redir_input(char *filename)
void	redir_input(int fd)
{
	dup2(fd, 0);
	close(fd);
}

//by default fd_out = 1;
//void	redir_output(char *filename)
void	redir_output(int new_fd)
{
	dup2(new_fd, 1);
	close(new_fd);
}

/*
** left part of pipe (redirecting output to pipe_fd)
** fd_out = 1 (default)
*/
void	pipe_out(int pipe_fd[2])
{
	close(pipe_fd[0]);
	redir_output(pipe_fd[1]);
}

/*
** right part of pipe (redirecting input from pipe_fd)
** fd_in = 0 (default)
*/
void	pipe_in(int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
