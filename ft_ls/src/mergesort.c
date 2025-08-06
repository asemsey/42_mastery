#include "ft_ls.h"

void	merge_sort(t_list **lst, t_list *(*comp)(t_list *, t_list *), int len);
t_list	*comp_time(t_list *l1, t_list *l2);
t_list	*comp_alpha(t_list *l1, t_list *l2);

// ----------------------------------------------------------------------

void		merge_sort(t_list **lst, t_list *(*comp)(t_list *, t_list *), int len) {
	t_list *c = NULL;
	t_list *f1 = NULL;
	t_list *f2 = NULL;
	t_list *buf = NULL;
	// if len<3 compare, swap, return
	if (len < 3) {
		c = comp(*lst, (*lst)->next);
		if (c == (*lst)->next)
			ft_lstswap(lst);
		return;
	}
	// for i=0;i<(len/2+len%2);i++   f2 = f2.next
	for (int i = 0; i < (len/2 + len%2);i++)
		ft_lstadd_back(&f1, ft_lstpopout(lst, (*lst)->content));
	for (int i = 0; i < (len/2);i++)
		ft_lstadd_back(&f2, ft_lstpopout(lst, (*lst)->content));
	merge_sort(&f1, comp, len/2+len%2);
	merge_sort(&f2, comp, len/2);
	// into result list:
	while (f1 || f2) {
		c = comp(f1, f2);
		if (!c)
			break;
		if (c == f1)
			ft_lstadd_back(&buf, ft_lstpopout(&f1, c->content));
		if (c == f2)
			ft_lstadd_back(&buf, ft_lstpopout(&f2, c->content));
	}
	ft_lstpushin(lst, buf);
}

t_list	*comp_alpha(t_list *l1, t_list *l2) {
	// NULL checks
	if (!l1 || !l1->content) {
		if (l2 && l2->content)
			return l2;
		return NULL;
	}
	if (!l2 || !l2->content)
		return l1;

	t_filedata *f1 = (t_filedata *)l1->content;
	t_filedata *f2 = (t_filedata *)l2->content;
	int len1 = ft_strlen(f1->name);
	int len2 = ft_strlen(f2->name);
	int c = ft_strncmp(f1->name, f2->name, (len1 <= len2 ? len1 : len2));
	if (c == 0) // return shorter one
		return (len1 <= len2 ? l1 : l2);
	return (c < 0 ? l1 : l2);
}

t_list	*comp_time(t_list *l1, t_list *l2) {
	// NULL checks
	if (!l1 || !l1->content) {
		if (l2 && l2->content)
			return l2;
		return NULL;
	}
	if (!l2 || !l2->content)
		return l1;

	t_filedata *f1 = (t_filedata *)l1->content;
	t_filedata *f2 = (t_filedata *)l2->content;
	if (f1->modified > f2->modified)
		return l1;
	return l2;
}

// DEBUG OUTPUT
// -rw-rw-r--  1 asemsey  asemsey  4396 Jul 30 16:25 directories.c
// -rw-rw-r--  1 asemsey  asemsey  3471 Jul 30 15:36 file_info.c
// -rw-rw-r--  1 asemsey  asemsey  1550 Jul 30 15:29 filedata.c
// -rw-rw-r--  1 asemsey  asemsey  3401 Jul 30 15:06 handle_args.c
// -rw-rw-r--  1 asemsey  asemsey  2258 Jul 30 14:46 test_helpers.c
// -rw-rw-r--  1 asemsey  asemsey  2108 Jul 30 16:23 mergesort.c
// -rw-rw-r--  1 asemsey  asemsey  3434 Jul 30 14:15 format.c
// -rw-rw-r--  1 asemsey  asemsey  2124 Jul 30 16:25 main.c

//  ./ft_ls -la src
// DEBUG called merge_sort len=10 lst=..
// DEBUG set f2=directories.c
// DEBUG set f2=file_info.c
// DEBUG set f2=filedata.c
// DEBUG set f2=handle_args.c
// DEBUG set f2=test_helpers.c
// DEBUG call f1
// DEBUG called merge_sort len=5 lst=..
// DEBUG set f2=directories.c
// DEBUG set f2=file_info.c
// DEBUG call f1
// DEBUG called merge_sort len=3 lst=..
// DEBUG set f2=directories.c
// DEBUG call f1
// DEBUG called merge_sort len=2 lst=..
// DEBUG set f2=directories.c
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=..
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=directories.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=directories.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=2 lst=file_info.c
// DEBUG set f2=filedata.c
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=file_info.c
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=filedata.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=5 lst=test_helpers.c
// DEBUG set f2=mergesort.c
// DEBUG set f2=format.c
// DEBUG call f1
// DEBUG called merge_sort len=3 lst=test_helpers.c
// DEBUG set f2=mergesort.c
// DEBUG call f1
// DEBUG called merge_sort len=2 lst=test_helpers.c
// DEBUG set f2=mergesort.c
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=test_helpers.c
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=mergesort.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=mergesort.c
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=2 lst=format.c
// DEBUG set f2=.
// DEBUG call f1
// DEBUG called merge_sort len=1 lst=format.c
// ft_ls: merge_sort returns
// DEBUG call f2
// DEBUG called merge_sort len=1 lst=.
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// ft_ls: merge_sort returns
// drwxrwxr-x  7 asemsey  asemsey  4096 Jul 30 16:33 ..
// -rw-rw-r--  1 asemsey  asemsey  6902 Jul 30 16:28 directories.c
// -rw-rw-r--  1 asemsey  asemsey  3471 Jul 30 15:36 file_info.c
// -rw-rw-r--  1 asemsey  asemsey  1550 Jul 30 15:29 filedata.c
// -rw-rw-r--  1 asemsey  asemsey  3401 Jul 30 15:06 handle_args.c
// -rw-rw-r--  1 asemsey  asemsey  2258 Jul 30 14:46 test_helpers.c
// -rw-rw-r--  1 asemsey  asemsey  2142 Jul 30 16:33 mergesort.c
// -rw-rw-r--  1 asemsey  asemsey  3434 Jul 30 14:15 format.c
// drwxrwxr-x  2 asemsey  asemsey  4096 Jul 30 12:23 .
// -rw-rw-r--  1 asemsey  asemsey  2121 Jul 30 16:25 main.c
