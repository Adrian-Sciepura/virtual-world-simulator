#include "SimulationManager.h"

SimulationManager::SimulationManager() : 
	world{ nullptr }, assetManager{ AssetManager::getAssetManager() }, singleEntitySize{ 16 }, graphicsEngine{ 500, 287 }, 
	colorBuffer{ graphicsEngine.getScreenColorsBuffer() }, round{ 0 }, abilityCooldown{ 5 }, player{ nullptr }, availableMenuOptions{ 0 }, quit{ false }
{
	font = assetManager->loadAsset("font", "./assets/font.bmp");

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

	menuMode(true);
}

SimulationManager::~SimulationManager()
{
	delete world;
	AssetManager::destroyAssetManager();
}

void SimulationManager::drawBoard()
{
	int screenWidth = graphicsEngine.getScreenWidth();
	int screenHeight = graphicsEngine.getScreenHeight();

	//Horizontal
	for (int i = 0; i <= renderMapHeight; i++)
		for (int j = 0; j < renderMapWidth * (singleEntitySize + 3); j++)
			colorBuffer[i * (singleEntitySize + 3) * screenWidth + j] = Color::WHITE;

	//Vertical
	for (int i = 0; i < renderMapHeight * (singleEntitySize + 3); i++)
		for (int j = 0; j <= renderMapWidth; j++)
			colorBuffer[i * screenWidth + j * (singleEntitySize + 3)] = Color::WHITE;
}

void SimulationManager::drawInfo()
{
	graphicsEngine.drawText(font, "Adrian Sciepura", { 330, 20 });
	graphicsEngine.drawText(font, ">-----------------<", { 314, 35 });
	graphicsEngine.drawText(font, "a - ability", { 330, 50 });
	graphicsEngine.drawText(font, "q - quit", { 330, 60 });
	graphicsEngine.drawText(font, "l - open logs", { 330, 70 });
	graphicsEngine.drawText(font, "m - open menu", { 330, 80 });
	graphicsEngine.drawText(font, "arrows - movement", { 330, 90 });
	graphicsEngine.drawText(font, ">---------------------<", { 306, 105 });

	updateInfo();
}

void SimulationManager::updateInfo()
{
	std::string rn = "Round: " + std::to_string(this->round) + "   ";
	std::string anim = "Animals: " + std::to_string(Animal::getNumberOfAnimals()) + "   ";
	std::string pl = "Plants: " + std::to_string(Plant::getNumberOfPlants()) + "   ";
	std::string ab = "Ability cooldown: ";
	std::string x = "X: " + (world->checkIfGameOver() ? " -- " : std::to_string(player->getPosition().y) + "   ");
	std::string y = "Y: " + (world->checkIfGameOver() ? " -- " : std::to_string(player->getPosition().x) + "   ");

	graphicsEngine.drawText(font, rn, {330, 120});
	graphicsEngine.drawText(font, anim, { 330, 130 });
	graphicsEngine.drawText(font, pl, { 330, 140 });

	if (abilityCooldown > 0)
	{
		ab.append(std::to_string(abilityCooldown) + " ");
		graphicsEngine.drawText(font, ab, { 330, 150 }, Color::WHITE);
	}
	else
	{
		ab.append("- ");
		graphicsEngine.drawText(font, ab, { 330, 150 }, Color::GREEN);
	}

	graphicsEngine.drawText(font, x, { 330, 160 });
	graphicsEngine.drawText(font, y, { 330, 170 });
}

