#include "graph.h"

t_graph *gnode_new(void *content, size_t size)
{
	t_graph *node;

	if (!(node = malloc(sizeof(t_graph))))
		return (NULL);
	node->content = content;
	node->size = size;
	node->adjacency_list = NULL;
	node->iterator = NULL;
	node->visited = 0;
	return (node);
}

int *fill_content_int(int n)
{
	int		*content;

	content = malloc(sizeof(int));
	*content = n;
	return (content);
}

void	link_gnodes_push(t_graph *g0, t_graph *g1)
{
	lst_push(&g0->adjacency_list, lst_new(g1, sizeof(t_graph)));
}

void	link_gnodes_enqueue(t_graph *g0, t_graph *g1)
{
	lst_enqueue(&g0->adjacency_list, lst_new(g1, sizeof(t_graph)));
}

t_graph	*get_adjacent_node(t_graph *g)
{
	if (!g->iterator)
	{
		g->iterator = g->adjacency_list;
	}
	else
	{
		g->iterator = g->iterator->next;
	}
	return (g->iterator ? (t_graph *)g->iterator->content : NULL);
}

void	traverse_dfs_post_order(t_graph *start)
{
	t_graph *i;

	start->visited = 1;
	while ((i = get_adjacent_node(start)) && !i->visited)
	{
		traverse_dfs_post_order(i);
	}
	printf("%d\n", *((int *)start->content));
}

void	traverse_dfs_pre_order(t_graph *start)
{
	t_graph *i;

	printf("%d\n", *((int *)start->content));
	start->visited = 1;
	while ((i = get_adjacent_node(start)) && !i->visited)
	{
		traverse_dfs_pre_order(i);
	}
}

// void	traverse_dfs_in_order(t_graph *start)


void	traverse_bfs(t_graph *start)
{
	t_graph *i;
	t_list *tmp;
	t_list *queue;

	if (!start)
		return ;
	queue = NULL;
	tmp = lst_new(start, sizeof(t_graph));
	while (tmp)
	{
		printf("%d\n", *((int *)((t_graph *)tmp->content)->content));
		((t_graph *)tmp->content)->visited = 1;
		while ((i = get_adjacent_node((t_graph *)tmp->content)))
		{
			if (!i->visited)
				lst_enqueue(&queue, lst_new(i, sizeof(t_graph)));
		}
		free(tmp);
		tmp = lst_dequeue(&queue);
	}
}

int main(void)
{
	t_graph *gnode[7];

	gnode[0] = gnode_new(fill_content_int(0), sizeof(int));
	gnode[1] = gnode_new(fill_content_int(1), sizeof(int));
	gnode[2] = gnode_new(fill_content_int(2), sizeof(int));
	gnode[3] = gnode_new(fill_content_int(3), sizeof(int));
	gnode[4] = gnode_new(fill_content_int(4), sizeof(int));
	gnode[5] = gnode_new(fill_content_int(5), sizeof(int));
	gnode[6] = gnode_new(fill_content_int(6), sizeof(int));
	link_gnodes_enqueue(gnode[0], gnode[1]);
	link_gnodes_enqueue(gnode[0], gnode[2]);
	link_gnodes_enqueue(gnode[1], gnode[3]);
	link_gnodes_enqueue(gnode[1], gnode[4]);
	link_gnodes_enqueue(gnode[2], gnode[5]);
	link_gnodes_enqueue(gnode[2], gnode[6]);
			// traverse_dfs_in_order(gnode[0]);
	// traverse_dfs_pre_order(gnode[0]);
	// traverse_dfs_post_order(gnode[0]);
	traverse_bfs(gnode[0]);
	return (0);
}
