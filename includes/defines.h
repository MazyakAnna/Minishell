/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaegan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:25:37 by bmaegan           #+#    #+#             */
/*   Updated: 2021/11/16 20:25:39 by bmaegan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

//token identifiers (token->id): WORDS (0) and OPERATORS (1-5).
//(-1) if not identified
# define WORD 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define APPEND 3
# define HEREDOC 4
# define PIPE 5
# define FILE_REDIR 6

//standard fds:
# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define TMP_FILE "/tmp/minishell_heredoc"

//modes:
# define M_SILENT 0
# define M_INTERACTIVE 1

# define MINISHELL "minishell: "
# define NO_CMD ": command not found\n"
# define NO_FILE ": No such file or directory\n"
# define PERM_ERROR ": Permission denied\n"
# define SNTX_ERROR "syntax error near unexpected token\n"
# define WRONG_REDIR "ambiguous redirect\n"
# define DOUBLE_REDIR "ambiguous redirect\n"
# define WRONG_EXPORT "not a valid identifier\n"

# define FORK_ERROR "fork: Resource temporarily unavailable\n"

//Errors codes according to bash
# define SUCCESS 0
# define GENERAL_ERRORS 1
# define BUILTIN_MISUSE 2
# define PERMISSION_DENIED 126
# define CMD_NOT_FOUND 127
# define TERMINATED_CTRL_C 130

//MY OWN ERROR CODES =)
# define BUILTIN_NOT_EXECUTED 147//RANDOM

# define MAX_UNSIGNED_INT 4294967295

# define BUFFER_SIZE 16

#endif
