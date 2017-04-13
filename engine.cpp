#include "engine.hpp"
#include "colors.hpp"
ALLEGRO_DISPLAY *window = NULL;
ALLEGRO_BITMAP *square_white, *square_dark, *pawn_white, *pawn_dark, *board, *pointer, *expointer, *king_white, *king_dark, *player_white, *player_dark, *nec_square;
void initialize_window(char window_name[25] = "Warcaby")
{
    al_init();
    al_set_new_window_position(100,100);
    al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED );
    al_set_window_title(window, window_name);

}
void creating_elements(int window_w, int window_h, int board_w, int board_h, int square_wh, int pawn_wh, int pointer_wh)
{
    window = al_create_display( window_w, window_h);
    board = al_create_bitmap(board_w, board_h);
    square_white = al_create_bitmap(square_wh, square_wh);
    square_dark = al_create_bitmap(square_wh, square_wh);
    pawn_white = al_create_bitmap(pawn_wh, pawn_wh);
    pawn_dark = al_create_bitmap(pawn_wh, pawn_wh);
    king_white = al_create_bitmap(pawn_wh, pawn_wh);
    king_dark = al_create_bitmap(pawn_wh, pawn_wh);
    pointer = al_create_bitmap(pointer_wh,pointer_wh);
    expointer = al_create_bitmap(pointer_wh,pointer_wh);
    player_white = al_create_bitmap(square_wh, square_wh);
    player_dark = al_create_bitmap(square_wh, square_wh);
    nec_square = al_create_bitmap(pawn_wh, pawn_wh);
}

void color_elements()
{
    al_set_target_bitmap(al_get_backbuffer(window));
    al_clear_to_color(window_color);

    al_set_target_bitmap(board);
    al_clear_to_color(board_color);

    al_set_target_bitmap(square_white);
    al_clear_to_color(white_square);

    al_set_target_bitmap(square_dark);
    al_clear_to_color(dark_square);

    al_set_target_bitmap(pawn_white);
    al_clear_to_color(white_pawn);

    al_set_target_bitmap(pawn_dark);
    al_clear_to_color(dark_pawn);

    al_set_target_bitmap(king_white);
    al_clear_to_color(white_king);

    al_set_target_bitmap(king_dark);
    al_clear_to_color(dark_king);

    al_set_target_bitmap(pointer);
    al_clear_to_color(pointer_color);

    al_set_target_bitmap(expointer);
    al_clear_to_color(expointer_color);

    al_set_target_bitmap(player_dark);
    al_clear_to_color(dark_pawn);

    al_set_target_bitmap(player_white);
    al_clear_to_color(white_pawn);

    al_set_target_bitmap(nec_square);
    al_clear_to_color(nec_color);

}

void board_update(int board_x, int board_y, int square_x, int square_wh, int square_y, int pawn_wh, int old_x, int old_y, int x, int y, int T_Board[8][8], int T_Pawns[8][8], int player, int nec_pawn[20])
{
    al_set_target_bitmap(al_get_backbuffer(window));
    al_draw_bitmap(board,board_x,board_y, 0);
        for(int i = 0; i < 8 ; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                //PLANSZA
                if(T_Board[i][j] == 1) al_draw_bitmap(square_dark,square_x+j*square_wh, square_y+i*square_wh, 0);
                else al_draw_bitmap(square_white,square_x+j*square_wh, square_y+i*square_wh, 0);
                //PIONKI
                if(T_Pawns[i][j] == 1) al_draw_bitmap(pawn_white,square_x+(square_wh-pawn_wh)/2+j*square_wh, square_y+(square_wh-pawn_wh)/2+i*square_wh, 0);
                else if(T_Pawns[i][j] == 2) al_draw_bitmap(pawn_dark,square_x+(square_wh-pawn_wh)/2+j*square_wh, square_y+(square_wh-pawn_wh)/2+i*square_wh, 0);
                //DAMKI
                else if(T_Pawns[i][j] == 22) al_draw_bitmap(king_dark,square_x+(square_wh-pawn_wh)/2+j*square_wh, square_y+(square_wh-pawn_wh)/2+i*square_wh, 0);
                else if(T_Pawns[i][j] == 11) al_draw_bitmap(king_white,square_x+(square_wh-pawn_wh)/2+j*square_wh, square_y+(square_wh-pawn_wh)/2+i*square_wh, 0);
            }
        }
    if(nec_pawn[0] > 0) al_draw_bitmap(nec_square,square_x+(square_wh-pawn_wh)/2+(nec_pawn[0]-1)*square_wh, square_y+(square_wh-pawn_wh)/2+(nec_pawn[1]-1)*square_wh, 0);
    al_draw_bitmap(expointer,old_x,old_y, 0);
    al_draw_bitmap (pointer,x,y,0);
    if(player == 1 ) al_draw_bitmap(player_white, 0 ,0, 0);
    else al_draw_bitmap(player_dark, 0, 0, 0);
    al_flip_display();
}

