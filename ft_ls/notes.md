# ft_ls
## about ls
### options
option | description
-------|---------------------------------------
`-l`   | long format. show permissions, file size, owner, etc.
`-R`   | list subdirectories recursively
`-a`   | include . (hidden) directories
`-r`   | reversed sort. normally reverse lexicographical, can be combined with other options
`-t`   | sort by last modified (new to old), then lexicographical

### allowed funcs
- `<stdio.h>`
	perror ◦ strerror
- `<stdlib.h>`
	malloc ◦ free ◦ exit
- `<unistd.h>`
	write ◦ readlink
- `<uuid/uuid.h>`
	getpwuid ◦ getgrgid -> search the password/group database
- `<sys/xattr.h>`
	listxattr ◦ getxattr
- `<sys/stat.h>`
	stat ◦ lstat -> get file info, lstat does not follow link
- `<time.h>`
	time ◦ ctime
- `<dirent.h>`
	opendir ◦ readdir ◦ closedir

## planing process

### ls needs...
- file names
- file permissions
- file sizes
- file creation/edit time
- file type info
- file group/owner
- normal/hidden files/symlinks
- data type sortable by different criteria
- files in subdirectories

### ls features
- when multilpe paths are given each arg is first checked for existence, then valid ones are announced (`dir:\n`) and handled. flags apply to all.
- files go first, then directories are listed.
- `--` signals the end of flag arguments, so that files starting with `-` can be listed without being interpreted as a flag.

### file data struct

```
typedef struct s_filedata {
	char *name;
	int f_type;// dir|symlink|file|socket
	double bytes;
	int permissions;// format of chmod - three bits?
	t_time created;
	t_time modified;
	struct s_filedata **files;// if f_type is dir this contains files
	int num_files;//len of `files`
}	t_filedata;
```
