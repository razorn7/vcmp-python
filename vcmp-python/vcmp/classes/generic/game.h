#pragma once
#include "../core.h"
#include "../vcmp/classes/entity/player.h"
#include "../vcmp/classes/entity/vehicle.h"
#include "../vcmp/classes/entity/checkpoint.h"
#include "../vcmp/classes/entity/pickup.h"
#include "../vcmp/classes/entity/object.h"

class CGame {
public:
    static CPlayer* find_player_instance(int id);
    static CPickup* find_pickup_instance(int id);
    static CObject* find_object_instance(int id);
    static CVehicle* find_vehicle_instance(int id);
    static CCheckpoint* find_checkpoint_instance(int id);

    static CVehicle* create_vehicle(int32_t model, int32_t world, Vector* pos, float angle, int32_t col1, int32_t col2);
    static CCheckpoint* create_checkpoint(CPlayer* pPlayer, int32_t world, bool isSphere, Vector* pos, RGBa* color, float radius);
    static CPickup* create_pickup(int32_t model, int32_t world, int32_t quantity, Vector* pos, int32_t alpha, bool isAuto);
    static CObject* create_object(int32_t model, int32_t world, Vector* pos, int32_t alpha);
	
    static void create_radio(int32_t radioId, const char* radioName, const char* radioUrl, uint8_t isListed);
	static void destroy_radio(int32_t radioId);

	static int32_t create_blip(int32_t world, Vector* pos, int32_t scale, RGBa color, int32_t nSpriteId);
	static void destroy_blip(int32_t blipID);

	static void create_explosion(int32_t world, int32_t type, Vector* pos, int32_t playerCaused, bool onGround);

	static void play_sound(int32_t world, int32_t sound, Vector* pos);
	static void play_sound_for_player(CPlayer* player, int32_t sound);
	static void play_sound_for_world(int32_t world, int32_t sound);

    static void set_time_rate(uint32_t time_rate);
    static void set_hour(int32_t hour);
    static void set_minute(int32_t minute);
    static void set_weather(int32_t weather);
    static void set_gravity(float gravity);
    static void set_game_speed(float speed);
    static void set_water_level(float water_level);
    static void set_max_flight_altitude(float max_height);
    static void set_fall_timer(uint16_t time_rate);

    static uint32_t get_time_rate();
    static int32_t get_hour();
    static int32_t get_minute();
    static int32_t get_weather();
    static float get_gravity();
    static float get_game_speed();
    static float get_water_level();
    static float get_max_flight_altitude();
    static uint16_t get_fall_timer();

    static void set_kill_delay(int32_t delay);
    static int get_kill_delay();

    static void toggle_sync_frame_limiter(bool toggle);
    static void toggle_frame_limiter(bool toggle);
    static void toggle_taxi_boost_jump(bool toggle);
    static void toggle_drive_on_water(bool toggle);
    static void toggle_fast_switch(bool toggle);
    static void toggle_friendly_fire(bool toggle);
    static void toggle_disable_driveby(bool toggle);
    static void toggle_perfect_handling(bool toggle);
    static void toggle_flying_cars(bool toggle);
    static void toggle_jump_switch(bool toggle);
    static void toggle_show_on_radar(bool toggle);
    static void toggle_stunt_bike(bool toggle);
    static void toggle_shoot_in_air(bool toggle);
    static void toggle_show_name_tags(bool toggle);
    static void toggle_join_messages(bool toggle);
    static void toggle_death_messages(bool toggle);
    static void toggle_chat_tags_default(bool toggle);
    static void toggle_only_show_team_markers(bool toggle);
    static void toggle_wallglitch(bool toggle);
    static void toggle_disable_backface_culling(bool toggle);
    static void toggle_disable_heli_blade_damage(bool toggle);
    static bool is_sync_frame_limiter_enabled();
    static bool is_frame_limiter_enabled();
    static bool is_taxi_boost_jump_enabled();
    static bool is_drive_on_water_enabled();
    static bool is_fast_switch_enabled();
    static bool is_friendly_fire_enabled();
    static bool is_drive_by_enabled();
    static bool is_perfect_handling_enabled();
    static bool is_flying_cars_enabled();
    static bool is_jump_switch_enabled();
    static bool is_show_on_radar_enabled();
    static bool is_stunt_bike_enabled();
    static bool is_shoot_in_air_enabled();
    static bool is_show_name_tags_enabled();
    static bool is_join_messages_enabled();
    static bool is_death_messages_enabled();
    static bool is_chat_tags_default_enabled();
    static bool is_show_only_team_markers_enabled();
    static bool is_wall_glitch_enabled();
    static bool is_disable_backface_culling_enabled();
    static bool is_disable_heli_blade_damage_enabled();

    static void toggle_use_player_classes(bool toUse);
    static bool is_using_player_classes();
    static void add_player_class(int32_t team, cRGB* colour, int32_t skin, Vector* spawnPos, float spawnAngle, int32_t wep1, int32_t ammo1, int32_t wep2, int32_t ammo2, int32_t wep3, int32_t ammo3);

    static void set_spawn_player_position(Vector* pos);
    static void set_spawn_camera_position(Vector* pos);
    static void set_spawn_camera_look_at(Vector* pos);

    static bool is_world_compatible_with_player(CPlayer* player, int32_t world);

    static void set_world_bounds(float maxX, float minX, float maxY, float minY);
    static Bounds get_world_bounds();
    static void set_wasted_settings(int32_t deathTime, int32_t fadeTime, float fadeInSpeed, float fadeOutSpeed, cRGB colour, int32_t corpseFadeDelay, int32_t corpseFadeTime);
    static WastedSettings get_wasted_settings();
    static void raw_hide_map_object(int32_t nModelId, int16_t x, int16_t y, int16_t z);
    static void hide_map_object(int nModelId, float x, float y, float z);
    static void show_map_object(int nModelId, float x, float y, float z);
    static void show_all_map_objects();
    static void force_select_all_players();
    static void reset_all_vehicle_handlings();
    static bool is_handling_rule_set(int32_t model, int32_t rule);
    static void set_handling_rule(int32_t model, int32_t rule, float value);
    static double get_handling_rule(int32_t model, int32_t rule);
    static void reset_handling_rule(int32_t model, int32_t rule);
    static void reset_vehicle_handling(int32_t model);

    static bool get_cinematic_borders(CPlayer* player);
    static bool get_green_scan_lines(CPlayer* player);
    static bool get_white_scan_lines(CPlayer* player);
    static void set_cinematic_borders(CPlayer* player, bool toEnable);
    static void set_green_scan_lines(CPlayer* player, bool toEnable);
    static void set_white_scan_lines(CPlayer* player, bool toEnable);

    static pybind11::str get_weapon_name_from_model(int weaponID);
    static int get_weapon_model_from_name(char const* name);
    static pybind11::str get_skin_name_from_model(int skinID);
    static int get_skin_model_from_name(char const* name);
    static pybind11::str get_district_name(Vector position);

    static bool set_weapon_data_value(int32_t weaponID, int32_t fieldID, double value);
    static double get_weapon_data_value(int32_t weaponID, int32_t fieldID);
    static bool reset_weapon_data_value(int32_t weaponID, int32_t fieldID);
    static bool is_weapon_data_modified(int32_t weaponID, int32_t fieldID);
    static bool reset_weapon_data(int32_t weaponID);
    static void reset_all_weapon_data();

    static int get_vehicle_model_from_name(char const* name);
    static pybind11::str get_vehicle_name_from_model(int model);
};