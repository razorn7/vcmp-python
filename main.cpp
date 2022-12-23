#include <iostream>
#include <string>
#include <simpleini/SimpleIni.h>
#include <fstream>

#include "main.h"
#include "vcmp_wrapper/classes/entity/player.h"
#include "vcmp_wrapper/classes/entity/vehicle.h"
#include "vcmp_wrapper/classes/entity/checkpoint.h"
#include "vcmp_wrapper/classes/utility/console.h"
#include "vcmp_wrapper/classes/utility/event_manager.h"
#include "vcmp_wrapper/callbacks/callbacks.h"

extern bool debug_messages;
extern bool enable_logging;
extern bool logging_timestamp;
extern std::string timestamp_format;
extern std::string file_name;

ofstream logging_file_;
bool can_load;

int initialise_core() {
    pybind11::initialize_interpreter();
    pybind11::module::import("vcmp_player");
    pybind11::module::import("vcmp_vehicle");
    pybind11::module::import("vcmp_checkpoint");
    pybind11::module::import("vcmp_pickup");
    pybind11::module::import("vcmp_object");

    CSimpleIniA ini(false, true, false);
    ini.SetUnicode();
    std::string error;
    SI_Error rc = ini.LoadFile("py_config.ini");
    if(rc < 0) {
        switch (rc) {
            case SI_FAIL:
                error = "Fail";
            break;

            case SI_NOMEM:
                error = "No enough memory";
            break;

            case SI_FILE:
                if (errno == 2) {
                    CLogger::warning("Configuration file not found, trying to create a new one...");
                    ofstream file;
                    file.open("py_config.ini", ios::out);
                    if (!file) {
                        error = "Failed to create a new configuration file";
                    }
                    else {
                        file << "[config]\ndebug_messages = false\nenable_logging = true\nlogging_file = server.txt\nlogging_timestamp = false\nlogging_timestamp_format = [%Y-%m-%d %X]";
                    
                        file.close();
                    }
                }
                else {
                    char buffer[256];
                    strerror_s(buffer, 256, errno);
                    error = std::string(buffer);
                }
            break;
            default: 
                error = "Unknown error";
        }
        if (!error.empty()) {
            CLogger::error(std::string("Failed to load configuration file: " + error).c_str());
            
            return false;
        }
    }
    else {
        std::string timestamp_format_ = ini.GetValue("config", "logging_timestamp_format", "[%Y-%m-%d %X]");
        std::string logging_timestamp_ = ini.GetValue("config", "logging_timestamp", "false");
        std::string debug_messages_ = ini.GetValue("config", "debug_messages", "false");
        std::string enable_logging_ = ini.GetValue("config", "enable_logging", "true");
        std::list<CSimpleIniA::Entry> scripts;
        timestamp_format = timestamp_format_;

        if (logging_timestamp_ == "true") {
            logging_timestamp = true;

            CLogger::debug("Configuration: Logger timestamp has been enabled.");
        }

        if (debug_messages_ == "true") {
            debug_messages = true;

            CLogger::debug("Configuration: Debug messages has been enabled.");
        }

        if (enable_logging_ == "true") {
            file_name = ini.GetValue("config", "logging_file", "server-log.txt");
            logging_file_.open(file_name.c_str());

            if (!logging_file_) {
                CLogger::error("Configuration: The logging file coundn't be created.");

                return false;
            }
            else {
                enable_logging = true;
                logging_file_.close();

                CLogger::debug("Configuration: Logging file has been created.");
            }
        }

        if (ini.GetAllValues("modules", "import", scripts) && scripts.size() > 0) {
            for (auto it = scripts.begin(); it != scripts.end(); it++) {
                std::string str = it->pItem;
                size_t lastindex = str.find_last_of(".");
                std::string rawname = str.substr(0, lastindex);
                std::replace(rawname.begin(), rawname.end(), '/', '.');

                try {
                    pybind11::module::import(rawname.c_str());

                    CLogger::debug(std::string("Python Module: The module '" + rawname + "' has been imported.").c_str());
                }
                catch (pybind11::error_already_set& e) {
                    CLogger::error(std::string("Python Module: Failed to import '" + rawname + "': " + e.what()).c_str());

                    return false;
                }
            }
        }
        else {
            CLogger::warning("No modules were found to be imported in the configuration file!");
            return false;
        }
    }
    return true;
}

