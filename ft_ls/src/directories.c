#include "ft_ls.h"

void		handle_dirs(t_list *files, int cmd_flags, char *prefix);
char		*create_file_prefix(char *path, char *dirname);
void		handle_one_dir(t_list *files, int cmd_flags);
t_list		*dir_to_lst(char *path);
int			ignore_dir(char *str, int hiddenflag);

// ----------------------------------------------------------------------

void handle_dirs(t_list *files, int cmd_flags, char *prefix) {
	char *pre = NULL;
	if (!files)
		return;
	while (files != NULL) {
		t_filedata *data = files->content;
		if (data->f_type != 'd' || ignore_dir(data->name, cmd_flags & HIDDEN)) {
			files = files->next;
			continue;
		}
		if (prefix) {
			pre = create_file_prefix(prefix, data->name);
			ft_printf("%s:\n", pre);
			data->files = dir_to_lst(pre);
		} else {
			ft_printf("%s:\n", data->name);
			data->files = dir_to_lst(data->name);
		}
		for (t_list *t = data->files; t != NULL; t = t->next) {
			set_fileinfo((t_filedata *)t->content, cmd_flags, (pre == NULL ? data->name: pre));
		}
		merge_sort(&data->files, ((cmd_flags & TIMESORT) ? comp_time : comp_alpha), ft_lstsize(data->files), (cmd_flags & REVERSE));//SORT
		display_entries(data->files, cmd_flags);
		if (cmd_flags & RECURSIVE)
			handle_dirs(data->files, cmd_flags, pre);
		ft_lstclear(&data->files, free_filedata);
		if (pre)
			free(pre);
		files = files->next;
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

void handle_one_dir(t_list *files, int cmd_flags) {
	if (!files)
		return;
	t_filedata *data = (t_filedata *)files->content;
	if (data->f_type != 'd') {
		display_entries(files, cmd_flags);
		return;
	}
	if (cmd_flags & RECURSIVE)
		ft_printf("%s:\n", data->name);
	data->files = dir_to_lst(data->name);
	for (t_list *t = data->files; t != NULL; t = t->next) {
		set_fileinfo((t_filedata *)t->content, cmd_flags, data->name);
	}
	merge_sort(&data->files, ((cmd_flags & TIMESORT) ? comp_time : comp_alpha), ft_lstsize(data->files), (cmd_flags & REVERSE));//SORT
	display_entries(data->files, cmd_flags);
	if (cmd_flags & RECURSIVE)
		handle_dirs(data->files, cmd_flags, data->name);
	ft_lstclear(&data->files, free_filedata);
}

// read directory and create list of t_filedata
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
		ft_lstadd_back(&lst, ft_lstnew(init_file_name(ft_strdup(file->d_name))));
		file = readdir(dir);
	}
	closedir(dir);
	return lst;
}

int ignore_dir(char *str, int hiddenflag) {
	if (!str || !*str)
		return 1;
	if (*str != '.')
		return 0;
	if (!hiddenflag && *str == '.')//hidden directory
		return 1;
	if (!str[1] || (str[1] == '.' && !str[2]))// . or ..
		return 1;
	return 0;
}
