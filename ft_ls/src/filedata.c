#include "ft_ls.h"

t_filedata	*init_filedata();
t_list		*init_dir(char *name);
t_filedata	*init_file_name(char *name);
void		free_filedata(void *file);

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

// initialize a filedata list from dir contents (malloc)
t_list	*init_dir(char *name) {
	// t_list	*init;
	t_list	*files;

	files = dir_to_lst(name);
	if (!files)
		return NULL;
	// init = names_to_filedata(files);
	// ft_lstclear(&files, free);
	return files;
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

void free_filedata(void *file) {

	if (!file)
		return ;
	t_filedata *f = (t_filedata *)file;
	if (f->files)
		ft_lstclear(&f->files, free_filedata);
	if (f->name)
		free(f->name);
	free(file);
	return ;
}
