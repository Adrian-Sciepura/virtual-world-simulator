#include "SimulationManager.h"

SimulationManager::SimulationManager() : 
	world{ 15, 15 }, worldMap{ world.getMap() }, worldWidth{ world.getWidth() }, worldHeight{ world.getHeight() }, 
	assetManager{ AssetManager::getAssetManager() }, singleEntitySize{ 16 }, graphicsEngine{ 500, 287 }, 
	colorBuffer{ graphicsEngine.getScreenColorsBuffer() }, round{ 0 }, abilityCooldown{ 5 }, gameOver{ false },
	player{ nullptr }
{

	std::fstream logFile = std::fstream("log.txt", std::ios::out);
	logFile.close();

	assetManager->loadAsset("font", "./assets/font.bmp");

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

	//Horizontal
	for (int i = 0; i <= 15; i++)
		for (int j = 0; j < 15 * singleEntitySize + 15 * 3; j++)
			colorBuffer[i * (singleEntitySize + 3) * screenWidth + j] = Color::WHITE;

	//Vertical
	for (int i = 0; i < 15 * (singleEntitySize + 3); i++)
		for (int j = 0; j <= 15; j++)
			colorBuffer[i * screenWidth + j * (singleEntitySize + 3)] = Color::WHITE;
}

void SimulationManager::drawInfo()
{
	drawText("Adrian Sciepura", { 330, 20 });
	drawText(">-----------------<", { 314, 35 });
	drawText("a - ability", { 330, 50 });
	drawText("q - quit", { 330, 60 });
	drawText("n - new game", { 330, 70 });
	drawText("s - save game", { 330, 80 });
	drawText("l - load game", { 330, 90 });
	drawText("m - show logs", { 330, 100 });
	drawText("enter - next round", { 330, 110 });
	drawText("arrows - movement", { 330, 120 });
	drawText(">---------------------<", { 306, 135 });

	updateInfo();
}

void SimulationManager::updateInfo()
{
	std::string rn = "Round: " + std::to_string(this->round) + "   ";
	std::string anim = "Animals: " + std::to_string(Animal::getNumberOfAnimals()) + "   ";
	std::string pl = "Plants: " + std::to_string(Plant::getNumberOfPlants()) + "   ";
	std::string ab = "Ability cooldown: ";

	drawText(rn, {330, 150});
	drawText(anim, { 330, 160 });
	drawText(pl, { 330, 170 });

	if (abilityCooldown > 0)
	{
		ab.append(std::to_string(abilityCooldown) + " ");
		drawText(ab, { 330, 180 }, Color::WHITE);
	}
	else
	{
		ab.append("- ");
		drawText(ab, { 330, 180 }, Color::GREEN);
	}
}

void SimulationManager::drawText(std::string text, const Point& position, Color color)
{
	const int lineSpacing = 2;
	int currentCharASCII = 0;
	int row = 0;
	int column = 0;
	int line = 0;
	int letter = 0;

	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\n')
		{
			line++;
			letter = 0;
			continue;
		}

		currentCharASCII = (int)text[i];
		row = currentCharASCII / 16;
		column = currentCharASCII % 16;

		graphicsEngine.drawBMPChunk(assetManager->getAsset("font"), { position.x + letter * 8, position.y + line * (8 + lineSpacing) }, { column * 8, row * 8 }, { (column + 1) * 8, (row + 1) * 8 });
		letter++;
	}

	if (color != Color::NONE)
		graphicsEngine.recolor(color, position, { position.x + letter * 8, position.y + (line + 1) * 8 });
}

void SimulationManager::draw()
{
	BMPFile* currentTexture = nullptr;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			currentTexture = worldMap[i][j] != nullptr ? worldMap[i][j]->getTexture() : assetManager->getAsset("blank");
			graphicsEngine.drawBMP(currentTexture, { 2 + j * 19, 2 + i * 19 });
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

	std::fstream logFile = std::fstream("log.txt", std::ios::app);
	logFile << "$\n";
	while (!entities.empty())
	{
		Entity* entity = entities.top();
		if (entity->checkIfAlive())
		{
			entity->update(logFile);
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
	logFile.close();
}

void SimulationManager::start()
{
	drawBoard();
	drawInfo();
	player = new Human(&world, Point(5, 10));

	worldMap[5][10] = player;
	worldMap[1][1] = new Fox(&world, Point(1, 1));
	worldMap[1][8] = new Fox(&world, Point(1, 8));
	worldMap[1][10] = new Fox(&world, Point(1, 10));
	worldMap[10][10] = new Fox(&world, Point(10, 10));
	worldMap[2][2] = new Wolf(&world, Point(2, 2));
	worldMap[2][3] = new Wolf(&world, Point(2, 3));
	worldMap[3][3] = new Turtle(&world, Point(3, 3));
	worldMap[4][4] = new Turtle(&world, Point(4, 4));
	worldMap[5][5] = new Antelope(&world, Point(5, 5));
	worldMap[5][6] = new Antelope(&world, Point(5, 6));
	worldMap[7][2] = new Grass(&world, Point(7, 2));
	worldMap[7][3] = new Grass(&world, Point(7, 3));
	worldMap[7][12] = new Dandelion(&world, Point(7, 12));
	worldMap[7][13] = new Dandelion(&world, Point(7, 13));
	worldMap[13][13] = new Guarana(&world, Point(13, 13));
	worldMap[8][8] = new Nightshade(&world, Point(8, 8));
	worldMap[8][9] = new Nightshade(&world, Point(8, 9));
	
	int key = NULL;
	draw();
	while (!gameOver)
	{
		key = _getch();
		if (checkKey(key))
			continue;

		update();
		updateInfo();
		draw();
		round++;
	}
}

bool SimulationManager::checkKey(int keyCode)
{
	switch (keyCode)
	{
		case KeyCodes::A:
		{

			break;
		}
		case KeyCodes::Q:
		{
			gameOver = true;
			break;
		}
		case KeyCodes::N:
		{
			break;
		}
		case KeyCodes::S:
		{
			break;
		}
		case KeyCodes::L:
		{
			break;
		}
		case KeyCodes::M:
		{
			break;
		}
		default:
		{
			if (player->setNewPosition(keyCode))
				return false;

			break;
		}
	}

	return true;
}