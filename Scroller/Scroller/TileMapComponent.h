#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <string>
#include "Math.h"

class TileMapComponent : SpriteComponent
{
public:

	TileMapComponent(class Actor* owner, int drawOrder = 10);

	void ReadTileMapCSV();

	void Draw(SDL_Renderer* renderer) override;

	void SetTileMapFileName(std::string fileName) { mTileMapFileName = fileName; }

	void SetTileData(std::string fileName);

	void SetTexture(SDL_Texture* texture) { mTexture = texture; }
	SDL_Texture* GetTexture() { return mTexture; }


private:

	std::vector<std::vector<int>> mMapLayer;
	std::string mTileMapFileName;
	std::vector<std::vector<SDL_Texture*>> mMapTextures;

	int mTileWidth;
	int mTileHeight;
	int mTileCount;
	int mColumns;
	std::string mPngFile;

	SDL_Surface* mSurface;
	SDL_Texture* mTexture;

};

