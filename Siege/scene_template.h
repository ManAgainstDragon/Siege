#pragma once

class scene_template {
	/* functional */
public:
	scene_template();
	virtual ~scene_template();

	virtual void Render();
	virtual void Update(float dt);

	virtual void Load();
	virtual void Unload();
};