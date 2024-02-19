#pragma once
#include "../core.h"
#include "vehicle.h"
#include "object.h"

class CVehicle;
class CObject;
class CPlayer {
public:
    int32_t playerId;

    int32_t ID();

    void set_name(char const* name);
    pybind11::str get_name();

    void send_message(RGBa colour, char const* message);
    void send_announcement(int32_t type, char const* text);

    bool get_admin();
    void set_admin(bool toggle);

    pybind11::str get_ip();
    pybind11::str get_uid();
    pybind11::str get_uid2();

    void kick();
    void ban();

    bool is_streamed_for_player(CPlayer* plr);
    int32_t get_key();
    int32_t get_state();

    void set_option(int32_t option, bool toggle);
    bool get_option(int32_t option);

    void set_world(int32_t worldId);
    int32_t get_world();

    void set_sec_world(int32_t worldId);
    int32_t get_sec_world();

    int32_t get_unique_world();

    bool is_world_compatible(int32_t worldId);

    int32_t get_class();

    void set_team(int32_t teamId);
    int32_t get_team();

    void set_skin(int32_t skinId);
    int32_t get_skin();

    void set_colour(cRGB colour);
    cRGB get_colour();

    bool is_spawned();

    void force_spawn();
    void force_select();

    bool is_typing();

    void set_money(int32_t money);
    int32_t get_money();

    void set_score(int32_t score);
    int32_t get_score();

    void set_wanted_level(int32_t wantedLevel);
    int32_t get_wanted_level();

    int32_t get_ping();
    double get_fps();

    void set_health(float health);
    float get_health();

    void set_armour(float armour);
    float get_armour();

    void set_immunity_flags(int32_t flags);
    int32_t get_immunity_flags();

    void set_position(Vector position);
    Vector get_position();

    void set_speed(Vector speed);
    Vector get_speed();

    void add_speed(Vector speed);

    void set_heading(float heading);
    float get_heading();

    void set_alpha(int32_t alpha, uint32_t fadeTime);
    int32_t get_alpha();

    Vector get_aim_position();
    Vector get_aim_direction();

    bool is_player_on_fire();
    bool is_player_crouching();

    int32_t action();
    int32_t game_key();

    void put_in_vehicle(CVehicle* vehicle);
    void put_in_vehicle_slot(CVehicle* vehicle, int32_t slot);

    void remove_from_vehicle();

    int32_t get_vehicle_status();
    int32_t get_vehicle_slot();

    int32_t give_weapon(int32_t weaponId, int32_t ammo);
    void set_weapon(int32_t weaponId, int32_t ammo);

    int32_t get_weapon();
    int32_t get_weapon_ammo();

    void set_weapon_slot(int32_t slot);
    int32_t get_weapon_slot();

    int32_t get_weapon_at_slot(int32_t slot);
    int32_t get_weapon_ammo_at_slot(int32_t slot);

    void remove_weapon(int32_t weaponId);
    void remove_all_weapons();

    void set_camera(Vector position, Vector look);
    void restore_camera();
    bool is_camera_locked();

    void set_animation(int32_t groupId, int32_t animationId);
    CVehicle* get_standing_vehicle();
    CObject* get_standing_object();

    bool is_away();

    CPlayer* get_spectate_target();
    void set_spectate_target(CPlayer* plr);

    void redirect_to_server(const char* ip, uint32_t port, const char* nick, const char* serverPassword, const char* userPassword);

    void request_module_list();

    void set_frozen(bool toFreeze);
    void set_drive_by_enabled(bool canDb);
    void set_white_scanlines(bool hasWhiteScan);
    void set_green_scanlines(bool hasGreenScan);
    void set_widescreen(bool hasWidescreen);
    void set_on_radar(bool showOnRadar);
    void set_can_attack(bool canAttack);

    bool get_frozen();
    bool get_drive_by_enabled();
    bool get_white_scanlines();
    bool get_green_scanlines();
    bool get_widescreen();
    bool get_on_radar();
    bool get_can_attack();

    bool get_drunk_status();
    void set_drunk_status(bool isDrunk);
    void set_drunk_level(int32_t visuals, int32_t handling);

    void show_markers(bool setMarkers);
    bool is_showning_markers();

    void set_marker(int32_t nDummy);
    void remove_marker();
    bool get_marker_visible();
    void set_marker_visible(bool isVisible);

    bool get_can_use_colors();
    void set_can_use_colors(bool canUse);
};

CPlayer* allocate_player_instance(int32_t gPlayerId);
CPlayer* retrieve_player_instance(int32_t gPlayerId);
void destroy_player_instance(int32_t gPlayerId);