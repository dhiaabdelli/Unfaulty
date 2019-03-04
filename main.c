#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_ttf.h"
#include "resource/menu/menu.h"

int main(){
	SDL_Surface *screen;
	Mix_Music *MenuMusic;
	Mix_Chunk *SoundButtonHover, *SoundButtonClick;
	Button button[10];
	Background menu, menutop, menuExit, menuSingleplayer,NULLL;
	Text title;
	Sprite smoke,dust;
	NULLL.src = NULL;
	int done = 0, choix, poskeys = -1;
	initGame(&screen, &title, &smoke, &dust, button, &menu, &menutop, &menuExit, &MenuMusic, &SoundButtonHover, &SoundButtonClick, &menuSingleplayer);
	cinematiqueLJ(screen);
	Mix_PlayMusic(MenuMusic, -1);
	while(!done){
		choix = mainMenu(screen, title, smoke, dust, menu, menutop, button, SoundButtonHover, SoundButtonClick, &poskeys);
		switch(choix){
			case 1:
				choix = subMenu(screen, title, smoke, dust, menu, button, SoundButtonHover, SoundButtonClick, NULLL, menutop, 4, 7);
				switch(choix){
					case 5:
						//choix = subMenu(screen, menu, button, music, menuSingleplayer, 6, 9);
						/*switch(choix){
							case 7:
								//jeuSingleplayer();
								break;
							case 8:
								//jeuLoadgame();
								break;
						}*/
						break;
					case 6:
							//jeuMultiplayer();
						break;
				}
				break;
			case 2:
				//settingsMenu();
				break;
			case 3:
				//creditsMenu();
				break;
			case 4:
				choix = subMenu(screen, title, smoke, dust, menu, button, SoundButtonHover, SoundButtonClick, menuExit, menutop, 7, 9);
				if(choix == 8){
					done = 1;
				}
				break;
		}
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(menu.src);
	SDL_FreeSurface(menutop.src);
	SDL_FreeSurface(menuExit.src);
	SDL_FreeSurface(title.message);
	TTF_CloseFont(title.font);
	Mix_FreeChunk(SoundButtonClick);
	Mix_FreeChunk(SoundButtonHover);
	Mix_FreeMusic(MenuMusic);
	TTF_Quit();
	SDL_Quit();
	return 0;
}