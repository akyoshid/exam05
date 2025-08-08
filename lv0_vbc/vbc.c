/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 05:56:49 by akyoshid          #+#    #+#             */
/*   Updated: 2025/08/08 12:14:06 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct s_data {
    char *s;
    int i;
    bool error_flag;
} t_data;

int parse_expr(t_data *d);
int parse_term(t_data *d);
int parse_factor(t_data *d);
void handle_error(t_data *d);

int parse_expr(t_data *d) {
    int ret = parse_term(d);
    while (d->s[d->i] == '+') {
        ++(d->i);
        ret += parse_term(d);
    }
    return ret;
}

int parse_term(t_data *d) {
    int ret = parse_factor(d);
    while (d->s[d->i] == '*') {
        ++(d->i);
        ret *= parse_factor(d);
    }
    return ret;
}

int parse_factor(t_data *d) {
    if (d->s[d->i] == '(') {
        ++(d->i);
        int ret = parse_expr(d);
        if (d->s[d->i] == ')') {
            ++(d->i);
            return (ret);
        } else {
            handle_error(d);
            return (-1);
        }
    } else if (isdigit(d->s[d->i]) != 0) {
        return (d->s[d->i++] - '0');
    } else {
        handle_error(d);
        return (-1);
    }
}

void handle_error(t_data *d) {
    if (d->error_flag == 1)
        return ;
    if (d->s[d->i] == '\0') {
        write(2, "Unexpected end of input\n", 24);
        d->error_flag = 1;
    } else {
        write(2, "Unexpected token '", 18);
        write(2, d->s + d->i, 1);
        write(2, "'\n", 2);
        d->error_flag = 1;
        while (d->s[d->i] != '\0')
            ++(d->i);
    }
}

static int check_argc(int argc) {
    if (argc < 2) {
        write(2, "vbc: too few arguments\n", 23);
        write(2, "Usage: ./vbc MATH_EXPRESSION\n", 29);
        return (EXIT_FAILURE);
    } else if (argc > 2) {
        write(2, "vbc: too many arguments\n", 24);
        write(2, "Usage: ./vbc MATH_EXPRESSION\n", 29);
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]) {
    if (check_argc(argc) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    t_data d = {argv[1], 0, 0};
    int result = parse_expr(&d);
    if (d.s[d.i] != '\0')
        handle_error(&d);
    if (d.error_flag == 1)
        return (EXIT_FAILURE);
    else {
        printf("%d\n", result);
        return (EXIT_SUCCESS);
    }
}
