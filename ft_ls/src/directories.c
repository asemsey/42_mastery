#include "../include/ft_ls.h"

t_list		*dir_to_lst(char *path);
void		handle_dirs(t_filedata **files, int cmd_flags);

// ----------------------------------------------------------------------

void handle_dirs(t_filedata **files, int cmd_flags) {
	t_filedata **contents = NULL;
	if (!files)
		return;
	for (int i = 0; files[i] != NULL; i++) {
		if (files[i]->f_type != 'd')
			continue;
		contents = init_dir(files[i]->name);
		for (int i = 0; contents[i] != NULL; i++) {
			set_fileinfo(contents[i], cmd_flags);
		}
		display_entries(contents, cmd_flags);
		if (cmd_flags & RECURSIVE)
			handle_dirs(contents, cmd_flags);
		for (int i = 0; contents[i] != NULL; i++) {
			free_filedata(contents[i]);
		}
		free(contents);
	}
}
// foreach file in files
// if (is_dir)
// 	handle_dir(files, cmd_flags);
// 	read = all_files_in_dir();
// 	sort(read, cmd_flags);
// 	display(read, cmd_flags);
// 	if (cmd_flags & R)
// 		foreach file in read ..., free when a dir is closed

t_list *dir_to_lst(char *path) {
	DIR *dir;
	t_list *lst = NULL;
	if (!path || !*path)
		return NULL;

	dir = opendir(path);
	if (!dir)
		return NULL;
	struct dirent *file = readdir(dir);
	while (file) {
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(file->d_name)));
		file = readdir(dir);
	}
	closedir(dir);
	return lst;
}
