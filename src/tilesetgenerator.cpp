#include "tilesetgenerator.h"

TilesetGenerator::TilesetGenerator(const std::string& filename):
    configFilename(filename),
    tilesetPos(0, 0)
{
}

bool TilesetGenerator::generate()
{
    bool status = false;
    readConfig();
    setupImage();
    for (unsigned imageNum = start; imageNum <= end; ++imageNum)
        addImage(imageDirectory + std::to_string(imageNum) + "." + imageExtension);
    saveTileset();
    return status;
}

void TilesetGenerator::readConfig()
{
    cfg::File config(configFilename, cfg::File::AllFlags);

    // Tilset settings
    config.useSection("Tileset");
    outputFilename = config("outputFilename");
    backgroundColor.setString(config("backgroundColor"));
    config("backgroundColor") = backgroundColor.toString();
    padding = sf::Vector2i(config("paddingX").toInt(), config("paddingY").toInt());
    tileCount = sf::Vector2u(config("horizontalTiles").toInt(), config("verticalTiles").toInt());
    tileSize = sf::Vector2u(config("tileWidth").toInt(), config("tileHeight").toInt());
    tilesetSize = sf::Vector2u(tileCount.x * tileSize.x, tileCount.y * tileSize.y);
    applyAlpha = config("applyAlpha").toBool();

    // Image settings
    config.useSection("Images");
    imageExtension = config("extension");
    imageDirectory = config("directory");
    if (!imageDirectory.empty() && imageDirectory.back() != '/')
        imageDirectory += '/';
    start = config("start").toInt();
    end = config("end").toInt();
    //end = std::min(config("end").toInt(), tileCount.x * tileCount.y);
}

void TilesetGenerator::setupImage()
{
    tilesetImage.create(tilesetSize.x, tilesetSize.y, backgroundColor.toColor());
}

bool TilesetGenerator::addImage(const std::string& filename)
{
    sf::Image image;
    bool status = image.loadFromFile(filename);
    if (status)
        tilesetImage.copy(image, tilesetPos.x * tileSize.x, tilesetPos.y * tileSize.y, sf::IntRect(0, 0, 0, 0), applyAlpha);
    // Increment coordinates, even if the image was not copied
    if (++tilesetPos.x >= tileCount.x)
    {
        tilesetPos.x = 0;
        ++tilesetPos.y;
    }
    return status;
}

bool TilesetGenerator::saveTileset()
{
    return tilesetImage.saveToFile(outputFilename);
}
