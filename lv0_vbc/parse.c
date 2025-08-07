/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 07:05:16 by akyoshid          #+#    #+#             */
/*   Updated: 2025/08/07 07:08:09 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

static int check_token_type(char c) {
    if (c >= '0' && c <= '9')
        return (TOKEN_NUM);
    else if (c == '+')
        return (TOKEN_ADD);
    else if (c == '*')
        return (TOKEN_MUL);
    else if (c == '(')
        return (TOKEN_L_PAR);
    else if (c == ')')
        return (TOKEN_R_PAR);
    else
        return (TOKEN_INVALID);
}

t_token *parse(char *arg) {
    int len = ft_strlen(arg);
    t_token *token_array = (t_token *)malloc(sizeof(t_token) * (len + 1));
    if (token_array == NULL) {
        printf("vbc: cannot allocate memory\n");
        return (NULL);
    }
    int i = 0;
    while (i < len) {
        token_array[i].type = check_token_type(arg[i]);
        if (token_array[i].type == TOKEN_NUM)
            token_array[i].num = arg[i] - '0';
        else
            token_array[i].num = -1;
        i++;
    }
    token_array[i].type = TOKEN_TERMINAL;
    token_array[i].num = -1;
    return (token_array);
}

void print_token_list(t_token *token_list) {
    int i = 0;
    while (token_list[i].type != TOKEN_TERMINAL) {
        if (token_list[i].type == TOKEN_NUM)
            printf("%d", token_list[i].num);
        else if (token_list[i].type == TOKEN_ADD)
            printf("+");
        else if (token_list[i].type == TOKEN_MUL)
            printf("*");
        else if (token_list[i].type == TOKEN_L_PAR)
            printf("(");
        else if (token_list[i].type == TOKEN_R_PAR)
            printf(")");
        else if (token_list[i].type == TOKEN_INVALID)
            printf("?");
        i++;
    }
    printf("\n");
}