void destroy_elements()
{
    /*
    al_destroy_bitmap(pawn_white);
    al_destroy_bitmap(pawn_dark);
    al_destroy_bitmap(square_white);
    al_destroy_bitmap(square_dark);
    al_destroy_bitmap(player_white);
    al_destroy_bitmap(player_dark);
    al_destroy_bitmap(king_white);
    al_destroy_bitmap(king_dark);
    al_destroy_bitmap(pointer);
    al_destroy_bitmap(expointer);
    al_destroy_bitmap(board);
    al_destroy_bitmap(nec_square);
    */
    al_destroy_display(window);
}

//-----BICIA-------------------------------------------------------------------------

bool possible_beat_pawn(int xx, int yy, int T_Pawns[8][8])
{
    //CZY JEST MO¯LIWE GDZIEŒ BICIE (PO SKOSIE PIONEK/DAMKA INNEGO KOLORU I WOLNE POLE ZARAZ ZA)
    if(xx <= 6 && yy <= 6)
    {
        if(T_Pawns[-1+yy+1][-1+xx+1] != 0 && T_Pawns[-1+yy+1][-1+xx+1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy+2][-1+xx+2] == 0) return true;
    }
    if(xx >= 3  && yy <= 6)
    {
        if(T_Pawns[-1+yy+1][-1+xx-1] != 0 && T_Pawns[-1+yy+1][-1+xx-1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy+2][-1+xx-2] == 0) return true;
    }
    if(xx <= 6 && yy >= 3)
    {
        if(T_Pawns[-1+yy-1][-1+xx+1] != 0 && T_Pawns[-1+yy-1][-1+xx+1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy-2][-1+xx+2] == 0) return true;
    }
    if(xx >= 3 && yy >= 3)
    {
        if(T_Pawns[-1+yy-1][-1+xx-1] != 0 && T_Pawns[-1+yy-1][-1+xx-1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy-2][-1+xx-2] == 0) return true;
    }
    return false;
}

