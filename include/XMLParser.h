#ifndef XMLPARSER_H
#define XMLPARSER_H

//#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureManager.h"
#include "LevelInfo.h"
#include <string>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

class XMLParser
{
    public:
        std::vector<std::string> getElementItems(tinyxml2::XMLElement * element);
        tinyxml2::XMLElement * visitElement(std::vector<std::string> pathList);
    	void loadXML(const char*);
    	void loadTexture(TextureManager& texture_manager,std::string type="default");
    	std::vector<int> getTileMap();
        void loadLevel(LevelInfo& level, int level_num);

    private:
    	tinyxml2::XMLDocument doc;
    	
};

#endif