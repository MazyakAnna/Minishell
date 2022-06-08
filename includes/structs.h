/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:25:55 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 20:25:56 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	int				id;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

typedef struct s_command
{
	char				**argv;
	int					argc;
	int					id;
	int					fds[3];
	int					err;
	struct s_command	*next;
	struct s_command	*prev;
}			t_command;

typedef struct s_flags
{
	int		start;
	int		quot;
	int		operator;
	int		count;
}			t_flags;

#endif
