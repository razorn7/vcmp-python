#include "../main.h"
#include "player.h"
#include <iostream>

PluginFuncs* functions;
std::array<CPlayer*, 100> playerMap;

int CPlayer::ID()
{
    return this->playerId;
}

pybind11::str CPlayer::get_name()
{
    char buffer[64];
    functions->GetPlayerName(this->playerId, buffer, sizeof(buffer));

    return static_cast<pybind11::str>(buffer);
}

void CPlayer::set_name(char const* name)
{
    functions->SetPlayerName(this->playerId, name);
}

pybind11::str CPlayer::get_ip()
{
    char buffer[12];
    functions->GetPlayerIP(this->playerId, buffer, sizeof(buffer));

    return static_cast<pybind11::str>(buffer);
}

pybind11::str CPlayer::get_uid()
{
    char buffer[40];
    functions->GetPlayerUID(this->playerId, buffer, sizeof(buffer));

    return static_cast<pybind11::str>(buffer);
}

pybind11::str CPlayer::get_uid2()
{
    char buffer[40];
    functions->GetPlayerUID2(this->playerId, buffer, sizeof(buffer));

    return static_cast<pybind11::str>(buffer);
}

void CPlayer::send_message(RGBa colour, char const* text)
{
    functions->SendClientMessage(this->playerId, colour.toUInt(), text);
}

void CPlayer::send_announcement(int32_t type, char const* text)
{
    functions->SendGameMessage(this->playerId, type, text);
}

bool CPlayer::get_admin()
{
    return functions->IsPlayerAdmin(this->playerId) == 1 ? true : false;
}

void CPlayer::set_admin(bool toggle)
{
    functions->SetPlayerAdmin(this->playerId, toggle == 1 ? true : false);
}

void CPlayer::kick()
{
    functions->KickPlayer(this->playerId);
}

void CPlayer::ban()
{
    functions->BanPlayer(this->playerId);
}

bool CPlayer::is_streamed_for_player(CPlayer* plr)
{
    return functions->IsPlayerStreamedForPlayer(this->playerId, plr->playerId) == 1 ? true : false;
}

int CPlayer::get_key()
{
    return functions->GetPlayerKey(this->playerId);
}

int CPlayer::get_state()
{
    return functions->GetPlayerState(this->playerId);
}

void CPlayer::set_option(int option, bool toggle)
{
    functions->SetPlayerOption(this->playerId, static_cast<vcmpPlayerOption>(option), toggle == true ? 1 : 0);
}

bool CPlayer::get_option(int option)
{
    return functions->GetPlayerOption(this->playerId, static_cast<vcmpPlayerOption>(option)) == 1 ? true : false;
}

void CPlayer::set_world(int32_t worldId)
{
    functions->SetPlayerWorld(this->playerId, worldId);
}

int CPlayer::get_world()
{
    return functions->GetPlayerWorld(this->playerId);
}

void CPlayer::set_sec_world(int32_t worldId)
{
    functions->SetPlayerSecondaryWorld(this->playerId, worldId);
}

int CPlayer::get_sec_world()
{
    return functions->GetPlayerSecondaryWorld(this->playerId);
}

int CPlayer::get_unique_world()
{
    return functions->GetPlayerUniqueWorld(this->playerId);
}

bool CPlayer::is_world_compatible(int32_t worldId)
{
    return functions->IsPlayerWorldCompatible(this->playerId, worldId);
}

int CPlayer::get_class()
{
    return functions->GetPlayerClass(this->playerId);
}

void CPlayer::set_team(int32_t teamId)
{
    functions->SetPlayerTeam(this->playerId, teamId);
}

int CPlayer::get_team()
{
    return functions->GetPlayerTeam(this->playerId);
}

void CPlayer::set_skin(int32_t skinId)
{
    functions->SetPlayerSkin(this->playerId, skinId);
}

int CPlayer::get_skin()
{
    return functions->GetPlayerSkin(this->playerId);
}

