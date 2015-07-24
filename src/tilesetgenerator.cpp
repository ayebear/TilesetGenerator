// See the file COPYRIGHT.txt for authors and copyright information.
// See the file LICENSE.txt for copying conditions.

#include "tilesetgenerator.h"
#include <iostream>

TilesetGenerator::TilesetGenerator(const std::string& filename):
    config(filename)
{
    // Disable SFML error messages
    sf::err().rdbuf(NULL);
}

bool TilesetGenerator::generate()
{
    bool status = false;
    for (auto& section: config)
    {
        std::cout << "Generating " << section.first << "...\n";
        readConfig(section.first);
        setupImage();
        for (unsigned imageNum = start; imageNum <= end; ++imageNum)
            addImage(imageDirectory + std::to_string(imageNum) + "." + imageExtension);
        status = tilesetImage.saveToFile(section.first);
    }
    return status;
}

void TilesetGenerator::readConfig(const std::string& sectionName)
{
    config.useSection(sectionName);

    // Tilset settings
    backgroundColor.setString(config("backgroundColor"));
    config("backgroundColor") = backgroundColor.toString();
    padding = sf::Vector2i(config("paddingX").toInt(), config("paddingY").toInt());
    tileCount = sf::Vector2u(config("horizontalTiles").toInt(), config("verticalTiles").toInt());
    tileSize = sf::Vector2u(config("tileWidth").toInt(), config("tileHeight").toInt());
    tilesetSize = sf::Vector2u(tileCount.x * (tileSize.x + padding.x) + padding.x,
                               tileCount.y * (tileSize.y + padding.y) + padding.y);
    applyAlpha = config("applyAlpha").toBool();

    // Image settings
    imageExtension = config("imageExtension");
    imageDirectory = config("imageDirectory");
    strlib::mustEndWith(imageDirectory, "/");
    start = config("imageStart").toInt();
    end = config("imageEnd").toInt();
    //end = std::min(config("end").toInt(), tileCount.x * tileCount.y);
}

void TilesetGenerator::setupImage()
{
    tilesetImage.create(tilesetSize.x, tilesetSize.y, backgroundColor.toColor());
    tilesetPos = sf::Vector2u(0, 0);
}

bool TilesetGenerator::addImage(const std::string& filename)
{
    sf::Image image;
    bool status = image.loadFromFile(filename);
    if (status)
    {
        tilesetImage.copy(image, tilesetPos.x * (tileSize.x + padding.x) + padding.x,
            tilesetPos.y * (tileSize.y + padding.y) + padding.y, sf::IntRect(0, 0, 0, 0), applyAlpha);
    }

    // Increment coordinates, even if the image was not copied
    if (++tilesetPos.x >= tileCount.x)
    {
        tilesetPos.x = 0;
        ++tilesetPos.y;
    }

    return status;
}
