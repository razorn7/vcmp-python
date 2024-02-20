#include <iostream>
#include <string>
#include <simpleini/SimpleIni.h>
#include <fstream>

#include "core.h"
#include "vcmp/classes/entity/player.h"
#include "vcmp/classes/entity/vehicle.h"
#include "vcmp/classes/entity/checkpoint.h"
#include "vcmp/classes/utility/console.h"
#include "vcmp/classes/utility/event_manager.h"
#include "vcmp/callbacks/callbacks.h"

std::string config_file_str{R"([settings]
# Toggle debug messages [false/true]
debug_messages = false

# Toggle plugin logger [false/true]
enable_logger = true

# Defines the name of the file wich logger will write to
logger_file = server.log

# Toggle whether the date and time on which the log line to be written will be shown
logger_timestamp = false

# Defines the format in which the date and time is shown
# The format below means [2024-01-01 00:00:00]
logger_timestamp_format = [%Y-%m-%d %X]

# Here will be listed the modules you want to import into your environment
[modules]
# moduleName = [false/true] (false: will not be imported | true: will be imported)
scripts = true)" 
};

extern bool debug_messages;
extern bool enable_logger;
extern bool logger_timestamp;
extern std::string timestamp_format;
extern std::string file_name;

ofstream logger_file_;
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
    SI_Error rc = ini.LoadFile("pyconfig.ini");
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
                    file.open("pyconfig.ini", ios::out);
                    if (!file) {
                        error = "Failed to create a new configuration file";
                    }
                    else {
                        file << config_file_str;
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
        std::string timestamp_format_ = ini.GetValue("settings", "logger_timestamp_format", "[%Y-%m-%d %X]");
        std::string logger_timestamp_ = ini.GetValue("settings", "logger_timestamp", "false");
        std::string debug_messages_ = ini.GetValue("settings", "debug_messages", "false");
        std::string enable_logger_ = ini.GetValue("settings", "enable_logger", "true");
        std::list<CSimpleIniA::Entry> scripts;
        timestamp_format = timestamp_format_;

        if (logger_timestamp_ == "true") {
            logger_timestamp = true;

            CLogger::debug("Configuration: Logger timestamp enabled");
        }

        if (debug_messages_ == "true") {
            debug_messages = true;

            CLogger::debug("Configuration: Debug messages enabled");
        }

        if (enable_logger_ == "true") {
            file_name = ini.GetValue("config", "logger_file", "server.txt");
            logger_file_.open(file_name.c_str());

            if (!logger_file_) {
                CLogger::error("Configuration: The log file coundn't be created");

                return false;
            }
            else {
                enable_logger = true;
                logger_file_.close();

                CLogger::debug("Configuration: Log file created");
                CLogger::debug(std::string("Core: Logging at '" + file_name + "'").c_str());
            }
        }

        std::list<CSimpleIniA::Entry> modules;
        if (ini.GetAllKeys("modules", modules) && modules.size() > 0) {
            int iModules = 0;

            for (const auto& module : modules) {
                if (std::string(ini.GetValue("modules", module.pItem)) == "true") {
                    std::string rawname = module.pItem;

                    CLogger::debug(std::string("Importing module: " + rawname).c_str());

                    try {
                        pybind11::module::import(module.pItem);

                        CLogger::debug(std::string("Python Module: Module '" + rawname + "' imported").c_str());
                    }
                    catch (pybind11::error_already_set& e) {
                        CLogger::error(std::string("Python Module: Failed to import module '" + rawname + "': " + e.what()).c_str());
                    }

                    iModules++;
                }
            }

            if (iModules == 0) {
                CLogger::warning("No modules to be imported");
            }
        }
        else {
            CLogger::warning("No modules to be imported found in the configuration file");
            return false;
        }
    }

    CLogger::debug("Core: Module started");
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

    CLogger::script("Python module for VC:MP 0.4");
    CLogger::script("razorn7 (C) 2024\n");

    can_load = initialise_core();
    return 1;
}