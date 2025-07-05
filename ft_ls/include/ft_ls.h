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

enum e_ftype {
	F_DIR,
	F_LINK,
	F_FILE,
	F_SOCK
};

typedef struct s_filedata {
	char *name;
	enum e_ftype f_type;// dir|symlink|file|socket
	double bytes;
	int permissions;// format of chmod - three bits?
	time_t created;
	time_t modified;
	struct s_filedata **files;// if f_type is dir this contains files -- should this be linkedlist?
	int num_files;// len of `files`
}	t_filedata;

// functions --------------------------------

// 		filedata.c
t_filedata	*init_filedata();
void free_filedata(t_filedata *file);

#endif
