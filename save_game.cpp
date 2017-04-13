#include "allegro5/allegro.h"
#include <stdio.h>
#include <stdlib.h>
#include "save_game.hpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "colors.hpp"
#include "keyboard.hpp"




void save(int T_Pawns[8][8],int window_w ,int window_h, int game_type, int player)
{
    ALLEGRO_DISPLAY *window_save = NULL;
    ALLEGRO_FONT *font_save;
    FILE *fps;
    al_init();
    al_set_new_window_position(300,300);
    al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED );
    al_set_window_title(window_save, "save");

    window_save = al_create_display( window_w/2, window_h/2);
    al_init_font_addon();
    al_init_ttf_addon();

    char font_path[30] = "fonts/Bubblegum.ttf";
    int font_size = 40;
    font_save = al_load_ttf_font(font_path,font_size,0 );


    fps = fopen("save.txt", "w");
    fprintf (fps, "%d\n", game_type);
    fprintf (fps, "%d\n", player);
    for(int i = 0; i < 8 ; i++)
        for(int j = 0; j < 8; j++)
            fprintf (fps, "%d ", T_Pawns[i][j]);

    al_set_target_bitmap(al_get_backbuffer(window_save));
    al_clear_to_color(window_color);
    al_draw_textf(font_save,text_color , window_w/16,window_h/6 , 0,"Gra zapisana poprawnie.");
    fclose (fps);
    al_flip_display();
    al_rest(1);
    al_destroy_display(window_save);
}



