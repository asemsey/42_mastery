# ft_ls
## about ls
### options
option | description
-------|---------------------------------------
`-l`   | long format. total file size in blocks on top, then show permissions, file size, owner, etc.
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

**Symlinks:**
cmd|result|change
---|------|------
ls    | `lib_link`
ls -l | `lrwxr-xr-x  1 asemsey  2023_heilbronn  5 Jul  7 12:39 lib_link -> libft`   | "l" and "-> name_of_file"
ls -R | `lib_link`
stat -l | `lrwxr-xr-x 1 asemsey 2023_heilbronn 5 Jul  7 12:39:15 2025 lib_link -> libft`

### stat and ls -l
```bash
ls -l:		-rw-r--r--  1  asemsey  2023_heilbronn  844 Jul  7 10:55 Makefile
stat:		16777225 6081377 -rw-r--r-- 1 asemsey 2023_heilbronn 0 844 "Jul  7 11:22:49 2025" "Jul  7 10:55:25 2025" "Jul  7 10:55:25 2025" "Jul  5 12:20:17 2025" 4096 8 0 Makefile
stat -l:	-rw-r--r-- 1 asemsey 2023_heilbronn 844 Jul  7 10:55:25 2025 Makefile
```

```C
struct stat {
	mode_t          st_mode;        /* [XSI] Mode of file (see below)*/
	nlink_t         st_nlink;       /* [XSI] Number of hard links*/
	uid_t           st_uid;         /* [XSI] User ID of the file*/
	gid_t           st_gid;         /* [XSI] Group ID of the file*/
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
	struct  timespec st_mtimespec;  /* time of last data modification*/
#else
	time_t          st_mtime;       /* [XSI] Last data modification time << this one*/ 
#endif
	off_t           st_size;        /* [XSI] file size, in bytes*/
	blkcnt_t        st_blocks;      /* [XSI] blocks allocated for file*/
	blksize_t       st_blksize;     /* [XSI] optimal blocksize for I/O*/
}
```

### file data struct (recursive)

```C
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

## man ls - long format
```txt
If the -l option is given, the following information is displayed for each file: 
file mode, number of links, owner name, group name, number of bytes in the file, 
abbreviated month, day-of-month file was last modified, hour file last modified, 
minute file last modified, and the pathname.  In addition, for each directory whose 
contents are displayed, the total number of 512-byte blocks used by the files in 
the directory is displayed on a line by itself, immediately before the information 
for the files in the directory.  If the file or directory has extended attributes, 
the permissions field printed by the -l option is followed by a '@' character.
Otherwise, if the file or directory has extended security information (such as an 
access control list), the permissions field printed by the -l option is followed 
by a '+' character.  If the -% option is given, a '%' character follows the 
permissions field for dataless files and directories, possibly replacing the 
'@' or '+' character.

If the modification time of the file is more than 6 months in the past or future, then the year of the last modification is displayed in place of the hour and minute fields.

If the owner or group names are not a known user or group name, or the -n option is given, the numeric ID's are displayed.

If the file is a character special or block special file, the major and minor device numbers for the file are displayed in the size field.  If the file is a symbolic link, the pathname of the linked-to file is preceded by ``->''.

The file mode printed under the -l option consists of the entry type, owner permissions, and group permissions.  The entry type character describes the type of file, as follows:

	b	Block special file.
	c	Character special file.
	d	Directory.
	l	Symbolic link.
	s	Socket link.
	p	FIFO.
	-	Regular file.

The next three fields are three characters each: owner permissions, group permissions, and other permissions.  Each field has three character positions:

	1.	If r, the file is readable; if -, it is not readable.

	2.	If w, the file is writable; if -, it is not writable.

	3.	The first of the following that applies:

		S	If in the owner permissions, the file is not executable and set-user-ID mode is set.  If in the group permissions, the file is not executable and set-group-ID mode is set.

		s	If in the owner permissions, the file is executable and set-user-ID mode is set.  If in the group permissions, the file is executable and setgroup-ID mode is set.

		x	The file is executable or the directory is searchable.

		-	The file is neither readable, writable, executable, nor set-user-ID nor set-group-ID mode, nor sticky.  (See below.)

	These next two apply only to the third character in the last group (other permissions).

		T	The sticky bit is set (mode 1000), but not execute or search permission.  (See chmod(1) or sticky(8).)

		t	The sticky bit is set (mode 1000), and is searchable or executable.  (See chmod(1) or sticky(8).)

```