void CPlayer::set_colour(cRGB colour)
{
    functions->SetPlayerColour(this->playerId, colour.toUInt());
}

cRGB CPlayer::get_colour()
{
    unsigned int colour = functions->GetPlayerColour(this->playerId);
    unsigned char r = (colour >> 16) & 0xff;
    unsigned char g = (colour >> 8) & 0xff;
    unsigned char b = colour & 0xff;

    cRGB rgb = cRGB(r, g, b);
    return rgb;
}

bool CPlayer::is_spawned()
{
    return functions->IsPlayerSpawned(this->playerId) == 1 ? true : false;
}

void CPlayer::force_spawn()
{
    functions->ForcePlayerSpawn(this->playerId);
}

void CPlayer::force_select()
{
    functions->ForcePlayerSelect(this->playerId);
}

bool CPlayer::is_typing()
{
    return functions->IsPlayerTyping(this->playerId) == 1 ? true : false;
}

void CPlayer::set_money(int32_t cash)
{
    functions->SetPlayerMoney(this->playerId, cash);
}

int CPlayer::get_money()
{
    return functions->GetPlayerMoney(this->playerId);
}

void CPlayer::set_score(int32_t score)
{
    functions->SetPlayerScore(this->playerId, score);
}

int CPlayer::get_score()
{
    return functions->GetPlayerScore(this->playerId);
}

void CPlayer::set_wanted_level(int32_t wantedLevel)
{
    functions->SetPlayerWantedLevel(this->playerId, wantedLevel);
}

int CPlayer::get_wanted_level()
{
    return functions->GetPlayerWantedLevel(this->playerId);
}

int CPlayer::get_ping()
{
    return functions->GetPlayerPing(this->playerId);
}

double CPlayer::get_fps()
{
    return functions->GetPlayerFPS(this->playerId);
}

void CPlayer::set_health(float health)
{
    functions->SetPlayerHealth(this->playerId, health);
}

float CPlayer::get_health()
{
    return functions->GetPlayerHealth(this->playerId);
}

void CPlayer::set_armour(float armour)
{
    functions->SetPlayerArmour(this->playerId, armour);
}

float CPlayer::get_armour()
{
    return functions->GetPlayerArmour(this->playerId);
}

void CPlayer::set_immunity_flags(int32_t flags)
{
    functions->SetPlayerImmunityFlags(this->playerId, flags);
}

int CPlayer::get_immunity_flags()
{
    return functions->GetPlayerImmunityFlags(this->playerId);
}

void CPlayer::set_position(Vector position)
{
    functions->SetPlayerPosition(this->playerId, position.x, position.y, position.z);
}

Vector CPlayer::get_position()
{
    float x, y, z;
    functions->GetPlayerPosition(this->playerId, &x, &y, &z);

    return Vector(x, y, z);
}

void CPlayer::set_speed(Vector speed)
{
    functions->SetPlayerSpeed(this->playerId, speed.x, speed.y, speed.z);
}

Vector CPlayer::get_speed()
{
    float x, y, z;
    functions->GetPlayerSpeed(this->playerId, &x, &y, &z);

    return Vector(x, y, z);
}

void CPlayer::add_speed(Vector speed)
{
    functions->AddPlayerSpeed(this->playerId, speed.x, speed.y, speed.y);
}

void CPlayer::set_heading(float heading)
{
    functions->SetPlayerHeading(this->playerId, heading);
}

float CPlayer::get_heading()
{
    return functions->GetPlayerHeading(this->playerId);
}

void CPlayer::set_alpha(int32_t alpha, uint32_t fadeTime)
{
    functions->SetPlayerAlpha(this->playerId, alpha, fadeTime);
}

int CPlayer::get_alpha()
{
    return functions->GetPlayerAlpha(this->playerId);
}

Vector CPlayer::get_aim_position()
{
    float x, y, z;
    functions->GetPlayerAimPosition(this->playerId, &x, &y, &z);

    return Vector(x, y, z);
}

