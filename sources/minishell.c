/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:16:45 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/06/17 08:23:55 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tchbi7a(void)
{
    printf(RED "██████  ██░ ██ ▓█████  ██▓     ██▓            \n"
"▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒            \n"
"░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░            \n"
"  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░            \n"
"▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒        \n"
"▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░        \n"
"░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░        \n"
"░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░           \n"
"      ░   ░  ░  ░   ░  ░    ░  ░    ░  ░        \n" RESET);
}

int main(int ac, char **av, char  **ev)
{
    print_tchbi7a();
    (void)ac;
    (void)av;
    
    // t_global_data *global_data;
    // t_env *env;
    t_elem *elem;
    (void)ev;

    // global_data = malloc(sizeof(t_global_data)); 
    // env = init_env(ev);
    while (1)
    {
        elem = lexer();
        if (!elem)
            continue;
        t_command * root = parser(elem);
        print_tree(root, 0);
    }
}