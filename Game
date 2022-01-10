///HEADERS
#include "Game.h"

/*----------------------------------------------------------------------------------------*/
//CONSTRUCTORS / DESTRUCTORS//
/*----------------------------------------------------------------------------------------*/

 ///CONSTRUCTOR
Game::Game()
{
	initWindow();
	initTextures();
	initAudio();
	initFont();
	initText();
	mainMenu();
	initLives();
	initPlayer();
}

///DECONSTRUCTOR
Game::~Game()
{
	//DELETING//

	//Delete window
	delete window;

	//Delete Player
	delete player;

	//Delete enemies
	for (auto* i : enemies)
	{
		delete i;
	}

	//Delete special enemies
	for (auto* i : specialEnemies)
	{
		delete i;
	}

	//Delete Textures
	for (auto &i : textures)
	{
		delete i.second;
	}

	//Delete Textures
	for (auto &i : audio)
	{
		delete i.second;
	}

	//Delete Bullets
	for (auto *i : bullets)
	{
		delete i;
	}

	//Delete EnemyBullets
	for (auto *i : enemyBullets)
	{
		delete i;
	}

	//Delete Blockades
	for (auto *i : blockades)
	{
		delete i;
	}

	//Delete Text
	for (auto *i : texts)
	{
		delete i;
	}
}

/*----------------------------------------------------------------------------------------*/
//PRIVATE FUNCTIONS//
/*----------------------------------------------------------------------------------------*/

///INITIATE WINDOW
void Game::initWindow()
{
	videoMode.height = 1000;
	videoMode.width = 800;

	this->window = new sf::RenderWindow(videoMode, "Space Invaders");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(false);

	rectangle.setSize(sf::Vector2f(window->getSize().x, 5));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(5);
	rectangle.setPosition(0, window->getSize().y - 70);

	//Start Clocks
	enemyShootClock.restart();
	enemySpawnClock.restart();
	enemySpawnSpecialClock.restart();
}

///INITIATE TEXTURE
void Game::initTextures()
{
	//SHIP TEXTURE//
	this->textures["SHIP"] = new sf::Texture();
	this->textures["SHIP"]->loadFromFile("images/Ship-SpriteSheet.png");

	//BULLET TEXTURE//
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("images/Bullet-SpriteSheet.png");

	//ENEMY TEXTURE//

	//Enemy A
	this->textures["ENEMY"] = new sf::Texture();
	this->textures["ENEMY"]->loadFromFile("images/Invaders-SpriteSheet.png");

	//BLOCKADE//

	//Full
	this->textures["BLOCKADEFULL"] = new sf::Texture();
	this->textures["BLOCKADEFULL"]->loadFromFile("images/Blockade.png");

	//Damaged 1
	this->textures["BLOCKADE1"] = new sf::Texture();
	this->textures["BLOCKADE1"]->loadFromFile("images/Blockade_Damaged1.png");

	//Damaged 2
	this->textures["BLOCKADE2"] = new sf::Texture();
	this->textures["BLOCKADE2"]->loadFromFile("images/Blockade_Damaged2.png");

	//Damaged 3
	this->textures["BLOCKADE3"] = new sf::Texture();
	this->textures["BLOCKADE3"]->loadFromFile("images/Blockade_Damaged3.png");

	//Damaged 4
	this->textures["BLOCKADE4"] = new sf::Texture();
	this->textures["BLOCKADE4"]->loadFromFile("images/Blockade_Damaged4.png");
}

