#include "engine.hpp"
#include "multi.hpp"
#include "save_game.hpp"
#include "colors.hpp"
#include "keyboard.hpp"
#include "main.hpp"
#include "the_end.hpp"


int possible_beat_sides(int xx, int yy, int T_Pawns[8][8])
{
    //CZY JEST MOŻLIWE GDZIEŚ BICIE (PO SKOSIE PIONEK/DAMKA INNEGO KOLORU I WOLNE POLE ZARAZ ZA)
    if(xx <= 6 && yy <= 6)
    {
        if(T_Pawns[-1+yy+1][-1+xx+1] != 0 && T_Pawns[-1+yy+1][-1+xx+1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy+2][-1+xx+2] == 0) return 1;//prawo góra
    }
    if(xx >= 3  && yy <= 6)
    {
        if(T_Pawns[-1+yy+1][-1+xx-1] != 0 && T_Pawns[-1+yy+1][-1+xx-1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy+2][-1+xx-2] == 0) return 2;//lewo góra
    }
    if(xx <= 6 && yy >= 3)
    {
        if(T_Pawns[-1+yy-1][-1+xx+1] != 0 && T_Pawns[-1+yy-1][-1+xx+1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy-2][-1+xx+2] == 0) return 3; //prawo dół
    }
    if(xx >= 3 && yy >= 3)
    {
        if(T_Pawns[-1+yy-1][-1+xx-1] != 0 && T_Pawns[-1+yy-1][-1+xx-1]%10 != T_Pawns[-1+yy][-1+xx]%10 && T_Pawns[-1+yy-2][-1+xx-2] == 0) return 4; //lewo dół
    }
    return 0;
}
void choose_pawn_single(int &pawn_id_x, int &pawn_id_y, int &old_player, int &old_x, int &old_y, bool &new_position, int x, int y, int square_x, int square_y, int pointer_wh, int square_wh, int T_Pawns[8][8], int player, int nec_pawn[20])
{
    // ID STAREGO PIONKA
    if(nec_pawn[0] > 0)
    {
        pawn_id_x = nec_pawn[0];
        pawn_id_y = nec_pawn[1];
    }
    //SPRAWDZENIE CZY MOŻLIWY JEST RUCH TEGO PIONKA
    if(not_blocked(pawn_id_x, pawn_id_y, T_Pawns, player))
    {
        new_position = true;
        old_x = x; old_y = y; //NADAWANIE STAREGO WSKAŹNIKA
    }
    else printf("pionek zablokowany / nie ma tu żadnego pionka / NIE TWÓJ RUCH\n");
    old_player = player;
}
void choose_square_single(int &new_pawn_id_x, int &new_pawn_id_y, int pawn_id_x, int pawn_id_y, int &old_x, int &old_y, bool &new_position, bool &pawn_move, int x, int y, int square_x, int square_y, int pointer_wh, int square_wh, int T_Pawns[8][8], int T_Board[8][8])
{
    // WARUNEK PORUSZANIA SIĘ TYLKO PO CIEMNYCH POLACH I BRAK MOŻLIWOŚCI STANIĘCIA NA INNYM PIONKU
    pawn_move = possible_move(pawn_id_x, pawn_id_y, new_pawn_id_x, new_pawn_id_y, T_Board, T_Pawns);
    new_position = false;
    //CHOWANIE ID WSKAŹNIKA
    old_x = -pointer_wh;
    old_y = -pointer_wh;
}
void single_play(int T_Pawns[8][8],int window_w ,int window_h ,int board_w,int board_h ,int square_wh ,int player)
{
    int T_Board[8][8] = {{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0}};
    int board_x = window_w/2-board_w/2, board_y = window_h/2-board_h/2, square_x = board_x+(board_w-8*square_wh)/2 , square_y = board_y+(board_h-8*square_wh)/2,
    pawn_wh = square_wh/2, pointer_wh = pawn_wh/2, x=square_x+(square_wh-pointer_wh)/2, y=square_y+(square_wh-pointer_wh)/2,
    old_x = -pointer_wh, old_y = -pointer_wh;
    int new_pawn_id_x, new_pawn_id_y, pawn_id_x, pawn_id_y;
    bool new_position = false, pawn_move = false;
    int old_player = player * -1; // 1 -gracz bia³y, -1 - gracz ciemny
    int nec_pawn[20] = {-50}; // parzyste x, nieparzyste y
    double time;
    initialize_window("Warcaby");
    creating_elements(window_w, window_h, board_w, board_h, square_wh, pawn_wh, pointer_wh);
    color_elements();
    board_update(board_x, board_y, square_x, square_wh, square_y, pawn_wh, old_x, old_y, x, y, T_Board, T_Pawns, player, nec_pawn);
    int key;
    int i_d = 0, j_d = 0;
    int new_x_single = 1;
    int new_y_single = 1;
    int repeat = 0;
    while( true)
    {
        if(player == 1)
        {
            key = keyboard_state();
            if ( key == ALLEGRO_KEY_ESCAPE ) break;
            if ( key == ALLEGRO_KEY_S ) save(T_Pawns, window_w , window_h,1, player);
            game_keyboard(x, y, square_x, square_y, square_wh, pointer_wh, T_Pawns, window_w , window_h,1, key);
            if ( key == ALLEGRO_KEY_ENTER    )
            {
                if(!new_position) choose_pawn( pawn_id_x, pawn_id_y, old_player, old_x, old_y, new_position, x, y, square_x, square_y, pointer_wh, square_wh, T_Pawns, player, nec_pawn);
                else choose_square(new_pawn_id_x, new_pawn_id_y, pawn_id_x, pawn_id_y, old_x, old_y, new_position, pawn_move, x, y, square_x, square_y, pointer_wh, square_wh, T_Pawns, T_Board);
            }
            if(pawn_move)
            {
                move_change(pawn_id_x, pawn_id_y, new_pawn_id_x, new_pawn_id_y, T_Pawns, player, pawn_move);
                for(int i = 0; i< 18; i++)
                {
                    nec_pawn[i] = nec_pawn[i + 2];
                }
                nec_pawn[18] = -square_wh;
                nec_pawn[19] = -square_wh;
                if(old_player == player)
                {
                    nec_pawn[0] = new_pawn_id_x;
                    nec_pawn[1] = new_pawn_id_y;
                    choose_pawn( pawn_id_x,  pawn_id_y, old_player, old_x, old_y, new_position, x, y, square_x, square_y, pointer_wh, square_wh, T_Pawns, player, nec_pawn);
                    new_position = true;
                }
            }
        }
        else
        {
            al_rest(0.3);
            i_d = -1;
            j_d = -1;
            for(int i = 1; i < 9; i++)
            {
                for(int j = 1; j < 9; j++)
                {
                    if(not_blocked(j,i,T_Pawns, -1) && possible_beat_pawn(j, i, T_Pawns))
                    {
                        i_d = i;
                        j_d = j;
                    }
                }
            }
            if(i_d == -1)
            {
                         for(int i = 1; i < 9; i++)
            {
                for(int j = 1; j < 9; j++)
                {
                    if(not_blocked(j,i,T_Pawns, -1))
                    {
                        i_d = i;
                        j_d = j;
                    }
                }
            }
            }
            pawn_id_x = j_d;
            pawn_id_y = i_d;
            new_pawn_id_x = pawn_id_x +8 ;
            new_pawn_id_y = pawn_id_y +8;
            while(!possible_move(pawn_id_x, pawn_id_y,  new_pawn_id_x,  new_pawn_id_y,T_Board,T_Pawns))
            {
            switch(repeat)
                {
            case 0:
            new_x_single = 1;
            new_y_single = 1; break;
            case 1:
            new_x_single = -1;
            new_y_single = 1; break;
            case 2:
            new_x_single = 1;
            new_y_single = -1;break;
            case 3:
            new_x_single = -1;
            new_y_single = -1;break;
            case 4:
                break;
            }
            if(possible_beat_pawn(pawn_id_x, pawn_id_y, T_Pawns))
            {
            switch(possible_beat_sides(pawn_id_x, pawn_id_y,T_Pawns))
            {
            case 1:
            new_x_single = 2;
            new_y_single = 2;break;
            case 2:
            new_x_single = -2;
            new_y_single = 2;break;
            case 3:
            new_x_single = 2;
            new_y_single = -2;break;
            case 4:
            new_x_single = -2;
            new_y_single = -2;break;
            case 0:
                break;
            }
            }
            repeat++;
            new_pawn_id_x = pawn_id_x + new_x_single;
            new_pawn_id_y = pawn_id_y +new_y_single;
            }
                repeat = 0;
            if(!new_position) choose_pawn_single( pawn_id_x, pawn_id_y, old_player, old_x, old_y, new_position, x, y, square_x, square_y, pointer_wh, square_wh, T_Pawns, player, nec_pawn);
            if(new_position)
            {
            choose_square_single(new_pawn_id_x, new_pawn_id_y, pawn_id_x, pawn_id_y, old_x, old_y, new_position, pawn_move, x, y, square_x, square_y, pointer_wh, square_wh, T_Pawns, T_Board);
            }

            if(pawn_move)
            {
                move_change(pawn_id_x, pawn_id_y, new_pawn_id_x, new_pawn_id_y, T_Pawns, player, pawn_move);

                for(int i = 0; i< 18; i++)
                {
                    nec_pawn[i] = nec_pawn[i + 2];
                }
                nec_pawn[18] = -square_wh;
                nec_pawn[19] = -square_wh;
                if(old_player == player)
                {
                    nec_pawn[0] = new_pawn_id_x;
                    nec_pawn[1] = new_pawn_id_y;
                    choose_pawn( pawn_id_x,  pawn_id_y, old_player, old_x, old_y, new_position, x, y, square_x, square_y, pointer_wh, square_wh, T_Pawns, player, nec_pawn);
                    new_position = true;
                }
            }
        }

        board_update(board_x, board_y, square_x, square_wh, square_y, pawn_wh, old_x, old_y, x, y, T_Board, T_Pawns, player, nec_pawn);
        winner(T_Pawns, window_w , window_h);
    }
    destroy_elements();
    //al_destroy_display(window);
    main();

}
