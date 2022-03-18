/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thamon <thamon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 14:35:48 by thamon            #+#    #+#             */
/*   Updated: 2022/03/18 13:37:02 by thamon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = 127;
	else
		ret = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	child(char *path, char **args, t_mini *mini, t_env *env)
{
	char	**env_array;
	char	*tmp;
	int		ret;

	ret = 0;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		tmp = env_on_str(env);
		env_array = ft_split(tmp, '\n');
		ft_memdel(tmp);
		if (ft_strchr(path, '/'))
			execve(path, args, env_array);
		ret = error_message(path);
		free_array(env_array);
		free_token(mini->token);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	ret = child2(ret);
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	*check_dir(char *bin, char *cmd)
{
	DIR				*folder;
	struct dirent	*dir;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	dir = readdir(folder);
	while (dir != NULL)
	{
		if (dir == NULL)
			break ;
		if (ft_strcmp(dir->d_name, cmd) == 0)
			path = path_join(bin, dir->d_name);
		dir = readdir(folder);
	}
	closedir(folder);
	return (path);
}

int	exec_bin(char **args, t_mini *mini, t_env *env)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = 0;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (child(args[0], args, mini, env));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (1);
	path = check_dir(bin[0] + 5, args[0]);
	i = 1;
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path)
		ret = child(path, args, mini, env);
	else
		ret = child(args[0], args, mini, env);
	free_array(bin);
	ft_memdel(path);
	return (ret);
}
