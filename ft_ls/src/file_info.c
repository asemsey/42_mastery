#include "../include/ft_ls.h"

void		set_file_info(t_filedata **files, int flags);
void		set_permissions(mode_t st_mode, char *p);
char		get_filemode(mode_t st_mode);
void		print_modified(time_t seconds, time_t now);


// ----------------------------------------------------------------------

// go through files and fetch needed info according to flags
void		set_file_info(t_filedata **files, int flags) {
	int i;
	struct stat filestat;
	i = 0;
	while (files && files[i]) {
		if (lstat(files[i]->name, &filestat) < 0) {
			ft_printf("ft_ls: %s: No such file or directory\n", files[i++]->name);
			continue;
		}
		files[i]->f_type = get_filemode(filestat.st_mode);
		if (flags & LONG) {
			files[i]->bytes = filestat.st_size;
			files[i]->blocks = filestat.st_blocks;
			files[i]->links = filestat.st_nlink;
			files[i]->modified = filestat.st_mtimespec.tv_sec;
			set_permissions(filestat.st_mode, files[i]->permissions);
			// HERE
		}
		i++;
	}
}

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

void print_modified(time_t seconds, time_t now) {
	char *str = ctime(&seconds);
	char *year = str + 20;
	char *date = str + 4;
	time_t diff;

	if (ft_strlen(str) < 25)// format different?
		return;
	*(year + 4) = '\0';

	diff = now - seconds;// if past > 0, future < 0
	if (diff < 0)
		diff = -diff;
	if (diff > 15552000) {//six months
		*(date + 6) = '\0';
		ft_printf("%s %s", date, year);
	} else {
		*(date + 12) = '\0';
		ft_printf("%s", date);
	}
	// Www Mmm dd hh:mm:ss yyyy\n
	// Mmm dd hh:mm -> Jul  7 10:55
	// Mmm dd yyyy  -> Jul  7 2025
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