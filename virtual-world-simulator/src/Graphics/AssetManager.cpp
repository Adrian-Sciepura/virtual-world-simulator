#include "AssetManager.h"

std::mutex AssetManager::mutex_;
AssetManager* AssetManager::assetManager_ = nullptr;

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
    this->assets.clear();
}

AssetManager* AssetManager::getAssetManager()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if(assetManager_ == nullptr)
		assetManager_ = new AssetManager();
    
    return assetManager_;
}

void AssetManager::destroyAssetManager()
{
    if(assetManager_ != nullptr)
		delete assetManager_;
	
	assetManager_ = nullptr;
}

BMPFile* AssetManager::loadAsset(std::string name, const char* path)
{
    this->assets.push_back(new Asset(name, Utility::readBMP(path)));
    return assets.back()->bmpFile;
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
