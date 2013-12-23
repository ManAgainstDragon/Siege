#pragma once

#include "scene_template.h"

class won : public scene_template {
	/* functional */
public:
	won();
	~won();

	virtual void Render();
	virtual void Update(float dt);

	virtual void Load();
	virtual void Unload();

};