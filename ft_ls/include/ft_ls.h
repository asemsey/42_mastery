#ifndef FT_LS_H
#define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <time.h>
# include <dirent.h>

# include "../libft/libft.h"

// data -------------------------------------

typedef struct s_filedata t_filedata;

// main data structure
typedef struct s_ls {
	int			cmd_flags;
	t_filedata	**files;
	char		*pwd;
	t_list		*flag_args;
	t_list		*path_args;
}	t_ls;

enum e_flag {
	LONG = 1 << 0,
	RECURSIVE = 1 << 1,
	HIDDEN = 1 << 2,
	REVERSE = 1 << 3,
	TIMESORT = 1 << 4,
	INVALID = 1 << 5
};

enum e_ftype {
	F_DIR,
	F_LINK,
	F_FILE,
	F_SOCK
};

struct s_filedata {
	char *name;
	char *path;
	enum e_ftype f_type;// dir|symlink|file|socket
	double bytes;
	int permissions;// format of chmod - three bits?
	time_t created;
	time_t modified;
	struct s_filedata **files;// if f_type is dir this contains files -- should this be linkedlist?
	int num_files;// len of `files`
};

// functions --------------------------------

// 		filedata.c
t_filedata	*init_filedata();
t_filedata	*init_file_name(char *name, char *path);
void		free_filedata(t_filedata *file);
// 		handle_args.c
t_filedata	**set_paths(t_list *paths, char *pwd);
int			set_flags(t_list *flags);
void		separate_args(int argc, char **argv, t_list **paths, t_list **flags);
char		*arg_to_path(char *pwd, char *arg);

// 		test_helpers.c
void		test_arg_init(t_ls *data);

#endif
