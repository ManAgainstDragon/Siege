#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "stdafx.h"

class sys : public sf::RenderWindow {
	/* singleton */
public:
	static sys& GetInstance();

private:
	sys();
	~sys();

	static sys* _instance;

	/* functional */
public:
	void Init(std::string _name);

	void Start();
	void Stop();
	void Render();
	void Update(float dt);

	void SetGameManager(game_manager* _instance);

private:
	game_manager* _gmi;

};

#define Window sys::GetInstance()