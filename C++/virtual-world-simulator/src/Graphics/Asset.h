#ifndef ASSET_H
#define ASSET_H

#include <string>
#include "BMPFile.h"

struct Asset
{
	std::string name;
	BMPFile* bmpFile;

	Asset(std::string name, BMPFile* bmpFile);
	~Asset();
};

#endif