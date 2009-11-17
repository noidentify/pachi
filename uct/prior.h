#ifndef ZZGO_UCT_PRIOR_H
#define ZZGO_UCT_PRIOR_H

#include "move.h"
#include "uct/tree.h"

struct tree;
struct tree_node;
struct uct;
struct board;

struct prior_map {
	struct board *b;
	enum stone to_play;
	int parity;
	/* [board_size2(b)] array, move_stats are the prior
	 * values to be assigned to individual moves;
	 * move_stats.value is not updated. */
	struct move_stats *prior;
	/* [board_size2(b)] array, whether to compute
	 * prior for the given value. */
	bool *consider;
	/* [board_size2(b)] array from cfg_distances() */
	int *distances;
};

/* @value is the value, @playouts is its weight. */
static void add_prior_value(struct prior_map *map, coord_t c, float value, int playouts);

void uct_prior(struct uct *u, struct tree_node *node, struct prior_map *map);

struct uct_prior;
struct uct_prior *uct_prior_init(char *arg);


static inline void
add_prior_value(struct prior_map *map, coord_t c, float value, int playouts)
{
	float v = map->parity > 0 ? value : 1 - value;
	stats_add_result(&map->prior[c], v, playouts);
}

#endif
