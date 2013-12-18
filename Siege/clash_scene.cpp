#include "clash_scene.h"

/*
All units are dead by default
*/
field::field() {
	for (int i = 0; i < 10; i++) {
		_units[i]._isExisiting = false;
	}
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
		}
	}
}

void field::Kill(unsigned short k) {
	for (unsigned short i = 9; i >= 0 && k > 0; i--) {
		if (_units[i]._isExisiting) {
			k--;
			_units[i]._isExisiting = false;
		}
	}
}

#include "sys.h"
/*
Constructor
*/
clash::clash() {
	_currentMouseOver = sf::Vector2i(0, 0);
	_currentChoosen = sf::Vector2i(-1, -1);
	_font.loadFromFile("font.ttf");
	_turn = PLAYER1;
	_pcTurn = 0;
	_moves = 1;
	_movesPPlayer = 1;
	Window.UpdateStatusbar(toString(_movesPPlayer) + " moves left");
	_turnCounter = 0;
	_check = true;
	_keyPress = 10.f;
}

/*
Destructor
*/
clash::~clash() {

}

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
	if (_turn == AI) NextTurn();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && _keyPress > 1.f) {
		NextTurn();
		_keyPress = 0;
	}

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
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && _currentChoosen.x >= 0 && _keyPress > 0.2f) {
		int i = _currentChoosen.x;
		int j = _currentChoosen.y;
		int x = _currentMouseOver.x;
		int y = _currentMouseOver.y;
		if (((abs(x - i) <= 2 && j == y) || (abs(j - y) <= 2 && i == x)) && _movesPPlayer > 0 && _checkBoard[i][j].CountUnits() > 0) {
			if (_checkBoard[i][j]._entity == _checkBoard[x][y]._entity && _turn == _checkBoard[i][j]._entity)
				MoveUnit(_currentChoosen, _currentMouseOver);
			if (_checkBoard[x][y]._entity == NONE && _turn == _checkBoard[i][j]._entity) {
				_checkBoard[x][y]._entity = _turn;
				_checkBoard[x][y]._field = UNIT;
				MoveUnit(_currentChoosen, _currentMouseOver);
			}
			if (_checkBoard[x][y]._entity > 0 && _checkBoard[x][y]._entity != _checkBoard[i][j]._entity) {
				if (_checkBoard[x][y].CountUnits() > 0 && _checkBoard[i][j].CountUnits() > 0) {
					_checkBoard[x][y].Kill(1);
					_checkBoard[i][j].Kill(1);
				}
				else if (_checkBoard[x][y].CountUnits() == 0 && _checkBoard[i][j].CountUnits() > 0)	{
					if (_checkBoard[x][y]._field == FACTORY) {
						_checkBoard[x][y]._field = UNIT;
						_player[_checkBoard[x][y]._entity - 1] = false;
					}
					_checkBoard[x][y]._entity = _checkBoard[i][j]._entity;
					MoveUnit(_currentChoosen, _currentMouseOver);
				}
			}
		}

		_keyPress = 0;
	}

	// Every			this argument	pc and players gets units
	if (_turn == AI && _pcTurn == 2) {
		for (int i = 0; i < CHECKBOARD; i++) {
			for (int j = 0; j < CHECKBOARD; j++) {
				if (_checkBoard[i][j]._entity == AI) {
					_checkBoard[i][j].TurnAlive(1);
				}
			}
		}

		for (int i = 1; i <= 4; i++) {
			int ww = 0, wh = 0;
			if (i == 1 || i == 2) wh = 1;
			if (i == 1 || i == 3) ww = 1;
			if (i == 3 || i == 4) wh = CHECKBOARD - 2;
			if (i == 2 || i == 4) ww = CHECKBOARD - 2;
			if (_checkBoard[ww][wh]._entity == NONE) {
				_checkBoard[ww][wh]._entity = (ENTITY_TYPE) (i);
				_checkBoard[ww][wh]._field = UNIT;
			}
			if (_checkBoard[ww][wh]._entity == (ENTITY_TYPE) (i) && _player[_checkBoard[ww][wh]._entity-1]) {
				_checkBoard[ww][wh].TurnAlive(2);
			}
		}

		_pcTurn = 0;
	}

	if (_movesPPlayer > 0) _check = false;
	if (_moves != _movesPPlayer) {
		if (_movesPPlayer == 0) Window.UpdateStatusbar("Press ENTER for next turn");
		else if (_turnCounter == 1 && _movesPPlayer == 0 && _check) {
			_moves = 1;
			_check = false;
		}
		else Window.UpdateStatusbar(toString(_movesPPlayer) + " moves left");
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
				_checkBoard[i][j].TurnAlive(1);
			}
			else if (i == 0 && j == CHECKBOARD - 1) {
				_checkBoard[i][j]._entity = PLAYER3;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j].TurnAlive(1);
			}
			else if (i == CHECKBOARD - 1 && j == 0) {
				_checkBoard[i][j]._entity = PLAYER2;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j].TurnAlive(1);
			}
			else if (i == CHECKBOARD - 1 && j == CHECKBOARD - 1) {
				_checkBoard[i][j]._entity = PLAYER4;
				_checkBoard[i][j]._field = FACTORY;
				_checkBoard[i][j].TurnAlive(1);
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
				_checkBoard[i][j].TurnAlive(2 + (i + j) % 2);
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
	else if (_player[_turn - 1] == false) return;
	else if (_turn == 1) msg = "player 1 move";
	else if (_turn == 2) msg = "player 2 move";
	else if (_turn == 3) msg = "player 3 move";
	else if (_turn == 4) msg = "player 4 move";

	if (_moves < 0) _moves = 1;

	if (_turn == AI) {
		if (++_moves > 5) { _moves--; }
	}
	else _turnCounter++;

	_movesPPlayer = _moves;

	Window.UpdateStatusbar(msg);
}

/*
Swaps units between fields
*/
void clash::MoveUnit(sf::Vector2i from, sf::Vector2i to) {
	if (_movesPPlayer > 0 && _checkBoard[from.x][from.y].CountUnits() > 0) {
		_checkBoard[from.x][from.y].Kill(1);
		_checkBoard[to.x][to.y].TurnAlive(1);
		_movesPPlayer--;
	}
}