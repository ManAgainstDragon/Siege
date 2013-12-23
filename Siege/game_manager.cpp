#include "game_manager.h"

#define addScene(x)	_scenes.push_back(new x);\
					_sceneNames.push_back(#x)

/*
Constructor, creating instancs of all scenes and setups
*/
game_manager::game_manager() {
	addScene(clash);
	addScene(won);

	_current = 0;
	GetCurrentScene()->Load();
}

/*
Destructor
*/
game_manager::~game_manager() {

}

/*
Calls scene to render
*/
void game_manager::Render() {
	GetCurrentScene()->Render();
}

/*
Calls scene to update
*/
void game_manager::Update(float dt) {
	GetCurrentScene()->Update(dt);
}

/*
Places iterator forward
*/
void game_manager::MoveForward() {
	GetCurrentScene()->Unload();
	_current++;
	if (_current >= _sceneNames.size()) --_current;
	GetCurrentScene()->Load();
}

/*
Places iterator backwards
*/
void game_manager::MoveBackward() {
	GetCurrentScene()->Unload();
	_current--;
	if (_current < 0) _current = 0;
	GetCurrentScene()->Load();
}

/*
Places iterator at choosen scene
*/
void game_manager::MoveInto(std::string _scene) {
	unsigned short int temp = 0;
	while (_sceneNames[temp] != _scene) { if (++temp >= _sceneNames.size()) return; }
	if (temp < _sceneNames.size()) {
		GetCurrentScene()->Unload();
		_current = temp;
		GetCurrentScene()->Load();
	}
}

/*
Returns current scene
*/
scene_template* game_manager::GetCurrentScene() {
	return _scenes[_current];
}