///INITIATE AUDIO
void Game::initAudio()
{
	//Shooting
	this->audio["SHOOT"] = new sf::SoundBuffer();
	this->audio["SHOOT"]->loadFromFile("audio/shoot.wav");

	shootSFX.setBuffer(*audio["SHOOT"]);

	//Enemy Death
	this->audio["ENEMYDEATH"] = new sf::SoundBuffer();
	this->audio["ENEMYDEATH"]->loadFromFile("audio/invaderkilled.wav");

	enemyDeathSFX.setBuffer(*audio["ENEMYDEATH"]);

	//Player Death
	this->audio["PLAYERDEATH"] = new sf::SoundBuffer();
	this->audio["PLAYERDEATH"]->loadFromFile("audio/explosion.wav");

	playerDeathSFX.setBuffer(*audio["PLAYERDEATH"]);

	//Enemy Movement
	this->audio["ENEMYMOVEMENT"] = new sf::SoundBuffer();
	this->audio["ENEMYMOVEMENT"]->loadFromFile("audio/fastinvader.wav");

	enemyMovementSFX.setBuffer(*audio["ENEMYMOVEMENT"]);

	//SpecialEnemy Movement
	this->audio["SPECIALENEMYMOVEMENT"] = new sf::SoundBuffer();
	this->audio["SPECIALENEMYMOVEMENT"]->loadFromFile("audio/ufo_highpitch.wav");

	specialEnemySFX.setBuffer(*audio["SPECIALENEMYMOVEMENT"]);

	//Background Music
	if (!backgroundMusic.openFromFile("audio/spaceinvadersmusic.wav"))
	{
		std::cout << "Could not load music file" << std::endl;
	}

}

///INITIATE FONT
void Game::initFont()
{
	//Load Font
	if (!font.loadFromFile("fonts/unifont.ttf"))
	{
		std::cout << "Error loading unifont.ttf fonts" << std::endl;
	}

	//Set Font
	score.setFont(font);
	highScoreText.setFont(font);
	lives.setFont(font);
	menu.setFont(font);
}

///INITIATE PLAYER
void Game::initPlayer()
{
	//Spawn Player
	player = new Player(textures["SHIP"]);

	//set players original position to variable
	playerOriginalPos = sf::Vector2f((window->getSize().x - player->getGlobalBounds().width) / 2, (window->getSize().y - player->getGlobalBounds().height) - 100);

	//set Position
	player->setPos(playerOriginalPos);
}

///INITIATE ENEMIES
void Game::initEnemies()
{
	unsigned int row = 0;
	unsigned int column = 0;

	//Algorithm to spawn enemies in one at a time like in the original space invaders!
	while (!enemiesSpawned)
	{
		render();

		if (row == 5)
		{
			nextWave = false;
			enemiesSpawned = true;
		}

		if (enemySpawnClock.getElapsedTime().asMicroseconds() >= 0.2f)
		{
			if (column == 11)
			{
				row++;
				column = 0;
			}

			//Spawn Enemies - Textures, position and enemy type
			if (row == 0)
			{
				//Spawn EnemyC
				this->enemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(75 + column * 60, (window->getSize().y / 3) - 100 + row * 50), EnemyTypes::EnemyC));
				column++;
				enemySpawnClock.restart();
			}
			else if (row >= 1 && row <= 2)
			{
				//Spawn EnemyB
				this->enemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(75 + column * 60, (window->getSize().y / 3) - 100 + row * 50), EnemyTypes::EnemyB));
				column++;
				enemySpawnClock.restart();
			}
			else if (row >= 3 && row <= 4)
			{
				//Spawn EnemyA
				this->enemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(75 + column * 60, (window->getSize().y / 3) - 100 + row * 50), EnemyTypes::EnemyA));
				column++;
				enemySpawnClock.restart();
			}
		}
	}
}

///INITIATE BLOCKADE
void Game::initBlockade()
{
	for (int i = 0; i < 4; i++)
	{
		this->blockades.push_back(new Blockade(textures["BLOCKADEFULL"], textures["BLOCKADE1"], textures["BLOCKADE2"], textures["BLOCKADE3"], textures["BLOCKADE4"], sf::Vector2f(50 + i * 200, (window->getSize().y / 2) + 200)));
	}
}

///INITIATE LIVES
void Game::initLives()
{
	//setting character size, colour and position to bottom left corner
	lives.setCharacterSize(50);
	lives.setFillColor(sf::Color::White);
	lives.setPosition(30, window->getSize().y - 70);
}

