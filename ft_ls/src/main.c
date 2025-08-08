#include "ft_ls.h"

void	free_ls_data(t_ls *data);
int		do_ls(t_ls *data);

int	main(int argc, char **argv, char **env) {
	t_ls data;
	ft_bzero(&data, sizeof(t_ls));
	// get current path
	if (!env)
		return 1;
	data.pwd = ft_getenv("PWD", env);
	if (!data.pwd)
		return 1;
	// separate args to files and flags
	separate_args(argc, argv, &(data.path_args), &(data.flag_args));
	data.cmd_flags = set_flags(data.flag_args);
	if (data.cmd_flags == INVALID) {
		free_ls_data(&data);
		return 1;
	}
	// collect data about files and display
	data.files = names_to_filedata(data.path_args);
	if (data.files) {
		do_ls(&data);
	}

	free_ls_data(&data);
	return 0;
}

int	do_ls(t_ls *data) {
	for (t_list *tmp = data->files; tmp != NULL; tmp = tmp->next) {
		set_fileinfo((t_filedata *)tmp->content, data->cmd_flags, NULL);
	}
	if (data->files && !data->files->next) {
		handle_one_dir(data->files, data->cmd_flags);
	} else {
		merge_sort(&data->files, ((data->cmd_flags & TIMESORT) ? comp_time : comp_alpha),\
					ft_lstsize(data->files), (data->cmd_flags & REVERSE));
		display_entries(data->files, data->cmd_flags);
		handle_dirs(data->files, data->cmd_flags, NULL);
	}
	return 0;
}

void	free_ls_data(t_ls *data) {
	if (data->files)
		ft_lstclear(&(data->files), free_filedata);
	if (data->flag_args)
		ft_lstclear(&(data->flag_args), NULL);
	if (data->path_args)
		ft_lstclear(&(data->path_args), NULL);
}
