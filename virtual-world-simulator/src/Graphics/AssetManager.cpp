#include "AssetManager.h"

AssetManager* AssetManager::assetManager = nullptr;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
    std::list<Asset*>::iterator it;
    for (it = this->assets.begin(); it != this->assets.end(); it++)
    {
        delete (*it);
    }
    //this->assets.clear();
}

AssetManager* AssetManager::getAssetManager()
{
    if(assetManager == nullptr)
		assetManager = new AssetManager();
    
    return assetManager;
}

void AssetManager::destroyAssetManager()
{
    if(assetManager != nullptr)
		delete assetManager;
	
	assetManager = nullptr;
}

BMPFile* AssetManager::loadAsset(std::string name, const char* path)
{
    this->assets.push_back(new Asset(name, Utility::readBMP(path)));
    return nullptr;
}

BMPFile* AssetManager::getAsset(std::string name)
{
    std::list<Asset*>::iterator it;
    for (it = this->assets.begin(); it != this->assets.end(); it++)
    {
		if((*it)->name == name)
            return (*it)->bmpFile;
	}

    return nullptr;
}