bool possible_beat_king(int xx, int yy, int T_Pawns[8][8])
{
    int copy_x = xx, copy_y = yy;
    bool pionek = false;
    copy_x = xx - 1, copy_y = yy - 1;
    while(copy_x >= 2 and copy_y >= 2)
    {
        if(T_Pawns[-1+yy][-1+xx]%10 != T_Pawns[-1+copy_y][-1+copy_x]%10 && T_Pawns[-1+copy_y][-1+copy_y]%10 != 0 &&
           T_Pawns[-1+copy_y - 1][-1+copy_x - 1] == 0) return true;
        if(T_Pawns[-1+yy][-1+xx]%10 == T_Pawns[-1+copy_y][-1+copy_x]%10) return false;
        copy_x--; copy_y--;
    }
    copy_x = xx + 1; copy_y = yy - 1;
    while(copy_x <= 7 and copy_y >= 2)
    {
        if(T_Pawns[-1+yy][-1+xx]%10 != T_Pawns[-1+copy_y][-1+copy_x]%10 && T_Pawns[-1+copy_y][-1+copy_y]%10 != 0 &&
           T_Pawns[-1+copy_y + 1][-1+copy_x - 1] == 0) return true;
        if(T_Pawns[-1+yy][-1+xx]%10 == T_Pawns[-1+copy_y][-1+copy_x]%10) return false;
        copy_x++; copy_y--;
    }
    copy_x = xx - 1; copy_y = yy + 1;
    while(copy_x >= 2 and copy_y <= 7)
    {
        if(T_Pawns[-1+yy][-1+xx]%10 != T_Pawns[-1+copy_y][-1+copy_x]%10 && T_Pawns[-1+copy_y][-1+copy_y]%10 != 0 &&
           T_Pawns[-1+copy_y - 1][-1+copy_x + 1] == 0) return true;
        if(T_Pawns[-1+yy][-1+xx]%10 == T_Pawns[-1+copy_y][-1+copy_x]%10) return false;
        copy_x--; copy_y++;
    }
        copy_x = xx + 1; copy_y = yy + 1;
    while(copy_x <= 7 and copy_y <= 7)
    {
        if(T_Pawns[-1+yy][-1+xx]%10 != T_Pawns[-1+copy_y][-1+copy_x]%10 && T_Pawns[-1+copy_y][-1+copy_y]%10 != 0 &&
           T_Pawns[-1+copy_y + 1][-1+copy_x + 1] == 0) return true;
        if(T_Pawns[-1+yy][-1+xx]%10 == T_Pawns[-1+copy_y][-1+copy_x]%10) return false;
        copy_x++; copy_y++;
    }
    return false;
}

bool beat_king_know(int xx, int yy, int new_x, int new_y, int T_Board[8][8], int T_Pawns[8][8])
{
    if(T_Board[new_y-1][new_x-1] == 1 && T_Pawns[new_y-1][new_x-1] == 0)
    {
        int copy_x = xx,copy_y = yy;
        //bool beat_k = false;
        while(copy_x != new_x && copy_y != new_y)
        {
            if(T_Pawns[-1+yy][-1+xx]%10 == T_Pawns[-1+copy_y][-1+copy_x]%10)
            {
                printf("Masz bicie, musisz biæ! / Nieodpowiedni ruch!");
                return false;
            }
            if(T_Pawns[-1+yy][-1+xx]%10 != T_Pawns[-1+copy_y][-1+copy_x]%10 && T_Pawns[-1+copy_y][-1+copy_x]%10 != 0) return true;
            if( copy_x < new_x ) copy_x++;
            else copy_x --;
            if( copy_y < new_y ) copy_y++;
            else copy_y --;
        }
    }
}

bool beat(int xx, int yy, int new_x, int new_y, int T_Pawns[8][8])
{
    //NOWY ALGORYTM BICIA
    int copy_x = xx,copy_y = yy;
    bool beat_k = false;
    while(copy_x != new_x && copy_y != new_y)
    {
        if( copy_x < new_x ) copy_x++;
        else if( copy_x > new_x ) copy_x --;
        if( copy_y < new_y ) copy_y++;
        else if( copy_y > new_y ) copy_y --;
        if(T_Pawns[-1+yy][-1+xx]%10 != T_Pawns[-1+copy_y][-1+copy_x]%10 && T_Pawns[-1+copy_y][-1+copy_x] != 0)
        {
            T_Pawns[-1+copy_y][-1+copy_x] = 0;
            beat_k = true;
        }
    }
    return beat_k;
}

//-----DAMKA-----------------------------------------------------------------------------------------------

bool king(int xx, int yy, int T_Pawns[8][8])
{
    if(yy == 1 && T_Pawns[yy-1][xx-1] == 2) T_Pawns[yy-1][xx-1] = 22;
    if(yy == 8 && T_Pawns[yy-1][xx-1] == 1) T_Pawns[yy-1][xx-1] = 11;
}

