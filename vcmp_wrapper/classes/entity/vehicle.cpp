#include "vehicle.h"
#include "../main.h"
#include <iostream>

std::array<CVehicle*, 1000> vehicleMap;

int32_t CVehicle::ID()
{
    return this->vehicleId;
}

void CVehicle::delete_()
{
    functions->DeleteVehicle(this->vehicleId);
}

int32_t CVehicle::get_option(vcmpVehicleOption option)
{
    return functions->GetVehicleOption(this->vehicleId, option);
}

void CVehicle::set_option(vcmpVehicleOption option, bool toggle)
{
    functions->SetVehicleOption(this->vehicleId, option, toggle == true ? 1 : 0);
}

int32_t CVehicle::get_sync_source()
{
    return functions->GetVehicleSyncSource(this->vehicleId);
}

int32_t CVehicle::get_sync_type()
{
    return functions->GetVehicleSyncType(this->vehicleId);
}

bool CVehicle::is_streamed_for_player(CPlayer* plr)
{
    return functions->IsVehicleStreamedForPlayer(this->vehicleId, plr->playerId) == 1 ? true : false;
}

void CVehicle::set_world(int32_t worldId)
{
    functions->SetVehicleWorld(this->vehicleId, worldId);
}

int32_t CVehicle::get_world()
{
    return functions->GetVehicleWorld(this->vehicleId);
}

int32_t CVehicle::get_model()
{
    return functions->GetVehicleModel(this->vehicleId);
}

CPlayer* CVehicle::get_occupant(int32_t slotIndex)
{
    int32_t playerId = functions->GetVehicleOccupant(this->vehicleId, slotIndex);
    return retrieve_player_instance(playerId);
}

void CVehicle::respawn()
{
    functions->RespawnVehicle(this->vehicleId);
}

void CVehicle::set_immunity_flags(int32_t flags)
{
    functions->SetVehicleImmunityFlags(this->vehicleId, flags);
}

int32_t CVehicle::get_immunity_flags()
{
    return functions->GetVehicleImmunityFlags(this->vehicleId);
}

void CVehicle::explode()
{
    functions->ExplodeVehicle(this->vehicleId);
}

bool CVehicle::is_wrecked()
{
    return functions->IsVehicleWrecked(this->vehicleId) == 1 ? true : false;
}

void CVehicle::set_position(Vector pos)
{
    functions->SetVehiclePosition(this->vehicleId, pos.x, pos.y, pos.z, 0);
}

Vector CVehicle::get_position()
{
    float x, y, z;
    functions->GetVehiclePosition(this->vehicleId, &x, &y, &z);

    return Vector(x, y, z);
}

void CVehicle::set_rotation(Quaternion rotation)
{
    functions->SetVehicleRotation(this->vehicleId, rotation.x, rotation.y, rotation.z, rotation.w);
}

Quaternion CVehicle::get_rotation()
{
    float w, x, y, z;
    functions->GetVehicleRotation(this->vehicleId, &x, &y, &z, &w);

    return Quaternion(x, y, z, w);
}

void CVehicle::set_rotation_euler(Vector rotation)
{
    functions->SetVehicleRotationEuler(this->vehicleId, rotation.x, rotation.y, rotation.z);
}

Vector CVehicle::get_rotation_euler()
{
    float x, y, z;
    functions->GetVehicleRotationEuler(this->vehicleId, &x, &y, &z);

    return Vector(x, y, z);
}

Vector CVehicle::get_speed()
{
    float x, y, z;
    functions->GetVehicleSpeed(this->vehicleId, &x, &y, &z, false);

    return Vector(x, y, z);
}

Vector CVehicle::get_relative_speed()
{
    float x, y, z;
    functions->GetVehicleSpeed(this->vehicleId, &x, &y, &z, true);

    return Vector(x, y, z);
}

Vector CVehicle::get_turn_speed()
{
    float x, y, z;
    functions->GetVehicleTurnSpeed(this->vehicleId, &x, &y, &z, false);

    return Vector(x, y, z);
}

Vector CVehicle::get_relative_turn_speed()
{
    float x, y, z;
    functions->GetVehicleTurnSpeed(this->vehicleId, &x, &y, &z, true);

    return Vector(x, y, z);
}

void CVehicle::add_speed(Vector speed)
{
    functions->SetVehicleSpeed(this->vehicleId, speed.x, speed.y, speed.z, true, false);
}

void CVehicle::add_relative_speed(Vector speed)
{
    functions->SetVehicleSpeed(this->vehicleId, speed.x, speed.y, speed.z, true, true);
}

void CVehicle::add_turn_speed(Vector speed)
{
    functions->SetVehicleTurnSpeed(this->vehicleId, speed.x, speed.y, speed.z, true, false);
}

