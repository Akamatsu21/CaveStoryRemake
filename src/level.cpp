#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <SDL2/SDL.h>
#include "tinyxml2.h"
#include "graphics.h"
#include "level.h"

using namespace tinyxml2;

Level::Level()
{
	background = NULL;
	map_name = "";
	map_size = Vector2(0, 0);
	spawn_point = Vector2(0, 0);
	tile_size = Vector2(0, 0);
}
Level::Level(Graphics &graphics, std::string name, Vector2 point):
	map_name(name), map_size(Vector2(0, 0)), spawn_point(point), tile_size(Vector2(0,0))
{
	loadMap(graphics, map_name);
}

Level::~Level()
{
	
}

void Level::loadMap(Graphics &graphics, std::string name)
{
	//Parse the .tmx file
	XMLDocument doc;
	std::stringstream ss;
	ss << "..\\content\\maps\\" << map_name << ".tmx";
	doc.LoadFile(ss.str().c_str());
	
	//Get the map size
	XMLElement *map_node = doc.FirstChildElement("map");
	int mw, mh;
	map_node->QueryIntAttribute("width", &mw);
	map_node->QueryIntAttribute("height", &mh);
	map_size = Vector2(mw, mh);
	
	//Get the tile size
	int tw, th;
	map_node->QueryIntAttribute("tilewidth", &tw);
	map_node->QueryIntAttribute("tileheight", &th);
	tile_size = Vector2(tw, th);
	
	//Load the tileset
	XMLElement *tileset_node = map_node->FirstChildElement("tileset");
	while(tileset_node)
	{
		//Load the firt gid
		int first_gid;
		tileset_node->QueryIntAttribute("firstgid", &first_gid);
		
		//Load the image
		std::string image_path = std::string(tileset_node->FirstChildElement("image")->Attribute("source"));
		std::stringstream ss;
		ss << "..\\content\\tilesets\\" << image_path.substr(12);
		SDL_Texture *tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
		
		tilesets.push_back(Tileset(tex, first_gid));
		
		tileset_node = tileset_node->NextSiblingElement("tileset");
	}
	
	//Load the layers
	XMLElement *layer_node = map_node->FirstChildElement("layer");
	while(layer_node)
	{
		//Load data
		XMLElement *data_node = layer_node->FirstChildElement("data");
		while(data_node)
		{
			//Load a tile
			XMLElement *tile_node = data_node->FirstChildElement("tile");
			unsigned int tile_count = 0;
			while(tile_node)
			{
				//Get the tile's gid
				int gid = tile_node->IntAttribute("gid");
				//std::cerr << gid << std::endl;
				
				//If it's the 0 tile, don't draw
				if(gid != 0)
				{
					//Get tileset
					Tileset *tls;
					for(int i = 0; i < tilesets.size(); i++)
					{
						//If it's the right one, the next tileset wil be after current gid
						if(tilesets[i].first_gid <= gid)
						{
							tls = &(tilesets[i]);
							break;
						}
					}
					
					//Check if tileset loaded prperly
					if(tls->first_gid != -1)
					{
						//Get the position on the map
						int mx = (tile_count % mw) * tw;
						int my = (tile_count / mw) * th;
						Vector2 map_pos = Vector2(mx, my);
						//std::cerr << "mx" << mx << std::endl;
						//std::cerr << "my" << my << std::endl;
				
						//Get the positon on the tileset
						int tsw, tsh;
						SDL_QueryTexture(tls->image, NULL, NULL, &tsw, &tsh);
						//std::cerr << "tsw" << tsw << std::endl;
						//std::cerr << "tsh" << tsh << std::endl;
						int tsx = (gid % (tsw / tw) - 1) * tw;
						int tsy = (gid / (tsw / tw)) * th;
						//std::cerr << "tsx" << tsx << std::endl;
						//std::cerr << "tsy" << tsy << std::endl;
						Vector2 tileset_pos = Vector2(tsx, tsy);
						
						//Build tile
						tiles.push_back(Tile(tls->image, tile_size, tileset_pos, map_pos));
					}
				}
				
				tile_count++;
				tile_node = tile_node->NextSiblingElement("tile");
			}
			
			data_node = data_node->NextSiblingElement("data");
		}
		
		layer_node = layer_node->NextSiblingElement("layer");
	}
}


void Level::draw(Graphics &graphics)
{
	for(int i = 0; i < tiles.size(); i++)
	{
		tiles[i].draw(graphics);
	}
}

void Level::update(float elapsed_time)
{
	
}