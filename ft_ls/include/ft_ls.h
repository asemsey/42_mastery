#ifndef FT_LS_H
#define FT_LS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>

# include "libft.h"

// data -------------------------------------

typedef struct s_filedata t_filedata;

// main data structure
typedef struct s_ls {
	int			cmd_flags;
	t_list		*files;
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

struct s_filedata {
	char				*name;
	char				f_type;// dir|symlink|file|socket
	char				permissions[10];
	off_t				bytes;
	blkcnt_t			blocks;
	time_t				modified;
	nlink_t				links;
	uid_t				own_user;
	gid_t				own_group;
	t_list				*files;
	int					num_files;// len of `files`
};

// functions --------------------------------

// 		filedata.c
t_filedata	*init_filedata();
t_filedata	*init_file_name(char *name);
void		free_filedata(void *file);
// 		handle_args.c
t_list		*names_to_filedata(t_list *paths);
int			set_flags(t_list *flags);
void		separate_args(int argc, char **argv, t_list **paths, t_list **flags);
char		*arg_to_path(char *pwd, char *arg);
// 		file_info.c
void		set_fileinfo(t_filedata *file, int flags, char *prefix);
void		set_permissions(mode_t st_mode, char *p);
char		get_filemode(mode_t st_mode);
//		display.c
void		display_entries(t_list *files, int flags);
// 		format.c
int			size_columns(t_list *files, int sizes[4], int flags);
void		display_modified(time_t seconds, time_t now);
void		print_space(int n);
// 		directories.c
void		handle_one_dir(t_list *files, int cmd_flags);
void		handle_dirs(t_list *files, int cmd_flags, char *prefix);
char		*create_file_prefix(char *path, char *dirname);
t_list		*dir_to_lst(char *path);
// 		mergesort.c
void		merge_sort(t_list **lst, t_list *(*comp)(t_list *, t_list *, int), int len, int reverse);
t_list		*comp_time(t_list *l1, t_list *l2, int reverse);
t_list		*comp_alpha(t_list *l1, t_list *l2, int reverse);

#endif
