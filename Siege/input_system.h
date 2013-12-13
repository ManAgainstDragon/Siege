#pragma once

#include <SFML\Graphics.hpp>

class input_system {
	/* singleton */
public:
	static input_system& GetInstance();

private:
	input_system();
	~input_system();

	static input_system* _instance;

	/* functional */
public:
	void GrabEvent(sf::Event* _ev);
	sf::Event* CurrentEvent();

private:
	sf::Event* _event;

};

#define InputSystem input_system::GetInstance()
#define InsertEvent(x) InputSystem.GrabEvent(x)
#define InEv InputSystem.CurrentEvent()