unsigned int VcmpPluginInit(PluginFuncs* pluginFuncs, PluginCallbacks* pluginCalls, PluginInfo* pluginInfo) {
    functions = pluginFuncs;

    pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;
    pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;

    pluginCalls->OnServerInitialise = on_server_initialise;
    pluginCalls->OnServerShutdown = on_server_shutdown;
    pluginCalls->OnServerFrame = on_server_frame;

    pluginCalls->OnPluginCommand = on_plugin_command;
    pluginCalls->OnIncomingConnection = on_player_incoming_connection;
    pluginCalls->OnClientScriptData = on_client_script_data;

    pluginCalls->OnPlayerConnect = on_player_connect;
    pluginCalls->OnPlayerDisconnect = on_player_disconnect;

    pluginCalls->OnPlayerRequestClass = on_player_request_class;
    pluginCalls->OnPlayerRequestSpawn = on_player_request_spawn;
    pluginCalls->OnPlayerSpawn = on_player_spawn;
    pluginCalls->OnPlayerDeath = on_player_death;
    pluginCalls->OnPlayerUpdate = on_player_update;

    pluginCalls->OnPlayerRequestEnterVehicle = on_player_request_enter_vehicle;
    pluginCalls->OnPlayerEnterVehicle = on_player_enter_vehicle;
    pluginCalls->OnPlayerExitVehicle = on_player_exit_vehicle;

    pluginCalls->OnPlayerNameChange = on_player_name_changeable;
    pluginCalls->OnPlayerStateChange = on_player_state_changeable;
    pluginCalls->OnPlayerActionChange = on_player_action_changeable;
    pluginCalls->OnPlayerOnFireChange = on_player_on_fire_changeable;
    pluginCalls->OnPlayerCrouchChange = on_player_crouch_changeable;
    pluginCalls->OnPlayerGameKeysChange = on_player_game_keys_changeable;
    pluginCalls->OnPlayerBeginTyping = on_player_begin_typing;
    pluginCalls->OnPlayerEndTyping = on_player_end_typing;
    pluginCalls->OnPlayerAwayChange = on_player_away_changeable;

    pluginCalls->OnPlayerMessage = on_player_message;
    pluginCalls->OnPlayerCommand = on_player_command;
    pluginCalls->OnPlayerPrivateMessage = on_player_private_message;

    pluginCalls->OnPlayerKeyBindDown = on_player_key_press;
    pluginCalls->OnPlayerKeyBindUp = on_player_key_release;
    pluginCalls->OnPlayerSpectate = on_player_spectate;
    pluginCalls->OnPlayerCrashReport = on_player_crashreport;

    pluginCalls->OnVehicleUpdate = on_vehicle_update;
    pluginCalls->OnVehicleExplode = on_vehicle_explode;
    pluginCalls->OnVehicleRespawn = on_vehicle_respawn;

    pluginCalls->OnEntityPoolChange = on_entity_pool_changeable;
    pluginCalls->OnPlayerMessage = on_player_message;

    pluginCalls->OnObjectShot = on_object_shot;
    pluginCalls->OnObjectTouched = on_object_touched;

    pluginCalls->OnPickupPickAttempt = on_pickup_pick_attempt;
    pluginCalls->OnPickupPicked = on_pickup_picked;
    pluginCalls->OnPickupRespawn = on_pickup_respawn;

    pluginCalls->OnCheckpointEntered = on_checkpoint_entered;
    pluginCalls->OnCheckpointExited = on_checkpoint_exited;

    pluginCalls->OnPlayerModuleList = on_player_module_list;

    CLogger::script("Loading Python module for VC:MP 0.4...");
    CLogger::script("Author: razorn7 (C) 2022\n");

    can_load = initialise_core();

    CLogger::debug("Core: The module has been initialised!");
    return 1;
}