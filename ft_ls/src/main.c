#include "../include/ft_ls.h"

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
	data.files = set_paths(data.path_args, data.pwd);

	set_file_info(data.files, data.cmd_flags);
	// open given directory
	// DIR *directory = opendir(data.pwd);
	// if (!directory) {
	// 	free_data(&data);
	// 	return 1;
	// }
	// // list names of all files separated by two tabs
	// struct dirent *one_file = readdir(directory);
	// while (one_file) {
	// 	ft_printf("%s\t\t", one_file->d_name);
	// 	one_file = readdir(directory);
	// }
	// write(1, "\n", 1);
	// // clean up
	// closedir(directory);

	do_ls(&data);

	free_ls_data(&data);
	return 0;
}

void free_ls_data(t_ls *data) {
	if (data->files) {
		for (int i = 0; data->files[i] != NULL; i++) {
			free_filedata(data->files[i]);
		}
		free(data->files);
	}
	if (data->flag_args)
		ft_lstclear(&(data->flag_args), NULL);
	if (data->path_args)
		ft_lstclear(&(data->path_args), NULL);
}

int do_ls(t_ls *data) {
	// test_arg_init(data);
	test_modtime(data);
	// go through data.files, check if exists and set info according to flags
		// set error strings in struct
	// display errors, run ls on rest
		// illegal option shows nothing but error and usage !
		// all other errors listed then correct input exec
	return 0;
}
