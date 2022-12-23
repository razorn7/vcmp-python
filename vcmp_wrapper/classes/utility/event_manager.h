#pragma once
#include "../main.h"
#include "../../classes/utility/console.h"

class CEventManager {
public:
	static bool check_event(std::string event_name);
	static bool check_exist(std::string event_name);
	static bool create(std::string event_name);
	static bool bind(std::string event_name, pybind11::function function);
	static bool trigger(std::string event_name, pybind11::tuple args);
	static bool unbind(std::string event_name, pybind11::function function);
};