#ifndef FREE_H
#define FREE_H

void exit_game(struct gamestate *game);

void free_textures(struct list *textures);
void free_entities(struct list *entities);

void destroy_map(struct map *map);

#endif /* FREE_H */