Vector CPlayer::get_aim_direction()
{
    float x, y, z;
    functions->GetPlayerAimDirection(this->playerId, &x, &y, &z);

    return Vector(x, y, z);
}

bool CPlayer::is_player_on_fire()
{
    return functions->IsPlayerOnFire(this->playerId) == 1 ? true : false;
}

bool CPlayer::is_player_crouching()
{
    return functions->IsPlayerCrouching(this->playerId) == 1 ? true : false;
}

int CPlayer::action()
{
    return functions->GetPlayerAction(this->playerId);
}

int CPlayer::game_key()
{
    return functions->GetPlayerKey(this->playerId);
}

void CPlayer::put_in_vehicle(CVehicle* vehicle)
{
    if (vehicle != NULL) {
        //on_player_enter_vehicle(this->playerId, vehicle->vehicleId)

        functions->PutPlayerInVehicle(this->playerId, vehicle->vehicleId, 0, 0, 1);
    }
}

void CPlayer::put_in_vehicle_slot(CVehicle* vehicle, int32_t slot)
{
    if (vehicle != NULL) {
        //on_player_enter_vehicle(this->playerId, vehicle->vehicleId)

        functions->PutPlayerInVehicle(this->playerId, vehicle->vehicleId, slot, 1, 1);
    }
}

void CPlayer::remove_from_vehicle()
{
    functions->RemovePlayerFromVehicle(this->playerId);
}

int CPlayer::get_vehicle_status()
{
    return functions->GetPlayerInVehicleStatus(this->playerId);
}

int CPlayer::get_vehicle_slot()
{
    return functions->GetPlayerInVehicleSlot(this->playerId);
}

int CPlayer::give_weapon(int32_t weaponId, int32_t ammo)
{
    return functions->GivePlayerWeapon(this->playerId, weaponId, ammo);
}

void CPlayer::set_weapon(int32_t weaponId, int32_t ammo)
{
    functions->SetPlayerWeapon(this->playerId, weaponId, ammo);
}


int CPlayer::get_weapon_at_slot(int32_t slot)
{
    return functions->GetPlayerWeaponAtSlot(this->playerId, slot);
}

int CPlayer::get_weapon_ammo_at_slot(int32_t slot)
{
    return functions->GetPlayerAmmoAtSlot(this->playerId, slot);
}

void CPlayer::remove_weapon(int32_t weaponId)
{
    functions->RemovePlayerWeapon(this->playerId, weaponId);
}

void CPlayer::remove_all_weapons()
{
    functions->RemoveAllWeapons(this->playerId);
}

void CPlayer::set_camera(Vector position, Vector look)
{
    functions->SetCameraPosition(this->playerId, position.x, position.y, position.z, look.x, look.y, look.z);
}

void CPlayer::restore_camera()
{
    functions->RestoreCamera(this->playerId);
}

bool CPlayer::is_camera_locked()
{
    return functions->IsCameraLocked(this->playerId) == 1 ? true : false;
}

void CPlayer::set_animation(int32_t groupId, int32_t animationId)
{
    functions->SetPlayerAnimation(this->playerId, groupId, animationId);
}

CVehicle* CPlayer::get_standing_vehicle()
{
    int vehicleId = functions->GetPlayerStandingOnVehicle(this->playerId);
    return retrieve_vehicle_instance(vehicleId);
}

CObject* CPlayer::get_standing_object() {
    int objectId = functions->GetPlayerStandingOnObject(this->playerId);
    return retrieve_object_instance(objectId);
}

CPlayer* CPlayer::get_spectate_target()
{
    int vehicleId = functions->GetPlayerSpectateTarget(this->playerId);
    return retrieve_player_instance(vehicleId);
}

void CPlayer::set_spectate_target(CPlayer* plr)
{
    functions->SetPlayerSpectateTarget(this->playerId, plr->playerId);
}

