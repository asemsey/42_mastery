#include "ft_ls.h"

void	merge_sort(t_list **lst, t_list *(*comp)(t_list *, t_list *, int), int len, int reverse);
t_list	*comp_time(t_list *l1, t_list *l2, int reverse);
t_list	*comp_alpha(t_list *l1, t_list *l2, int reverse);

// ----------------------------------------------------------------------

void		merge_sort(t_list **lst, t_list *(*comp)(t_list *, t_list *, int), int len, int reverse) {
	t_list *c = NULL;
	t_list *f1 = NULL;
	t_list *f2 = NULL;
	t_list *buf = NULL;
	// if len<3 compare, swap, return
	if (len < 3) {
		c = comp(*lst, (*lst)->next, reverse);
		if (c == (*lst)->next)
			ft_lstswap(lst);
		return;
	}
	for (int i = 0; i < (len/2 + len%2);i++)
		ft_lstadd_back(&f1, ft_lstpopout(lst, (*lst)->content));
	for (int i = 0; i < (len/2);i++)
		ft_lstadd_back(&f2, ft_lstpopout(lst, (*lst)->content));
	merge_sort(&f1, comp, len/2+len%2, reverse);
	merge_sort(&f2, comp, len/2, reverse);
	// into result list:
	while (f1 || f2) {
		c = comp(f1, f2, reverse);
		if (!c)
			break;
		if (c == f1)
			ft_lstadd_back(&buf, ft_lstpopout(&f1, c->content));
		if (c == f2)
			ft_lstadd_back(&buf, ft_lstpopout(&f2, c->content));
	}
	ft_lstpushin(lst, buf);
}

t_list	*comp_alpha(t_list *l1, t_list *l2, int reverse) {
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
	if (c == 0) {
		if (reverse)
			return (len1 <= len2 ? l2 : l1);
		return (len1 <= len2 ? l1 : l2);// return shorter one
	}
	if (reverse)
		return (c < 0 ? l2 : l1);
	return (c < 0 ? l1 : l2);
}

t_list	*comp_time(t_list *l1, t_list *l2, int reverse) {
	if (!l1 || !l1->content) {
		if (l2 && l2->content)
			return l2;
		return NULL;
	}
	if (!l2 || !l2->content)
		return l1;

	t_filedata *f1 = (t_filedata *)l1->content;
	t_filedata *f2 = (t_filedata *)l2->content;
	if (f1->modified == f2->modified)
		return comp_alpha(l1, l2, reverse);
	if (f1->modified > f2->modified)
		return (reverse ? l2 : l1);
	return (reverse ? l1 : l2);
}
