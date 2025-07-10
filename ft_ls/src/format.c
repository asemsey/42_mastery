#include "ft_ls.h"

void		display_entries(t_filedata **files, int flags);
void		print_modified(time_t seconds, time_t now);

// ----------------------------------------------------------------------

void display_entries(t_filedata **files, int flags) {
	char *user;
	if (!files)
		return ;
	if (flags & LONG) {// case -l
		time_t now = time(NULL);
		// display total blocks HERE
		for (int i = 0; files[i] != NULL; i++) {
			if (!(flags & HIDDEN) && files[i]->name[0] == '.')
				continue;
			if (files[i]->bytes >= 0) {
				user = find_id(files[i]->own_user, 1);
				if (user)
					ft_printf("%c%s  %d %s  ", files[i]->f_type, files[i]->permissions, files[i]->links, user);
				else
					ft_printf("%c%s  %d %u  ", files[i]->f_type, files[i]->permissions, files[i]->links, files[i]->own_user);
				user = find_id(files[i]->own_group, 0);
				if (user)
					ft_printf("%s  %d ", user, files[i]->bytes);
				else
					ft_printf("%u  %d ", files[i]->own_group, files[i]->bytes);
				print_modified(files[i]->modified, now);
				ft_printf(" %s\n", files[i]->name);
			}
		}
	} else {// default
		for (int i = 0; files[i] != NULL; i++) {
			if (!(flags & HIDDEN) && files[i]->name[0] == '.')
				continue;
			if (files[i]->bytes >= 0)
				ft_printf("%s\t\t", files[i]->name);
		}
		write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

// print the date string in the ls -l format, no '\n'
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
