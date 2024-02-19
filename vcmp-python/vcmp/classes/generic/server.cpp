#include "../core.h"

#include "server.h"

void CServerSettings::set_name(char const* name) {
    functions->SetServerName(name);
}

pybind11::str CServerSettings::get_name() {
    char buffer[128];
    functions->GetServerName(buffer, sizeof(buffer));
    return static_cast<pybind11::str>(buffer);
}

void CServerSettings::set_max_players(int32_t maxPlayers) {
    functions->SetMaxPlayers(maxPlayers);
}

int32_t CServerSettings::get_max_players() {
    return functions->GetMaxPlayers();
}

void CServerSettings::set_password(char const* password) {
    functions->SetServerPassword(password);
}

pybind11::str CServerSettings::get_password(){
    char buffer[255];
    functions->GetServerPassword(buffer, sizeof(buffer));
    return static_cast<pybind11::str>(buffer);
}

void CServerSettings::set_game_mode_text(char const* text) {
    functions->SetGameModeText(text);
}

pybind11::str CServerSettings::get_game_mode_text() {
    char buffer[255];
    functions->GetGameModeText(buffer, sizeof(buffer));
    return static_cast<pybind11::str>(buffer);
}

void CServerSettings::shutdown() {
    functions->ShutdownServer();
}

void CServerSettings::ban_ip(char const* ip) {
    functions->BanIP(const_cast<char*>(ip));
}

void CServerSettings::unban_ip(char const* ip) {
    functions->UnbanIP(const_cast<char*>(ip));
}

bool CServerSettings::is_ip_banned(char const* ip) {
    return functions->IsIPBanned(const_cast<char*>(ip)) == 1 ? true : false;
}

int32_t CServerSettings::get_player_id_from_name(char const* name) { 
    return functions->GetPlayerIdFromName(const_cast<char*>(name));
}

PYBIND11_EMBEDDED_MODULE(vcmp_server, module)
{
    pybind11::class_<CServerSettings>(module, "Server")
        .def_static("get_name", &CServerSettings::get_name)
        .def_static("set_name", &CServerSettings::set_name)
        .def_static("set_password", &CServerSettings::get_password)
        .def_static("get_password", &CServerSettings::set_password)
        .def_static("get_game_mode", &CServerSettings::get_game_mode_text)
        .def_static("set_game_mode", &CServerSettings::set_game_mode_text)
        .def_static("get_max_players", &CServerSettings::get_max_players)
        .def_static("set_max_players", &CServerSettings::set_max_players)
        .def_static("shutdown", &CServerSettings::shutdown)
        .def("ban_ip", &CServerSettings::ban_ip)
        .def("ban_ip", &CServerSettings::unban_ip)
        .def("is_ip_banned", &CServerSettings::is_ip_banned)
        .def("get_player_id_from_name", &CServerSettings::get_player_id_from_name);
}