void SimulationManager::draw()
{
	BMPFile* currentTexture = nullptr;
	int x = 0;
	int y = 0;
	for (int i = 0; i < renderMapHeight; i++)
	{
		for (int j = 0; j < renderMapWidth; j++)
		{
			y = i + horizontalMapShift;
			x = j + verticalMapShift;
			currentTexture = worldMap[y][x] != nullptr ? worldMap[y][x]->getTexture() : assetManager->getAsset("blank");
			graphicsEngine.drawBMP(currentTexture, { 2 + j * 19, 2 + i * 19 });
		}
	}
	
	if (world->checkIfGameOver())
		gameOver();

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
	graphicsEngine.clearBuffer();
	drawBoard();
	drawInfo();

	int key = NULL;
	draw();
	while (!quit)
	{
		key = _getch();
		if (checkKey(key))
			continue;

		if (!world->checkIfGameOver())
		{
			update();
			round++;
			updateInfo();
		}

		draw();
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
			quit = true;
			break;
		}
		case KeyCodes::M:
		{
			menuMode(false);
			drawBoard();
			drawInfo();
			draw();
			break;
		}
		case KeyCodes::L:
		{
			logMode();
			drawBoard();
			drawInfo();
			draw();
			break;
		}
		default:
		{
			if(world->checkIfGameOver())
				return true;

			if (player->setNewPosition(keyCode))
			{
				Point newPosition = player->getNewPosition();
				if (newPosition.x > 14 + horizontalMapShift)
					horizontalMapShift++;
				else if (newPosition.x < horizontalMapShift)
					horizontalMapShift--;
				else if (newPosition.y > 14 + verticalMapShift)
					verticalMapShift++;
				else if (newPosition.y < verticalMapShift)
					verticalMapShift--;

				return false;
			}

			break;
		}
	}

	graphicsEngine.drawBuffer();
	return true;
}

void SimulationManager::placeEntities()
{
	int freeSpace = worldWidth * worldHeight;
	char types[] = { 'A', 'F', 'S', 'T', 'W', 'G', 'D', 'N', 'U' };

	int x = 0;
	int y = 0;
	int type = 0;
	int howMany = freeSpace / 3;
	for (int i = 0; i < howMany; i++)
	{
		y = rand() % worldHeight;
		x = rand() % worldWidth;
		type = rand() % 9;

		if (worldMap[y][x] == nullptr)
		{
			worldMap[y][x] = getEntityFromSymbol(world, {y, x}, types[type]);
		}
	}

}

void SimulationManager::gameOver()
{
	availableMenuOptions = 1;
	std::string line = "----------";
	std::string message = "Game over!";

	int pos = (15 * (singleEntitySize + 3) - message.length() * 8) / 2;

	graphicsEngine.drawText(font, line, { pos, 100 }, Color::DARKRED);
	graphicsEngine.drawText(font, message, { pos, 115 }, Color::RED);
	graphicsEngine.drawText(font, line, { pos, 130 }, Color::DARKRED);
}

void SimulationManager::logMode()
{
	graphicsEngine.clearBuffer();
	std::fstream logFile = std::fstream("log.txt", std::ios::in);
	const int maxLines = (graphicsEngine.getScreenHeight() - 15) / 10;
	int currentCursorPosition = 0;
	int howManyLinesToSkip = 0;
	int numberOfLines = 0;

	std::vector<std::streampos> sections;
	std::string line;


	while (getline(logFile, line))
		if(line == "$")
			sections.push_back(logFile.tellg());

	logFile.clear();

	int key = NULL;
	bool refresh = true;
	while (key != KeyCodes::L)
	{
		switch (key)
		{
			case KeyCodes::LEFT:
			{
				if (currentCursorPosition > 0)
				{
					howManyLinesToSkip = 0;
					currentCursorPosition--;
					refresh = true;
				}
				break;
			}
			case KeyCodes::RIGHT:
			{
				if(currentCursorPosition < round - 1)
				{
					howManyLinesToSkip = 0;
					currentCursorPosition++;
					refresh = true;
				}
				break;
			}
			case KeyCodes::DOWN:
			{
				if (numberOfLines - howManyLinesToSkip > maxLines)
				{
					howManyLinesToSkip++;
					refresh = true;
				}
				break;
			}
			case KeyCodes::UP:
			{
				if (howManyLinesToSkip > 0)
				{
					howManyLinesToSkip--;
					refresh = true;
				}
				break;
			}
		}
	
		if (refresh)
		{
			refresh = false;
			graphicsEngine.clearBuffer();
			drawLogMenu(currentCursorPosition);
			logFile.seekg(sections[currentCursorPosition]);
			
			int lineNumber = 0;
			int skipped = 0;
			while (getline(logFile, line))
			{
				if (line == "$")
					break;

				if(skipped > howManyLinesToSkip)
					graphicsEngine.drawText(font, line, { 5, 8 + (lineNumber - howManyLinesToSkip) * 10 });
				else
					skipped++;

				lineNumber++;
			}
			numberOfLines = lineNumber;

			if (currentCursorPosition == round - 1)
				logFile.clear();

			graphicsEngine.drawBuffer();
		}

		key = _getch();
	}

	logFile.close();
	graphicsEngine.clearBuffer();
}

