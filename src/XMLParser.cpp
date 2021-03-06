#include "XMLParser.h"

void XMLParser::loadXML(const char* path) {
	doc.LoadFile(path);
}

void XMLParser::loadLevel(LevelInfo& level, int level_num) {
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * level_list = root->FirstChildElement("LevelList");
	tinyxml2::XMLElement * level_element = level_list->FirstChildElement();
	
	// find level in level list
	while(level_element!=NULL && (level_element->FirstChildElement("LevelNumber")->GetText())!=(std::to_string(level_num))) {
		level_element=level_element->NextSiblingElement();
	}

	// load level settings
	level.setLevelNumber(std::stoi(level_element->FirstChildElement("LevelNumber")->GetText()));
	level.setLevelLength(std::stoi(level_element->FirstChildElement("LevelLength")->GetText()));
	level.setMinionNumber(std::stoi(level_element->FirstChildElement("MinionsNumber")->GetText()));
	level.setBackgroundImage(level_element->FirstChildElement("BackgroundImage")->GetText());
	level.setBackgroundMusic(level_element->FirstChildElement("BackgroundMusic")->GetText());

	// load terrain map
	std::vector<std::vector<sf::Vector2f>> polygon_list;
	for(tinyxml2::XMLElement * polygon = level_element->FirstChildElement("TerrainList")->FirstChildElement();
		polygon!=NULL; polygon=polygon->NextSiblingElement()) {
		std::vector<sf::Vector2f> polygon_entry;
		for(tinyxml2::XMLElement * vertex = polygon->FirstChildElement();
		vertex!= NULL;vertex=vertex->NextSiblingElement()) {
			sf::Vector2f point;
			std::string vertex_text = vertex->GetText();
			point.x = std::stoi((vertex_text).substr(0, (vertex_text).find(",")));
			point.y = std::stoi((vertex_text).substr((vertex_text).find(",")+1));
			polygon_entry.push_back(point);
	}
	polygon_list.push_back(polygon_entry);
		
	}

	level.setTerrain(polygon_list);

}

void XMLParser::setSwordfishInfoList() {
	tinyxml2::XMLNode * root = doc.FirstChild();

	// load swordfish info
	int pos_x, pos_y, delay;
	float dir_x, dir_y;
	for(tinyxml2::XMLElement * algorithm = root->FirstChildElement("SwordfishAlgorithmList")->FirstChildElement();
		algorithm!=NULL; algorithm=algorithm->NextSiblingElement()) {
		SwordfishInfo swordfish_info;

		std::vector<int> pos_x_vector = getIntList(algorithm->FirstChildElement("position_x")->GetText());
		std::vector<int> pos_y_vector = getIntList(algorithm->FirstChildElement("position_y")->GetText());
		std::vector<int> dir_x_vector = getIntList(algorithm->FirstChildElement("direction_x")->GetText());;
		std::vector<int> dir_y_vector = getIntList(algorithm->FirstChildElement("direction_y")->GetText());;
		
		int delay = std::stoi(algorithm->FirstChildElement("delay")->GetText());

		for(int i = 0;i<5;i++) {

			swordfish_info.addSwordfish(pos_x_vector[i],pos_y_vector[i],delay * (i + 1),dir_x_vector[i],dir_y_vector[i]);
			
		}
		swordfish_info_list.push_back(swordfish_info);
}
}

std::vector<SwordfishInfo> XMLParser::getSwordfishInfoList() {
	return swordfish_info_list;
}


std::vector<std::string> XMLParser::getElementItems(tinyxml2::XMLElement * element) {
	
	std::vector<std::string> items;

	for(tinyxml2::XMLElement * item = element->FirstChildElement();
		item!= NULL;item=item->NextSiblingElement()) {
		items.push_back(item->GetText());
}

return items;
}

std::vector<int> XMLParser::getTileMap() {
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * tileMap = root->FirstChildElement("TileMap");
	std::string tileMapText = tileMap->GetText();

	std::stringstream ss(tileMapText);

	int i;
	std::vector<int> v;
	while(ss>> i) {
		v.push_back(i);
		if(ss.peek()==',')
			ss.ignore();
	}

	return v;
}

// adds texture info from the XML file to the texture manager 
void XMLParser::loadTexture(TextureManager &texture_manager, std::string name) {
	// Find specific texture needed
	tinyxml2::XMLNode * root = doc.FirstChild();
	tinyxml2::XMLElement * textureList = root->FirstChildElement("TextureList");
	tinyxml2::XMLElement * texture = textureList->FirstChildElement();
	while(texture!=NULL && (texture->FirstChildElement("name")->GetText())!=(name)) {
		texture=texture->NextSiblingElement();
	}
//		std::cout<<texture->FirstChildElement("name")->GetText()<<std::endl;

	// sets location of texture
	tinyxml2::XMLElement * location = texture->FirstChildElement("location");
	texture_manager.addTexture(location->GetText(),name);

	// iterate through areas listed and add to texture manager
	for(tinyxml2::XMLElement * item = texture->FirstChildElement("Positions")->FirstChildElement();
		item!= NULL;item=item->NextSiblingElement()) {
		std::string itemText = item->GetText();
	std::string areaName = (itemText).substr(0, (itemText).find("|"));
	std::string value = (itemText).substr((itemText).find("|")+1);
	std::stringstream ss(value);

	int i;
	std::vector<int> v;
	while(ss>> i) {
		v.push_back(i);
		if(ss.peek()==',')
			ss.ignore();
	}
	texture_manager.addArea(areaName,sf::IntRect(v.at(0),v.at(1),v.at(2),v.at(3)),name);
}
}

std::vector<int> XMLParser::getIntList(std::string list) {
	int x;
	std::vector<int> vector;
	std::stringstream ss(list);

	while(ss>> x) {
			vector.push_back(x);
			if(ss.peek()==',')
				ss.ignore();
		}
		return vector;
}
