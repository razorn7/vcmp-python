#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "callbacks.h"

uint8_t on_server_initialise(void) {
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple();
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    return 1;
}

void on_server_shutdown(void) {
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple();
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    pybind11::finalize_interpreter();
}

void on_server_frame(float elapsedtime) {
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(elapsedtime);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

uint8_t on_plugin_command(uint32_t commandidentifier, const char* message) {
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(commandidentifier, message);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    return 1;
}

uint8_t on_player_incoming_connection(char* playerName, size_t namebuffersize, const char* userpassword, const char* ipaddress) {
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(playerName, userpassword, ipaddress);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    return 1;
}
	
void on_client_script_data(int32_t playerId, const uint8_t* data, size_t size) {
    CPlayer* player = retrieve_player_instance(playerId);
    CStream::load_input(data, size);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_connect(int32_t playerId) {
	CPlayer* player = allocate_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_disconnect(int32_t playerId, vcmpDisconnectReason reason) {
	CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    destroy_player_instance(playerId);
}

uint8_t on_player_request_class(int32_t playerId, int32_t offset) {
	CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, offset);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    return 1;
}
	
uint8_t on_player_request_spawn(int32_t playerId) {
	CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    return 1;
}

void on_player_spawn(int32_t playerId) {
	CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_death(int32_t playerId, int32_t killerid, int32_t reason, vcmpBodyPart bodypart) {
	CPlayer* player = retrieve_player_instance(playerId);
    CPlayer* killer = retrieve_player_instance(killerid);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(killer, player, reason, static_cast<int>(bodypart));
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_update(int32_t playerId, vcmpPlayerUpdate updatetype) {
	CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, static_cast<int>(updatetype));
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

uint8_t on_player_request_enter_vehicle(int32_t playerId, int32_t vehicleId, int32_t slotindex) {
	CPlayer* player = retrieve_player_instance(playerId);
	CVehicle* vehicle = retrieve_vehicle_instance(vehicleId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, vehicle, slotindex);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
	return 1;
}

void on_player_enter_vehicle(int32_t playerId, int32_t vehicleId, int32_t slotindex) {
	CPlayer* player = retrieve_player_instance(playerId);
	CVehicle* vehicle = retrieve_vehicle_instance(vehicleId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, vehicle, slotindex);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_exit_vehicle(int32_t playerId, int32_t vehicleId) {
	CPlayer* player = retrieve_player_instance(playerId);
	CVehicle* vehicle = retrieve_vehicle_instance(vehicleId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, vehicle);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_name_changeable(int32_t playerId, const char* oldName, const char* newName) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, oldName, newName);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_state_changeable(int32_t playerId, vcmpPlayerState oldstate, vcmpPlayerState newstate) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, static_cast<int>(oldstate), static_cast<int>(newstate));
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_action_changeable(int32_t playerId, int32_t oldaction, int32_t newaction) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, oldaction, newaction);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_on_fire_changeable(int32_t playerId, uint8_t is_on_fire) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, is_on_fire);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_crouch_changeable(int32_t playerId, uint8_t is_crouching) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, is_crouching);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_game_keys_changeable(int32_t playerId, uint32_t oldkeys, uint32_t newkeys) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, oldkeys, newkeys);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_begin_typing(int32_t playerId) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_end_typing(int32_t playerId) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_away_changeable(int32_t playerId, uint8_t is_away) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, (is_away == 1 ? true : false));
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

uint8_t on_player_message(int32_t playerId, const char* message) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, message);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
	
	return 1;
}

