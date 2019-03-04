#ifndef MENU_H_INCLUDE
#define MENU_H_INCLUDE

typedef struct{
	SDL_Surface* current, * regular, * hover;
	SDL_Rect pos;
	int soundPlayedHover, soundPlayedClick;
} Button;

typedef struct{
	SDL_Surface* src;
	SDL_Rect pos;
} Background;

typedef struct{
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Surface *message;
	SDL_Rect pos;
} Text;

typedef struct{
	SDL_Surface* src;
	SDL_Rect pos;
	SDL_Rect posprite;
} Sprite;

void initGame(SDL_Surface* *screen, Text *title, Sprite *smoke, Sprite *dust, Button *button, Background *menu, Background *menutop, Background *menuExit, Mix_Music* *MenuMusic , Mix_Chunk* *soundButtonHover, Mix_Chunk* *SoundButtonClick, Background *menuSingleplayer);
void cinematiqueLJ(SDL_Surface* screen);
void initButton(Button *button, int x, int y, char* regular, char* hover);
int hover(SDL_Rect pos, int x,int y);
int mainMenu(SDL_Surface* screen, Text title, Sprite smoke, Sprite dust, Background menu, Background menutop, Button* button, Mix_Chunk* SoundButtonHover, Mix_Chunk* SoundButtonClick, int *poskeys);
int subMenu(SDL_Surface* screen, Text title, Sprite smoke, Sprite dust, Background menu, Button* button, Mix_Chunk* SoundButtonHover, Mix_Chunk* SoundButtonClick, Background subMenu, Background menutop, int j, int j2);
void settingsMenu();
void creditsMenu();
void kbMenu(int a, int b, int* k);
#endif //MENU_H_INCLUDE