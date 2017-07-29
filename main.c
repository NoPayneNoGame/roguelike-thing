// gcc *.c -I../ZDK -L../ZDK -lzdk -lm -lncurses -o game

#include <stdlib.h>
#include <curses.h>

#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

#include "map.h"
#include "helpers.h"
#include "tile.h"


#define DELAY 10 /* milliseconds */
#define ABS(x)	 (((x) >= 0) ? (x) : -(x))
#define show_screen() show_screen_override()

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

bool gameOver = false;
bool updateScreen = true;

sprite_id character;
int char_facing;
TileArray sightCone;

void setup();
void gameloop();
void cleanup();
void handleInput(int input);
bool collisionAt(int x, int y);
void line(TileArray *a, int x1, int y1, int x2, int y2);
void draw_triangle(int x, int y, int width, int dist);

void setup() {
    map_init();

    int cX, cY;

    /* Place the character randomly, but try again
     * if too close to a wall */
    do {
        cX = rand() % screen_width();
        cY = rand() % screen_height();
    } while(countNeighbourTiles(cX, cY) > 4);

    character = sprite_create(cX, cY, 1, 1, "@");
    char_facing = UP;
    tilearray_init(&sightCone, 110);

    /* Everywhere there's no tile, put another character,
     * the wall char (█) is two wide and needs to be overrode */
    // for(int x = 0; x < screen_width(); x++) {
    //     for(int y = 0; y < screen_height(); y++) {
    //         if(!getTileAt(x, y)) {
    //             zdk_screen->pixels[y][x] = '!';
    //         }
    //     }
    // }

    sprite_draw(character);
}



void draw_triangle(int x, int y, int width, int dist) {

    // switch(char_facing) {
    //     case UP:
    //         draw_line(x, y, x - width/2, y - dist, '~');
    //         draw_line(x - width/2, y - dist, x + width/2, y - dist, '~');
    //         draw_line(x + width/2, y - dist, x, y, '~');
    //         break;
    //     case DOWN:
    //         draw_line(x, y, x + width/2, y + dist, '~');
    //         draw_line(x + width/2, y + dist, x - width/2, y + dist, '~');
    //         draw_line(x - width/2, y + dist, x, y, '~');
    //         break;
    //     case LEFT:
    //         draw_line(x, y, x - dist, y - width/2, '~');
    //         draw_line(x - dist, y - width/2, x - dist, y + width/2, '~');
    //         draw_line(x - dist, y + width/2, x, y, '~');
    //         break;
    //     case RIGHT:
    //         draw_line(x, y, x + dist, y + width/2, '~');
    //         draw_line(x + dist, y + width/2, x + dist, y - width/2, '~');
    //         draw_line(x + dist, y - width/2, x, y, '~');
    //         break;
    // }

    /* * * * * * * * * * *
     * TODO:
     *
     *  Draw two lines
     *  Each tile in line, set visible flag
     *  Get y, min_x, max_x to make rect
     *  For each in rect
     *    If visible toggle bool
     *    Set visible for each until meet already visible
     *
     * * * * * * * * * * */


}

void gameloop() {
    clear_screen();

    int input = get_char();

    handleInput(input);

    for(int i = 0; i < tileArray.used; i++) {
        tile_draw(tilearray_get(&tileArray, i));
    }

    int cX = sprite_x(character);
    int cY = sprite_y(character);

    draw_triangle(cX, cY, 16, 12);

    sprite_draw(character);
}

void cleanup() {
    sprite_destroy(character);

    for(int i = 0; i < tileArray.used; i++) {
        tile_destroy(tileArray.array[i]);
    }

    tilearray_destroy(&sightCone);
    tilearray_destroy(&tileArray);

    cleanup_screen();
}

void show_screen_override() {
    // Draw parts of the display that are different in the front
	// buffer from the back buffer.
	char ** back_px = zdk_prev_screen->pixels;
	char ** front_px = zdk_screen->pixels;
	int w = zdk_screen->width;
	int h = zdk_screen->height;
	bool changed = false;

    tile_id temp;

	for ( int y = 0; y < h; y++ ) {
		for ( int x = 0; x < w; x++ ) {
			if ( front_px[y][x] != back_px[y][x] ) {

                if( temp = getTileAt(x, y) ) {
                    attron(COLOR_PAIR(temp->colorPair));
                }

				mvaddch(y, x, front_px[y][x]);
				back_px[y][x] = front_px[y][x];
				changed = true;

                if(temp) {
                    attroff(COLOR_PAIR(temp->colorPair));
                    temp = NULL;
                }
			}
		}
	}

	if ( !changed ) {
		return;
	}

	// Save a screen shot, if automatic saves are enabled.
	//save_screen_(zdk_save_stream);

	// Force an update of the curses display.
	if ( !zdk_suppress_output ) {
		refresh();
	}
}

void handleInput(int input) {
    int x = sprite_x(character);
    int y = sprite_y(character);
    int speed = 1;

    if ( input == 'q' ) {
        gameOver = true;
        return;
    }

    if ( (input == 'w' || input == 259) && !collisionAt(x, y-speed))  {
        char_facing = UP;
        sprite_move(character, 0, -speed);
    } else if ( (input == 's' || input == 258)  && !collisionAt(x, y+speed)) {
        char_facing = DOWN;
        sprite_move(character, 0, speed);
    } else if ( (input == 'a'|| input == 260)  && !collisionAt(x-speed, y)) {
        char_facing = LEFT;
        sprite_move(character, -speed, 0);
    } else if ( (input == 'd' || input == 261)  && !collisionAt(x+speed, y)) {
        char_facing = RIGHT;
        sprite_move(character, speed, 0);
    }

}

bool collisionAt(int x, int y) {
    if (x < 0 || y < 0 || x >= screen_width() || y >= screen_height())
        return true;

    if (tile_isBlocking(x, y))
        return true;

    return false;
}

int main(int argc, char * argv[]) {

    setup_screen();

    start_color();

    init_pair(1, COLOR_BLACK, COLOR_CYAN);

    setup();
    show_screen();

    while(!gameOver) {
        gameloop();

        if(updateScreen) {
            show_screen();
        }

        timer_pause(DELAY);
    }

    cleanup();

    return 0;
}