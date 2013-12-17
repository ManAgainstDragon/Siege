#include "clash_scene.h"

/*
All units are dead by default
*/
field::field() {
	for (int i = 0; i < 10; i++) {
		_units[i]._isExisiting = false;
	}
	//_hasMove = CountUnits();
	_wasAttacked = false;
}

/*
Returns number of units in the field
*/
unsigned short field::CountUnits() {
	int k = 0;
	for (int i = 0; i < 10; i++) {
		if (_units[i]._isExisiting) k++;
	}
	return k;
}

/*
Increases units by amount
*/
void field::TurnAlive(unsigned short k) {
	for (unsigned short i = 0; i < 10 && k > 0; i++) {
		if (!_units[i]._isExisiting) {
			k--;
			_units[i]._isExisiting = true;
			//_hasMove--;
		}
	}
}

void field::Kill(unsigned short k) {
	for (unsigned short i = 9; i >= 0 && k > 0; i--) {
		if (_units[i]._isExisiting) {
			//if (_hasMove > 0) {
				k--;
				_units[i]._isExisiting = false;
			//}
		}
	}
}

/*
Makes all units movable by turn start
*/
void field::ResetMove() {
	//_hasMove = CountUnits();
}

/*
Constructor
*/
clash::clash() {
	_currentMouseOver = sf::Vector2i(0, 0);
	_currentChoosen = sf::Vector2i(-1, -1);
	_font.loadFromFile("font.ttf");
	_turn = AI;
	NextTurn();
	_pcTurn = 0;
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
	sf::Text _number;
	_number.setFont(_font);
	_number.setCharacterSize(20);
	_number.setColor(sf::Color::Black);
	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			DrawUnit(_checkBoard[i][j], sf::Vector2i(i, j));
			if (_checkBoard[i][j]._field == FACTORY) DrawMarker(sf::Vector2i(i, j), sf::Color::Black);
			if (_checkBoard[i][j]._entity != NONE) {
				if (_checkBoard[i][j]._field == FACTORY) _number.setString("F: " + toString(_checkBoard[i][j].CountUnits()));
				else if (_checkBoard[i][j]._field == CORE) _number.setString("CORE: " + toString(_checkBoard[i][j].CountUnits()));
				else _number.setString(toString(_checkBoard[i][j].CountUnits()));
				_number.setPosition(sf::Vector2f(_checkBoard[i][j]._pos.x + 5, _checkBoard[i][j]._pos.y + 5));
				Window.draw(_number);
			}
		}
	}
	DrawMarker(_currentMouseOver, sf::Color(49, 49, 76));
	if (_currentChoosen.x >= 0) DrawMarker(_currentChoosen, sf::Color(0xb3, 0x68, 0xb3));
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _currentChoosen != _currentMouseOver) DrawMarker(_currentMouseOver, sf::Color(120, 0, 0));
}

/*
Updates player moves
*/
void clash::Update(float dt) {
	_keyPress += dt;
	// Mouse-over type marker
	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			if (IsMouseOver(_checkBoard[i][j])) {
				_currentMouseOver = sf::Vector2i(i, j);
			}
		}
	}
	// Selection tool
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		_currentChoosen = _currentMouseOver;
	}
	// Moving units
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		DrawMarker(_currentMouseOver, sf::Color::Red);
	}
	if (_turn == AI) NextTurn();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && _keyPress > 1.5f) {
		NextTurn();
		_keyPress = 0;
	}
	if (_turn == AI && _pcTurn == 3) {
		for (int i = 0; i < CHECKBOARD; i++) {
			for (int j = 0; j < CHECKBOARD; j++) {
				if (_checkBoard[i][j]._entity == AI) {
					_checkBoard[i][j].TurnAlive(1);
				}
			}
		}
		_pcTurn = 0;
	}
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
				_checkBoard[i][j].TurnAlive(10);
			}
			else if (i == 0 && j == CHECKBOARD - 1) {
				_checkBoard[i][j]._entity = PLAYER3;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j].TurnAlive(10);
			}
			else if (i == CHECKBOARD - 1 && j == 0) {
				_checkBoard[i][j]._entity = PLAYER2;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j].TurnAlive(10);
			}
			else if (i == CHECKBOARD - 1 && j == CHECKBOARD - 1) {
				_checkBoard[i][j]._entity = PLAYER4;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j].TurnAlive(10);
			}
			else if (i == floor((double) CHECKBOARD/2) && j == floor((double) CHECKBOARD/2)) {
				_checkBoard[i][j]._entity = AI;
				_checkBoard[i][j]._field = CORE;
				_checkBoard[i][j].TurnAlive(10);
			}
			else if (((i > floor((double) CHECKBOARD / 2) - 2) && (i < floor((double) CHECKBOARD / 2) + 2)
				&& (j > floor((double) CHECKBOARD / 2) - 2) && (j < floor((double) CHECKBOARD / 2) + 2)) &&
				!(i == floor((double) CHECKBOARD / 2) && j == floor((double) CHECKBOARD / 2))) {
				_checkBoard[i][j]._entity = AI;
				_checkBoard[i][j]._field = DEFENDER;
				_checkBoard[i][j].TurnAlive(4 - (i + j) % 2);
			}
			else {
				_checkBoard[i][j]._entity = NONE;
				_checkBoard[i][j]._field = WASTELAND;
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
	temp.setOutlineThickness(5); // Or thickness = 3, to be decided
	Window.draw(temp);
}

/*
Switches turn to another player
*/
void clash::NextTurn() {
	_turn = (TURN)((_turn + 1) % 5);
	std::string msg;
	if (_turn == AI) {
		msg = "PC makes moves";
		_pcTurn++;
	}
	else if (_turn == 1) msg = "player 1 move";
	else if (_turn == 2) msg = "player 2 move";
	else if (_turn == 3) msg = "player 3 move";
	else if (_turn == 4) msg = "player 4 move";

	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			_checkBoard[i][j].ResetMove();
		}
	}

	Window.UpdateStatusbar(msg);
}