///RESET VARIABLES
void Game::resetVariables()
{
	points = 0;
	waves = 1;

	player->playerLives = player->maxPlayerLives;

	enemyShootCounter = 0;

	spawnTimerUFO = 0;
}

void Game::mainMenu()
{
	mainMenuState = true;
	backgroundMusic.play();

	menu.setCharacterSize(60);
	menu.setFillColor(sf::Color::White);

	menu.setPosition(20, window->getSize().y / 6);

	this->imageEnemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(window->getSize().x / 4, window->getSize().y / 2 - 50), EnemyTypes::EnemyD));

	this->imageEnemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(window->getSize().x / 4, window->getSize().y / 2 + 10), EnemyTypes::EnemyC));

	this->imageEnemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(window->getSize().x / 4, window->getSize().y / 2 + 75), EnemyTypes::EnemyB));

	this->imageEnemies.push_back(new Enemy(textures["ENEMY"], sf::Vector2f(window->getSize().x / 4, window->getSize().y / 2 + 140), EnemyTypes::EnemyA));
}

///INITIATE TEXT
void Game::initText()
{
	this->texts.push_back(new Text(window->getSize().x - 150, window->getSize().y - 50, 50, "CREDIT 01", sf::Color(255, 255, 255)));
}

/*----------------------------------------------------------------------------------------*/
//ACCESSORS//
/*----------------------------------------------------------------------------------------*/

const bool Game::getWindowIsOpen() const
{
	return window->isOpen();
}

/*----------------------------------------------------------------------------------------*/
//PUBLIC FUNCTIONS//
/*----------------------------------------------------------------------------------------*/

///POLLEVENTS
void Game::pollEvents()
{
	//Event polling
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyPressed:

			//Close window
			if (ev.key.code == sf::Keyboard::Escape)
			{
				window->close();
				break;
			}
		default:
			break;
		}
	}
}

///KEYBOARD INPUT
void Game::updateInput()
{
	//Start Game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !isGameOver)
	{
		mainMenuState = false;
	}

	//Restart Game
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && isGameOver)
	{
		resetVariables();
		isGameOver = false;
	}

	//Player Controls
	if (!mainMenuState && !playerDead)
	{
		//Move Player Left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !nextWave && !isGameOver)
		{
			player->move(-1.f, 0.f);
		}

		//Move Player Right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !nextWave && !isGameOver)
		{
			player->move(1.f, 0.f);
		}

		//Shoot - texture, position, speed, direction
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player->canShoot() && !nextWave && !isGameOver)
		{
			//play shoot audio
			shootSFX.play();

			//push back bullet
			this->bullets.push_back(
				new Bullet(this->textures["BULLET"],
					sf::Vector2f(player->getPos().x + player->getGlobalBounds().width / 2,
						player->getPos().y), 4.f, sf::Vector2f(0.f, -1.0f)));
		}
	}
}

///UPDATE PLAYER
void Game::updatePlayer()
{
	player->updatePlayer();

	if (player->playerLives < 0)
	{
		gameOver();
	}
}

