// See the file COPYRIGHT.txt for authors and copyright information.
// See the file LICENSE.txt for copying conditions.

#ifndef TILESETGENERATOR_H
#define TILESETGENERATOR_H

#include <string>
#include <SFML/Graphics.hpp>
#include "configfile.h"
#include "colorcode.h"

/*
TODO:
    Make it able to generate any number of tilesets!
        This way you don't have to re-configure it each time you use it
    If the tile size isn't specified, use the first image as the size
    Make sure start and end are valid
    Add ranges on options in config
    Implement padding
*/

// This class combines a bunch of image files into a single image file
class TilesetGenerator
{
    public:
        TilesetGenerator(const std::string& filename);
        bool generate();

    private:
        void readConfig();
        void setupImage();
        bool addImage(const std::string& filename);

        // Objects
        cfg::File config;
        sf::Image tilesetImage;

        // Settings
        std::string imageExtension;
        std::string imageDirectory;
        ColorCode backgroundColor;
        sf::Vector2i padding;
        sf::Vector2u tileCount;
        sf::Vector2u tileSize;
        sf::Vector2u tilesetSize;
        sf::Vector2u tilesetPos;
        unsigned start;
        unsigned end;
        bool applyAlpha;
};

#endif
