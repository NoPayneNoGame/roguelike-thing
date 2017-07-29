
#include <assert.h>
#include <stdlib.h>
#include <cab202_graphics.h>
#include "tile.h"

tile_id tile_create(int x, int y, char symbol, bool blocking, int colorPair) {
    tile_id tile = malloc(sizeof(Tile));

    if( tile != NULL ) {
        tile->x = x;
        tile->y = y;
        tile->is_visible = true;
        tile->symbol = symbol;
        tile->blocking = blocking;
        tile->colorPair = colorPair;
    }

    return tile;
}

void tile_destroy( tile_id tile ) {
	if ( tile != NULL ) {
		free( tile );
	}
}

void tile_draw(tile_id tile) {
    assert( tile != NULL );

	if ( !tile->is_visible ) return;

    draw_char(tile->x, tile->y, tile->symbol);
}

tile_id getTileAt(int x, int y) {
    if(tilemap->get(tilemap, (screen_width() * y) + x)) {
        for(int i = 0; i < tileArray.used; i++) {
            tile_id temp = tilearray_get(&tileArray, i);

            if(temp->x == x && temp->y == y) {
                return temp;
            }
        }
    }
    return NULL;
}

bool tile_isBlocking(int x, int y) {
    tile_id temp = getTileAt(x, y);

    if(temp) {
        return temp->blocking;
    }

    return false;
}

void tile_set_symbol(tile_id tile, char symbol) {
    tile->symbol = symbol;
}

void tilearray_init(TileArray *a, size_t initialSize) {
    a->array = (tile_id *)malloc(initialSize * sizeof(tile_id));
    a->used = 0;
    a->size = initialSize;
}

void tilearray_insert(TileArray *a, tile_id element) {
    if(a->used == a->size) {
        a->size = (a->size*3)/2+8; //Some guy on stackoverflow said this is a good number
        a->array = (tile_id *)realloc(a->array, a->size * sizeof(tile_id));
    }
    a->array[a->used++] = element;
}

void tilearray_destroy(TileArray *a) {
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

tile_id tilearray_get(TileArray *a, int i) {
    return a->array[i];
}