/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akyoshid <akyoshid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 05:56:49 by akyoshid          #+#    #+#             */
/*   Updated: 2025/08/07 07:08:16 by akyoshid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vbc.h"

static int check_argc(int argc) {
    if (argc < 2) {
        printf("vbc: too few arguments\n");
        printf("Usage: ./vbc MATH_EXPRESSION\n");
        return (EXIT_FAILURE);
    } else if (argc > 2) {
        printf("vbc: too many arguments\n");
        printf("Usage: ./vbc MATH_EXPRESSION\n");
        return (EXIT_FAILURE);
    } else {
        return (EXIT_SUCCESS);
    }
}

int main(int argc, char *argv[]) {
    if (check_argc(argc) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    t_token *token_list = parse(argv[1]);
    if (token_list == NULL)
        return (EXIT_FAILURE);
    print_token_list(token_list);
    free(token_list);
    return (EXIT_SUCCESS);
}
