/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:06:05 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/20 00:23:39 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	create_tmpfile(void)
{
	int	fd;

	if (access(TMP_FILE, F_OK) == -1
		|| (access(TMP_FILE, W_OK) == 0 && access(TMP_FILE, R_OK) == 0))
	{
		fd = open(TMP_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		return (fd);
	}
	else
		ft_putstr_fd("heredoc file already exists and access required!\n", 2);
	return (-1);
}

void	clear_tmpfile(void)
{
	int	fd;

	if ((access(TMP_FILE, F_OK) == 0) && (access(TMP_FILE, W_OK) == 0))
	{
		fd = open(TMP_FILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
		close(fd);
	}
}

int	kill_readline(void)
{
	rl_line_buffer[0] = '\n';
	rl_done = 1;
	return (0);
}

int	heredoc_start(char *delimiter, int fd)
{
	char	*input;
	int		ret;

	ret = 0;
	input = readline("> ");
	while (ft_strcmp(input, delimiter) != 0)
	{
		if (g_status == 247)
		{
			g_status = 1;
			ret = 1;
			break ;
		}
		ft_putstr_fd_nl(input, fd);
		free(input);
		input = readline("> ");
	}
	if (input != NULL)
		free(input);
	rl_event_hook = 0;
	rl_done = 0;
	return (ret);
}

int	here_doc(t_data *data, char *delimiter)
{
	int	fd;
	int	ret;

	signal(SIGINT, SIG_IGN);
	fd = create_tmpfile();
	if (fd < 0)
	{
		ret_error(data, 0, "Bad fd. Sorry, no heredoc for ya\n", -1);
		ft_exit(0, data, 1, 1);
	}
	signal(SIGINT, heredoc_sig);
	ret = heredoc_start(delimiter, fd);
	close(fd);
	signal(SIGINT, signal_control);
	if (ret != 0)
		return (-1);
	fd = open(TMP_FILE, O_RDONLY);
	return (fd);
}
