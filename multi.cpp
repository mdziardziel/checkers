#include "engine.hpp"
#include "multi.hpp"
#include "save_game.hpp"
#include "colors.hpp"
#include "keyboard.hpp"
#include "main.hpp"
#include "the_end.hpp"

void multi_play(int T_Pawns[8][8],int window_w ,int window_h ,int board_w,int board_h ,int square_wh , int player)
{
    int T_Board[8][8] = {{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0}};
    int board_x = window_w/2-board_w/2, board_y = window_h/2-board_h/2, square_x = board_x+(board_w-8*square_wh)/2 , square_y = board_y+(board_h-8*square_wh)/2,
    pawn_wh = square_wh/2, pointer_wh = pawn_wh/2, x=square_x+(square_wh-pointer_wh)/2, y=square_y+(square_wh-pointer_wh)/2,
    old_x = -pointer_wh, old_y = -pointer_wh;
    int new_pawn_id_x, new_pawn_id_y, pawn_id_x, pawn_id_y;
    bool new_position = false, pawn_move = false;
    int old_player = player * -1 ;// 1 -gracz bia³y, -1 - gracz ciemny
    int nec_pawn[20] = {-50}; // parzyste x, nieparzyste y
    double time;
    initialize_window("Warcaby");
    creating_elements(window_w, window_h, board_w, board_h, square_wh, pawn_wh, pointer_wh);
    color_elements();
    board_update(board_x, board_y, square_x, square_wh, square_y, pawn_wh, old_x, old_y, x, y, T_Board, T_Pawns, player, nec_pawn);
    int key;
    while( true)
    {
        key = keyboard_state();
        if ( key == ALLEGRO_KEY_ESCAPE )break;
        if ( key == ALLEGRO_KEY_S ) save(T_Pawns, window_w , window_h,2, player);
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
        board_update(board_x, board_y, square_x, square_wh, square_y, pawn_wh, old_x, old_y, x, y, T_Board, T_Pawns, player, nec_pawn);
        winner(T_Pawns, window_w , window_h);
    }
    destroy_elements();
    //al_destroy_display(window);
    main();

}
