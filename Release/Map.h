#include<SFML\Graphics.hpp>
#include<time.h>
const int Height_Map =34;
const int Wight_Map = 60;

sf::String TileMap[Height_Map] = {
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
	"bllllllllllllllllllllllllblllllllllllllllllllllllllllllllllb",
	"blllllllbllllllllllllllllbllllllllllllllllllllllllbllllllllb",
	"blllllllbllllllllllllllllbllllllllllllllllllllllllbllllllllb",
	"blllllllbllllllllllllllllbllllllllllllllllllllllllbllllllllb",
	"bbbbbbbbbllllllllllllllllbllllllllllllllllllllllllbbbbbbbbbb",
	"blllllllblllllllllllllllllllllllllllllllllllllllllbllllllllb",
	"blllllllblllllllllllllllllllllllllllllllllllllllllbllllllllb",
	"blllllllblllllllllllllllllllllllllllllllllllllllllbllllllllb",
	"bllllllllllllllllllllllllllllllllllllllllllllllllllllllllllb",
	"bllllllllllllllllllllbllllllllbllllllllllllllllllllllllllllb",
	"bllllllllllllllllllllbllllllllbllllllllllllllllllllllllllllb",
	"bllllllllllllllllllllbllllllllbllllllllllllllllllllllllllllb",
	"bllllllllllllllllllllbbbbbbbbbbllllllllllllllllllllllllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"bllbbbbbbbbbbbbllllllllllllllllllllllllllllbbbbbbbbbbbbbbbbb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllblllllllb",
	"blllllllbllllllllllllllllllllllllllllllllllllllllllllllllllb",
	"bllllllllllllllllllllllllllllllllllllllllllllllllllllllllllb",
	"bllllllllblllllllllllllllllllllllllllllllllllllllllblllllllb",
	"bllllllllblllllllllllllllllllllllllllllllllllllllllblllllllb",
	"bllllllllblllllllllllllllllllllllllllllllllllllllllblllllllb",
	"bbbbbbbbbbllllllllllllllbllllllllllllllllllllllllllbbbbbbbbb",
	"bllllllllbllllllllllllllbllllllllllllllllllllllllllblllllllb",
	"bllllllllbllllllllllllllbllllllllllllllllllllllllllblllllllb",
	"bllllllllbllllllllllllllbllllllllllllllllllllllllllblllllllb",
	"blllllllllllllllllllllllbllllllllllllllllllllllllllllllllllb",
	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
};
void randomMapGenerate() 
{
	int randomElementX = 0;
	int randomElementY = 0;
	srand(time(NULL));
	int numBoxes = 25, numRoses = 15;


	while (numBoxes > 0) 
	{
		randomElementX = 1 + rand() % (Wight_Map- 1);
		randomElementY = 1 + rand() % (Height_Map - 1);
		if (TileMap[randomElementY][randomElementX] == 'l') 
		{
			TileMap[randomElementY][randomElementX] = 'r'; 
			numBoxes--;
		}
	}
	while (numRoses > 0)
	{
		randomElementX = 1 + rand() % (Wight_Map - 1);
		randomElementY = 1 + rand() % (Height_Map - 1);
		if (TileMap[randomElementY][randomElementX] == 'l')
		{
			TileMap[randomElementY][randomElementX] = 'd';
			numRoses--;
		}
	}
}
