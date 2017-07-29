
#ifndef TILE_H_
#define TILE_H_

#include "bitmap.h"

#define WALL_COLOR 1

typedef struct Tile {
    int x;
    int y;
    char symbol;
    bool blocking:1;
    bool is_visible:1;
    int colorPair;
} Tile;

typedef Tile * tile_id;

typedef struct TileArray {
    tile_id *array;
    size_t used;
    size_t size;
} TileArray;

//tile_id **tilemap;

clib_bitmap *tilemap;

TileArray tileArray;

tile_id getTileAt(int x, int y);

tile_id tile_create(int x, int y, char symbol, bool blocking, int colorPair);
void tile_destroy(tile_id tile);
void tile_draw(tile_id tile);
void tile_set_symbol(tile_id tile, char symbol);
bool tile_isBlocking(int x, int y);

void tilearray_init(TileArray *a, size_t initialSize);
void tilearray_insert(TileArray *a, tile_id element);
void tilearray_destroy(TileArray *a);
tile_id tilearray_get(TileArray *a, int i);


#endif /* TILE_H_ */