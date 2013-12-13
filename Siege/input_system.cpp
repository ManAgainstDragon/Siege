#include "input_system.h"

input_system* input_system::_instance = NULL;

/*
Returns only existing instance of input system
*/
input_system& input_system::GetInstance(){
	if (_instance == NULL) _instance = new input_system;
	return *_instance;
}

/*
Constructor, empty
*/
input_system::input_system() {
	
}

/*
Destructor, empty
*/
input_system::~input_system() {

}

/*
Stores event
*/
void input_system::GrabEvent(sf::Event* _ev) {
	_event = _ev;
}

/*
Returns event
*/
sf::Event* input_system::CurrentEvent() {
	return _event;
}