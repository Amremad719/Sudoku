// @author: Amremad719
#include "bits/stdc++.h"
#include "Game.h"
#include <windows.h>
#include <time.h>
#define s ' '
using namespace std;
using namespace sf;


 int main()
 {
	 srand(time(NULL));
	//bool opened = freopen("log.txt", "w", stdout);

	//Init Game
	Game game;

	// Main Loop
	while(game.running())
	{
		//update
		game.update();

		//render
		game.render();
	}
	return 0;
 }