///UPDATE TEXT
void Game::updateText()
{
	//update mainmenu text
	sf::String menuText = "\t\t   PLAY\n\t  SPACE INVADERS\n\n  *SCORE ADVANCE TABLE*\n\t\t = ? MYSTERY\n\t\t = 30 POINTS\n\t\t = 20 POINTS\n\t\t = 10 POINTS\n\n  PRESS <ENTER> TO PLAY";

	menu.setString(menuText);


	//Update Score text
	std::ostringstream ssScore;

	if (points < 10)
	{
		ssScore << "SCORE<1>\n  000" << points;
	}
	else if (points < 100)
	{
		ssScore << "SCORE<1>\n  00" << points;
	}
	else if (points < 1000)
	{
		ssScore << "SCORE<1>\n  0" << points;
	}
	else if (points < 10000)
	{
		ssScore << "SCORE<1>\n  " << points;
	}

	score.setCharacterSize(50);
	score.setFillColor(sf::Color::White);
	score.setPosition(30, 10);
	score.setString(ssScore.str());

	//Update HighScore text
	std::ostringstream ssHighScore;

	if (highScore < 10)
	{
		ssHighScore << "HI-SCORE\n  000" << highScore;
	}
	else if (highScore < 100)
	{
		ssHighScore << "HI-SCORE\n  00" << highScore;
	}
	else if (highScore < 1000)
	{
		ssHighScore << "HI-SCORE\n  0" << highScore;
	}
	else if (highScore < 10000)
	{
		ssHighScore << "HI-SCORE\n  " << highScore;
	}

	highScoreText.setCharacterSize(50);
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setPosition(window->getSize().x / 4 + 110, 10);
	highScoreText.setString(ssHighScore.str());

	//Update HighScore File
	std::ifstream readFile;
	readFile.open("HighScore.txt");

	if (readFile.is_open())
	{
		while (!readFile.eof())
		{
			readFile >> highScore;
		}

		readFile.close();

		std::ofstream writeFile("HighScore.txt");

		if (writeFile.is_open())
		{
			if (points > highScore)
			{
				highScore = points;
			}

			writeFile << highScore;
		}

		writeFile.close();
	}


	//Update Lives text
	std::ostringstream ssLives;
	ssLives << player->playerLives;

	if (!mainMenuState || !isGameOver)
	{
		lives.setString(ssLives.str());
	}
}

///UPDATE WAVE
void Game::updateWave()
{
	//increase wave
	nextWave = true;
	waves++;

	//delete stuff
	deleteAll();

	//Spawn in blockades
	initBlockade();

	//place player back in centre
	player->setPos(playerOriginalPos);

	//Spawn in enemies
	initEnemies();
}

///GAME OVER
void Game::gameOver()
{
	isGameOver = true;
	paused = true;

	//delete stuff
	deleteAll();

	//reset Spawn in enemies
	enemiesSpawned = false;

	this->texts.push_back(new Text(window->getSize().x / 4 + 30, window->getSize().y / 2 - 100, 70, "\t\t  GAME OVER", sf::Color(255, 0, 0)));

	this->texts.push_back(new Text(window->getSize().x / 2, window->getSize().y / 2 - 20, 60, "PRESS <ENTER> TO CONTINUE", sf::Color(255, 255, 255)));
}

/*----------------------------------------------------------------------------------------*/

///UPDATE
void Game::update()
{
	pollEvents();
	updateInput();
	updateText();

	if (!mainMenuState)
	{
		backgroundMusic.stop();
		if (!playerDead)
		{
			updateEnemies();
			updateBlockade();
		}
		updateBullets();
		updatePlayer();
		updateCollision();
	}
}

///RENDER STUFF
void Game::render()
{
	//clear window
	window->clear();

	if (!mainMenuState)
	{
		if (!isGameOver)
		{
			//Player render
			player->renderTo(window);

			//Enemy render
			for (auto *enemy : this->enemies)
			{
				enemy->renderTo(window);
			}

			//Special Enemy render
			for (auto *enemy : this->specialEnemies)
			{
				enemy->renderTo(window);
			}

			// specialEnemy->renderTo(window);

			 //Player bullet render
			for (auto *bullet : this->bullets)
			{
				bullet->renderTo(window);
			}

			//Enemy bullet render
			for (auto *bullet : this->enemyBullets)
			{
				bullet->renderTo(window);
			}

			//Blockade render
			for (auto *blockade : this->blockades)
			{
				blockade->renderTo(window);
			}

			//lives render
			window->draw(lives);
		}
		else
		{
			//Text render
			for (auto *text : this->texts)
			{
				text->renderTo(window);
			}
		}

		//HUD Render
		window->draw(rectangle);
	}
	else
	{
		for (auto *enemy : this->imageEnemies)
		{
			enemy->renderTo(window);
		}

		//Score Render
		window->draw(menu);
	}

	//Score Render
	window->draw(score);

	//HighScore Render
	window->draw(highScoreText);

	//Display Window
	window->display();
}
