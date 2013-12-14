#include "clash_scene.h"

/*
Constructor
*/
clash::clash() {

}

/*
Destructor
*/
clash::~clash() {

}

#include "sys.h"

#define GRID_SIZ 3
/*
Renders all players positions every frame
*/
void clash::Render() {
	Window.clear(/*sf::Color(95, 95, 95)*/ sf::Color(64, 64, 64));
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			sf::RectangleShape temp;
			sf::Vector2f size = sf::Vector2f(((WIDTH - GRID_SIZ * 8) / 7), ((HEIGHT - GRID_SIZ * 8) / 7));
			sf::Vector2f position = sf::Vector2f(GRID_SIZ*(i + 1) + size.x * i, GRID_SIZ*(j + 1) + size.y * j);
			sf::Color color;
			if (_checkboardSmall[i][j]._ownerType == "player") {
				color = GetSelectedPlayer(_checkboardSmall[i][j]._ownerName)._color;
			}
			else if (_checkboardSmall[i][j]._ownerType == "ai") {
				if (_checkboardSmall[i][j]._type == "core") color = sf::Color(0xAB, 0x55, 0xFF);
				else color = sf::Color(0x8B, 0xC5, 0xFF);
			}
			else color = sf::Color(150, 150, 150);
			temp.setFillColor(color);
			temp.setPosition(position);
			temp.setSize(size);

			Window.draw(temp);
		} // FOR j
	} // FOR i
}

/*
Updates player moves
*/
void clash::Update(float dt) {

}

/*
Filling the array of fields with starting set
*/
void clash::Load() {
	/* player temporary init */
	// TODO: add creation of your own player
	AddPlayer(0, "p1", sf::Color(0xFF, 0x55, 0x55));
	AddPlayer(1, "p2", sf::Color(0xFF, 0xFF, 0x55));
	AddPlayer(2, "p3", sf::Color(0xAB, 0xFF, 0x55));
	AddPlayer(3, "p4", sf::Color(0x55, 0x55, 0xFF));
	/* initialization of borad */
	field temp;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (i == 0 && j == 0) {
				temp._units = 10;
				temp._type = "factory";
				temp._ownerType = "player";
				temp._ownerName = _players[0]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == BOARD_SIZE - 1 && j == 0) {
				temp._units = 10;
				temp._type = "factory";
				temp._ownerType = "player";
				temp._ownerName = _players[1]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == 0 && j == BOARD_SIZE - 1) {
				temp._units = 10;
				temp._type = "factory";
				temp._ownerType = "player";
				temp._ownerName = _players[2]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == BOARD_SIZE - 1 && j == BOARD_SIZE - 1) {
				temp._units = 10;
				temp._type = "factory";
				temp._ownerType = "player";
				temp._ownerName = _players[3]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if ((i >= 2 && i <= 4) && (j >= 2 && j <= 4) && !(i == 3 && j == 3)) {
				temp._units = 7 + abs(i - 4) + abs(j - 4);
				temp._type = "defender";
				temp._ownerType = "ai";
				temp._ownerName = "ai";
				_checkboardSmall[i][j] = temp;
			}
			else if (i == 3 && j == 3) {
				temp._units = 10;
				temp._type = "core";
				temp._ownerType = "ai";
				temp._ownerName = "ai";
				_checkboardSmall[i][j] = temp;
			}
			else {
				temp._units = 0;
				temp._type = "wasteland";
				temp._ownerType = "none";
				temp._ownerName = "none";
				_checkboardSmall[i][j] = temp;
			}
		} // FOR j
	} // FOR i
}

/*
Clears everything
*/
void clash::Unload() {

}

void clash::DrawUnit(sf::Color _color, sf::Vector2u _field) {
	
}

void clash::AddPlayer(unsigned short int _which, char* _name, sf::Color _color) {
	if (_which < 4 && _which >= 0) {
		_players[_which]._name = _name;
		_players[_which]._color = _color;
		_players[_which]._didHeWon = false;
	}
}

player clash::GetSelectedPlayer(char* _name) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (_players[i]._name == _name) return _players[i];
	}
	return _players[0];
}