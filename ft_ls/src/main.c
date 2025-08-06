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
	data.files = names_to_filedata(data.path_args);

	if (data.files) {
		do_ls(&data);
	}

	free_ls_data(&data);
	return 0;
}

	/*
	// args are in data.files, flags set
	// set info for each
			foreach file in files set_info(file);
	// sort and display all
			sort(files, cmd_flags);
			display(files, cmd_flags);
	// go into dirs (new func so recursion is considered)
			foreach file in files
				if (is_dir)
					handle_dir(files, cmd_flags);
		// readdir to list
					read = all_files_in_dir();
		// sort and display
					sort(read, cmd_flags);
					display(read, cmd_flags);
		// if -R go into dirs, repeat this last algo
					if (cmd_flags & R)
						foreach file in read ..., free when a dir is closed
	// free and exit
		free_data(data);
	*/

int do_ls(t_ls *data) {
	// test_arg_init(data);//test
	for (t_list *tmp = data->files; tmp != NULL; tmp = tmp->next) {
		set_fileinfo((t_filedata *)tmp->content, data->cmd_flags, NULL);
	}
	// for (int i = 0; data->files[i] != NULL; i++) {
	// 	set_fileinfo(data->files[i], data->cmd_flags, NULL);
	// }

	// sort_entries(data->files, data->cmd_flags);
	if (data->files && !data->files->next) {
		handle_one_dir(data->files, data->cmd_flags);
	} else {
		merge_sort(&data->files, ((data->cmd_flags & TIMESORT) ? comp_time : comp_alpha), ft_lstsize(data->files), (data->cmd_flags & REVERSE));//SORT
		display_entries(data->files, data->cmd_flags);
		handle_dirs(data->files, data->cmd_flags, NULL);
	}
	return 0;
}

void free_ls_data(t_ls *data) {
	if (data->files)
		ft_lstclear(&(data->files), free_filedata);
	if (data->flag_args)
		ft_lstclear(&(data->flag_args), NULL);
	if (data->path_args)
		ft_lstclear(&(data->path_args), NULL);
}
