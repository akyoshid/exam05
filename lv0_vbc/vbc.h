/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 05:57:32 by akyoshid          #+#    #+#             */
/*   Updated: 2025/08/07 07:06:26 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBC_H
# define VBC_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

typedef struct s_token {
    int type;
    int num;
} t_token;

enum e_token_type{
    TOKEN_NUM,
    TOKEN_ADD,
    TOKEN_MUL,
    TOKEN_L_PAR,
    TOKEN_R_PAR,
    TOKEN_TERMINAL,
    TOKEN_INVALID,
};

// ft_strlen.c
int ft_strlen(char *str);
// parse.c
t_token *parse(char *arg);
void print_token_list(t_token *token_list);

#endif
