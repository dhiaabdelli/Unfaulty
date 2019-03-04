#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_ttf.h"
#include "menu.h"

void initGame(SDL_Surface* *screen, Text *title, Sprite *smoke, Sprite *dust, Button *button, Background *menu, Background *menutop, Background *menuExit, Mix_Music* *MenuMusic , Mix_Chunk* *soundButtonHover, Mix_Chunk* *SoundButtonClick, Background *menuSingleplayer){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	if(TTF_Init() == -1)
	{
    	printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    	exit(EXIT_FAILURE);
	}
	//screen = SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE | SDL_DOUBLEBUF^SDL_FULLSCREEN);
	*screen = SDL_SetVideoMode(1000, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(*screen == NULL){
		printf("Unable to set video mode: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	menu->src = IMG_Load("materials/menu/background.png");
	if(menu->src == NULL){
		printf("Unable to load Menu background: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	menu->pos.x = 0;
	menu->pos.y = 0;

	title->font = TTF_OpenFont( "materials/fonts/CaviarDreams_Bold.ttf", 15);
	if(title->font == NULL){
		printf("Unable to load font : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	//title->textColor = { 0, 0, 0 };
	title->textColor.r = 255;
  	title->textColor.g = 255;
  	title->textColor.b = 255;
	title->message = TTF_RenderText_Solid( title->font, "Copyright(C) Blindspot 2019 All Rights Reserved", title->textColor);
	title->pos.x = menu->src->w -  title->message->w;
	title->pos.y = menu->src->h - 20;

	smoke->src = IMG_Load("materials/sprites/menu/smokeSpritesheet.png");
	if(smoke->src == NULL){
		printf("Unable to load smoke sprites: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	smoke->pos.x = 290;
	smoke->pos.y = 115;

	smoke->posprite.x = 0;
	smoke->posprite.y = 0;
	smoke->posprite.h = smoke->src->h;
	smoke->posprite.w = 70;

	dust->src = IMG_Load("materials/sprites/menu/dustParticles.png");
	if(dust->src == NULL){
		printf("Unable to load smoke sprites: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	dust->pos.x = 484;
	dust->pos.y = 250;

	dust->posprite.x = 0;
	dust->posprite.y = 0;
	dust->posprite.h = smoke->src->h;
	dust->posprite.w = 398;
	/*menuSingleplayer->src = IMG_Load("materials/menu/menuPlay.png");
	if(menuSingleplayer->src == NULL){
		printf("Unable to load Singleplayer Menu File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}*/

	menuExit->src = IMG_Load("materials/menu/exit/exitMenu.png");
	if(menuExit->src == NULL){
		printf("Unable to load Exit Menu File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	menuExit->pos.x = (menu->src->w / 2 ) - (menuExit->src->w / 2);
	menuExit->pos.y = 200;

	menutop->src = IMG_Load("materials/menu/topThing.png");
	if(menu->src == NULL){
		printf("Unable to load Menu background: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	menutop->pos.x = 0;
	menutop->pos.y = 0;

	initButton(&button[9], (menu->src->w / 2) - 40, 0, "materials/menu/logo.png", "materials/menu/logoHover.png");
	initButton(&button[0], 0, 81, "materials/menu/play.png", "materials/menu/playHover.png");
	initButton(&button[1], 0, 137, "materials/menu/settings.png", "materials/menu/settingsHover.png");
	initButton(&button[2], 0, 193, "materials/menu/credits.png", "materials/menu/creditsHover.png");
	initButton(&button[3], 0, 493, "materials/menu/exit.png", "materials/menu/exitHover.png");
	initButton(&button[4], 200, 120, "materials/menu/singleplayer.png", "materials/menu/singleplayerHover.png");
	initButton(&button[5], 550, 120, "materials/menu/cooperative.png", "materials/menu/cooperativeHover.png");
	initButton(&button[6], menu->src->w - 58, 493, "materials/menu/back.png", "materials/menu/backHover.png");
	initButton(&button[7], menuExit->pos.x + 60, 300, "materials/menu/exit/yes.png", "materials/menu/exit/yesHover.png");
	initButton(&button[8], menuExit->pos.x + 300, 300, "materials/menu/exit/no.png", "materials/menu/exit/noHover.png");
	//initButton(&button[6], 0, 493, "materials/menu/newgame.png", "materials/menu/newgamehover.png");
	//initButton(&button[6], 0, 493, "materials/menu/loadgame.png", "materials/menu/loadgamehover.png");


	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) == -1){
		printf("Error : %s\n", Mix_GetError());
	}

	*MenuMusic = Mix_LoadMUS("sound/Music.mp3");
	if(*MenuMusic == NULL){
		printf("Unable to load Sound File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	*soundButtonHover = Mix_LoadWAV("sound/buttonHover.wav");
	if(*soundButtonHover == NULL){
		printf("Unable to load Sound File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	*SoundButtonClick = Mix_LoadWAV("sound/buttonClick.wav");
	if(*SoundButtonClick == NULL){
		printf("Unable to load Sound File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

void cinematiqueLJ(SDL_Surface* screen){
	int i;
	for(i = 0; i < 5; i++){
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_Flip(screen);
		SDL_Delay(100);
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));
		SDL_Flip(screen);
		SDL_Delay(100);
	}
}


void initButton(Button *button, int x, int y, char* regular, char* hover){
	button->pos.x = x;
	button->pos.y = y;
	button->regular = IMG_Load(regular);
	if(button->regular == NULL){
		printf("Unable to load button regular: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	button->hover = IMG_Load(hover);
	if(button->hover == NULL){
		printf("Unable to load button hover: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	button->pos.h = button->regular->h;
	button->pos.w = button->regular->w;
	button->soundPlayedHover = 0;
	button->soundPlayedClick = 0;
}


int hover(SDL_Rect pos,int x,int y){
	return (x > pos.x && x < pos.x + pos.w && y > pos.y && y < pos.y+pos.h);
}

void kbMenu(int a, int b, int* k){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_KEYDOWN:{
				if(event.key.keysym.sym == a){
					if(*k < 3){
						(*k)++;
					}else{
						*k = 0;
					}
				}else if(event.key.keysym.sym == b){
					if(*k > 0){
							(*k)--;
						}else{
							*k = 3;
						}
				}	
				
			}
		}	
	}
}

int mainMenu(SDL_Surface* screen, Text title, Sprite smoke, Sprite dust, Background menu, Background menutop, Button* button, Mix_Chunk* SoundButtonHover, Mix_Chunk* SoundButtonClick, int *poskeys){
	int x, y, i, choix = -1, k = 0;
	SDL_Event event;
	Uint8 p;
	Uint8* keys;
	do{
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		SDL_BlitSurface(menu.src, NULL, screen, &menu.pos);
		SDL_BlitSurface(menutop.src, NULL, screen, &menutop.pos);
		SDL_BlitSurface(dust.src, &dust.posprite, screen, &dust.pos);
		SDL_BlitSurface(smoke.src, &smoke.posprite, screen, &smoke.pos);
		SDL_BlitSurface(title.message, NULL, screen, &title.pos);
		if(k == 4){
			k = 0;
			if(smoke.posprite.x <= 60*5){
				smoke.posprite.x += 70;
				dust.posprite.x += 398;
			}else{
				smoke.posprite.x = 0;
				dust.posprite.x = 0;
			}
		}else{
			k++;
		}
		p = SDL_GetMouseState(&x, &y);
		for(i = 0; i < 4; i++){
			if(hover(button[i].pos, x, y)){
				button[i].current = button[i].hover;
				if(!button[i].soundPlayedHover){
					Mix_PlayChannel(-1, SoundButtonHover, 0);
					button[i].soundPlayedHover = 1;
				}
				if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
					if(!button[i].soundPlayedClick){
						Mix_PlayChannel(-1, SoundButtonClick, 0);
						button[i].soundPlayedClick = 1;
					}
					choix = i + 1;
				}else{
					button[i].soundPlayedClick = 0;
					*poskeys = i;
				}
			}else{
				if(*poskeys != i){
						button[i].current = button[i].regular;
						button[i].soundPlayedHover = 0;
				}
			}
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
		}
		SDL_BlitSurface(menu.src, NULL, screen, &menu.pos);
		SDL_BlitSurface(menutop.src, NULL, screen, &menutop.pos);
		SDL_BlitSurface(dust.src, &dust.posprite, screen, &dust.pos);
		SDL_BlitSurface(smoke.src, &smoke.posprite, screen, &smoke.pos);
		SDL_BlitSurface(title.message, NULL, screen, &title.pos);
		if(k == 4){
			k = 0;
			if(smoke.posprite.x <= 60*5){
				smoke.posprite.x += 70;
				dust.posprite.x += 398;
			}else{
				smoke.posprite.x = 0;
				dust.posprite.x = 0;
			}
		}else{
			k++;
		}
		keys=SDL_GetKeyState(NULL);
		kbMenu(SDLK_DOWN, SDLK_UP, poskeys);
		for(i = 0; i < 4 && choix == -1; i++){
			if(*poskeys == i){
				button[i].current = button[i].hover;
				if(!button[i].soundPlayedHover){
					Mix_PlayChannel(-1, SoundButtonHover, 0);
					button[i].soundPlayedHover = 1;
				}else if(hover(button[i].pos, x, y)){
					*poskeys = -1;
				}
				if(keys[SDLK_RETURN] || keys[SDLK_KP_ENTER]){
					if(!button[i].soundPlayedClick){
						Mix_PlayChannel(-1, SoundButtonClick, 0);
						button[i].soundPlayedClick = 1;
					}
					choix = i + 1;
				}else{
					button[i].soundPlayedClick = 0;
				}
			}else{
				button[i].current = button[i].regular;
				button[i].soundPlayedHover = 0;
			}
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
		}
		if(hover(button[9].pos, x, y)){
			button[9].current = button[9].hover;
		}else{
			button[9].current = button[9].regular;
		}
		SDL_BlitSurface(button[9].current, NULL, screen, &button[9].pos);
		SDL_Flip(screen);
	}while(choix == -1 && *poskeys == -1);
	return choix;
}

int subMenu(SDL_Surface* screen, Text title, Sprite smoke, Sprite dust, Background menu, Button* button, Mix_Chunk* SoundButtonHover, Mix_Chunk* SoundButtonClick, Background subMenu, Background menutop, int j, int j2){
	int x, y, i, choix = -1;
	SDL_Event event;
	Background greySurface;
	greySurface.src = IMG_Load("materials/menu/greySurface.png");
	if(greySurface.src == NULL){
		printf("Unable to load greySurface File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	greySurface.pos.x = 0;
	greySurface.pos.y = 0;
	Uint8 p;
	do{
		SDL_BlitSurface(menu.src, NULL, screen, &menu.pos);
		SDL_BlitSurface(greySurface.src, NULL, screen, &greySurface.pos);
		for(i = 0; i < 4; i++){
			button[i].current = button[i].regular;
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
		}
		SDL_BlitSurface(subMenu.src, NULL, screen, &subMenu.pos);
		SDL_BlitSurface(menutop.src, NULL, screen, &menutop.pos);
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		p = SDL_GetMouseState(&x, &y);
		for(i = j; i < j2; i++){
			if(hover(button[i].pos, x, y)){
				button[i].current = button[i].hover;
				if(!button[i].soundPlayedHover){
					Mix_PlayChannel(-1, SoundButtonHover, 0);
					button[i].soundPlayedHover = 1;
				}
				if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
					if(!button[i].soundPlayedClick){
						Mix_PlayChannel(-1, SoundButtonClick, 0);
						button[i].soundPlayedClick = 1;
					}
					choix = i + 1;
				}else{
					button[i].soundPlayedClick = 0;
				}
			}else{
				button[i].current = button[i].regular;
				button[i].soundPlayedHover = 0;
			}
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);

		}
		if(hover(button[9].pos, x, y)){
			button[9].current = button[9].hover;
		}else{
			button[9].current = button[9].regular;
		}
		SDL_BlitSurface(button[9].current, NULL, screen, &button[9].pos);
		SDL_Flip(screen);
	}while(choix == -1);
	SDL_FreeSurface(greySurface.src);
	return choix;
}
