#ifndef CONSTANTSANDENUMS_HPP
#define CONSTANTSANDENUMS_HPP

#include <string>

extern "C" {
    #include <SDL2/SDL_types.h>
}
#include <exception>

/**
 * class to represent exception when trying to get element outside the board
 */
class InvalidPosition : public std::exception {};

//-----------------------------------------------------------------------------------------------------------------

const unsigned int SCREEN_WIDTH = 1080;
const unsigned int SCREEN_HEIGHT = (int)(SCREEN_WIDTH*2/3);

const Uint8 WHITE_COLOR_R = 255;
const Uint8 WHITE_COLOR_G = 255;
const Uint8 WHITE_COLOR_B = 255;

const Uint8 BLACK_COLOR_R = 0;
const Uint8 BLACK_COLOR_G = 0;
const Uint8 BLACK_COLOR_B = 0;

//-----------------------------------------------------------------------------------------------------------------

//for makefile and CLion I need different paths to files with font and images of figures
// font
extern const char * CHESS_FONT_FILE;// = "../src/fonts/OpenSans-Bold.ttf"; //for makefile one dot, for CLion two dots
extern std::string CHESS_IMAGE_DIRECTORY; // = "../src/chess_figures/";
extern std::string FILE_WITH_STATE_NAME;
extern std::string FILE_WITH_STATE_EXTENSION;
extern std::string FILES_WITH_STATES_DIR;


// main menu fonts
const Uint8 MAIN_MENU_BACKGROUND_R = 0;
const Uint8 MAIN_MENU_BACKGROUND_G = 0;
const Uint8 MAIN_MENU_BACKGROUND_B = 0;

const Uint8 MAIN_MENU_BUTTON_FONT_R = 255;
const Uint8 MAIN_MENU_BUTTON_FONT_G = 0;
const Uint8 MAIN_MENU_BUTTON_FONT_B = 0;

const Uint8 MAIN_MENU_TITLE_FONT_R = 0;
const Uint8 MAIN_MENU_TITLE_FONT_G = 255;
const Uint8 MAIN_MENU_TITLE_FONT_B = 0;

const Uint8 MAIN_MENU_AUTHOR_FONT_R = 255;
const Uint8 MAIN_MENU_AUTHOR_FONT_G = 255;
const Uint8 MAIN_MENU_AUTHOR_FONT_B = 255;

const Uint8 MAIN_MENU_BUTTON_BACKGROUND_R = 0;
const Uint8 MAIN_MENU_BUTTON_BACKGROUND_G = 0;
const Uint8 MAIN_MENU_BUTTON_BACKGROUND_B = 255;

const int MAIN_MENU_BUTTON_FONT_SIZE = 75;
const int MAIN_MENU_TITLE_FONT_SIZE = 175;
const int MAIN_MENU_AUTHOR_FONT_SIZE = 20;

//-----------------------------------------------------------------------------------------------------------------

//board consts
const unsigned int BOARD_SIZE = 8;
const unsigned int BOARD_FIELD_SIZE = 80;
const unsigned int BOARD_SURR_BEGIN_X = 0;
const unsigned int BOARD_SURR_BEGIN_Y = 0;
const unsigned int BOARD_BEGIN_X = BOARD_SURR_BEGIN_X + BOARD_FIELD_SIZE/2;
const unsigned int BOARD_BEGIN_Y = BOARD_SURR_BEGIN_Y + BOARD_FIELD_SIZE/2;
const int BOARD_FONT_SIZE = BOARD_FIELD_SIZE/2;

const Uint8 BOARD_SURROUNDING_R = 0;
const Uint8 BOARD_SURROUNDING_G = 74;
const Uint8 BOARD_SURROUNDING_B = 158;

const Uint8 BOARD_LIGHT_R = 232;
const Uint8 BOARD_LIGHT_G = 235;
const Uint8 BOARD_LIGHT_B = 239;

const Uint8 BOARD_DARK_R = 125;
const Uint8 BOARD_DARK_G = 135;
const Uint8 BOARD_DARK_B = 150;

const Uint8 BOARD_MARKED_R = 40;
const Uint8 BOARD_MARKED_G = 40;
const Uint8 BOARD_MARKED_B = 40;

