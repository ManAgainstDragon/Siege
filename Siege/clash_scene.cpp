#include "clash_scene.h"

/*
Constructor
*/
clash::clash() {
	_currentMouseOver = sf::Vector2i(0, 0);
	_currentChoosen = sf::Vector2i(-1, -1);
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
	sf::RectangleShape temp;
	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			DrawUnit(_checkBoard[i][j], sf::Vector2i(i, j));
		}
	}
	DrawMarker(_currentMouseOver, sf::Color(47, 47, 79));
	if (_currentChoosen.x >= 0) DrawMarker(_currentChoosen, sf::Color(0xb3, 0x68, 0xb3));
}

/*
Updates player moves
*/
void clash::Update(float dt) {
	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			if (IsMouseOver(_checkBoard[i][j])) {
				_currentMouseOver = sf::Vector2i(i, j);
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		_currentChoosen = _currentMouseOver;
}

/*
Filling the array of fields with starting set
*/
void clash::Load() {
	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			if (i == 0 && j == 0) {
				_checkBoard[i][j]._entity = PLAYER1;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j]._units = 10;
			}
			else if (i == 0 && j == CHECKBOARD - 1) {
				_checkBoard[i][j]._entity = PLAYER3;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j]._units = 10;
			}
			else if (i == CHECKBOARD - 1 && j == 0) {
				_checkBoard[i][j]._entity = PLAYER2;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j]._units = 10;
			}
			else if (i == CHECKBOARD - 1 && j == CHECKBOARD - 1) {
				_checkBoard[i][j]._entity = PLAYER4;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j]._units = 10;
			}
			else if (i == floor((double) CHECKBOARD/2) && j == floor((double) CHECKBOARD/2)) {
				_checkBoard[i][j]._entity = AI;
				_checkBoard[i][j]._field = CORE;
				_checkBoard[i][j]._units = 10;
			}
			else if (((i > floor((double) CHECKBOARD / 2) - 2) && (i < floor((double) CHECKBOARD / 2) + 2)
				&& (j > floor((double) CHECKBOARD / 2) - 2) && (j < floor((double) CHECKBOARD / 2) + 2)) &&
				!(i == floor((double) CHECKBOARD / 2) && j == floor((double) CHECKBOARD / 2))) {
				_checkBoard[i][j]._entity = AI;
				_checkBoard[i][j]._field = DEFENDER;
				_checkBoard[i][j]._units = 6 + (i+j)%2;
			}
			else {
				_checkBoard[i][j]._entity = NONE;
				_checkBoard[i][j]._field = WASTELAND;
				_checkBoard[i][j]._units = 0;
			}
		}
	}
}

/*
Clears everything
*/
void clash::Unload() {

}

/*
Draws unit
*/
void clash::DrawUnit(field& in, sf::Vector2i pos) {
	int i = pos.x;
	int j = pos.y;
	in._siz = sf::Vector2f((WIDTH - (GRID_SIZE*(CHECKBOARD + 1))) / CHECKBOARD, (WIDTH - (GRID_SIZE*(CHECKBOARD + 1))) / CHECKBOARD);
	in._pos = sf::Vector2f((i+1)*GRID_SIZE + i*in._siz.x, (j+1)*GRID_SIZE + j*in._siz.y);
	sf::RectangleShape temp;
	temp.setSize(in._siz);
	temp.setPosition(in._pos);
	if (in._entity == -1) temp.setFillColor(ColorWasteland);
	else if (in._entity == 0) {
		if (in._field == 2)	temp.setFillColor(ColorDefender);
		else temp.setFillColor(ColorCore);
	}
	else {
		if (in._entity == 1) temp.setFillColor(ColorPlayer1);
		else if (in._entity == 2) temp.setFillColor(ColorPlayer2);
		else if (in._entity == 3) temp.setFillColor(ColorPlayer3);
		else if (in._entity == 4) temp.setFillColor(ColorPlayer4);
	}
	Window.draw(temp);
}

/*
Checks if mouse is over unit
*/
bool clash::IsMouseOver(field in) {
	if (sf::Mouse::getPosition(Window).x > in._pos.x && sf::Mouse::getPosition(Window).y > in._pos.y
		&& sf::Mouse::getPosition(Window).x < in._pos.x + in._siz.x && sf::Mouse::getPosition(Window).y < in._pos.y + in._siz.y)
		return true;
	return false;
}

/*
Draws hollow rectangle at choosen unit
*/
void clash::DrawMarker(sf::Vector2i pos, sf::Color color) {
	sf::RectangleShape temp;
	sf::Vector2f _siz = sf::Vector2f(((WIDTH - (GRID_SIZE*(CHECKBOARD + 1))) / CHECKBOARD), ((WIDTH - (GRID_SIZE*(CHECKBOARD + 1))) / CHECKBOARD));
	temp.setSize(_siz);
	temp.setPosition(sf::Vector2f((pos.x + 1)*GRID_SIZE + pos.x*_siz.x, (pos.y + 1)*GRID_SIZE + pos.y*_siz.y));
	temp.setFillColor(sf::Color::Transparent);
	temp.setOutlineColor(color);
	temp.setOutlineThickness(5.0f);
	Window.draw(temp);
}