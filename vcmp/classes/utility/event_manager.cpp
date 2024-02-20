#include "event_manager.h"
#include <map>
#include <vector>

std::map<std::string, std::vector<pybind11::function>> events = {
    /*
        @ Server Events
    */
    {"on_server_initialise", {}},
    {"on_server_shutdown", {}},
    {"on_server_frame", {}},
    {"on_plugin_command", {}},

    /*
        @ Player Events
    */
    {"on_client_script_data", {}},
    {"on_player_incoming_connection", {}},
    {"on_player_connect", {}},
    {"on_player_disconnect", {}},
    {"on_player_request_class", {}},
    {"on_player_request_spawn", {}},
    {"on_player_spawn", {}},
    {"on_player_death", {}},
    {"on_player_kill", {}},
    {"on_player_update", {}},
    {"on_player_request_enter_vehicle", {}},
    {"on_player_enter_vehicle", {}},
    {"on_player_exit_vehicle", {}},
    {"on_player_name_changeable", {}},
    {"on_player_state_changeable", {}},
    {"on_player_action_changeable", {}},
    {"on_player_on_fire_changeable", {}},
    {"on_player_crouch_changeable", {}},
    {"on_player_game_keys_changeable", {}},
    {"on_player_begin_typing", {}},
    {"on_player_end_typing", {}},
    {"on_player_away_changeable", {}},
    {"on_player_message", {}},
    {"on_player_issue_command", {}},
    {"on_player_private_message", {}},
    {"on_player_key_press", {}},
    {"on_player_key_release", {}},
    {"on_player_spectate", {}},
    {"on_player_crash_report", {}},
    {"on_player_module_list", {}},

    /*
        @ Vehicle Events
    */
    {"on_vehicle_update", {}},
    {"on_vehicle_explode", {}},
    {"on_vehicle_respawn", {}},

    /*
        @ Object Events
    */
    {"on_object_shot", {}},
    {"on_object_touch", {}},

    /*
        @ Pickup Events
    */
    {"on_pickup_pick_attempt", {}},
    {"on_pickup_picked", {}},
    {"on_pickup_respawn", {}},

    /*
        @ Checkpoint Events
    */
    {"on_checkpoint_enter", {}},
    {"on_checkpoint_exit", {}},
};

bool CEventManager::check_event(std::string event_name) {
    for (auto event_ : events) {
        if (event_.first == event_name) {
            if (event_.second.size() > 0) {
                return true;
            }
        }
    }

    return false;
}

bool CEventManager::check_exist(std::string event_name) {
    auto exist = events.find(event_name);
    if (exist != events.end())
        return true;
    return false;
}

bool CEventManager::create(std::string event_name) {
    if (CEventManager::check_exist(event_name)) {
        CLogger::error(std::string("Event Manager: The event named as '" + event_name + "' already exists.").c_str());
        return false;
    }
    else {
        events.insert(std::pair < std::string, std::vector<pybind11::function>>(event_name, {}));

        CLogger::debug(std::string("Event Manager: The event named as '" + event_name + "' has been created.").c_str());
        return true;
    }
}

bool CEventManager::bind(std::string event_name, pybind11::function function) {
    if (!CEventManager::check_exist(event_name)) {
        CLogger::error(std::string("Event Manger: The event '" + event_name + "' does not exists.").c_str());

        return false;
    }
    else {
        for (auto event_ : events[event_name]) {
            if (event_.ptr() == function.ptr()) {
                CLogger::error(std::string("Event Manager: The event '" + event_name + "' is already bound to the given function.").c_str());
                return false;
            }
        }
    }

    events[event_name].push_back(function);
    CLogger::debug(std::string("Event Manager: The event '" + event_name + "' has been bound.").c_str());
    return true;
}

bool CEventManager::unbind(std::string event_name, pybind11::function function) {
    if (!CEventManager::check_exist(event_name)) {
        CLogger::error(std::string("Event Manager: The event '" + event_name + "' does not exists.").c_str());

        return false;
    }

    else {
        for (auto event_ : events[event_name]) {
            if (event_.ptr() == function.ptr()) {
                events[event_name] = {};

                CLogger::debug(std::string("Event Manager: The event '" + event_name + "' has been unbound.").c_str());
                return true;
            }
        }
        CLogger::error(std::string("Event Manager: The event '" + event_name + "' is not bound with any function.").c_str());
    }
    return false;
}

bool CEventManager::trigger(std::string event_name, pybind11::tuple args) {
    if (!check_exist(event_name)) {
        CLogger::error(std::string("Event Manager: The event '" + event_name + "' does not exists.").c_str());

        return false;
    }
    else {
        for (auto event_ : events[event_name]) {
            return event_(*args).release().cast<bool>();
        }
    }
    return true;
}

PYBIND11_EMBEDDED_MODULE(vcmp_event_manager, module) {
    pybind11::class_<CEventManager>(module, "Event")
        .def_static("create", &CEventManager::create)
        .def_static("bind", &CEventManager::bind)
        .def_static("unbind", &CEventManager::unbind)
        .def_static("trigger", &CEventManager::trigger);
}