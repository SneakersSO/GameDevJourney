#pragma once
#include "TileMapComponent.h"
#include "Actor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Resources/tinyxml2.h"
#include "SDL_image.h"
#include <math.h>

TileMapComponent::TileMapComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mTexture(nullptr)
{

}

void TileMapComponent::ReadTileMapCSV()
{
	if (mTileMapFileName.empty())
	{
		SDL_Log("Tile Map File Name has not been set.");
	}

	else
	{
		std::ifstream tileCSV(mTileMapFileName);
		std::string line;

		while (tileCSV.good())
		{
			std::getline(tileCSV, line);
			std::stringstream ss(line);
			std::vector<int> row;
			std::string data;

			while (getline(ss, data, ','))
			{
				row.emplace_back(stoi(data));
			}
			mMapLayer.emplace_back(row);
			row.clear();
		}

	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{

	int mapIndex = 0;

	for (auto row : mMapLayer)
	{
		for (auto col : row)
		{
			mapIndex++;
			if (col < 0) continue;

			SDL_Rect rSrc;
			rSrc.w = mTileWidth;
			rSrc.h = mTileHeight;

			rSrc.x = mTileWidth * (col % mColumns);
			rSrc.y = mTileHeight * floor(col / mColumns);
 

			SDL_Rect rDest;
			rDest.w = mTileWidth;
			rDest.h = mTileHeight;

			rDest.x = mTileWidth * (mapIndex % row.size());
			rDest.y = mTileHeight * floor(mapIndex  / row.size());

			SDL_RenderCopyEx(
				renderer,
				mTexture,
				&rSrc,
				&rDest,
				-Math::ToDegrees(mOwner->GetRot()),
				nullptr,
				SDL_FLIP_NONE);
		}
	}

}

void TileMapComponent::SetTileData(std::string fileName)
{
	
	tinyxml2::XMLDocument TileSetDoc;
	TileSetDoc.LoadFile(fileName.c_str());

	mTileWidth = static_cast<int>(TileSetDoc.FirstChildElement("tileset")->FindAttribute("tilewidth")->DoubleValue());
	mTileHeight = static_cast<int>(TileSetDoc.FirstChildElement("tileset")->FindAttribute("tileheight")->DoubleValue());
	mTileCount = static_cast<int>(TileSetDoc.FirstChildElement("tileset")->FindAttribute("tilecount")->DoubleValue());
	mColumns = static_cast<int>(TileSetDoc.FirstChildElement("tileset")->FindAttribute("columns")->DoubleValue());
	mPngFile = TileSetDoc.FirstChildElement("tileset")->FirstChildElement("image")->FindAttribute("source")->Value();

	mPngFile = "Assets/" + mPngFile;

}

