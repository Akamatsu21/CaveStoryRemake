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
Level::Level(Graphics &graphics, std::string name):
	map_name(name), map_size(Vector2(0, 0)), tile_size(Vector2(0,0))
{
	loadMap(graphics, map_name);
}

Level::~Level()
{
	
}

std::vector<Rectangle> Level::checkTileCollisions(Rectangle &rect)
{
	std::vector<Rectangle> rects;
	for(unsigned int i = 0; i < collision_rects.size(); i++)
	{
		if(collision_rects[i].collides(rect))
		{
			rects.push_back(collision_rects[i]);
		}
	}
	return rects;
}

Vector2 Level::getPlayerSpawnPoint()
{
	return spawn_point;
}

void Level::loadMap(Graphics &graphics, std::string name)
{
	//Parse the .tmx file
	XMLDocument doc;
	{
		std::stringstream ss;
		ss << "..\\content\\maps\\" << map_name << ".tmx";
		doc.LoadFile(ss.str().c_str());
	}
	
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
				
				//If it's the 0 tile, don't draw
				if(gid != 0)
				{
					//Get tileset
					Tileset *tls;
					for(unsigned int i = 0; i < tilesets.size(); i++)
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
				
						//Get the positon on the tileset
						int tsw, tsh;
						SDL_QueryTexture(tls->image, NULL, NULL, &tsw, &tsh);
						int tsx = (gid % (tsw / tw) - 1) * tw;
						int tsy = (gid / (tsw / tw)) * th;
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
	
	//Parse the collisions
	XMLElement *object_group = map_node->FirstChildElement("objectgroup");
	while(object_group)
	{
		std::string name = std::string(object_group->Attribute("name"));
		if(name == "collisions")
		{
			XMLElement *object_node = object_group->FirstChildElement("object");
			while(object_node)
			{
				float rx, ry, rw, rh;
				rx = object_node->FloatAttribute("x");
				ry = object_node->FloatAttribute("y");
				rw = object_node->FloatAttribute("width");
				rh = object_node->FloatAttribute("height");
				
				collision_rects.push_back(Rectangle(std::ceil(rx) * globals::SPRITE_SCALE, std::ceil(ry) * globals::SPRITE_SCALE,
													std::ceil(rw) * globals::SPRITE_SCALE, std::ceil(rh) * globals::SPRITE_SCALE));
				
				object_node = object_node->NextSiblingElement("object");
			}
		}
		else if(name == "spawn points")
		{
			XMLElement *object_node = object_group->FirstChildElement("object");
			while(object_node)
			{
				float px = object_node->FloatAttribute("x");
				float py = object_node->FloatAttribute("y");
				std::string object_name = std::string(object_node->Attribute("name"));
				
				if(object_name == "player")
				{
					spawn_point = Vector2(std::ceil(px) * globals::SPRITE_SCALE, std::ceil(py) * globals::SPRITE_SCALE);
				}
				
				object_node = object_node->NextSiblingElement("object");
			}
		}
		
		object_group = object_group->NextSiblingElement("objectgroup");
	}
}


void Level::draw(Graphics &graphics)
{
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i].draw(graphics);
	}
}

void Level::update(float elapsed_time)
{
	
}