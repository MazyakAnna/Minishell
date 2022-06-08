/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:03:54 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/20 09:20:15 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_tokens(t_token *token, t_data *data)
{
	while (token != NULL)
	{
		if (token->id == PIPE)
			return (ret_error(data, 0, SNTX_ERROR, 258));
		while (token != NULL && token->id != PIPE)
		{
			if (token->id > WORD && token->id < PIPE)
			{
				if (token->next != NULL && token->next->id == WORD)
				{
					token->next->id = FILE_REDIR;
					token = token->next;
				}
				else
					return (ret_error(data, 0, SNTX_ERROR, 258));
			}
			token = token->next;
		}
		if (token != NULL && token->next == NULL)
			return (ret_error(data, 0, SNTX_ERROR, 258));
		else if (token != NULL)
			token = token->next;
	}
	return (0);
}

void	get_tokens_and_run(t_data *data, char *input)
{
	t_token	*head_token;

	head_token = token_recognition(input, data);
	if (head_token != NULL)
	{
		data->cmd = parse_commands(head_token->next, data);
		if (data->cmd != NULL)
		{
			if (data->num_pipes > 0)
				ft_pipex(data);
			else if (data->cmd != NULL)
			{
				if (data->cmd->err == 0)
					run_simple_command(data, data->cmd);
				else
					g_status = data->cmd->err;
			}
		}
		free_tokens(head_token);
	}
}

void	exec_script(t_data *data, char *script)
{
	int		fd;
	int		check;
	char	*input;

	if (check_infile(script) != 0)
		ft_exit(0, data, 127, 1);
	fd = open(script, O_RDONLY);
	if (fd < 0)
		ft_exit(0, data, 127, 1);
	check = get_next_line(fd, &input);
	while (check > 0)
	{
		get_tokens_and_run(data, input);
		if (data->cmd != NULL)
			free_commands(data);
		free(input);
		check = get_next_line(fd, &input);
	}
	close(fd);
	ft_exit(0, data, g_status, 1);
}

void	minishell(t_data *data)
{
	char	*input;

	input = readline(MINISHELL);
	while (input != NULL)
	{
		if (input != NULL && *input != 0)
			add_history(input);
		get_tokens_and_run(data, input);
		if (data->cmd != NULL)
			free_commands(data);
		free(input);
		input = readline(MINISHELL);
	}
	free(input);
	ft_exit(0, data, g_status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	signal_init();
	init_data(&data, argc, argv, envp);
	if (argc > 1)
		exec_script(&data, argv[1]);
	minishell(&data);
	return (0);
}