uint8_t on_player_issue_command(int32_t playerId, std::string cmds, std::string c) {
    if (can_load) {
        try {
            CPlayer* player = retrieve_player_instance(playerId);
            pybind11::tuple args = pybind11::make_tuple(player, cmds, c);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
    return 1;
}

uint8_t on_player_command(int32_t pPlayer,
    const char* pszText) {
    char* szCommand = _strdup(pszText);
    char* szSpacePos = strchr(szCommand, ' ');

    if (szSpacePos) {
        szSpacePos[0] = '\0';
    }

    char* szArguments = szSpacePos ? &szSpacePos[1] : NULL;

    std::string strCommand(szCommand);
    std::string strArguments;
    std::transform(strCommand.begin(), strCommand.end(), strCommand.begin(), ::tolower);
    if (szArguments == NULL || strlen(szArguments) <= 0)
        strArguments = std::string("");
    else {
        strArguments = std::string(szArguments);
    }

    on_player_issue_command(pPlayer, std::move(strCommand), std::move(strArguments));

    return 1;
}

uint8_t on_player_private_message(int32_t playerId, int32_t targetplayer_id, const char* message) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, targetplayer_id, message);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
	
	return 1;
}

void on_player_key_press(int32_t playerId, int32_t bindid) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, bindid);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_key_release(int32_t playerId, int32_t bindid) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, bindid);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_spectate(int32_t playerId, int32_t targetplayer_id) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, targetplayer_id);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_player_crashreport(int32_t playerId, const char* report) {
	CPlayer* player = retrieve_player_instance(playerId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, report);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_vehicle_update(int32_t vehicleId, vcmpVehicleUpdate updatetype) {
	CVehicle* vehicle = retrieve_vehicle_instance(vehicleId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(vehicle, static_cast<int>(updatetype));
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_vehicle_explode(int32_t vehicleId) {
	CVehicle* vehicle = retrieve_vehicle_instance(vehicleId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(vehicle);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_vehicle_respawn(int32_t vehicleId) {
    CVehicle* vehicle = retrieve_vehicle_instance(vehicleId);
	
    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(vehicle);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_object_shot(int32_t objectId, int32_t playerId, int32_t weaponId) {
    CObject* object = retrieve_object_instance(objectId);
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, object, weaponId);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_object_touched(int32_t objectId, int32_t playerId) {
    CObject* object = retrieve_object_instance(objectId);
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, object);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

uint8_t on_pickup_pick_attempt(int32_t pickupId, int32_t playerId) {
    CPickup* pickup = retrieve_pickup_instance(pickupId);
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, pickup);
            return CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_pickup_picked(int32_t pickupId, int32_t playerId) {
    CPickup* pickup = retrieve_pickup_instance(pickupId);
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, pickup);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_pickup_respawn(int32_t pickupId) {
    CPickup* pickup = retrieve_pickup_instance(pickupId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(pickup);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_checkpoint_entered(int32_t checkpointId, int32_t playerId) {
    CCheckpoint* checkpoint = retrieve_checkpoint_instance(checkpointId);
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, checkpoint);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_checkpoint_exited(int32_t checkpointId, int32_t playerId) {
    CCheckpoint* checkpoint = retrieve_checkpoint_instance(checkpointId);
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, checkpoint);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}

void on_entity_pool_changeable(vcmpEntityPool nEntityType, int nEntityId, uint8_t bDeleted)
{
    if (nEntityType == vcmpEntityPoolVehicle)
    {
        if (bDeleted)
            destroy_vehicle_instance(nEntityId);
    }
    else if (nEntityType == vcmpEntityPoolObject)
    {
        if (bDeleted)
            destroy_object_instance(nEntityId);
    }
    else if (nEntityType == vcmpEntityPoolPickup)
    {
        if (bDeleted)
            destroy_pickup_instance(nEntityId);
    }
    else if (nEntityType == vcmpEntityPoolCheckPoint) {
        if (bDeleted)
            destroy_checkpoint_instance(nEntityId);
    }
}

void on_server_performance_report(size_t entrycount, const char** descriptions, uint64_t* times) {
}

	// todo: move Later
void on_player_module_list(int32_t playerId, const char* list) {
    CPlayer* player = retrieve_player_instance(playerId);

    if (can_load) {
        try {
            pybind11::tuple args = pybind11::make_tuple(player, list);
            CEventManager::trigger(__FUNCTION__, args);
        }
        catch (pybind11::error_already_set& e) {
            CLogger::error(e.what());
        }
    }
}
