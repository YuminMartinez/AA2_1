#include "util.h"
#include "Game.h"

int numRandom(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void limpiarPantalla() {
	system("cls");  

}
int main()
{
	srand(time(NULL));
	
	Game game;
	game.m_map;
	game.m_player;
	game.m_NPC;
	game.setPlayer();
	game.CreateNPC();	
	while (game.finish == false)
	{
		Sleep(100);
		limpiarPantalla();
		
		
		game.printMap();
		game.NPCMoviment();
		game.PlayerInPut();

	}
}