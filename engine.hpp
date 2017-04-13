#ifndef engine_hpp
#define engine_hpp

#include <allegro5/allegro.h>
#include <stdio.h>


void initialize_window(char window_name[25]);
void creating_elements(int window_w, int window_h, int board_w, int board_h, int square_wh, int pawn_wh, int pointer_wh);
void color_elements();
void board_update(int board_x, int board_y, int square_x, int square_wh, int square_y, int pawn_wh, int old_x, int old_y, int x, int y, int T_Board[8][8], int T_Pawns[8][8], int player, int nec_pawn[20]);
void destroy_elements();
bool possible_beat_pawn(int xx, int yy, int T_Pawns[8][8]);
bool possible_beat_pawn(int xx, int yy, int T_Pawns[8][8]);
bool beat_king_know(int xx, int yy, int new_x, int new_y, int T_Board[8][8], int T_Pawns[8][8]);
bool beat(int xx, int yy, int new_x, int new_y, int T_Pawns[8][8]);
bool king(int xx, int yy, int T_Pawns[8][8]);
bool right_player(int xx, int yy, int T_Pawns[8][8],int player);
bool not_blocked(int xx, int yy, int T_Pawns[8][8],int player);
bool possible_move(int xx, int yy, int new_x, int new_y, int T_Board[8][8], int T_Pawns[8][8]);
bool move_pawn_king(int xx, int yy, int new_x, int new_y, int T_Pawns[8][8]);
void choose_pawn(int &pawn_id_x, int &pawn_id_y, int &old_player, int &old_x, int &old_y, bool &new_position, int x, int y, int square_x, int square_y, int pointer_wh, int square_wh, int T_Pawns[8][8], int player, int nec_pawn[20]);
void choose_square(int &new_pawn_id_x, int &new_pawn_id_y, int pawn_id_x, int pawn_id_y, int &old_x, int &old_y, bool &new_position, bool &pawn_move, int x, int y, int square_x, int square_y, int pointer_wh, int square_wh, int T_Pawns[8][8], int T_Board[8][8]);
void move_change(int pawn_id_x, int pawn_id_y, int new_pawn_id_x, int new_pawn_id_y, int T_Pawns[8][8], int &player, bool &pawn_move);
#endif

