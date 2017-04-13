#include "keyboard.hpp"
#include "allegro5/allegro.h"
#include "save_game.hpp"
#include "stdio.h"
int keyboard_state()
{
    al_install_keyboard();
    ALLEGRO_KEYBOARD_STATE keyboard;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_wait_for_event(event_queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        return event.keyboard.keycode;
    return 0;
}
void game_keyboard(int &x,int &y, int square_x, int square_y, int square_wh, int pointer_wh, int T_Pawns[8][8],int window_w, int window_h, int game_type, int key)
{
    if ( key == ALLEGRO_KEY_RIGHT  && x < square_x+square_wh*7-pointer_wh) x = x+square_wh;
    if ( key == ALLEGRO_KEY_LEFT   && x > square_x+(square_wh-pointer_wh)/2) x = x - square_wh;
    if ( key == ALLEGRO_KEY_DOWN    && y < square_y+square_wh*7 - pointer_wh) y = y + square_wh;
    if ( key == ALLEGRO_KEY_UP      && y > square_y+(square_wh-pointer_wh)/2) y = y - square_wh;
}
