#include "won_scene.h"

#include "stdafx.h"

#include "sys.h"

won::won() {

}

won::~won() {

}

void won::Render() {
	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(100.f);
	circ.setOrigin(100, 100);
	circ.setPosition(WIDTH / 2, HEIGHT / 2);
	Window.draw(circ);
}

void won::Update(float dt) {

}

void won::Load() {
	Window.UpdateStatusbar("You have won");
}

void won::Unload() {

}