//-----MULTIPLAYER---------------------------------------------------------------------------------------------------------
bool right_player(int xx, int yy, int T_Pawns[8][8],int player)
{
    if( player == 1 && T_Pawns[-1 + yy][-1 + xx]%10 == 1 ) return true;
    else if( player == -1 && T_Pawns[-1 + yy][-1 + xx]%10 == 2 ) return true;
    else return false;
}
//---BLOKOWANIE---------------------------------------------------------------------------------------------------

bool not_blocked(int xx, int yy, int T_Pawns[8][8],int player)
{
    if(!right_player(xx, yy, T_Pawns, player)) return false;
    if(T_Pawns[-1+yy][-1+xx] == 1 || T_Pawns[-1+yy][-1+xx] == 11 || T_Pawns[-1+yy][-1+xx] == 22)
    {
        if(xx <= 7 && yy <= 7)
        {
            if(T_Pawns[-1+yy+1][-1+xx+1] == 0 ) return true;
        }
        if(xx >= 2  && yy <= 7)
        {
            if(T_Pawns[-1+yy+1][-1+xx-1] == 0 ) return true;
        }
    }
    if(T_Pawns[-1+yy][-1+xx] == 2 || T_Pawns[-1+yy][-1+xx] == 11 || T_Pawns[-1+yy][-1+xx] == 22)
    {
        if(xx <= 7 && yy >= 2)
            if(T_Pawns[-1+yy-1][-1+xx+1] == 0 ) return true;
        if(xx >=2  && yy >= 2)
            if(T_Pawns[-1+yy-1][-1+xx-1] == 0 ) return true;
    }
    return possible_beat_pawn(xx, yy, T_Pawns);
}

//------RUCH--------------------------------------------------------
bool possible_move(int xx, int yy, int new_x, int new_y, int T_Board[8][8], int T_Pawns[8][8])
{
    if(T_Board[new_y-1][new_x-1] == 1 && T_Pawns[new_y-1][new_x-1] == 0) //SPRAWDZANIE CZY RUCH JEST NA CIEMNE WOLNE POLE
    {
        if(T_Pawns[-1+yy][-1+xx] == 1 || T_Pawns[-1+yy][-1+xx] == 2) //CZY ZWYK£Y PIONEK
        {
            if(possible_beat_pawn(xx, yy, T_Pawns)) //CZY JEST BICIE
                if((new_y - yy == 2 || new_y - yy == -2) && new_x - xx >=-2 && new_x - xx <= 2 &&
                    T_Pawns[-1 + yy +( new_y - yy ) / 2][-1 + xx + ( new_x - xx ) / 2] != T_Pawns[-1 + yy][-1 + xx]) return true; //CZY BICIE JEST O DWA POLA OD POCZ¥TKOWEGO
                else
                    printf("Masz bicie, musisz biæ! / Niedozowlony ruch pionkiem\n");
            else
                if(T_Pawns[yy-1][xx-1] == 1)//SPRAWDZANIE CZY RUCH JEST O JEDEN DO PRZODU PO SKOSIE
                    if(new_y - yy == 1 && new_x - xx >=-1 && new_x - xx <= 1 ) return true;
                    else printf("Pionek tylko jeden do przodu po skosie!\n");
                else if(T_Pawns[yy-1][xx-1] == 2)
                    if(new_y - yy == -1 && new_x - xx >=-1 && new_x - xx <= 1 ) return true;
                    else printf("Pionek tylko jeden do przodu po skosie!\n");
        }
        else if(T_Pawns[-1+yy][-1+xx] == 11 || T_Pawns[-1+yy][-1+xx] == 22) //CZY DAMKI
        {
            if(possible_beat_king(xx, yy, T_Pawns)) return beat_king_know(xx, yy, new_x, new_y, T_Board, T_Pawns);//SPRAWDZANIE CZY JEST BICIE W TYM RUCHU
            else if(new_y - yy == new_x - xx || new_y - yy == xx-new_x ) return true; //SPRAWDZANIE CZY RUCH JEST PO SKOSIE
            else printf("Pionek tylko po skosie!\n");
        }
    }

    return false;
}