void CVehicle::add_relative_turn_speed(Vector speed)
{
    functions->SetVehicleTurnSpeed(this->vehicleId, speed.x, speed.y, speed.z, true, true);
}

Vector CVehicle::get_spawn_position()
{
    float x, y, z;
    functions->GetVehicleSpawnPosition(this->vehicleId, &x, &y, &z);

    return Vector(x, y, z);
}

Quaternion CVehicle::get_spawn_rotation()
{
    float x, y, z, w;
    functions->GetVehicleSpawnRotation(this->vehicleId, &x, &y, &z, &w);

    return Quaternion(x, y, z, w);
}

Vector CVehicle::get_spawn_rotation_euler()
{
    float x, y, z;
    functions->GetVehicleSpawnRotationEuler(this->vehicleId, &x, &y, &z);

    return Vector(x, y, z);
}

Vector CVehicle::get_turret_rotation()
{
    float x, y;
    functions->GetVehicleTurretRotation(this->vehicleId, &x, &y);

    return Vector(x, y, 0.0f);
}

void CVehicle::set_spawn_position(Vector pos)
{
    functions->SetVehicleSpawnPosition(this->vehicleId, pos.x, pos.y, pos.z);
}

void CVehicle::set_spawn_rotation(Quaternion angle)
{
    functions->SetVehicleSpawnRotation(this->vehicleId, angle.x, angle.y, angle.z, angle.w);
}

void CVehicle::set_spawn_rotation_euler(Vector angle)
{
    functions->SetVehicleSpawnRotationEuler(this->vehicleId, angle.x, angle.y, angle.z);
}

void CVehicle::set_idle_respawn_timer(uint32_t millis)
{
    functions->SetVehicleIdleRespawnTimer(this->vehicleId, millis);
}

uint32_t CVehicle::get_idle_respawn_timer()
{
    return functions->GetVehicleIdleRespawnTimer(this->vehicleId);
}

void CVehicle::set_health(float health)
{
    functions->SetVehicleHealth(this->vehicleId, health);
}

float CVehicle::get_health()
{
    return functions->GetVehicleHealth(this->vehicleId);
}

void CVehicle::set_primary_color(int32_t colour1)
{
    int oldCol1, col2;
    functions->GetVehicleColour(this->vehicleId, &oldCol1, &col2);
    functions->SetVehicleColour(this->vehicleId, colour1, col2);
}

void CVehicle::set_secondary_color(int32_t colour2)
{
    int col1, oldCol2;
    functions->GetVehicleColour(this->vehicleId, &col1, &oldCol2);
    functions->SetVehicleColour(this->vehicleId, col1, colour2);
}

int32_t CVehicle::get_primary_color()
{
    int col1, col2;
    functions->GetVehicleColour(this->vehicleId, &col1, &col2);

    return col1;
}

int32_t CVehicle::get_secondary_color()
{
    int col1, col2;
    functions->GetVehicleColour(this->vehicleId, &col1, &col2);

    return col2;
}

int32_t CVehicle::get_part_status(int32_t part)
{
    return functions->GetVehiclePartStatus(this->vehicleId, part);
}

void CVehicle::set_part_status(int32_t part, int32_t status)
{
    functions->SetVehiclePartStatus(this->vehicleId, part, status);
}

int32_t CVehicle::get_tyre_status(int32_t tyre)
{
    return functions->GetVehicleTyreStatus(this->vehicleId, tyre);
}

void CVehicle::set_tyre_status(int32_t tyre, int32_t status)
{
    functions->SetVehicleTyreStatus(this->vehicleId, tyre, status);
}

int32_t CVehicle::get_damage()
{
    return functions->GetVehicleDamageData(this->vehicleId);
}

void CVehicle::set_damage(int32_t damage)
{
    functions->SetVehicleDamageData(this->vehicleId, damage);
}

int32_t CVehicle::get_radio()
{
    return functions->GetVehicleRadio(this->vehicleId);
}

void CVehicle::set_radio(int32_t radio)
{
    functions->SetVehicleRadio(this->vehicleId, radio);
}

int32_t CVehicle::set_handling_data(int32_t rule, float value)
{
    return functions->SetInstHandlingRule(this->vehicleId, rule, value);
}

double CVehicle::get_handling_data(int32_t rule)
{
    return functions->GetInstHandlingRule(this->vehicleId, rule);
}

void CVehicle::reset_handling_data(int32_t rule)
{
    functions->ResetInstHandlingRule(this->vehicleId, rule);
}

void CVehicle::reset_all_handling_data()
{
    functions->ResetInstHandling(this->vehicleId);
}

bool CVehicle::is_handling_set(int32_t rule)
{
    return (functions->ExistsInstHandlingRule(this->vehicleId, rule) == 1 ? true : false);
}

