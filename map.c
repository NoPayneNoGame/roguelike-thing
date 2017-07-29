
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <cab202_graphics.h>
#include "tile.h"
#include "bitmap.h"
#include "helpers.h"
#include "map.h"

double chanceToStartAlive = 0.4;
int birthLimit = 4;
int deathLimit = 4;
int numberOfSteps = 6;



void map_init() {
    srand(time(NULL));

    cellmap = (bool **)malloc(screen_width() * sizeof(bool *));
    for(int i=0; i < screen_width(); i++)
        cellmap[i] = (bool *)malloc(screen_height() * sizeof(bool));

    tilemap = clib_bitmap_init(screen_width() * screen_height());

    tilearray_init(&tileArray, 30);

    for(int x = 0; x < screen_width(); x++) {
        for(int y = 0; y < screen_height(); y++) {
            if(r2() < chanceToStartAlive) {
                cellmap[x][y] = true;
            }
        }
    }

    for(int i = 0; i < numberOfSteps; i++) {
        doSimulationStep();
    }

    for(int x = 0; x < screen_width(); x++) {
        for(int y = 0; y < screen_height(); y++) {
            if(cellmap[x][y]) {
                // tilearray_insert(&tileArray, tile_create(x, y, '█', true));
                tilearray_insert(&tileArray, tile_create(x, y, '#', true, WALL_COLOR));
                tilemap->set(tilemap, screen_width() * y + x);
            }
        }
    }

    for(int i = 0; i < screen_width(); i++){
        free(cellmap[i]);
    }
    free(cellmap);

}


int countNeighbourTiles(int x, int y) {
    int count = 0;

    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            int nX = x+i;
            int nY = y+j;
            
            if(i == 0 && j == 0) { }
            else if (nX < 0 || nY < 0 || nX >= screen_width() || nY >= screen_height()) {
                count++;
            } else if(getTileAt(nX, nY)) {
                count++;
            }
        }
    }
    return count;
}

int countAliveNeighbours(int x, int y) {
    int count = 0;
    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            int nX = x+i;
            int nY = y+j;
            if(i == 0 && j == 0) { }
            else if (nX < 0 || nY < 0 || nX >= screen_width() || nY >= screen_height()) {
                count++;
            } else if(cellmap[nX][nY]) {
                count++;
            }
        }
    }
    return count;
}

void doSimulationStep() {
    bool **newMap = (bool **)malloc(screen_width() * sizeof(bool *));
    for(int i = 0; i < screen_width(); i++)
        newMap[i] = (bool *)malloc(screen_height() * sizeof(bool));

    for(int x = 0; x < screen_width(); x++) {
        for(int y = 0; y < screen_height(); y++) {
            int nbs = countAliveNeighbours(x, y);
            if(cellmap[x][y]) {
                if(nbs < deathLimit) {
                    newMap[x][y] = false;
                } else {
                    newMap[x][y] = true;
                }
            } else {
                if(nbs > birthLimit) {
                    newMap[x][y] = true;
                } else {
                    newMap[x][y] = false;
                }
            }
        }
    }

    for(int i = 0; i < screen_width(); i++){
        free(cellmap[i]);
    }
    free(cellmap);

    cellmap = newMap;
}

void map_destroy() {
    // for(int i = 0; i < screen_width(); i++){
    //     free(tilemap[i]);
    // }
    // free(tilemap);
}

void floodFill(int x, int y) {
    // if(tilemap[x][y])
    //     return;
    // tilemap[x][y] = tile_create(x, y, '~', false);
    // floodFill(x, y+1);
    // floodFill(x, y-1);
    // floodFill(x-1, y);
    // floodFill(x+1, y);
    // return;
}