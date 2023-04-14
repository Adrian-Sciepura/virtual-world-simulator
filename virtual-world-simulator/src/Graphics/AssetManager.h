#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <list>
#include "Asset.h"
#include "../Common/Utility.h"

class AssetManager
{
private:
	static AssetManager* assetManager;
	std::list<Asset*> assets;

	AssetManager();
	~AssetManager();

public:
	static AssetManager* getAssetManager();
	static void destroyAssetManager();

	BMPFile* loadAsset(std::string name, const char* path);
	BMPFile* getAsset(std::string name);

	AssetManager(const AssetManager& assetManager) = delete;
	void operator=(const AssetManager& assetManager) = delete;
};

#endif