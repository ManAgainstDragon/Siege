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
	sf::RectangleShape temp;
	for (int i = 0; i < CHECKBOARD; i++) {
		for (int j = 0; j < CHECKBOARD; j++) {
			DrawUnit(_checkBoard[i][j], sf::Vector2i(i, j));
		}
	}
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
void clash::DrawUnit(field in, sf::Vector2i pos) {
	int i = pos.x;
	int j = pos.y;
	sf::Vector2f size = sf::Vector2f((WIDTH - (GRID_SIZE*(CHECKBOARD + 1))) / CHECKBOARD, (WIDTH - (GRID_SIZE*(CHECKBOARD + 1))) / CHECKBOARD);
	sf::Vector2f position = sf::Vector2f((i+1)*GRID_SIZE + i*size.x, (j+1)*GRID_SIZE + j*size.y);
	sf::RectangleShape temp;
	temp.setSize(size);
	temp.setPosition(position);
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