bool CPlayer::is_away()
{
    return functions->IsPlayerAway(this->playerId) == 1 ? true : false;
}

void CPlayer::redirect_to_server(const char* ip, uint32_t port, const char* nick, const char* serverPassword, const char* userPassword)
{
    functions->RedirectPlayerToServer(this->playerId, ip, port, nick, serverPassword, userPassword);
}

void CPlayer::request_module_list(void) {
    functions->GetPlayerModuleList(this->playerId);
}

void CPlayer::set_frozen(bool toFreeze) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionControllable, !toFreeze);
}

void CPlayer::set_drive_by_enabled(bool canDb) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionDriveBy, canDb);
}

void CPlayer::set_white_scanlines(bool hasWhiteScan) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionWhiteScanlines, hasWhiteScan);
}

void CPlayer::set_green_scanlines(bool hasGreenScan) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionGreenScanlines, hasGreenScan);
}

void CPlayer::set_widescreen(bool hasWidescreen) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionWidescreen, hasWidescreen);
}

void CPlayer::set_on_radar(bool showOnRadar) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionHasMarker, showOnRadar);
}

void CPlayer::set_can_attack(bool canAttack) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionCanAttack, canAttack);
}

void CPlayer::set_weapon_slot(int32_t slot) {
    functions->SetPlayerWeaponSlot(this->playerId, slot);
}

bool CPlayer::get_frozen() {
    return !functions->GetPlayerOption(this->playerId, vcmpPlayerOptionControllable);
}

bool CPlayer::get_drive_by_enabled() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionDriveBy) == 1 ? true : false;
}

bool CPlayer::get_white_scanlines() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionWhiteScanlines) == 1 ? true : false;
}

bool CPlayer::get_green_scanlines() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionGreenScanlines) == 1 ? true : false;
}

bool CPlayer::get_widescreen() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionWidescreen) == 1 ? true : false;
}

bool CPlayer::get_on_radar() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionHasMarker) == 1 ? true : false;
}

bool CPlayer::get_can_attack() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionCanAttack) == 1 ? true : false;
}

int32_t CPlayer::get_weapon_slot() {
    return functions->GetPlayerWeaponSlot(this->playerId);
}

int32_t CPlayer::get_weapon() {
    return functions->GetPlayerWeapon(this->playerId);
}

int32_t CPlayer::get_weapon_ammo() {
    return functions->GetPlayerWeaponAmmo(this->playerId);
}

bool CPlayer::get_drunk_status() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionDrunkEffects) == 1;
}

void CPlayer::set_drunk_status(bool isDrunk) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionDrunkEffects, isDrunk);
}

void CPlayer::set_drunk_level(int32_t visuals, int32_t handling) {
    if (visuals <= 0 && handling <= 0)
        functions->SetPlayerOption(this->playerId, vcmpPlayerOptionDrunkEffects, 0);
    else
        functions->SetPlayerOption(this->playerId, vcmpPlayerOptionDrunkEffects, 1);
}

void CPlayer::show_markers(bool setMarkers) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionShowMarkers, setMarkers);
}

bool CPlayer::is_showning_markers() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionShowMarkers) == 1 ? true : false;
}

void CPlayer::set_marker(int32_t nDummy) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionHasMarker, 1);
}

void CPlayer::remove_marker() {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionHasMarker, 0);
}

bool CPlayer::get_marker_visible() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionHasMarker) == 1;
}

void CPlayer::set_marker_visible(bool isVisible) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionHasMarker, isVisible);
}

bool CPlayer::get_can_use_colors() {
    return functions->GetPlayerOption(this->playerId, vcmpPlayerOptionChatTagsEnabled) == 1;
}

void CPlayer::set_can_use_colors(bool canUse) {
    functions->SetPlayerOption(this->playerId, vcmpPlayerOptionChatTagsEnabled, canUse);
}

