#include "../include/ft_ls.h"

t_filedata	*init_filedata();
t_filedata	*init_file_name(char *name, char *path);
void free_filedata(t_filedata *file);

// ----------------------------------------------------------------------

// initialize a filedata object by name,path (malloc)
t_filedata	*init_file_name(char *name, char *path) {
	t_filedata *init;

	init = init_filedata();
	if (!init)
		return NULL;
	init->path = path;
	init->name = name;
	return init;
}

// initialize a filedata object (malloc)
t_filedata	*init_filedata() {
	t_filedata *init;

	init = (t_filedata *)malloc(sizeof(t_filedata));
	if (!init)
		return NULL;
	init->bytes = -1;//unset
	init->created = (time_t)0;
	init->modified = (time_t)0;
	init->f_type = F_FILE;
	init->files = NULL;
	init->name = NULL;
	init->path = NULL;
	init->num_files = -1;//not a dir
	init->permissions = -1;//unset
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
	if (file->path)
		free(file->path);
	free(file);
	return ;
}
