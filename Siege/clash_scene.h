#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "stdafx.h"

struct field {
	unsigned short int _units;
	char* _ownerType;
	char* _ownerName;
	char* _type;
};

struct player {
	char* _name;
	sf::Color _color;
	bool _didHeWon;
};

class clash : public scene_template {
	/* functional */
public:
	clash();
	~clash();

	virtual void Render();
	virtual void Update(float dt);

	virtual void Load();
	virtual void Unload();

	void DrawUnit(sf::Color _color, sf::Vector2u _field);
	void AddPlayer(unsigned short int _which, char* _name, sf::Color _color);	
	player GetSelectedPlayer(char* _name);

#define BOARD_SIZE 7
private:
	field _checkboardSmall[BOARD_SIZE][BOARD_SIZE];
	player _players[4];

};