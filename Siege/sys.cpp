#include "sys.h"

sys* sys::_instance = NULL;

/*
Constructor, called once while first use of instance
*/
sys::sys() {

}

/*
Destructor
*/
sys::~sys() {

}

/*
Returns only existing instance
*/
sys& sys::GetInstance() {
	if (_instance == NULL) _instance = new sys;
	return *_instance;
}

/*
Initializes the game
*/
void sys::Init(std::string _name) {
	sf::VideoMode size = sf::VideoMode(WIDTH, HEIGHT);
	this->create(size, _name, sf::Style::Close);
}

/*
Initializes game loop
*/
void sys::Start() {
	sf::Clock _timer;
	sf::Event _ev;
	while (this->isOpen()) {
		while (this->pollEvent(_ev)) {
			InsertEvent(&_ev);
			if (InEv->type == sf::Event::Closed) Stop();
		}
		this->clear(sf::Color(110, 110, 110));
		this->Update(_timer.restart().asSeconds());
		this->Render();
		this->display();
	}
}

/*
Shuts down the game
*/
void sys::Stop() {
	this->close();
}

/*
Renders all objects on scene
*/
void sys::Render() {
	_gmi->Render();
}

/*
Updates all objects on scene
*/
void sys::Update(float dt) {
	_gmi->Update(dt);
}

/*
Grabs instance of screen manager
*/
void sys::SetGameManager(game_manager* _instance) {
	if(_instance != NULL) _gmi = _instance;
	else _gmi = new game_manager;
}