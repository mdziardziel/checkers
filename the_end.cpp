#include "allegro5/allegro.h"
#include "the_end.hpp"
#include "engine.hpp"
#include "colors.hpp"
int the_end(int T_Pawns[8][8])
{
    int white = 0, dark = 0, blocked_not = 0, white_nb = 0, dark_nb = 0;
    for(int i = 1; i <= 8; i++)
    {
        for(int j = 1; j <= 8; j++)
        {
            if(T_Pawns[i-1][j-1]%10 == 1) white++;
            if(T_Pawns[i-1][j-1]%10 == 2) dark++;
            if(T_Pawns[i-1][j-1]%10 == 1 && not_blocked(j,i,T_Pawns,1)) white_nb++;
            if(T_Pawns[i-1][j-1]%10 == 2 && not_blocked(j,i,T_Pawns,-1)) dark_nb++;
        }
    }
    if(white == 0 || white_nb == 0) return 2;
    if(dark == 0 || dark_nb == 0) return 1;
    if(dark_nb == 0 && white_nb == 0) return 3;
    return 0;
}

#include <allegro5/allegro_ttf.h>
#include "colors.hpp"


ALLEGRO_DISPLAY *window_win = NULL;
ALLEGRO_FONT *font_win;

void winner(int T_Pawns[8][8],int window_w ,int window_h)
{
    int end_t = the_end(T_Pawns);
    if(end_t != 0)
    {
        al_init();
        al_set_new_window_position(300,300);
        al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED );
        al_set_window_title(window_win, "win");

        window_win = al_create_display( window_w/2, window_h/2);
        al_init_font_addon();
        al_init_ttf_addon();

        char font_path[30] = "fonts/Bubblegum.ttf";
        int font_size = 40;
        font_win = al_load_ttf_font(font_path,font_size,0 );


        al_set_target_bitmap(al_get_backbuffer(window_win));
        al_clear_to_color(window_color);
        switch(end_t)
        {
            case 1: al_draw_textf(font_win,text_color , window_w/16,window_h/6 , 0,"Wygraly biale"); break;
            case 2: al_draw_textf(font_win,text_color , window_w/16,window_h/6 , 0,"Wygraly czarne");break;
            case 3: al_draw_textf(font_win,text_color , window_w/16,window_h/6 , 0,"remis");break;
            case 0:  break;
        }
        al_flip_display();
        al_rest(2);
        //al_destroy_display(window_win);

    }
    al_destroy_display(window_win);
}
