#ifndef CONSTS_H_
#define CONST_H_

#include <string>

//-----------------VENTANA-----------------
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

//-----------------TEXTURES-----------------
const std::string IMAGES_PATH = "..\\images\\";
const std::string TEXTURES_FILE_NAME = "textures.txt";

//-----------------FONTS-----------------
const std::string FONTS_PATH = "..\\fonts\\";
const std::string FONTS_FILE_NAME = "fonts.txt";

//-----------------UPDATE-----------------
const int FRAME_RATE = 60;

//-----------------BOTONES-----------------
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 114;
const int BIG_BUTTON_WIDTH = 350;
const int BIG_BUTTON_HEIGHT = 200;

//-----------------LOGO-----------------
const int LOGO_WIDTH = 640;
const int LOGO_HEIGHT = 360;
const int LOGO_POS_X = (WIN_WIDTH / 2) - (LOGO_WIDTH / 2);
const int LOGO_POS_Y = 50;

//-----------------ARROW-----------------
const int ARROW_SPEED = 15;
const int ARROW_HEIGHT = 30;
const int ARROW_WIDTH = 150;

//-----------------BALLOON-----------------
const int BALLOON_HEIGHT = 128;
const int BALLOON_WIDTH = 128;
const int BALLOON_ANIMATION_TIME = 300;
const int VEL_BALLOONS_MAX = 10;
const int VEL_BALLOONS_MIN = 3;

//-----------------BOW-----------------
const int ANGLE_LIMIT = 60;
const int BOW_HEIGHT = 140;
const int BOW_WIDTH = 150;
const int BOW_SPEED = 10;

//-----------------BUTTERFLY-----------------
const int BUTTERFLY_ANIMATION_TIME = 300;
const int BUTTERFLY_SPEED = 5;
const int BUTTERFLY_HEIGHT = 100;
const int BUTTERFLY_WIDTH = 100;
const int TIME_TO_CHANGE_DIR = 2000;
const int MARGIN_BUTTERFLY = 150;

//-----------------REWARD-----------------
const int REWARD_HEIGHT = 30;
const int REWARD_WIDTH = 50;
const int REWARD_SPEED = 2;
const int REWARD_ANIMATION_TIME = 300;
const int REWARD_TYPES = 2;

//-----------------SPAWNER-----------------
const int SPAWN_LOWER_BOUND = WIN_WIDTH / 3;
const int SPAWN_UPPER_BOUND = WIN_WIDTH - 100;
const int SPAWN_SPACE = SPAWN_UPPER_BOUND - SPAWN_LOWER_BOUND;

//-----------------PLAYSTATE-----------------
const int MAX_ARROWS = 10;
const int SPAWN_TIME = 800;
const int POINTS_PER_LEVEL = 100;
const int NUM_LEVELS = 4;
const int BUTTERFLIES_PER_LEVEL = 5;
const int POINTS_PER_BALLOON = 5;

//-----------------UI-----------------
const int UI_SCORE_POS_X = 100;
const int UI_SCORE_POS_Y = 40;
const int UI_ARROWS_WIDTH = 15;
const int UI_ARROWS_HEIGHT = 60;

#endif // !CONSTS_H_