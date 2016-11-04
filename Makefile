all:
	@gcc main.c avltree_site.c avltree_keywords.c interface.c site.c -I. -o main