bool move_pawn_king(int xx, int yy, int new_x, int new_y, int T_Pawns[8][8])
{
    bool beat_p = beat(xx, yy, new_x, new_y, T_Pawns);
    int mo = T_Pawns[yy-1][xx-1];
    T_Pawns[yy-1][xx-1] = 0;
    T_Pawns[new_y-1][new_x-1] = mo;
    king(new_x,new_y, T_Pawns);
    return beat_p;
}

//---FUNKCJE---G£ÓWNE

void choose_pawn(int &pawn_id_x, int &pawn_id_y, int &old_player, int &old_x, int &old_y, bool &new_position, int x, int y, int square_x, int square_y, int pointer_wh, int square_wh, int T_Pawns[8][8], int player, int nec_pawn[20])
{
    // ID STAREGO PIONKA
    if(nec_pawn[0] > 0)
    {
        pawn_id_x = nec_pawn[0];
        pawn_id_y = nec_pawn[1];
    }
    else
    {
        pawn_id_x = (x - square_x + pointer_wh/2 + square_wh/2)/square_wh;
        pawn_id_y = (y - square_y + pointer_wh/2 + square_wh/2)/square_wh;
    }
    //SPRAWDZENIE CZY MO¯LIWY JEST RUCH TEGO PIONKA
    if(not_blocked(pawn_id_x, pawn_id_y, T_Pawns, player))
    {
        new_position = true;
        old_x = x; old_y = y; //NADAWANIE STAREGO WSKANIKA
    }
    else printf("pionek zablokowany / nie ma tu ¿adnego pionka / NIE TWÓJ RUCH\n");
    old_player = player;
}

void choose_square(int &new_pawn_id_x, int &new_pawn_id_y, int pawn_id_x, int pawn_id_y, int &old_x, int &old_y, bool &new_position, bool &pawn_move, int x, int y, int square_x, int square_y, int pointer_wh, int square_wh, int T_Pawns[8][8], int T_Board[8][8])
{
    //ID NOWEGO PIONKA
    new_pawn_id_x = (x - square_x + pointer_wh/2 + square_wh/2)/square_wh;
    new_pawn_id_y = (y - square_y + pointer_wh/2 + square_wh/2)/square_wh;
    // WARUNEK PORUSZANIA SIÊ TYLKO PO CIEMNYCH POLACH I BRAK MO¯LIWOŒCI STANIÊCIA NA INNYM PIONKU
    pawn_move = possible_move(pawn_id_x, pawn_id_y, new_pawn_id_x, new_pawn_id_y, T_Board, T_Pawns);
    new_position = false;
    //CHOWANIE ID WSKANIKA
    old_x = -pointer_wh;
    old_y = -pointer_wh;
}

void move_change(int pawn_id_x, int pawn_id_y, int new_pawn_id_x, int new_pawn_id_y, int T_Pawns[8][8], int &player, bool &pawn_move)
{
    pawn_move = false;
    if(move_pawn_king(pawn_id_x, pawn_id_y, new_pawn_id_x, new_pawn_id_y, T_Pawns))
    {
        if(T_Pawns[-1+new_pawn_id_y][-1+new_pawn_id_x]/10 == 0 && !possible_beat_pawn(new_pawn_id_x,new_pawn_id_y, T_Pawns)) player = player * (-1);
        else if(T_Pawns[-1+new_pawn_id_y][-1+new_pawn_id_x]/10 > 0 && !possible_beat_king(new_pawn_id_x,new_pawn_id_y, T_Pawns)) player = player * (-1);
    } else player = player * (-1);
}

//----PRZYMUSOWWE---BICIE------------------------------------------------------------------------------------
/*void compulsory_beat(int T_Pawns[8][8], int player)
{
    int xx, yy;
    int max_beat = 0, beat_num = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            xx = j; yy = i;
            while(possible_beat_pawn(xx,yy,T_Pawns))
            {

            }
        }
    }

}
*/
//-----KONIEC-----------------------------------------------------------------------------------------------





