#include "Asset.h"

Asset::Asset(std::string name, BMPFile* bmpFile) :
	name{ name }, bmpFile{ bmpFile }
{
}

Asset::~Asset()
{
	delete this->bmpFile;
}
