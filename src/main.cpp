// See the file COPYRIGHT.txt for authors and copyright information.
// See the file LICENSE.txt for copying conditions.

#include "tilesetgenerator.h"

int main()
{
    // TODO: Take command line parameters
    TilesetGenerator tilesetGen("tileset.cfg");
    tilesetGen.generate();
    return 0;
}
