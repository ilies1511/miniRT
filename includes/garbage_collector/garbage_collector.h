#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

//Libs
# include <stdlib.h>
# include <stdio.h>

//BEGIN: Structs
typedef struct s_gc_node
{
	void					*pointer;
	struct s_gc_node		*next;
}							t_gc_node;

typedef struct s_garbage_collector
{
	t_gc_node		*head;
	t_gc_node		*tail;
	size_t			size;
}					t_garbage_collector;
//END: Structs

//BEGIN: FNC-Prototyps
t_gc_node			*gc_create_node(void *pointer2mem);
void				gc_add_begin(t_garbage_collector *gc, void *pointer);
t_garbage_collector	*gc_init_garbage_collector(void);
void				gc_print_linked_list(t_garbage_collector *gc);
void				gc_free_all(t_garbage_collector *gc);
t_garbage_collector	*get_gc(void);
// void				*ft_malloc(size_t size);
void				*ft_malloc(size_t len);
//END: FNC-Prototyps

//BEGIN: FNC-Prototyps TEST
int					test_gc_init(void);
//END: FNC-Prototyps TEST
#endif