CVehicle* allocate_vehicle_instance(int32_t vehicleId)
{
    if (vehicleId < 0 || vehicleId > 1000 - 1)
        return NULL;
    else if (functions->CheckEntityExists(vcmpEntityPoolVehicle, vehicleId) == 0)
        return NULL;
    else if (vehicleMap[vehicleId] != NULL)
        return vehicleMap[vehicleId];

    CVehicle* vehicle = new CVehicle();
    vehicle->vehicleId = vehicleId;

    vehicleMap[vehicle->vehicleId] = vehicle;
    return vehicle;
}

CVehicle* retrieve_vehicle_instance(int32_t vehicleId)
{
    if (vehicleId <= 0 || vehicleId > 1000)
        return NULL;

    return vehicleMap[vehicleId];
}

void destroy_vehicle_instance(int32_t vehicleId)
{
    if (vehicleId <= 0 || vehicleId > 1000)
        return;
    else if (vehicleMap[vehicleId] == NULL)
        return;
    else {
        CVehicle* vehicle = vehicleMap[vehicleId];
        delete vehicle;

        vehicleMap[vehicleId] = NULL;
    }
}

PYBIND11_EMBEDDED_MODULE(vcmp_vehicle, m)
{
    pybind11::class_<CVehicle, std::shared_ptr<CVehicle> >(m, "CVehicle")
        .def(pybind11::init<>())
        .def("delete", &CVehicle::delete_)
        .def("get_option", &CVehicle::get_option)
        .def("set_option", &CVehicle::set_option)
        .def("get_sync_source", &CVehicle::get_sync_source)
        .def("get_sync_type", &CVehicle::get_sync_type)
        .def("is_streamed_for_player", &CVehicle::is_streamed_for_player)
        .def_property("world", &CVehicle::get_world, &CVehicle::set_world)
        .def_property_readonly("model", &CVehicle::get_model)
        .def("get_occupant", &CVehicle::get_occupant)
        .def("respawn", &CVehicle::respawn)
        .def_property("immunity_flags", &CVehicle::get_immunity_flags, &CVehicle::set_immunity_flags)
        .def("explode", &CVehicle::explode)
        .def_property_readonly("is_wrecked", &CVehicle::is_wrecked)
        .def_property("position", &CVehicle::get_position, &CVehicle::set_position)
        .def_property("pos", &CVehicle::get_position, &CVehicle::set_position)
        .def_property("rotation", &CVehicle::get_rotation, &CVehicle::set_rotation)
        .def_property("rot", &CVehicle::get_rotation, &CVehicle::set_rotation)
        .def_property("rotation_euler", &CVehicle::get_rotation_euler, &CVehicle::set_rotation_euler)

        .def("get_speed", &CVehicle::get_speed)
        .def("get_relative_speed", &CVehicle::get_relative_speed)
        .def("get_turn_speed", &CVehicle::get_turn_speed)
        .def("get_relative_turn_speed", &CVehicle::get_relative_turn_speed)

        .def("add_speed", &CVehicle::add_speed)
        .def("add_relative_speed", &CVehicle::add_relative_speed)
        .def("add_turn_speed", &CVehicle::add_turn_speed)
        .def("add_relative_turn_speed", &CVehicle::add_relative_turn_speed)
        .def_property("spawn_position", &CVehicle::get_spawn_position, &CVehicle::set_spawn_position)
        .def_property("spawn_rotation", &CVehicle::get_spawn_rotation, &CVehicle::set_spawn_rotation)
        .def_property("spawn_rotation_euler", &CVehicle::get_spawn_rotation_euler, &CVehicle::set_spawn_rotation_euler)
        .def_property_readonly("turret_rotation", &CVehicle::get_turret_rotation)
        .def_property("idle_respawn_timer", &CVehicle::get_idle_respawn_timer, &CVehicle::set_idle_respawn_timer)
        .def_property("health", &CVehicle::get_health, &CVehicle::set_health)
        .def_property("primary_color", &CVehicle::get_primary_color, &CVehicle::set_primary_color)
        .def_property("secondary_color", &CVehicle::get_secondary_color, &CVehicle::set_secondary_color)
        .def("get_part_status", &CVehicle::get_part_status)
        .def("set_part_status", &CVehicle::set_part_status)
        .def("get_tyre_status", &CVehicle::get_tyre_status)
        .def("set_tyre_status", &CVehicle::set_tyre_status)
        .def_property("damage", &CVehicle::get_damage, &CVehicle::set_damage)
        .def_property("radio", &CVehicle::get_radio, &CVehicle::set_radio)
        .def("set_handling_data", &CVehicle::set_handling_data)
        .def("get_handling_data", &CVehicle::get_handling_data)
        .def("reset_handling_data", &CVehicle::reset_handling_data)
        .def("reset_all_handling_data", &CVehicle::reset_all_handling_data)
        .def("is_handling_set", &CVehicle::is_handling_set);
}