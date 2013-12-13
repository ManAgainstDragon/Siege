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
/*
Renders all players positions every frame
*/
void clash::Render() {
	Window.clear(sf::Color(95, 95, 95));
	sf::Vector2u size = Window.getSize();
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			sf::RectangleShape temp;
			sf::Text tempT;
			sf::Vector2f position = sf::Vector2f(sf::Vector2f(3 * (i + 1), 3 * (j + 1)) + sf::Vector2f((576 / 7) * i, (576 / 7) * j));
			sf::Vector2f size = sf::Vector2f((576 / 7), (576 / 7));
			temp.setFillColor(sf::Color(120, 120, 120));
			temp.setPosition(position);
			temp.setSize(size);
			tempT.setPosition(position + sf::Vector2f(5.f, 5.f));
			tempT.setString((char) _checkboardSmall[i][j]._units);
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
	AddPlayer(1, "p1", sf::Color::Red);
	AddPlayer(2, "p2", sf::Color::Yellow);
	AddPlayer(3, "p3", sf::Color::Green);
	AddPlayer(4, "p4", sf::Color::Blue);
	/* initialization of borad */
	field temp;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (i == 0 && j == 0) {
				temp._units = 10;
				temp._type = "factory";
				temp._owner = _players[0]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == BOARD_SIZE - 1 && j == 0) {
				temp._units = 10;
				temp._type = "factory";
				temp._owner = _players[1]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == 0 && j == BOARD_SIZE - 1) {
				temp._units = 10;
				temp._type = "factory";
				temp._owner = _players[2]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == BOARD_SIZE - 1 && j == BOARD_SIZE - 1) {
				temp._units = 10;
				temp._type = "factory";
				temp._owner = _players[3]._name;
				_checkboardSmall[i][j] = temp;
			}
			else if (i == 3 || i == 5 || j == 3 || j == 5) {
				temp._units = 7 + abs(i - 4) + abs(j - 4);
				temp._type = "defender";
				temp._owner = "ai";
				_checkboardSmall[i][j] = temp;
			}
			else if (i == 4 && j == 4) {
				temp._units = 10;
				temp._type = "core";
				temp._owner = "ai";
				_checkboardSmall[i][j] = temp;
			}
			else {
				temp._units = 0;
				temp._type = "wasteland";
				temp._owner = "none";
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
	if (_which - 1 < 4 && _which - 1 >= 0) {
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