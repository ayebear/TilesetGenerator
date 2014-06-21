#include "tilesetgenerator.h"

int main()
{
    // TODO: Take command line parameters
    TilesetGenerator tilesetGen("tileset.cfg");
    tilesetGen.generate();
    return 0;
}
