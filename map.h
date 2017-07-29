
#ifndef MAP_H_
#define MAP_H_

bool **cellmap;

void map_init();
void map_destroy();

int countNeighbourTiles(int x, int y);
int countAliveNeighbours(int x, int y);
void doSimulationStep();
void floodFill(int x, int y);

#endif /* MAP_H_ */