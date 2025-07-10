#include "ft_ls.h"

t_list		*dir_to_lst(char *path);
void		handle_one_dir(t_filedata **dir, int cmd_flags);
void		handle_dirs(t_filedata **files, int cmd_flags, char *prefix);
int			ignore_dir(char *str);
char		*create_file_prefix(char *path, char *dirname);

// ----------------------------------------------------------------------

void handle_dirs(t_filedata **files, int cmd_flags, char *prefix) {
	char *pre = NULL;
	t_filedata **contents = NULL;
	if (!files)
		return;
	for (int i = 0; files[i] != NULL; i++) {
		if (files[i]->f_type != 'd' || ignore_dir(files[i]->name))
			continue;
		if (prefix) {
			pre = create_file_prefix(prefix, files[i]->name);
			ft_printf("%s:\n", pre);
			contents = init_dir(pre);
		} else {
			ft_printf("%s:\n", files[i]->name);
			contents = init_dir(files[i]->name);
		}
		for (int i = 0; contents[i] != NULL; i++) {
			set_fileinfo(contents[i], cmd_flags, pre);
		}
		display_entries(contents, cmd_flags);
		if (cmd_flags & RECURSIVE)
			handle_dirs(contents, cmd_flags, pre);
		for (int i = 0; contents[i] != NULL; i++) {
			free_filedata(contents[i]);
		}
		free(contents);
		if (pre)
			free(pre);
	}
}

// create string: path/dirname (malloc)
char *create_file_prefix(char *path, char *dirname) {
	char *tmp;
	char *res;
	tmp = ft_strjoin(path, "/");
	res = ft_strjoin(tmp, dirname);
	free(tmp);
	return res;
}

void handle_one_dir(t_filedata **files, int cmd_flags) {
	t_filedata **contents = NULL;
	if (!files)
		return;
	if (files[0]->f_type != 'd') {
		display_entries(files, cmd_flags);
		return;
	}
	contents = init_dir(files[0]->name);
	for (int i = 0; contents[i] != NULL; i++) {
		set_fileinfo(contents[i], cmd_flags, files[0]->name);
	}
	display_entries(contents, cmd_flags);
	if (cmd_flags & RECURSIVE)
		handle_dirs(contents, cmd_flags, files[0]->name);
	for (int i = 0; contents[i] != NULL; i++) {
		free_filedata(contents[i]);
	}
	free(contents);
}

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

int ignore_dir(char *str) {
	if (!str || !*str)
		return 1;
	if (*str != '.')
		return 0;
	if (!str[1] || (str[1] == '.' && !str[2]))// . or ..
		return 1;
	return 0;
}