#pragma once
#include "../main.h"
#include "../classes/utility/event_manager.h"
#include "../classes/generic/stream.h"
#include "../classes/entity/player.h"
#include "../classes/entity/checkpoint.h"
#include "../classes/entity/pickup.h"
#include "../classes/entity/object.h"

uint8_t on_server_initialise(void);
void on_server_shutdown(void);
void on_server_frame(float elapsedtime);

uint8_t on_plugin_command(uint32_t commandidentifier, const char* message);
uint8_t on_player_incoming_connection(char* playerName, size_t namebuffersize, const char* userpassword, const char* ipaddress);
void on_client_script_data(int32_t playerid, const uint8_t* data, size_t size);

void on_player_connect(int32_t playerid);
void on_player_disconnect(int32_t playerid, vcmpDisconnectReason reason);

uint8_t on_player_request_class(int32_t playerid, int32_t offset);
uint8_t on_player_request_spawn(int32_t playerid);
void on_player_spawn(int32_t playerid);
void on_player_death(int32_t playerid, int32_t killerid, int32_t reason, vcmpBodyPart bodypart);
void on_player_update(int32_t playerid, vcmpPlayerUpdate updatetype);

uint8_t on_player_request_enter_vehicle(int32_t playerid, int32_t vehicle_id, int32_t slotindex);
void on_player_enter_vehicle(int32_t playerid, int32_t vehicle_id, int32_t slotindex);
void on_player_exit_vehicle(int32_t playerid, int32_t vehicle_id);

void on_player_name_changeable(int32_t playerid, const char* oldName, const char* newName);
void on_player_state_changeable(int32_t playerid, vcmpPlayerState oldstate, vcmpPlayerState newstate);
void on_player_action_changeable(int32_t playerid, int32_t oldaction, int32_t newaction);
void on_player_on_fire_changeable(int32_t playerid, uint8_t ison_fire);
void on_player_crouch_changeable(int32_t playerid, uint8_t iscrouching);
void on_player_game_keys_changeable(int32_t playerid, uint32_t oldkeys, uint32_t newkeys);
void on_player_begin_typing(int32_t playerid);
void on_player_end_typing(int32_t playerid);
void on_player_away_changeable(int32_t playerid, uint8_t isaway);

uint8_t on_player_message(int32_t playerid, const char* message);
uint8_t on_player_command(int32_t playerid, const char* message);
uint8_t on_player_private_message(int32_t playerid, int32_t targetplayer_id, const char* message);
uint8_t on_player_issue_command(int32_t playerId, std::string cmds, std::string c);

void on_player_key_press(int32_t playerid, int32_t bindid);
void on_player_key_release(int32_t playerid, int32_t bindid);
void on_player_spectate(int32_t playerid, int32_t targetplayer_id);
void on_player_crashreport(int32_t playerid, const char* report);

void on_vehicle_update(int32_t vehicle_id, vcmpVehicleUpdate updatetype);
void on_vehicle_explode(int32_t vehicle_id);
void on_vehicle_respawn(int32_t vehicle_id);

void on_object_shot(int32_t objectid, int32_t playerid, int32_t weaponid);
void on_object_touched(int32_t objectid, int32_t playerid);

uint8_t on_pickup_pick_attempt(int32_t pickupid, int32_t playerid);
void on_pickup_picked(int32_t pickupid, int32_t playerid);
void on_pickup_respawn(int32_t pickupid);

void on_checkpoint_entered(int32_t checkpointid, int32_t playerid);
void on_checkpoint_exited(int32_t checkpointid, int32_t playerid);

void on_entity_pool_changeable(vcmpEntityPool entitytype, int32_t entityid, uint8_t isdeleted);
void on_server_performance_report(size_t entrycount, const char** descriptions, uint64_t* times);

// todo: move Later
void on_player_module_list(int32_t playerid, const char* list);
