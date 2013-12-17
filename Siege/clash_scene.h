#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "stdafx.h"

enum ENTITY_TYPE { NONE = -1, AI = 0, PLAYER1 = 1, PLAYER2, PLAYER3, PLAYER4 };
enum FIELD_TYPE { WASTELAND = -1, FACTORY = 0, UNIT = 1, DEFENDER, CORE };

typedef ENTITY_TYPE TURN;

struct unit {
	bool _isExisiting;
};

struct field {
	ENTITY_TYPE _entity;
	FIELD_TYPE _field;
	unit _units[10];
	//int _hasMove;
	sf::Vector2f _pos;
	sf::Vector2f _siz;
	bool _wasAttacked;
	unsigned short CountUnits();
	void TurnAlive(unsigned short k);
	void Kill(unsigned short k);
	void ResetMove();
	field();
};

#define ColorPlayer1	sf::Color(0x66, 0x66, 0xcc) //Ciemnoniebieski, przechodzacy w szary
#define ColorPlayer2	sf::Color(0x33, 0x99, 0x66) //Zielony, przechodz¹cy w szary
#define ColorPlayer3	sf::Color(0xcc, 0xcc, 0x00) //Piaskowy
#define ColorPlayer4	sf::Color(0xcc, 0x33, 0x33) //Przygaszona czerwieñ
#define ColorCore		sf::Color(0xff, 0x99, 0x33) //Pomarañcz
#define ColorDefender	sf::Color(0xeb, 0xc7, 0x9e) //Ciemniejszy pomarañcz
#define ColorWasteland	sf::Color(170, 170, 170)	//Szary, jasny
#define GRID_SIZE		6
#define CHECKBOARD		9

class clash : public scene_template {
	/* functional */
public:
	clash();
	~clash();

	virtual void Render();
	virtual void Update(float dt);

	virtual void Load();
	virtual void Unload();

	void DrawUnit(field& in, sf::Vector2i pos);
	bool IsMouseOver(field in);
	void DrawMarker(sf::Vector2i pos, sf::Color color);

	void NextTurn();

private:
	field _checkBoard[CHECKBOARD][CHECKBOARD];
	sf::Vector2i _currentMouseOver;
	sf::Vector2i _currentChoosen;
	sf::Font _font;
	TURN _turn;
	float _keyPress;
	unsigned short _pcTurn; //Every third turn gets new soldiers

};