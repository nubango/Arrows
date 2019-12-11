#ifndef CONSTS_H_
#define CONST_H_

#include <string>

//-----------------VENTANA-----------------
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

//-----------------TEXTURES-----------------
const std::string IMAGES_PATH = "..\\images\\";
const std::string TEXTURES_FILE_NAME = "textures.txt";

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
const int LOGO_POS_X = (WIN_WIDTH/2) - (LOGO_WIDTH/2);
const int LOGO_POS_Y = 50;

#endif // !CONSTS_H_