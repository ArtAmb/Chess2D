#pragma once
enum CHESS_COLUMN { C_A = 0, C_B, C_C, C_D, C_E, C_F, C_G, C_H };
enum CHESS_ROW { R_1 = 0, R_2, R_3, R_4, R_5, R_6, R_7, R_8 };
enum PLAYER_COLOR { WHITE, BLACK };
enum CHESS_PIECES { PAWN, KNIGHT, ROOK, BISHOP, QUEEN, KING };
enum PAWN_PROMOTION { PROM_KNIGHT, PROM_ROOK, PROM_BISHOP, PROM_QUEEN };
enum CHESS_GAME_STATE { WINNER_BLACK, WINNER_WHITE, STALEMATE, CONTINIUE };
enum COLOR_OPTION {RANDOM_O, WHITE_O, BLACK_O};
enum LEVEL_OPTION {EASY, NORMAL, HARD};