/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:02:39 by amejdoub          #+#    #+#             */
/*   Updated: 2024/07/05 16:40:54 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*ft_freed_join(char *s1, char *s2)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && *s2)
	{
		res[i] = *s2;
		s2++;
		i++;
	}
	res[i] = '\0';
	free(s1);
	return (res);
}
char *get_path(char *command, t_env *env)
{
    char **paths;
    int i;
    char *tmp;
    char *tmp2;
    
    paths = ft_split(env->get(env->data, "PATH"), ':');
    i = 0;
    tmp = NULL;
    tmp2 = NULL;
    while (paths[i])
    {
        tmp = ft_freed_join(paths[i], "/");
        tmp2 = ft_freed_join(tmp, command);
        if (!access(tmp2, F_OK))
        {
            return (tmp2);
        }
        i++;
        free(tmp2);
        tmp2 = NULL;
    }
    
    return 0;
}
char **get_command_args(t_command_args *args, t_env *env)
{
    char **res;
    res = NULL;
    while (args)
    {
        res = add_to_args(res, env_expander(args->content, args->index_list, env));
        args = args->next;
    }
    return (res);
}
t_exec_ret *executor(t_command *command, t_env *env, char c)
{
    t_exec_ret *ret;
    t_exec_ret *tmp = NULL;
    ret = malloc(sizeof(t_exec_ret));
    ret->pids = NULL;
    if (!command)
    {
        ret->ret = -1;
        ret->pids = NULL;
        return (ret);
    }
    if (command->type_node == PIPE_LINE_NODE || command->type_node == ROOT_NODE)
    {
        if (command->type_node == PIPE_LINE_NODE )
        {
            int fd[2];
            if (command->outfd != -1)
                ((t_command *)command->left)->outfd = command->outfd;
            int k = pipe(fd);
            if (k == -1)
                exit(99);
            ((t_command *)command->right)->outfd = fd[1];
            ((t_command *)command->left)->infd = fd[0];
        }
        tmp = executor(command->right, env, 'r');
        if (tmp->pids)
            ret->pids = tmp->pids;
        else
            ret->pids = add_int(ret->pids, tmp->ret);
        tmp = executor(command->left, env, 'l');
        ret->pids = add_int(ret->pids, tmp->ret);
    }
    else 
    {
        pid_t i = fork();
        if (i == 0)
        {
            command->args = get_command_args(command->command_arg, env);
            command->path = get_path(command->args[0], env);
            if (c == 'r')
            {
                dup2(command->outfd, STDOUT_FILENO);
                close(command->outfd);
                close(command->infd);
            }
            else if (c == 'l')
            {
                dup2(command->infd, STDIN_FILENO);
                close(command->infd);
                if (command->outfd != -1)
                {
                    dup2(command->outfd, STDOUT_FILENO);
                    close(command->outfd);
                }
            }
            if (execve(command->path, command->args, NULL) == -1)
            {
                printf("str : -%s-\n", command->args[0]);
                perror("execve : ");
                exit(127);
            }
        }
        else if (i > 0)
        {
            close(command->outfd);
            close(command->infd);
            if (i == -1)
                ft_printf("something wrong !-----------\n");
            ret->ret = i;
            ret->pids = NULL;
            return (ret);
        }
        else if (i < 0)
            printf("THE FORK FAILED ! \n");
    }
    return (ret);
}
