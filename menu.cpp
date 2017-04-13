#include "menu.hpp"
#include "single.hpp"
#include "multi.hpp"
#include "load.hpp"
#include "colors.hpp"
#include "keyboard.hpp"

#include <allegro5/allegro.h>
#include <stdio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>



ALLEGRO_DISPLAY *window_menu = NULL;
ALLEGRO_BITMAP *rectangle, *active_rectangle;
ALLEGRO_FONT *font_menu;

void initialize_window_menu(char window_name[25])
{
    al_init();
    al_set_new_window_position(100,100);
    al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED );
    al_set_window_title(window_menu, window_name);

    al_init_font_addon();
    al_init_ttf_addon();

}
void creating_elements_menu(int window_w, int window_h, int rectangle_w, int rectangle_h, int font_size, char font_path[30])
{
    window_menu = al_create_display( window_w, window_h);
    rectangle = al_create_bitmap(rectangle_w, rectangle_h);
    active_rectangle = al_create_bitmap(rectangle_w, rectangle_h);
    font_menu = al_load_ttf_font(font_path,font_size,0 );
}

void color_elements_menu()
{
    al_set_target_bitmap(al_get_backbuffer(window_menu));
    al_clear_to_color(window_color);

    al_set_target_bitmap(rectangle);
    al_clear_to_color(rec_color);

    al_set_target_bitmap(active_rectangle);
    al_clear_to_color(active_rec_color);

}

void text_update(int x, int y, int h)
{
    int gap = 20;
     al_draw_textf(font_menu,text_color , x+gap, y+gap, 0,"Player vs Player");
     al_draw_textf(font_menu,text_color , x+gap, y+1*y +1*h+gap, 0,"Computer vs Player");
     al_draw_textf(font_menu,text_color , x+gap, y+2*y +2*h+gap, 0,"Load Last Saved Game");
     al_draw_textf(font_menu,text_color , x+gap, y+3*y +3*h+gap, 0,"Exit");
}

void board_update_menu(int rec_x, int rec_y, int rec_h, int number)
{
    al_set_target_bitmap(al_get_backbuffer(window_menu));
    for(int i = 0; i<4; i++)
    {
        al_draw_bitmap(rectangle,rec_x,rec_y+i*rec_y + i*rec_h, 0);
        if(i == number)  al_draw_bitmap(active_rectangle,rec_x,rec_y+i*rec_y + i*rec_h, 0);
    }
   text_update(rec_x, rec_y, rec_h);
    al_flip_display();
}


void destroy_elements_menu()
{
    al_destroy_bitmap(rectangle);
    al_destroy_bitmap(active_rectangle);
    al_destroy_display(window_menu);
}

void menu(int T_Pawns[8][8],int window_w ,int window_h ,int board_w,int board_h,int square_wh)
{
    int rec_w = 800, rec_h = 100, rec_x =window_w/2 - rec_w/2 , rec_y = (window_h)/12, font_size = 60;
    char font_path[30] = "fonts/Bubblegum.ttf";
    initialize_window_menu("menu");
    creating_elements_menu(window_w, window_h, rec_w ,rec_h, font_size, font_path);
    color_elements_menu();
    board_update_menu(rec_x, rec_y, rec_h, 0);

    int x=window_w/2, y=window_h/6;
    int key;
    while(true)
    {
        key = keyboard_state();
        if ( key == ALLEGRO_KEY_ESCAPE ) break;
        if ( key == ALLEGRO_KEY_DOWN   && y < window_h - window_h/6 )y=y + rec_y + rec_h;
        if ( key == ALLEGRO_KEY_UP     && y  >  window_h/12+10) y=y -  rec_y - rec_h;
        if ( key == ALLEGRO_KEY_ENTER )
        {
            switch((y-window_h/12)/(rec_y+rec_h))
            {
                case 0: destroy_elements_menu(); multi_play(T_Pawns, window_w, window_h, board_w, board_h, square_wh,1); break;
                case 1: destroy_elements_menu(); single_play(T_Pawns, window_w, window_h, board_w, board_h, square_wh,1); break;
                case 2: destroy_elements_menu(); load(T_Pawns, window_w, window_h, board_w, board_h, square_wh); break;
                case 3: break;
            }
            break;
        }
        board_update_menu(rec_x, rec_y, rec_h, (y-window_h/12)/(rec_y+rec_h));
    }
    //destroy_elements_menu();
    al_destroy_display(window_menu);
}
