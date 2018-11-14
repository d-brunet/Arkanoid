#include "game.h"

int main()
{
        Game game = Game();
        game.init("Arknoid", 864, 560);

        game.loop();

	return 0;
}