const Uint8 BOARD_CHECKED_R = 255;
const Uint8 BOARD_CHECKED_G = 0;
const Uint8 BOARD_CHECKED_B = 0;

//green
const Uint8 BOARD_SURR_MOVE_R = 0;
const Uint8 BOARD_SURR_MOVE_G = 128;
const Uint8 BOARD_SURR_MOVE_B = 0;

//orangered
const Uint8 BOARD_SURR_CAPTURE_R = 255;
const Uint8 BOARD_SURR_CAPTURE_G = 69;
const Uint8 BOARD_SURR_CAPTURE_B = 0;

//navy (some blue)
const Uint8 BOARD_SURR_CASTLE_R = 0;
const Uint8 BOARD_SURR_CASTLE_G = 0;
const Uint8 BOARD_SURR_CASTLE_B = 128;

//red
const Uint8 BOARD_SURR_CHECK_R = 255;
const Uint8 BOARD_SURR_CHECK_G = 0;
const Uint8 BOARD_SURR_CHECK_B = 0;

//darkred
const Uint8 BOARD_SURR_MATE_R = 139;
const Uint8 BOARD_SURR_MATE_G = 0;
const Uint8 BOARD_SURR_MATE_B = 0;

const int SURR_THICKNESS = 6;

const Uint8 BOARD_FONT_R = 0;
const Uint8 BOARD_FONT_G = 0;
const Uint8 BOARD_FONT_B = 25;

/**
 * enum to represent color of the board field
 */
enum BoardRectColor {
    LIGHT = 0,
    DARK = 1
};

/**
 * enum to represent what color of surrounding is actually draw on the board field (to mark a movement)
 */
enum RectSurrColor {
    NONE_S = 0,
    MOVE_S = 1,
    CAPTURE_S = 2,
    CASTLE_S = 3,
    CHECK_S = 4,
    MATE_S = 5
};

//----------------------------------------------------------------------------------------------------------------
//player's turn
const int PLAYER_TURN_FONT_SIZE = 90;
const int PLAYER_TURN_FONT_MIDDLE_X = SCREEN_WIDTH - SCREEN_HEIGHT / 4;
const int PLAYER_TURN_FONT_MIDDLE_Y = (PLAYER_TURN_FONT_SIZE);


const Uint8 WHITE_TURN_FONT_R = 255;
const Uint8 WHITE_TURN_FONT_G = 255;
const Uint8 WHITE_TURN_FONT_B = 255;

const Uint8 BLACK_TURN_FONT_R = 0;
const Uint8 BLACK_TURN_FONT_G = 0;
const Uint8 BLACK_TURN_FONT_B = 0;

const Uint8 PLAYER_TURN_BACKGROUND_R = 105;
const Uint8 PLAYER_TURN_BACKGROUND_G = 105;
const Uint8 PLAYER_TURN_BACKGROUND_B = 105;


//----------------------------------------------------------------------------------------------------------------

//end game view

/**
 * enum to distinguish what is the result of the game
 */
enum GameResult {
    WHITE_WIN = 0,
    BLACK_WIN = 1,
    DRAW_RESULT = 2
};

const int END_GAME_FONT_SIZE = MAIN_MENU_BUTTON_FONT_SIZE;

const int END_GAME_BUTTON_WIDTH = 400;
const int END_GAME_BUTTON_HEIGHT = (int)(1.25 * END_GAME_FONT_SIZE);

const int END_GAME_MAIN_MENU_BUTTON_MIDDLE_X = SCREEN_WIDTH / 2;
const int END_GAME_MAIN_MENU_BUTTON_MIDDLE_Y = SCREEN_HEIGHT - END_GAME_FONT_SIZE * 4;

const int END_GAME_EXIT_BUTTON_MIDDLE_X = SCREEN_WIDTH / 2;
const int END_GAME_EXIT_BUTTON_MIDDLE_Y = SCREEN_HEIGHT - END_GAME_FONT_SIZE * 2;

const int END_GAME_TITLE_MIDDLE_X = SCREEN_WIDTH / 2;
const int END_GAME_TITLE_MIDDLE_Y = MAIN_MENU_TITLE_FONT_SIZE * 1.25;

