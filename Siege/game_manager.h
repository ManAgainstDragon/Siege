#pragma once

#include <string>
#include <vector>

#include "scene_template.h"
#include "clash_scene.h"
#include "won_scene.h"

class game_manager {
	/* functional */
public:
	game_manager();
	virtual ~game_manager();

	virtual void Render();
	virtual void Update(float dt);

	virtual void MoveForward();
	virtual void MoveBackward();
	virtual void MoveInto(std::string _scene);

	virtual scene_template* GetCurrentScene();

	int _winner;

protected:
	std::vector<scene_template*> _scenes;
	std::vector<std::string> _sceneNames;
	unsigned short int _current;

};