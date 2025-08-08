#include "ft_ls.h"

t_list		*names_to_filedata(t_list *paths);
int			set_flags(t_list *flags);
void		separate_args(int argc, char **argv, t_list **paths, t_list **flags);
char		*arg_to_path(char *pwd, char *arg);

// ----------------------------------------------------------------------

// turns a string into an absolute path (malloc)
char *arg_to_path(char *pwd, char *arg) {
	char *tmp = NULL;
	char *path = NULL;

	if (!pwd || !arg)
		return NULL;
	// handle absolute path
	if (*arg && *arg == '/') {
		path = ft_strdup(arg);
	} else {
		tmp = ft_strjoin(pwd, "/");
		path = ft_strjoin(tmp, arg);
		free(tmp);
	}
	return path;
}

// split argv into flags and paths (t_lists malloc)
void separate_args(int argc, char **argv, t_list **paths, t_list **flags) {
	int flag_end = 0;
	if (argc == 1)
		ft_lstadd_back(paths, ft_lstnew("."));
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] && argv[i][0] == '-') {
			if (flag_end) {
				ft_lstadd_back(paths, ft_lstnew(argv[i]));// after --
			} else if (argv[i][1]) {
				if (argv[i][1] == '-' && !argv[i][2])
					flag_end = 1;// --
				else
					ft_lstadd_back(flags, ft_lstnew(argv[i]));// -? or --?
			} else {
				ft_lstadd_back(paths, ft_lstnew(argv[i]));// -
			}
		} else {
			flag_end = 1;
			ft_lstadd_back(paths, ft_lstnew(argv[i]));// path
		}
	}
	if (ft_lstsize(*paths) < 1)
		ft_lstadd_back(paths, ft_lstnew("."));
}

// go through flag strings and set bitflag
int set_flags(t_list *flags) {
	int bits = 0;
	while (flags) {
		char *s = flags->content + 1;
		while (s && *s) {
			if (*s == 'l')
				bits |= LONG;
			else if (*s == 'R')
				bits |= RECURSIVE;
			else if (*s == 'a')
				bits |= HIDDEN;
			else if (*s == 'r')
				bits |= REVERSE;
			else if (*s == 't')
				bits |= TIMESORT;
			else {
				ft_printf("ft_ls: illegal option -- %c\nusage: ./ft_ls [-Ralrt] [file ...]", *s);
				return INVALID;
			}
			s++;
		}
		flags = flags->next;
	}
	return bits;
}

// go through paths list and init filedata into list (t_list malloc)
t_list *names_to_filedata(t_list *paths) { //HERE can maybe be improved by adding param to say if was malloced and doing changes in place, no returning
	t_list *files = NULL;
	while (paths) {
		ft_lstadd_back(&files, ft_lstnew(init_file_name(ft_strdup(paths->content))));
		paths = paths->next;
	}
	return files;
}