CPlayer* allocate_player_instance(int gPlayerId)
{
    if (gPlayerId < 0 || gPlayerId > 100 - 1)
        return NULL;
    else if (functions->IsPlayerConnected(gPlayerId) == 0)
        return NULL;
    else if (playerMap[gPlayerId] != NULL)
        return playerMap[gPlayerId];

    CPlayer* pPlayer = new CPlayer();
    pPlayer->playerId = gPlayerId;

    playerMap[pPlayer->playerId] = pPlayer;
    return pPlayer;
}

CPlayer* retrieve_player_instance(int gPlayerId)
{
    if (gPlayerId < 0 || gPlayerId > 100 - 1)
        return NULL;

    return playerMap[gPlayerId];
}

void destroy_player_instance(int gPlayerId)
{
    if (gPlayerId < 0 || gPlayerId > 100 - 1)
        return;
    else if (playerMap[gPlayerId] == NULL)
        return;
    else {
        CPlayer* pPlayer = playerMap[gPlayerId];
        delete pPlayer;

        playerMap[gPlayerId] = NULL;
    }
}

PYBIND11_EMBEDDED_MODULE(vcmp_player, m) {
    pybind11::class_<CPlayer, std::shared_ptr<CPlayer> >(m, "CPlayer")
        .def(pybind11::init<>())
        .def_property_readonly("ID", &CPlayer::ID)
        .def_property_readonly("id", &CPlayer::ID)
        .def_property("name", &CPlayer::get_name, &CPlayer::set_name)
        .def("send_message", &CPlayer::send_message)
        .def("send_announcement", &CPlayer::send_announcement)
        .def_property("is_admin", &CPlayer::get_admin, &CPlayer::set_admin)
        .def_property_readonly("ip", &CPlayer::get_ip)
        .def_property_readonly("uid", &CPlayer::get_uid)
        .def_property_readonly("uid2", &CPlayer::get_uid2)
        .def("kick", &CPlayer::kick)
        .def("ban", &CPlayer::ban)
        .def("is_streamed_for_player", &CPlayer::is_streamed_for_player)
        .def_property_readonly("key", &CPlayer::get_key)
        .def_property_readonly("state", &CPlayer::get_state)
        .def_property("option", &CPlayer::get_option, &CPlayer::set_option)
        .def_property("world", &CPlayer::get_world, &CPlayer::set_world)
        .def_property("sec_world", &CPlayer::get_sec_world, &CPlayer::set_sec_world)
        .def_property_readonly("unique_world", &CPlayer::get_unique_world)
        .def("is_world_compatible", &CPlayer::is_world_compatible)
        .def_property_readonly("get_class", &CPlayer::get_class)
        .def_property("team", &CPlayer::get_team, &CPlayer::set_team)
        .def_property("skin", &CPlayer::get_skin, &CPlayer::set_skin)
        .def_property("colour", &CPlayer::get_colour, &CPlayer::set_colour)
        .def_property_readonly("is_spawned", &CPlayer::is_spawned)
        .def("force_spawn", &CPlayer::force_spawn)
        .def("force_select", &CPlayer::force_select)
        .def_property_readonly("is_typing", &CPlayer::is_typing)
        .def_property("money", &CPlayer::get_money, &CPlayer::set_money)
        .def_property("score", &CPlayer::get_score, &CPlayer::set_score)
        .def_property("wanted_level", &CPlayer::get_wanted_level, &CPlayer::set_wanted_level)
        .def_property_readonly("ping", &CPlayer::get_ping)
        .def_property_readonly("fps", &CPlayer::get_fps)
        .def_property("health", &CPlayer::get_health, &CPlayer::set_health)
        .def_property("armour", &CPlayer::get_armour, &CPlayer::set_armour)
        .def_property("immunity_flags", &CPlayer::get_immunity_flags, &CPlayer::set_immunity_flags)
        .def_property("position", &CPlayer::get_position, &CPlayer::set_position)
        .def_property("pos", &CPlayer::get_position, &CPlayer::set_position)
        .def_property("speed", &CPlayer::get_speed, &CPlayer::set_speed)
        .def("add_speed", &CPlayer::add_speed)
        .def_property("heading", &CPlayer::get_heading, &CPlayer::set_heading)
        .def_property("angle", &CPlayer::get_heading, &CPlayer::set_heading)
        .def_property("alpha", &CPlayer::get_alpha, &CPlayer::set_alpha)
        .def_property_readonly("aim_position", &CPlayer::get_aim_position)
        .def_property_readonly("aim_direction", &CPlayer::get_aim_direction)
        .def_property_readonly("is_player_crouching", &CPlayer::is_player_crouching)
        .def_property_readonly("is_player_on_fire", &CPlayer::is_player_on_fire)
        .def_property_readonly("game_key", &CPlayer::game_key)
        .def_property_readonly("action", &CPlayer::action)
        .def("put_in_vehicle", &CPlayer::put_in_vehicle)
        .def("put_in_vehicle_slot", &CPlayer::put_in_vehicle_slot)
        .def("remove_from_vehicle", &CPlayer::remove_from_vehicle)
        .def_property_readonly("vehicle_status", &CPlayer::get_vehicle_status)
        .def_property_readonly("vehicle_slot", &CPlayer::get_vehicle_slot)
        .def("give_weapon", &CPlayer::give_weapon)
        .def("set_weapon", &CPlayer::set_weapon)
        .def_property_readonly("weapon", &CPlayer::get_weapon)
        .def_property_readonly("weapon_ammo", &CPlayer::get_weapon_ammo)
        .def("get_weapon_at_slot", &CPlayer::get_weapon_at_slot)
        .def("get_weapon_ammo_at_slot", &CPlayer::get_weapon_ammo_at_slot)
        .def("remove_weapon", &CPlayer::remove_weapon)
        .def("remove_all_weapons", &CPlayer::remove_all_weapons)
        .def("set_camera", &CPlayer::set_camera)
        .def("restore_camera", &CPlayer::restore_camera)
        .def_property_readonly("is_camera_locked", &CPlayer::is_camera_locked)
        .def("set_animation", &CPlayer::set_animation)
        .def("get_standing_vehicle", &CPlayer::get_standing_vehicle)
        .def("get_standing_object", &CPlayer::get_standing_object)
        .def_property_readonly("is_away", &CPlayer::is_away)
        .def_property("spectate_target", &CPlayer::get_spectate_target, &CPlayer::set_spectate_target)
        .def("request_module_list", &CPlayer::request_module_list)
        .def_property("drunk_status", &CPlayer::get_drunk_status, &CPlayer::set_drunk_status)
        .def("set_drunk_level", &CPlayer::set_drunk_level)
        .def_property("can_attack", &CPlayer::get_can_attack, &CPlayer::set_can_attack)
        .def_property("can_driveby", &CPlayer::get_drive_by_enabled, &CPlayer::set_drive_by_enabled)
        .def_property("frozen_status", &CPlayer::get_frozen, &CPlayer::set_frozen)
        .def_property("green_scanlines_status", &CPlayer::get_green_scanlines, &CPlayer::set_green_scanlines)
        .def_property("has_chat_tags", &CPlayer::get_can_use_colors, &CPlayer::set_can_use_colors)
        .def_property("has_markers", &CPlayer::get_marker_visible, &CPlayer::set_marker_visible)
        .def_property("on_radar_status", &CPlayer::get_on_radar, &CPlayer::set_on_radar)
        .def_property("marker_status", &CPlayer::is_showning_markers, &CPlayer::show_markers)
        .def_property("weapon_slot", &CPlayer::get_weapon_slot, &CPlayer::set_weapon_slot)
        .def_property("white_scanlines_status", &CPlayer::get_white_scanlines, &CPlayer::set_white_scanlines)
        .def_property("widescreen_status", &CPlayer::get_widescreen, &CPlayer::set_widescreen);
}