const Uint8 END_GAME_BACKGROUND_R = BOARD_LIGHT_R;
const Uint8 END_GAME_BACKGROUND_G = BOARD_LIGHT_G;
const Uint8 END_GAME_BACKGROUND_B = BOARD_LIGHT_B;

//----------------------------------------------------------------------------------------------------------------

//choose player view

const int CHOOSE_PLAYER_POSITION_SET = SCREEN_WIDTH/18;

const int CHOOSE_PLAYER_IMAGE_SIZE = (int)(CHOOSE_PLAYER_POSITION_SET * 2.5);
const int CHOOSE_PLAYER_FONT_SIZE = (int)(CHOOSE_PLAYER_POSITION_SET * 1.5);

const int CHOOSE_PLAYER_TITLE_X = CHOOSE_PLAYER_POSITION_SET;
const int CHOOSE_PLAYER_TITLE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 0.25);

const int CHOOSE_PLAYER_WHITE_IMAGE_X = CHOOSE_PLAYER_POSITION_SET;
const int CHOOSE_PLAYER_WHITE_IMAGE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 3.00);

const int CHOOSE_PLAYER_BLACK_IMAGE_X = CHOOSE_PLAYER_POSITION_SET;
const int CHOOSE_PLAYER_BLACK_IMAGE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 5.75);

const int CHOOSE_PLAYER_WHITE_BUTTON_X = (int)(CHOOSE_PLAYER_POSITION_SET * 3.75);
const int CHOOSE_PLAYER_WHITE_BUTTON_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 3.00);

const int CHOOSE_PLAYER_BLACK_BUTTON_X = (int)(CHOOSE_PLAYER_POSITION_SET * 3.75);
const int CHOOSE_PLAYER_BLACK_BUTTON_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 5.75);

const int CHOOSE_PLAYER_START_BUTTON_X = CHOOSE_PLAYER_POSITION_SET;
const int CHOOSE_PLAYER_START_BUTTON_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 8.5);


const int CHOOSE_PLAYER_BUTTON_WIDTH = (int)(CHOOSE_PLAYER_POSITION_SET * 12.75);
const int CHOOSE_PLAYER_BUTTON_HEIGHT = (int)(CHOOSE_PLAYER_POSITION_SET * 2.5);
const int CHOOSE_PLAYER_START_BUTTON_WIDTH = CHOOSE_PLAYER_POSITION_SET * 16;

const int CHOOSE_PLAYER_TITLE_FONT_MIDDLE_X = CHOOSE_PLAYER_POSITION_SET * 9;
const int CHOOSE_PLAYER_TITLE_FONT_MIDDLE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 1.5);

const int CHOOSE_PLAYER_WHITE_FONT_MIDDLE_X = (int)(CHOOSE_PLAYER_POSITION_SET * 10.5);
const int CHOOSE_PLAYER_WHITE_FONT_MIDDLE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 4.25);

const int CHOOSE_PLAYER_BLACK_FONT_MIDDLE_X = (int)(CHOOSE_PLAYER_POSITION_SET * 10.5);
const int CHOOSE_PLAYER_BLACK_FONT_MIDDLE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 7);

const int CHOOSE_PLAYER_START_FONT_MIDDLE_X = CHOOSE_PLAYER_POSITION_SET * 9;
const int CHOOSE_PLAYER_START_FONT_MIDDLE_Y = (int)(CHOOSE_PLAYER_POSITION_SET * 9.75);

const Uint8 CHOOSE_PLAYER_BACKGROUND_R = BOARD_LIGHT_R;
const Uint8 CHOOSE_PLAYER_BACKGROUND_G = BOARD_LIGHT_G;
const Uint8 CHOOSE_PLAYER_BACKGROUND_B = BOARD_LIGHT_B;

const Uint8 CHOOSE_PLAYER_FONT_R = BOARD_DARK_R;
const Uint8 CHOOSE_PLAYER_FONT_G = BOARD_DARK_G;
const Uint8 CHOOSE_PLAYER_FONT_B = BOARD_DARK_B;

//----------------------------------------------------------------------------------------------------------------

//promotion view

const Uint8 PROMOTION_BACKGROUND_R = BOARD_LIGHT_R;
const Uint8 PROMOTION_BACKGROUND_G = BOARD_LIGHT_G;
const Uint8 PROMOTION_BACKGROUND_B = BOARD_LIGHT_B;

