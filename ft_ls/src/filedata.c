#include "ft_ls.h"

t_filedata	*init_filedata();
t_filedata	**init_dir(char *name);
t_filedata	*init_file_name(char *name);
void		free_filedata(t_filedata *file);

// ----------------------------------------------------------------------

// initialize a filedata object by name (malloc)
t_filedata	*init_file_name(char *name) {
	t_filedata *init;

	init = init_filedata();
	if (!init)
		return NULL;
	init->name = name;
	return init;
}

// t_filedata	*init_file_name(char *name, char *path) {
// 	t_filedata *init;

// 	init = init_filedata();
// 	if (!init)
// 		return NULL;
// 	init->path = path;
// 	init->name = name;
// 	return init;
// }

// initialize a filedata array from dir contents (malloc)
t_filedata	**init_dir(char *name) {
	t_filedata **init;
	t_list	*files;

	files = dir_to_lst(name);
	if (!files)
		return NULL;
	init = lst_to_filedata(files);
	ft_lstclear(&files, free);
	return init;
}

// initialize a filedata object (malloc)
t_filedata	*init_filedata() {
	t_filedata *init;

	init = (t_filedata *)malloc(sizeof(t_filedata));
	if (!init)
		return NULL;
	init->bytes = -1;//unset
	init->blocks = -1;//unset
	// init->created = (time_t)0;
	init->modified = (time_t)0;
	init->f_type = '-';
	init->files = NULL;
	init->name = NULL;
	ft_strlcpy(init->permissions, "---------", 10);
	init->num_files = -1;//not a dir
	return init;
}

void free_filedata(t_filedata *file) {
	int i;

	if (!file)
		return ;
	if (file->num_files > 0) {
		i = 0;
		while (i < file->num_files)
			free_filedata(file->files[i++]);
		free(file->files);
	}
	if (file->name)
		free(file->name);
	free(file);
	return ;
}
