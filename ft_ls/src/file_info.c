#include "ft_ls.h"

void		set_fileinfo(t_filedata *file, int flags, char *prefix);
void		set_permissions(mode_t st_mode, char *p);
char		get_filemode(mode_t st_mode);
char		*find_id(unsigned int id, int is_user);

// ----------------------------------------------------------------------

// fetch file information using lstat
void	set_fileinfo(t_filedata *file, int flags, char *prefix) {
	struct stat filestat;
	char *full_name;
	if (prefix)
		full_name = create_file_prefix(prefix, file->name);
	else
		full_name = ft_strdup(file->name);
	if (lstat(full_name, &filestat) < 0) {
		ft_printf("ft_ls: %s: No such file or directory\n", file->name);
		free(full_name);
		return ;
	}
	free(full_name);
	file->f_type = get_filemode(filestat.st_mode);
	file->bytes = filestat.st_size;
	file->modified = filestat.st_mtimespec.tv_sec;
	// file-> modified = filestat.st_mtime;
	if (flags & LONG) {
		file->blocks = filestat.st_blocks;
		file->links = filestat.st_nlink;
		file->own_user = filestat.st_uid;
		file->own_group = filestat.st_gid;
		set_permissions(filestat.st_mode, file->permissions);
	}
}

char	*find_id(unsigned int id, int is_user) {
	struct passwd	*user;
	struct group	*group;
	if (is_user) {
		user = (struct passwd *)getpwuid((uid_t)id);
		if (user)
			return user->pw_name;
		return NULL;
	} else {
		group = (struct group *)getgrgid((gid_t)id);
		if (group)
			return group->gr_name;
		return NULL;
	}
	return NULL;
}

// return the character associated with the file mode
char get_filemode(mode_t st_mode) {
	mode_t newmode = st_mode & S_IFMT;
	if (newmode == S_IFBLK)
		return 'b';
	if (newmode == S_IFCHR)
		return 'c';
	if (newmode == S_IFDIR)
		return 'd';
	if (newmode == S_IFLNK)
		return 'l';
	if (newmode == S_IFSOCK)
		return 's';
	if (newmode == S_IFIFO)
		return 'p';
	if (newmode == S_IFREG)
		return '-';
	return 0;
}

// create the permission string without the filemode character
void set_permissions(mode_t st_mode, char *p) {
	if (ft_strlen(p) < 9)
		return;
	// owner permissions xxx------
	if (st_mode & S_IRUSR)
		p[0] = 'r';
	if (st_mode & S_IWUSR)
		p[1] = 'w';
	if (st_mode & S_IXUSR)
		p[2] = 'x';
	// group permissions ---xxx---
	if (st_mode & S_IRGRP)
		p[3] = 'r';
	if (st_mode & S_IWGRP)
		p[4] = 'w';
	if (st_mode & S_IXGRP)
		p[5] = 'x';
	// other permissions ------xxx
	if (st_mode & S_IROTH)
		p[6] = 'r';
	if (st_mode & S_IWOTH)
		p[7] = 'w';
	if (st_mode & S_IXOTH)// HERE: this last one seems more complex...
		p[8] = 'x';
	p[9] = '\0';
}

// mode_t st_mode bits:
// #define S_IFMT 0170000           /* type of file */
// #define        S_IFIFO  0010000  /* named pipe (fifo) */
// #define        S_IFCHR  0020000  /* character special */
// #define        S_IFDIR  0040000  /* directory */
// #define        S_IFBLK  0060000  /* block special */
// #define        S_IFREG  0100000  /* regular */
// #define        S_IFLNK  0120000  /* symbolic link */
// #define        S_IFSOCK 0140000  /* socket */
// #define        S_IFWHT  0160000  /* whiteout */
// #define S_ISUID 0004000  /* set user id on execution */
// #define S_ISGID 0002000  /* set group id on execution */
// #define S_ISVTX 0001000  /* save swapped text even after use */
// #define S_IRUSR 0000400  /* read permission, owner */
// #define S_IWUSR 0000200  /* write permission, owner */
// #define S_IXUSR 0000100  /* execute/search permission, owner */