void SimulationManager::drawLogMenu(int cursorPosition)
{
	int skip = 12 * graphicsEngine.getScreenWidth();
	for (int i = 0; i < graphicsEngine.getScreenWidth()*2; i++)
		colorBuffer[skip + i] = Color::BLUE;

	int number = cursorPosition;
	std::string numAsString = std::to_string(number);
	graphicsEngine.drawText(font, numAsString, { 4, 1 }, Color::RED);
	int length = 4 + numAsString.size() * 8 + 4;
	number++;

	

	while (length-4 < graphicsEngine.getScreenWidth())
	{
		numAsString = std::to_string(number);
		graphicsEngine.drawText(font, numAsString, { length, 1 });
		length += numAsString.size() * 8;
		length += 4;
		number++;
	}
}

void SimulationManager::menuMode(bool firstGame)
{
	graphicsEngine.clearBuffer();

	bool (SimulationManager:: * functions[])() = { &SimulationManager::newGame, &SimulationManager::loadGame, &SimulationManager::saveGame };
	int options = firstGame ? 1 : 2;
	Menu menu(&graphicsEngine, "Virtual world simulator");
	menu.addItem({ MenuItem::ItemType::TEXT, "New Game" });
	menu.addItem({ MenuItem::ItemType::TEXT, "Load Game" });
	menu.addItem({ MenuItem::ItemType::TEXT, "Save Game" });
	bool success = false;

	while (!success)
	{
		std::vector<std::string> result = menu.open(options);
		success = (this->*functions[stoi(result[0])])();
	}

	graphicsEngine.clearBuffer();
}

bool SimulationManager::newGame()
{
	if(world != nullptr)
		delete world;

	Menu dimmensionsMenu(&graphicsEngine, "Enter world dimensions");
	dimmensionsMenu.addItem({ MenuItem::ItemType::ENTRY, "  Width  " });
	dimmensionsMenu.addItem({ MenuItem::ItemType::ENTRY, "  Height  " });
	dimmensionsMenu.addItem({ MenuItem::ItemType::TEXT, "  Accept  " });

	bool correctData = false;
	int width = 0;
	int height = 0;
	while (!correctData)
	{
		std::vector<std::string> result = dimmensionsMenu.open(2);
		try
		{
			width = stoi(result[1]);
			height = stoi(result[2]);
			if(height > 5 && width > 5)
				correctData = true;
		}
		catch (std::invalid_argument)
		{

		}
	}

	world = new World(width, height);
	worldMap = world->getMap();
	worldWidth = width;
	worldHeight = height;
	renderMapWidth = (worldWidth < 15 ? worldWidth : 15);
	renderMapHeight = (worldHeight < 15 ? worldHeight : 15);
	round = 0;
	verticalMapShift = 0;
	horizontalMapShift = 0;
	availableMenuOptions = 2;

	player = new Human(world, { 2, 2 });
	worldMap[2][2] = player;
	placeEntities();
	
	std::fstream logFile = std::fstream("log.txt", std::ios::out);
	logFile.close();

	return true;
}

bool SimulationManager::saveGame()
{
	std::fstream saveFile = std::fstream("save.txt", std::ios::out);
	
	saveFile << worldWidth << ' ' << worldHeight << '\n';
	Entity* curr = nullptr;
	for(int i = 0; i < worldHeight; i++)
		for (int j = 0; j < worldWidth; j++)
			if (worldMap[i][j] != nullptr)
			{
				curr = worldMap[i][j];
				saveFile << curr->getSymbol() << ' ' << i << ' ' << j << ' ' << worldMap[i][j]->getLifespan() << ' ' << worldMap[i][j]->getStrength() << '\n';
			}

	saveFile.close();


	return true;
}

bool SimulationManager::loadGame()
{
	return false;
}

Entity* SimulationManager::getEntityFromSymbol(World* world, Point position, char symbol, int lifespan, int strength)
{
	switch (symbol)
	{
		case 'H': return new Human(world, position);
		case 'A': return new Antelope(world, position);
		case 'F': return new Fox(world, position);
		case 'S': return new Sheep(world, position);
		case 'T': return new Turtle(world, position);
		case 'W': return new Wolf(world, position);
		case 'G': return new Grass(world, position);
		case 'D': return new Dandelion(world, position);
		case 'N': return new Nightshade(world, position);
		case 'U': return new Guarana(world, position);
	}

	return nullptr;
}