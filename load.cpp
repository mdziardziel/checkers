#include "load.hpp"
#include "allegro5/allegro.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "multi.hpp"
#include "single.hpp"
#include "colors.hpp"
FILE *fp;
void load(int T_Pawns[8][8],int window_w,int window_h,int board_w,int board_h,int square_wh)
{
    int game_type, player;
    fp = fopen("save.txt", "r");
    fscanf (fp, "%d", &game_type);
    fscanf (fp, "%d", &player);
    for(int i = 0; i < 8 ; i++)
        for(int j = 0; j < 8; j++)
            fscanf (fp, "%d", &T_Pawns[i][j]);
    if(game_type == 2)
        multi_play(T_Pawns, window_w, window_h, board_w, board_h, square_wh, player);
    else
        single_play(T_Pawns, window_w, window_h, board_w, board_h, square_wh, player);
    fclose (fp);

}
