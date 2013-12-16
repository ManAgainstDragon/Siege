#pragma once

#include <string>
#include <sstream>

template <typename T> std::string toString(T in) {
	std::ostringstream os;
	os << in;
	return os.str();
}