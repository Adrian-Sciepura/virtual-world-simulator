#include "SimulationManager.h"

SimulationManager::SimulationManager() : 
	world{ 15, 15 }, worldMap{ world.getMap() }, worldWidth{ world.getWidth() }, worldHeight{ world.getHeight() }, 
	assetManager{ AssetManager::getAssetManager() }, singleEntitySize{ 16 }, graphicsEngine{ 500, 287 }, colorBuffer{ graphicsEngine.getScreenColorsBuffer() }
{
	assetManager->loadAsset("blank", "./assets/blank.bmp");
	assetManager->loadAsset("sheep", "./assets/sheep.bmp");
	assetManager->loadAsset("wolf", "./assets/wolf.bmp");
	assetManager->loadAsset("turtle", "./assets/turtle.bmp");
	assetManager->loadAsset("fox", "./assets/fox.bmp");
	assetManager->loadAsset("human", "./assets/human.bmp");
	assetManager->loadAsset("antelope", "./assets/antelope.bmp");

	assetManager->loadAsset("grass", "./assets/grass.bmp");
	assetManager->loadAsset("dandelion", "./assets/dandelion.bmp");
	assetManager->loadAsset("guarana", "./assets/guarana.bmp");
	assetManager->loadAsset("nightShade", "./assets/nightShade.bmp");
}

SimulationManager::~SimulationManager()
{
	AssetManager::destroyAssetManager();
}

void SimulationManager::drawBoard()
{
	int screenWidth = graphicsEngine.getScreenWidth();
	int screenHeight = graphicsEngine.getScreenHeight();

	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j < 15 * singleEntitySize + 15 * 3; j++)
		{
			colorBuffer[i * (singleEntitySize + 3) * screenWidth + j] = Color::WHITE;
		}
	}

	for (int i = 0; i < 15 * (singleEntitySize + 3); i++)
	{
		for (int j = 0; j <= 15; j++)
		{
			colorBuffer[i * screenWidth + j * (singleEntitySize + 3)] = Color::WHITE;
		}
	}
}

void SimulationManager::draw()
{
	BMPFile* currentTexture = nullptr;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			currentTexture = worldMap[i][j] != nullptr ? worldMap[i][j]->getTexture() : assetManager->getAsset("blank");
			graphicsEngine.drawBMP(currentTexture, 2 + j * 19, 2 + i * 19);
		}
	}

	graphicsEngine.drawBuffer();
}

void SimulationManager::update()
{
	for (int i = 0; i < worldHeight; i++)
	{
		for (int j = 0; j < worldWidth; j++)
		{
			if (worldMap[i][j] != nullptr)
				entities.push(worldMap[i][j]);
		}
	}

	while (!entities.empty())
	{
		Entity* entity = entities.top();
		if (entity->checkIfAlive())
		{
			entity->update();
			if (!entity->checkIfAlive())
			{
				delete entity;
			}
		}
		else
		{
			delete entity;
		}

		entities.pop();
	}
}

void SimulationManager::start()
{
	drawBoard();

	worldMap[1][1] = new Fox(&world, Point(1, 1));
	worldMap[1][8] = new Fox(&world, Point(1, 8));
	worldMap[1][10] = new Fox(&world, Point(1, 10));
	worldMap[10][10] = new Fox(&world, Point(10, 10));
	worldMap[2][2] = new Wolf(&world, Point(2, 2));
	worldMap[2][3] = new Wolf(&world, Point(2, 3));
	//worldMap[7][18] = new Turtle(&world, Point(7, 18));
	//worldMap[7][19] = new Turtle(&world, Point(7, 19));
	//worldMap[19][19] = new Antelope(&world, Point(19, 19));
	//worldMap[19][18] = new Antelope(&world, Point(19, 18));
	//worldMap[18][18] = new Grass(&world, Point(18, 18));
	//worldMap[17][16] = new Grass(&world, Point(17, 16));
	//worldMap[15][15] = new Dandelion(&world, Point(15, 15));
	worldMap[13][13] = new Guarana(&world, Point(13, 13));
	worldMap[8][8] = new Nightshade(&world, Point(8, 8));
	worldMap[8][9] = new Nightshade(&world, Point(8, 9));
	//worldMap[8][8] = new Human(&world, Point(8, 8));

	char c = NULL;
	while (c != 'q')
	{
		update();
		draw();
		c = getchar();
	}
}