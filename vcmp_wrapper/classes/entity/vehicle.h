#pragma once
#include "player.h"
#include "../main.h"

class CPlayer;
class CVehicle {
public:
    int32_t vehicleId;

    int32_t ID();
    void delete_();

    int32_t get_option(vcmpVehicleOption option);
    void set_option(vcmpVehicleOption option, bool toggle);

    int32_t get_sync_source();
    int32_t get_sync_type();

    bool is_streamed_for_player(CPlayer* plr);

    void set_world(int32_t world);
    int32_t get_world();

    int32_t get_model();

    CPlayer* get_occupant(int32_t slotIndex);

    void respawn();

    void set_immunity_flags(int32_t flags);
    int32_t get_immunity_flags();

    void explode();
    bool is_wrecked();

    void set_position(Vector position);
    Vector get_position();

    void set_rotation(Quaternion rotation);
    void set_rotation_euler(Vector rotation);
    Quaternion get_rotation();
    Vector get_rotation_euler();

    Vector get_speed();
    Vector get_relative_speed();
    Vector get_turn_speed();
    Vector get_relative_turn_speed();

    void add_speed(Vector speed);
    void add_relative_speed(Vector speed);
    void add_turn_speed(Vector speed);
    void add_relative_turn_speed(Vector speed);

    Vector get_spawn_position();
    Quaternion get_spawn_rotation();
    Vector get_spawn_rotation_euler();
    Vector get_turret_rotation();

    void set_spawn_position(Vector pos);
    void set_spawn_rotation(Quaternion angle);
    void set_spawn_rotation_euler(Vector angle);

    void set_idle_respawn_timer(uint32_t millis);
    uint32_t get_idle_respawn_timer();

    void set_health(float health);
    float get_health();

    void set_primary_color(int32_t colour1);
    void set_secondary_color(int32_t colour2);
    int32_t get_primary_color();
    int32_t get_secondary_color();

    int32_t get_part_status(int32_t part);
    void set_part_status(int32_t part, int32_t status);

    int32_t get_tyre_status(int32_t part);
    void set_tyre_status(int32_t part, int32_t status);

    int32_t get_damage();
    void set_damage(int32_t damage);

    int32_t get_radio();
    void set_radio(int32_t damage);

    int32_t set_handling_data(int32_t rule, float value);
    double get_handling_data(int32_t rule);
    void reset_handling_data(int32_t rule);
    void reset_all_handling_data();
    bool is_handling_set(int32_t rule);
};

CVehicle* allocate_vehicle_instance(int32_t vehicleId);
CVehicle* retrieve_vehicle_instance(int32_t vehicleId);
void destroy_vehicle_instance(int32_t vehicleId);