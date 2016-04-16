#include "SDL_mixer.h"
#include <iostream>

int audioEffectOne(){
	Mix_Chunk *effectOne = NULL;
	effectOne = Mix_LoadWAV("effectOne.wav");
	Mix_PlayChannel(-1, effectOne, 0);
	//Error checking
	/*if(!effectOne) {
    	printf("Mix_LoadMUS(\"effectTwo.wav\"): %s\n", Mix_GetError());
	}*/
	//to keep program running
	int a = 0;
	std::cin >> a;
	//Stop effect one
	if (a == 1){
		Mix_FreeChunk(effectOne);
		effectOne = NULL;
	}
}
int audioEffectTwo(){
	Mix_Chunk *effectTwo = NULL;
	effectTwo = Mix_LoadWAV("effectTwo.wav");
	Mix_PlayChannel(-1, effectTwo, 0);
	//Error checking
	/*if(!effectTwo) {
    	printf("Mix_LoadMUS(\"effectTwo.wav\"): %s\n", Mix_GetError());
	}*/
	//to keep program running
	int b = 0;
	std::cin >> b;
	//Stop effect two
	if (b == 1){
		Mix_FreeChunk(effectTwo);
		effectTwo = NULL;
	}
}
int main(){
	std::cout << "PLAY: " << std::endl;
	//Initialize mixer
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Music *music = NULL;
	music = Mix_LoadMUS("backgroundmusic.wav");
	//music to play, -1(unlimited repeats)
	Mix_PlayMusic(music, -1);
	//to keep program running
	int i = 0;
	std::cin >> i;
	//trigger effects
	if (i==1){
		audioEffectOne();
	}
	if (i==2){
		audioEffectTwo();
	}
	//Close Audio
	Mix_FreeMusic(music);
	music = NULL;
	Mix_CloseAudio();
	return 0;
}