const Uint8 PROMOTION_FONT_R = BOARD_DARK_R;
const Uint8 PROMOTION_FONT_G = BOARD_DARK_G;
const Uint8 PROMOTION_FONT_B = BOARD_DARK_B;

const int PROMOTION_POSITION_SET = SCREEN_HEIGHT/20;

const int PROMOTION_IMAGE_SIZE = 7 * PROMOTION_POSITION_SET;
const int PROMOTION_FONT_SIZE = 3 * PROMOTION_POSITION_SET;

const int PROMOTION_FONT_MIDDLE_X = SCREEN_HEIGHT / 2;
const int PROMOTION_FONT_MIDDLE_Y = (int)(2 * PROMOTION_POSITION_SET);

const int PROMOTION_QUEEN_POS_X = (int)(2.5 * PROMOTION_POSITION_SET);
const int PROMOTION_QUEEN_POS_Y = 4 * PROMOTION_POSITION_SET;

const int PROMOTION_ROOK_POS_X = (int)(10.5 * PROMOTION_POSITION_SET);
const int PROMOTION_ROOK_POS_Y = 4 * PROMOTION_POSITION_SET;

const int PROMOTION_KNIGHT_POS_X = (int)(2.5 * PROMOTION_POSITION_SET);
const int PROMOTION_KNIGHT_POS_Y = 12 * PROMOTION_POSITION_SET;

const int PROMOTION_BISHOP_POS_X = (int)(10.5 * PROMOTION_POSITION_SET);
const int PROMOTION_BISHOP_POS_Y = 12 * PROMOTION_POSITION_SET;

//-----------------------------------------------------------------------------------------------------------------

/**
 * enum to represent wheter the player is playing with mouse or it is AI
 */
enum PlayerType {
    NORMAL_PLAYER = 0,
    COMPUTER = 1
};

/**
 * enum to represent what type of move can figure do on the given field
 */
enum MoveType {
    NONE = -1,
    NORMAL = 0,
    CAPTURE = 1,
    CASTLE = 2,
    EN_PASSANT = 3,
    CHECK = 4,
};

/**
 * enum to represent which side of en passant movement we currently check
 */
enum EnPassantSide {
    EN_LEFT = -1,
    EN_RIGHT = 1
};

/**
 * enum to represent which side of castling we currently check
 */
enum CastlingSide {
    CASTLING_LEFT = -1,
    CASTLING_RIGHT = 1
};

/**
 * enum to represent color of the figure
 */
enum FigureColor {
	NONE_C = -1,
    WHITE = 0,
	BLACK = 1
};

/**
 * enum which convert the numeric position to first index in the two dimensional array to represent board
 */
enum NumericPosition {
	NUM_POS_1 = 7,
	NUM_POS_2 = 6,
	NUM_POS_3 = 5,
	NUM_POS_4 = 4,
	NUM_POS_5 = 3,
	NUM_POS_6 = 2,
	NUM_POS_7 = 1,
	NUM_POS_8 = 0
};

/**
 * enum which convert the letter position to second index in the two dimensional array to represent board
 */
enum LetterPosition {
	LET_POS_A = 0,
	LET_POS_B = 1,
	LET_POS_C = 2,
	LET_POS_D = 3,
	LET_POS_E = 4,
	LET_POS_F = 5,
	LET_POS_G = 6,
	LET_POS_H = 7
};

/**
 * enum to represent type of figure
 */
enum FigureType {
	NONE_T = -1,
    PAWN = 0,
	BISHOP = 1,
	KNIGHT = 2,
	ROOK = 3,
	QUEEN = 4,
	KING = 5
};

//-----------------------------------------------------------------------------------------------------------------

/**
 * enum to represent view to be shown next
 */
enum WhichViewNext {
    CHOOSE_PLAYER = 0,
    NEW_GAME = 1,
    LOAD_GAME = 2,
    END_GAME = 3,
    HELP = 4,
    EXIT = 5,
    MAIN_MENU = 6,
    START_GAME_FROM_STATE = 7,
    DEFAULT_VALUE = 8
};

//-----------------------------------------------------------------------------------------------------------------

#endif //CONSTANTSANDENUMS_HPP