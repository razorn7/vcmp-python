#pragma once
#include "../core.h"

class CServerSettings {
public:
    static void set_name(char const* name);
    static pybind11::str get_name();

    static void set_max_players(int32_t maxPlayers);
    static int32_t get_max_players();

    static void set_password(char const* password);
    static pybind11::str get_password();

    static void set_game_mode_text(char const* text);
    static pybind11::str get_game_mode_text();

    static void shutdown();

    static void ban_ip(char const* ip);
    static void unban_ip(char const* ip);
    static bool is_ip_banned(char const* ip);

    static int32_t get_player_id_from_name(char const* name);
};
