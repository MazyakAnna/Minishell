/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:57:58 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/19 22:34:23 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//Add checking for numeric redirs
int	parse_redir_out(t_command *cmd, t_token *token, char *filename)
{
	if (check_outfile(filename))
		return (1);
	if (cmd->fds[1] != STD_OUT && cmd->fds[1] >= 0)
		close(cmd->fds[1]);
	if (token->id == REDIR_OUT)
		cmd->fds[1] = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (token->id == APPEND)
		cmd->fds[1] = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		return (1);
	if (cmd->fds[1] < 0)
	{
		cmd->err = 1;
		ft_putstr_fd("I can't redirect this, sorry...\n", 2);
		return (1);
	}
	return (0);
}

int	parse_redir_in(t_command *cmd, char *filename)
{
	if (check_infile(filename))
		return (1);
	if (cmd->fds[0] != STD_IN && cmd->fds[0] >= 0)
		close(cmd->fds[0]);
	cmd->fds[0] = open(filename, O_RDONLY);
	if (cmd->fds[0] < 0)
	{
		cmd->err = 1;
		ft_putstr_fd("Input redirect failed...\n", 2);
		return (1);
	}
	return (0);
}

char	*expand_heredoc(char *src)
{
	char	*res;
	size_t	i;
	size_t	pointer;

	i = 0;
	res = NULL;
	if (src == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		i += remember_normal_chars(&src[i], &res);
		if (src[i] == '\'')
			i += expand_single_quot(&src[i], &res);
		else if (src[i] == '"')
		{
			i++;
			pointer = i;
			while (src[i] != '"')
				i++;
			add_str(&res, &src[pointer], i - pointer);
			i++;
		}
	}
	return (res);
}

int	parse_heredoc(t_data *data, t_command *cmd, char *delimiter)
{
	int	fd;

	if (cmd->fds[0] != STD_IN)
		close(cmd->fds[0]);
	fd = here_doc(data, delimiter);
	if (fd == -1)
	{
		cmd->err = 1;
		return (1);
	}
	cmd->fds[0] = fd;
	return (0);
}

int	parse_redirection(t_command *cmd, t_token *token, t_data *data)
{
	char	*filename;
	int		ret;

	ret = 0;
	if (token->id == HEREDOC)
		filename = expand_heredoc(token->next->content);
	else
		filename = expand_redirect_filename(token->next->content, data);
	if (filename == NULL)
	{
		ft_put2str_fd(token->next->content, ": ", 2);
		ft_putstr_fd(WRONG_REDIR, 2);
		return (1);
	}
	else if (token->id == REDIR_IN)
		ret = parse_redir_in(cmd, filename);
	else if (token->id == REDIR_OUT || token->id == APPEND)
		ret = parse_redir_out(cmd, token, filename);
	else if (token->id == HEREDOC)
		ret = parse_heredoc(data, cmd, filename);
	if (ret < 0)
		ret_error(data, cmd, "failed to open file...\n", 1);
	free(filename);
	return (ret);
}
