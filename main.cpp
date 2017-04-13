#include "menu.hpp"
#include "main.hpp"
int main()
{
    int T_Pawns[8][8] = {{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{2,0,2,0,2,0,2,0},{0,2,0,2,0,2,0,2},{2,0,2,0,2,0,2,0}}, window_w = 1280, window_h = 720, board_w= 700, board_h = 700, square_wh = 80;
    menu(T_Pawns, window_w, window_h, board_w, board_h, square_wh);
}
