#include "game.h"

#undef PlaySound

CPlayer* CGame::find_player_instance(int id) {
    if (id < MAX_PLAYERS && id >= 0) {
        return retrieve_player_instance(id);
    }
    else {
        return NULL;
    }
}

CPickup* CGame::find_pickup_instance(int id) {
    return retrieve_pickup_instance(id);
}

CObject* CGame::find_object_instance(int id) {
    return retrieve_object_instance(id);
}

CVehicle* CGame::find_vehicle_instance(int id) {
    return retrieve_vehicle_instance(id);
}

CCheckpoint* CGame::find_checkpoint_instance(int id) {
    return retrieve_checkpoint_instance(id);
}

CVehicle* CGame::create_vehicle(int32_t model, int32_t world, Vector* pos, float angle, int32_t col1, int32_t col2)
{
    int32_t vId = functions->CreateVehicle(model, world, pos->x, pos->y, pos->z, angle, col1, col2);
    if (vId < 1)
        return NULL;
    else
        return allocate_vehicle_instance(vId);
}

CCheckpoint* CGame::create_checkpoint(CPlayer* pPlayer, int32_t world, bool isSphere, Vector* pos, RGBa* color, float radius)
{
    if (!pos || !color) {
        return NULL;
    }

    int id = (pPlayer ? pPlayer->ID() : -1);

    int cId = functions->CreateCheckPoint(id, world, isSphere, pos->x, pos->y, pos->z, color->r, color->g, color->b, color->a, radius);
    if (cId < 0)
        return NULL;
    else {
        CCheckpoint* pCheckpoint = allocate_checkpoint_instance(cId);
        pCheckpoint->ownerId = id;

        return pCheckpoint;
    }
}

CPickup* CGame::create_pickup(int32_t model, int32_t world, int32_t quantity, Vector* pos, int32_t alpha, bool isAuto)
{
    int pId = functions->CreatePickup(model, world, quantity, pos->x, pos->y, pos->z, alpha, isAuto);
    if (pId < 0)
        return NULL;
    else
        return allocate_pickup_instance(pId);
}

CObject* CGame::create_object(int32_t model, int32_t world, Vector* pos, int32_t alpha)
{
    int oId = functions->CreateObject(model, world, pos->x, pos->y, pos->z, alpha);
    if (oId < 0)
        return NULL;
    else
        return allocate_object_instance(oId);
}

void CGame::create_radio(int32_t radioId, const char* radioName, const char* radioUrl, uint8_t isListed)
{
    functions->AddRadioStream(radioId, radioName, radioUrl, isListed);
}

void CGame::destroy_radio(int32_t radioId)
{
    functions->RemoveRadioStream(radioId);
}

int32_t CGame::create_blip(int32_t world, Vector* pos, int32_t scale, RGBa color, int32_t nSpriteId)
{
    return functions->CreateCoordBlip(-1, world, pos->x, pos->y, pos->z, scale, color.toUInt(), nSpriteId);
}

void CGame::destroy_blip(int32_t blipID)
{
    functions->DestroyCoordBlip(blipID);
}

void CGame::create_explosion(int32_t world, int32_t type, Vector* pos, int32_t playerCaused, bool onGround)
{
    functions->CreateExplosion(world, type, pos->x, pos->y, pos->z, playerCaused, onGround);
}

void CGame::play_sound(int32_t world, int32_t sound, Vector* pos)
{
    functions->PlaySound(world, sound, pos->x, pos->y, pos->z);
}

void CGame::play_sound_for_player(CPlayer* player, int32_t sound)
{
    int32_t unique_world = functions->GetPlayerUniqueWorld(player->playerId);
    functions->PlaySound(unique_world, sound, NAN, NAN, NAN);
}

void CGame::play_sound_for_world(int32_t world, int32_t sound)
{
    functions->PlaySound(world, sound, NAN, NAN, NAN);
}

void CGame::set_time_rate(uint32_t time_rate)
{
    functions->SetTimeRate(time_rate);
}

void CGame::set_hour(int32_t hour)
{
    functions->SetHour(hour);
}

void CGame::set_minute(int32_t minute)
{
    functions->SetMinute(minute);
}

void CGame::set_weather(int32_t weather)
{
    functions->SetWeather(weather);
}

void CGame::set_gravity(float gravity)
{
    functions->SetGravity(gravity);
}

void CGame::set_game_speed(float speed)
{
    functions->SetGameSpeed(speed);
}

void CGame::set_water_level(float water_level)
{
    functions->SetWaterLevel(water_level);
}

void CGame::set_max_flight_altitude(float max_height)
{
    functions->SetMaximumFlightAltitude(max_height);
}

void CGame::set_fall_timer(uint16_t time_rate)
{
    functions->SetFallTimer(time_rate);
}

uint32_t CGame::get_time_rate()
{
    return (functions->GetTimeRate());
}

int32_t CGame::get_hour()
{
    return (functions->GetHour());
}

int32_t CGame::get_minute()
{
    return (functions->GetMinute());
}

int32_t CGame::get_weather()
{
    return (functions->GetWeather());
}

float CGame::get_gravity()
{
    return (functions->GetGravity());
}
float CGame::get_game_speed()
{
    return (functions->GetGameSpeed());
}
float CGame::get_water_level()
{
    return (functions->GetWaterLevel());
}
float CGame::get_max_flight_altitude()
{
    return (functions->GetMaximumFlightAltitude());
}

uint16_t CGame::get_fall_timer()
{
    return (functions->GetFallTimer());
}

void CGame::set_kill_delay(int32_t delay)
{
    functions->SetKillCommandDelay(delay);
}

int CGame::get_kill_delay()
{
    return functions->GetKillCommandDelay();
}

void CGame::toggle_sync_frame_limiter(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionSyncFrameLimiter, (toggle ? 1 : 0));
}
void CGame::toggle_frame_limiter(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionFrameLimiter, (toggle ? 1 : 0));
}
void CGame::toggle_taxi_boost_jump(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionTaxiBoostJump, (toggle ? 1 : 0));
}
void CGame::toggle_drive_on_water(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionDriveOnWater, (toggle ? 1 : 0));
}
void CGame::toggle_fast_switch(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionFastSwitch, (toggle ? 1 : 0));
}
void CGame::toggle_friendly_fire(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionFriendlyFire, (toggle ? 1 : 0));
}
void CGame::toggle_disable_driveby(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionDisableDriveBy, (toggle ? 1 : 0));
}
void CGame::toggle_perfect_handling(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionPerfectHandling, (toggle ? 1 : 0));
}
void CGame::toggle_flying_cars(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionFlyingCars, (toggle ? 1 : 0));
}
void CGame::toggle_jump_switch(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionJumpSwitch, (toggle ? 1 : 0));
}
void CGame::toggle_show_on_radar(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionShowMarkers, (toggle ? 1 : 0));
}
void CGame::toggle_stunt_bike(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionStuntBike, (toggle ? 1 : 0));
}
void CGame::toggle_shoot_in_air(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionShootInAir, (toggle ? 1 : 0));
}
void CGame::toggle_show_name_tags(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionShowNameTags, (toggle ? 1 : 0));
}
void CGame::toggle_join_messages(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionJoinMessages, (toggle ? 1 : 0));
}
void CGame::toggle_death_messages(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionDeathMessages, (toggle ? 1 : 0));
}
void CGame::toggle_chat_tags_default(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionChatTagsEnabled, (toggle ? 1 : 0));
}
void CGame::toggle_only_show_team_markers(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionOnlyShowTeamMarkers, (toggle ? 1 : 0));
}
void CGame::toggle_wallglitch(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionWallGlitch, (toggle ? 1 : 0));
}
void CGame::toggle_disable_backface_culling(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionDisableBackfaceCulling, (toggle ? 1 : 0));
}
void CGame::toggle_disable_heli_blade_damage(bool toggle)
{
    functions->SetServerOption(vcmpServerOptionDisableHeliBladeDamage, (toggle ? 1 : 0));
}

bool CGame::is_sync_frame_limiter_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionSyncFrameLimiter) != 0);
}
bool CGame::is_frame_limiter_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionFrameLimiter) != 0);
}
bool CGame::is_taxi_boost_jump_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionTaxiBoostJump) != 0);
}
bool CGame::is_drive_on_water_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionDriveOnWater) != 0);
}
bool CGame::is_fast_switch_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionFastSwitch) != 0);
}
bool CGame::is_friendly_fire_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionFriendlyFire) != 0);
}
bool CGame::is_drive_by_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionDisableDriveBy) == 0);
}
bool CGame::is_perfect_handling_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionPerfectHandling) != 0);
}
bool CGame::is_flying_cars_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionFlyingCars) != 0);
}
bool CGame::is_jump_switch_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionJumpSwitch) != 0);
}
bool CGame::is_show_on_radar_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionShowMarkers) != 0);
}
bool CGame::is_stunt_bike_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionStuntBike) != 0);
}
bool CGame::is_shoot_in_air_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionShootInAir) != 0);
}
bool CGame::is_show_name_tags_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionShowNameTags) != 0);
}
bool CGame::is_join_messages_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionJoinMessages) != 0);
}
bool CGame::is_death_messages_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionDeathMessages) != 0);
}
bool CGame::is_chat_tags_default_enabled()
{
    return (functions->GetServerOption(vcmpServerOptionChatTagsEnabled) != 0);
}
bool CGame::is_show_only_team_markers_enabled()
{
    return functions->GetServerOption(vcmpServerOptionOnlyShowTeamMarkers) != 0;
}
bool CGame::is_wall_glitch_enabled()
{
    return functions->GetServerOption(vcmpServerOptionWallGlitch) != 0;
}
bool CGame::is_disable_backface_culling_enabled()
{
    return functions->GetServerOption(vcmpServerOptionDisableBackfaceCulling) != 0;
}
bool CGame::is_disable_heli_blade_damage_enabled()
{
    return functions->GetServerOption(vcmpServerOptionDisableHeliBladeDamage) != 0;
}

void CGame::toggle_use_player_classes(bool toUse)
{
    functions->SetServerOption(vcmpServerOptionUseClasses, toUse);
}

bool CGame::is_using_player_classes()
{
    return (functions->GetServerOption(vcmpServerOptionUseClasses) != 0);
}

void CGame::add_player_class(int32_t team, cRGB* colour, int32_t skin, Vector* spawnPos, float spawnAngle, int32_t wep1, int32_t ammo1, int32_t wep2, int32_t ammo2, int32_t wep3, int32_t ammo3)
{
    functions->AddPlayerClass(team, colour->toUInt(), skin, spawnPos->x, spawnPos->y, spawnPos->z, spawnAngle, wep1, ammo1, wep2, ammo2, wep3, ammo3);
}

void CGame::set_spawn_player_position(Vector* pos)
{
    functions->SetSpawnPlayerPosition(pos->x, pos->y, pos->z);
}

void CGame::set_spawn_camera_position(Vector* pos)
{
    functions->SetSpawnCameraPosition(pos->x, pos->y, pos->z);
}

void CGame::set_spawn_camera_look_at(Vector* pos)
{
    functions->SetSpawnCameraLookAt(pos->x, pos->y, pos->z);
}

bool CGame::is_world_compatible_with_player(CPlayer* player, int32_t world)
{
    if (player != NULL)
        return (functions->IsPlayerWorldCompatible(player->playerId, world) != 0);

    return false;
}

void CGame::set_world_bounds(float maxX, float minX, float maxY, float minY)
{
    functions->SetWorldBounds(maxX, minX, maxY, minY);
}

Bounds CGame::get_world_bounds()
{
    float maxX, minX, maxY, minY;
    functions->GetWorldBounds(&maxX, &minX, &maxY, &minY);

    return Bounds(maxX, minX, maxY, minY);
}

void CGame::set_wasted_settings(int32_t deathTime, int32_t fadeTime, float fadeInSpeed, float fadeOutSpeed, cRGB colour, int32_t corpseFadeDelay, int32_t corpseFadeTime)
{
    unsigned int rDeathTime, rFadeTime, rCorpseFadeDelay, rCorpseFadeTime;

    rDeathTime = static_cast<unsigned int>(deathTime);
    rFadeTime = static_cast<unsigned int>(fadeTime);
    rCorpseFadeDelay = static_cast<unsigned int>(corpseFadeDelay);
    rCorpseFadeTime = static_cast<unsigned int>(corpseFadeTime);

    functions->SetWastedSettings(
        rDeathTime,
        rFadeTime,
        fadeInSpeed,
        fadeOutSpeed,
        colour.toUInt(),
        rCorpseFadeDelay,
        rCorpseFadeTime);
}

WastedSettings CGame::get_wasted_settings()
{
    unsigned int deathTime, fadeTime, corpseFadeDelay, corpseFadeTime, dwColour;
    float fadeInSpeed, fadeOutSpeed;

    functions->GetWastedSettings(
        &deathTime,
        &fadeTime,
        &fadeInSpeed,
        &fadeOutSpeed,
        &dwColour,
        &corpseFadeDelay,
        &corpseFadeTime);

    int rDeathTime, rFadeTime, rCorpseFadeDelay, rCorpseFadeTime;
    cRGB rColour;

    rDeathTime = static_cast<int>(deathTime);
    rFadeTime = static_cast<int>(fadeTime);
    rCorpseFadeDelay = static_cast<int>(corpseFadeDelay);
    rCorpseFadeTime = static_cast<int>(corpseFadeTime);

    rColour.r = (dwColour >> 16) & 255;
    rColour.g = (dwColour >> 8) & 255;
    rColour.b = dwColour & 255;

    return WastedSettings(
        rDeathTime,
        rFadeTime,
        fadeInSpeed,
        fadeOutSpeed,
        rColour,
        rCorpseFadeDelay,
        rCorpseFadeTime);
}

void CGame::raw_hide_map_object(int32_t nModelId, int16_t x, int16_t y, int16_t z)
{
    functions->HideMapObject(nModelId, x, y, z);
}

void CGame::hide_map_object(int nModelId, float x, float y, float z)
{
    int x2 = (int)(floor(x * 10.0f) + 0.5f);
    int y2 = (int)(floor(y * 10.0f) + 0.5f);
    int z2 = (int)(floor(z * 10.0f) + 0.5f);

    functions->HideMapObject(nModelId, x2, y2, z2);
}

void CGame::show_map_object(int nModelId, float x, float y, float z)
{
    int x2 = (int)(floor(x * 10.0f) + 0.5f);
    int y2 = (int)(floor(y * 10.0f) + 0.5f);
    int z2 = (int)(floor(z * 10.0f) + 0.5f);

    functions->ShowMapObject(nModelId, x2, y2, z2);
}

void CGame::show_all_map_objects()
{
    functions->ShowAllMapObjects();
}

void CGame::force_select_all_players()
{
    functions->ForceAllSelect();
}

void CGame::reset_all_vehicle_handlings()
{
    functions->ResetAllVehicleHandlings();
}

bool CGame::is_handling_rule_set(int32_t model, int32_t rule)
{
    return (functions->ExistsHandlingRule(model, rule) != 0);
}

void CGame::set_handling_rule(int32_t model, int32_t rule, float value)
{
    functions->SetHandlingRule(model, rule, value);
}

double CGame::get_handling_rule(int32_t model, int32_t rule)
{
    return functions->GetHandlingRule(model, rule);
}

void CGame::reset_handling_rule(int32_t model, int32_t rule)
{
    functions->ResetHandlingRule(model, rule);
}

void CGame::reset_vehicle_handling(int32_t model)
{
    functions->ResetHandling(model);
}

bool CGame::get_cinematic_borders(CPlayer* player)
{
    if (player != NULL)
        return (functions->GetPlayerOption(player->playerId, vcmpPlayerOptionWidescreen) != 0);

    return false;
}

bool CGame::get_green_scan_lines(CPlayer* player)
{
    if (player != NULL)
        return (functions->GetPlayerOption(player->playerId, vcmpPlayerOptionGreenScanlines) != 0);

    return false;
}

bool CGame::get_white_scan_lines(CPlayer* player)
{
    if (player != NULL)
        return (functions->GetPlayerOption(player->playerId, vcmpPlayerOptionWhiteScanlines) != 0);

    return false;
}

void CGame::set_cinematic_borders(CPlayer* player, bool toEnable)
{
    if (player != NULL)
        functions->SetPlayerOption(player->playerId, vcmpPlayerOptionWidescreen, toEnable);
}

void CGame::set_green_scan_lines(CPlayer* player, bool toEnable)
{
    if (player != NULL)
        functions->SetPlayerOption(player->playerId, vcmpPlayerOptionGreenScanlines, toEnable);
}

void CGame::set_white_scan_lines(CPlayer* player, bool toEnable)
{
    if (player != NULL)
        functions->SetPlayerOption(player->playerId, vcmpPlayerOptionWhiteScanlines, toEnable);
}

pybind11::str CGame::get_weapon_name_from_model(int weaponID)
{
    switch (weaponID) {
    case 0:
        return "Unarmed";
    case 1:
        return "Brass Knuckles";
    case 2:
        return "Screwdriver";
    case 3:
        return "Golf Club";
    case 4:
        return "Nightstick";
    case 5:
        return "Knife";
    case 6:
        return "Baseball Bat";
    case 7:
        return "Hammer";
    case 8:
        return "Meat Cleaver";
    case 9:
        return "Machete";
    case 10:
        return "Katana";
    case 11:
        return "Chainsaw";
    case 12:
        return "Grenade";
    case 13:
        return "Remote Detonation Grenade";
    case 14:
        return "Tear Gas";
    case 15:
        return "Molotov Cocktails";
    case 16:
        return "Rocket";
    case 17:
        return "Colt .45";
    case 18:
        return "Python";
    case 19:
        return "Pump-Action Shotgun";
    case 20:
        return "SPAS-12 Shotgun";
    case 21:
        return "Stubby Shotgun";
    case 22:
        return "TEC-9";
    case 23:
        return "Uzi";
    case 24:
        return "Silenced Ingram";
    case 25:
        return "MP5";
    case 26:
        return "M4";
    case 27:
        return "Ruger";
    case 28:
        return "Sniper Rifle";
    case 29:
        return "Laserscope Sniper Rifle";
    case 30:
        return "Rocket Launcher";
    case 31:
        return "Flamethrower";
    case 32:
        return "M60";
    case 33:
        return "Minigun";
    case 34:
        return "Explosion";
    case 35:
        return "Helicannon";
    case 36:
        return "Camera";
    case 39:
        return "Vehicle";
    case 41:
        return "Explosion";
    case 42:
        return "Driveby";
    case 43:
        return "Drowned";
    case 44:
        return "Fall";
    case 51:
        return "Explosion";
    case 70:
        return "Suicide";
    default:
        return "Unknown";
    }
}

pybind11::str CGame::get_district_name(Vector position)
{
    float x = position.x;
    float y = position.y;
    if (x > -1613.03f && y > 413.218f && x < -213.73f && y < 1677.32f)
        return "Downtown Vice City";
    else if (x > 163.656f && y > -351.153f && x < 1246.03f && y < 1398.85f)
        return "Vice Point";
    else if (x > -103.97f && y > -930.526f && x < 1246.03f && y < -351.153f)
        return "Washington Beach";
    else if (x > -253.206f && y > -1805.37f && x < 1254.9f && y < -930.526f)
        return "Ocean Beach";
    else if (x > -1888.21f && y > -1779.61f && x < -1208.21f && y < 230.39f)
        return "Escobar International Airport";
    else if (x > -748.206f && y > -818.266f && x < -104.505f && y < -241.467f)
        return "Starfish Island";
    else if (x > -213.73f && y > 797.605f && x < 163.656f && y < 1243.47f)
        return "Prawn Island";
    else if (x > -213.73f && y > -241.429f && x < 163.656f && y < 797.605f)
        return "Leaf Links";
    else if (x > -1396.76f && y > -42.9113f && x < -1208.21f && y < 230.39f)
        return "Junkyard";
    else if (x > -1208.21f && y > -1779.61f && x < -253.206f && y < -898.738f)
        return "Viceport";
    else if (x > -1208.21f && y > -898.738f && x < -748.206f && y < -241.467f)
        return "Little Havana";
    else if (x > -1208.21f && y > -241.467f && x < -578.289f && y < 412.66f)
        return "Little Haiti";
    else
        return "Vice City";
}

int CGame::get_skin_model_from_name(char const* name)
{
    // Verify that the name is valid and could actually represent a skin name
    if (name == NULL || strlen(name) < 1)
        return SKIN_ID_UNKNOWN;

    // Create a temporary variable that will hold the actual ID
    int id = SKIN_ID_UNKNOWN;

    // Allocate memory for an editable version of the string
    char* str = (char*)malloc(strlen(name) + 1);

    // Verify that the memory could be allocated and prepare the string
    if (str != NULL) {
        int i, j = 0;
        // Convert the string to lowercase and remove non alpha-numeric characters
        for (i = 0; name[i]; i++) {
            if (isalnum(name[i]) != 0) {
                str[j] = tolower(name[i]);
                j++;
            }
        }
        // Add the null character to the final string
        str[j] = '\0';
        // Make sure the string had any valid characters
        if (strlen(str) < 1) {
            // Free the previously allocated resources
            free(str);
            // Return the found ID
            return id;
        }
    }
    // No point in going forward
    else
        return id;

    // Grab the actual length of the string
    int len = strlen(str);

    // Get the most significant characters used to identify a skin
    char a, b, c, d;
    a = tolower(name[0]);
    b = 0;
    c = 0;
    d = tolower(str[len - 1]);

    // Look for deeper specifiers
    if (strlen(name) >= 3) {
        b = tolower(name[1]);
        c = tolower(name[2]);
    }
    else if (strlen(name) >= 2) {
        b = tolower(name[1]);
    }

    // Search for a pattern in the name
    switch (a) {
        // [A]lex Srub, [A]rabic guy, [A]rmy
    case 'a':
        switch (b) {
            // [Al]ex [S]rub
        case 'l':
        case 's':
            id = SKIN_ID_ALEX_SRUB;
            break;
            // [A]rabic [g]uy
        case 'g':
            id = SKIN_ID_ARABIC_GUY;
            break;
            // [Ara]bic guy, [Arm]y
        case 'r':
            if (c && c == 'a')
                id = SKIN_ID_ARABIC_GUY;
            else if (c && c == 'm')
                id = SKIN_ID_ARMY;
            break;
        }
        break;
        // [B]each guy (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)/(#8|H)
        // [B]each lady (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)
        // [B]iker (#1|A)/(#2|B)
        // [B]um guy (#1|A)/(#2|B)/(#3|C)
        // [B]um lady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
        // [B]usiness man (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
    case 'b':
        // [Be]ach [g]uy (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)/(#8|H)
        if (b && b == 'e' && ((c && c == 'g') || (len >= 6 && str[5] == 'g'))) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_BEACH_GUY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_BEACH_GUY_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_BEACH_GUY_C;
                break;
            case '4':
            case 'd':
                id = SKIN_ID_BEACH_GUY_D;
                break;
            case '5':
            case 'e':
                id = SKIN_ID_BEACH_GUY_E;
                break;
            case '6':
            case 'f':
                id = SKIN_ID_BEACH_GUY_F;
                break;
            case '7':
            case 'g':
                id = SKIN_ID_BEACH_GUY_G;
                break;
            case '8':
            case 'h':
                id = SKIN_ID_BEACH_GUY_H;
                break;
            }
        }
        // [Be]ach [l]ady (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)/(#7|G)
        else if (b && b == 'e' && ((c && c == 'l') || (len >= 6 && str[5] == 'l'))) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_BEACH_LADY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_BEACH_LADY_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_BEACH_LADY_C;
                break;
            case '4':
            case 'd':
                id = SKIN_ID_BEACH_LADY_D;
                break;
            case '5':
            case 'e':
                id = SKIN_ID_BEACH_LADY_E;
                break;
            case '6':
            case 'f':
                id = SKIN_ID_BEACH_LADY_F;
                break;
            case '7':
            case 'g':
                id = SKIN_ID_BEACH_LADY_G;
                break;
            }
        }
        // [Bi]ker (#1|A)/(#2|B)
        else if (b && b == 'i' && (d == '1' || d == 'a'))
            id = SKIN_ID_BIKER_A;
        else if (b && b == 'i' && (d == '2' || d == 'b'))
            id = SKIN_ID_BIKER_B;
        // [Bum] [g]uy (#1|A)/(#2|B)/(#3|C)
        // [Bum] [l]ady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
        else if (b && b == 'u' && (c && (c == 'm' || c == 'g' || c == 'l'))) {
            // [Bum] [g]uy (#1|A)/(#2|B)/(#3|C)
            if (c == 'g' || (len >= 4 && str[3] == 'g')) {
                if (d == '1' || d == 'a')
                    id = SKIN_ID_BUM_GUY_A;
                else if (d == '2' || d == 'b')
                    id = SKIN_ID_BUM_GUY_B;
                else if (d == '3' || d == 'c')
                    id = SKIN_ID_BUM_GUY_C;
            }
            // [Bum] [l]ady (#1|A)/(#2|B)/(#2|C)/(#3|D)/(#4|E)
            else if (c == 'l' || (len >= 4 && str[3] == 'l')) {
                if (d == '1' || d == 'a')
                    id = SKIN_ID_BUM_LADY_A;
                else if (d == '2' || d == 'b')
                    id = SKIN_ID_BUM_LADY_B;
                else if (d == '2' || d == 'c')
                    id = SKIN_ID_BUM_LADY_C;
                else if (d == '3' || d == 'd')
                    id = SKIN_ID_BUM_LADY_D;
                else if (d == '4' || d == 'e')
                    id = SKIN_ID_BUM_LADY_E;
            }
        }
        // [Bus]iness [m]an (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
        else if (b && b == 'u' && ((c && c == 's') || (len >= 10 && str[9] == 'm'))) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_BUSINESS_MAN_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_BUSINESS_MAN_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_BUSINESS_MAN_C;
                break;
            case '4':
            case 'd':
                id = SKIN_ID_BUSINESS_MAN_D;
                break;
            case '5':
            case 'e':
                id = SKIN_ID_BUSINESS_MAN_E;
                break;
            case '6':
            case 'f':
                id = SKIN_ID_BUSINESS_MAN_F;
                break;
            }
        }
        break;
        // [C]am, [C]am (Robber), [C]andy Suxx, [C]hef
        // [C]hurch guy, [C]hurch lady, [C]lub lady
        // [C]olumbian guy (#1|A)/(#2|B),
        // [C]onstruction worker (#1|A)/(#2|B)
        // [C]ool guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
        // [C]op, [C]ortez
        // [C]riminal (#1|A)/(#2|B)
        // [C]uban (#1|A)/(#2|B)
    case 'c':
        // [Ca]m, [Ca]m (Robber), [Ca]ndy Suxx
        if (b && b == 'a') {
            // [Cam] ([R]obbe[r])
            if (c && (c == 'm' || c == 'r') && d == 'r')
                id = SKIN_ID_CAM_ROBBER;
            // [Cam]
            else if (c && c == 'm')
                id = SKIN_ID_CAM;
            // [Can]dy [S]ux[x]
            else if (c && (c == 'n' || c == 's' || d == 'x'))
                id = SKIN_ID_CANDY_SUXX;
        }
        // [Ch]ef, [Ch]urch guy, [Ch]urch lady
        else if (b && b == 'h') {
            // [Che][f]
            if (c && (c == 'e' || d == 'f'))
                id = SKIN_ID_CHEF;
            // [Chu]rch [g]uy
            else if (c && ((c == 'u' && len >= 7 && str[6] == 'g') || (c == 'g')))
                id = SKIN_ID_CHURCH_GUY;
            // [Chu]rch [l]ady
            else if (c && ((c == 'u' && len >= 7 && str[6] == 'l') || (c == 'l')))
                id = SKIN_ID_CHURCH_LADY;
        }
        // [Cl]ub [l]ady
        else if (b && b == 'l')
            id = SKIN_ID_CLUB_LADY;
        // [Co]lumbian guy (#1|A)/(#2|B)
        // [Co]nstruction worker (#1|A)/(#2|B)
        // [Co]ol guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
        // [Co]p, [Co]rtez
        else if (b && b == 'o') {
            // [Col]umbian [g]uy (#1|A)/(#2|B)
            if (c && ((c == 'l' && len >= 10 && str[9] == 'g') || (c == 'g'))) {
                if (d == '1' || d == 'a')
                    id = SKIN_ID_COLUMBIAN_GUY_A;
                else if (d == '2' || d == 'b')
                    id = SKIN_ID_COLUMBIAN_GUY_B;
            }
            // [Con]struction [w]orker (#1|A)/(#2|B)
            else if (c && (c == 'n' || (len >= 13 && str[12] == 'g'))) {
                if (d == '1' || d == 'a')
                    id = SKIN_ID_CONSTRUCTION_WORKER_A;
                else if (d == '2' || d == 'b')
                    id = SKIN_ID_CONSTRUCTION_WORKER_B;
            }
            // [Coo]l guy (#1|A)/(#2|B)/(#3|C)/(#4|D)
            else if (c && c == 'o') {
                switch (d) {
                case '1':
                case 'a':
                    id = SKIN_ID_COOL_GUY_A;
                    break;
                case '2':
                case 'b':
                    id = SKIN_ID_COOL_GUY_B;
                    break;
                case '3':
                case 'c':
                    id = SKIN_ID_COOL_GUY_C;
                    break;
                case '4':
                case 'd':
                    id = SKIN_ID_COOL_GUY_D;
                    break;
                }
            }
            // [Cop]
            else if (c && c == 'p')
                id = SKIN_ID_COP;
            // [Cor]te[z]
            else if (c && (c == 'r' || c == 'z' || d == 'z'))
                id = SKIN_ID_CORTEZ;
        }
        // [Cr]iminal (#1|A)/(#2|B)
        else if (b && b == 'r' && (d == '1' || d == 'a'))
            id = SKIN_ID_CRIMINAL_A;
        else if (b && b == 'r' && (d == '2' || d == 'b'))
            id = SKIN_ID_CRIMINAL_B;
        // [Cu]ban (#1|A)/(#2|B)
        else if (b && b == 'u' && (d == '1' || d == 'a'))
            id = SKIN_ID_CUBAN_A;
        else if (b && b == 'u' && (d == '2' || d == 'b'))
            id = SKIN_ID_CUBAN_B;
        break;
        // [D]BP security (#1|A)/(#2|B)
        // [D]iaz guy (#1|A)/(#2|B)
    case 'd':
        switch (b) {
            // [DB]P [s]ecurity (#1|A)/(#2|B)
        case 'b':
        case 's':
            if (d == '1' || d == 'a')
                id = SKIN_ID_DBP_SECURITY_A;
            else if (d == '2' || d == 'b')
                id = SKIN_ID_DBP_SECURITY_B;
            break;
            // [Di]a[z] [g]uy (#1|A)/(#2|B)
        case 'i':
        case 'z':
        case 'g':
            if (d == '1' || d == 'a')
                id = SKIN_ID_DIAZ_GUY_A;
            else if (d == '2' || d == 'b')
                id = SKIN_ID_DIAZ_GUY_B;
            break;
        }
        break;
        // [F]BI, [F]ireman, [F]ood lady, [F]rench guy
    case 'f':
        switch (b) {
            // [FB]I
        case 'b':
            id = SKIN_ID_FBI;
            break;
            // [Fi]re[m]an
        case 'i':
        case 'm':
            id = SKIN_ID_FIREMAN;
            break;
            // [Fo]od [l]ady
        case 'o':
        case 'l':
            id = SKIN_ID_FOOD_LADY;
            break;
            // [Fr]ench [g]uy
        case 'r':
        case 'g':
            id = SKIN_ID_FRENCH_GUY;
            break;
        }
        break;
        // [G]arbageman (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
        // [G]olf guy (#1|A)/(#2|B)/(#3|C)
        // [G]olf lady
        // [G]ranny (#1|A)/(#2|B)
        // [G]ym guy, [G]ym lady
    case 'g':
        // [Ga]rbage[m]an (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
        if (b && (b == 'a' || b == 'm')) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_GARBAGEMAN_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_GARBAGEMAN_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_GARBAGEMAN_C;
                break;
            case '4':
            case 'd':
                id = SKIN_ID_GARBAGEMAN_D;
                break;
            case '5':
            case 'e':
                id = SKIN_ID_GARBAGEMAN_E;
                break;
            }
        }
        // [Go]lf [g]uy (#1|A)/(#2|B)/(#3|C)
        else if (b && b == 'o' && ((c && c == 'g') || (len >= 5 && str[4] == 'g'))) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_GOLF_GUY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_GOLF_GUY_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_GOLF_GUY_C;
                break;
            }
        }
        // [Go]lf [l]ady
        else if (b && b == 'o' && ((c && c == 'l') || (len >= 5 && str[4] == 'l')))
            id = SKIN_ID_GOLF_LADY;
        // [Gr]anny (#1|A)/(#2|B)
        else if (b && b == 'r') {
            if (d == '1' || d == 'a')
                id = SKIN_ID_GRANNY_A;
            else if (d == '2' || d == 'b')
                id = SKIN_ID_GRANNY_B;
        }
        // [Gy]m [g]uy
        else if (b && (b == 'g' || (b == 'y' && len >= 4 && str[3] == 'g')))
            id = SKIN_ID_GYM_GUY;
        // [Gy]m [l]ady
        else if (b && (b == 'l' || (b == 'y' && len >= 4 && str[3] == 'l')))
            id = SKIN_ID_GYM_LADY;
        break;
        // [H]atian (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
        // [H]ilary, [H]ilary (Robber), [H]ood lady
    case 'h':
        // [H]atian (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)
        if (b && b == 'a') {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_HATIAN_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_HATIAN_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_HATIAN_C;
                break;
            case '4':
            case 'd':
                id = SKIN_ID_HATIAN_D;
                break;
            case '5':
            case 'e':
                id = SKIN_ID_HATIAN_E;
                break;
            }
        }
        // [Hi]lary ([R]obbe[r])
        else if (b && (b == 'i' || b == 'r') && d == 'r')
            id = SKIN_ID_HILARY_ROBBER;
        // [Hi]lary
        else if (b && b == 'i')
            id = SKIN_ID_HILARY;
        // [Ho]od [l]ady
        if (b && (b == 'o' || b == 'l'))
            id = SKIN_ID_HOOD_LADY;
        break;
        // [K]en Rosenburg
    case 'k':
        id = SKIN_ID_KEN_ROSENBURG;
        break;
        // [L]ance (#1|A)/(#1|B)
        // [L]ance (Cop)
        // [L]awyer
        // [L]ove Fist (#1|A)/(#2|B)/(#3|C)/(#3|D)
    case 'l':
        //[Lan]ce ([C]o[p])
        if ((b && b == 'a') && (c && c == 'n') && ((len >= 6 && str[5] == 'c') || d == 'p'))
            id = SKIN_ID_LANCE_COP;
        else if (b && (b == 'c' || (b == 'a' && (c && c == 'n'))))
            id = SKIN_ID_LANCE_COP;
        // [La]nce (#1|A)/(#1|B)
        else if (b && b == 'a' && c && c == 'n') {
            if (d == '1' || d == 'a')
                id = SKIN_ID_LANCE_A;
            else if (d == '2' || d == 'b')
                id = SKIN_ID_LANCE_B;
        }
        // [Law]yer
        else if (b && (b == 'w' || (b == 'a' && c && c == 'w')))
            id = SKIN_ID_LAWYER;
        // [Lo]ve [F]ist (#1|A)/(#2|B)/(#3|C)/(#3|D)
        else if (b && (b == 'o' || b == 'f')) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_LOVE_FIST_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_LOVE_FIST_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_LOVE_FIST_C;
                break;
            case 'd':
                id = SKIN_ID_LOVE_FIST_D;
                break;
            }
        }
        break;
        // [M]ercades
    case 'm':
        if (d == 'b')
            id = SKIN_ID_MERCADES_B;
        else
            id = SKIN_ID_MERCADES_A;
        break;
        // [O]ffice lady (#1|A)/(#2|B)
    case 'o':
        if (d == '1' || d == 'a')
            id = SKIN_ID_OFFICE_LADY_A;
        else if (d == '2' || d == 'b')
            id = SKIN_ID_OFFICE_LADY_B;
        break;
        // [P]aramedic, [P]hil,  [P]hil (One arm), [P]hil (Robber)
        // [P]imp, [P]izzaman
        // [P]rostitute (#1|A)/(#2|B)/(#2|C)/(#2|D)/(#3|D)/(#4|D)
        // [P]unk (#1|A)/(#2|B)/(#3|C)
    case 'p':
        // [Pa]ramedic
        if (b && b == 'a')
            id = SKIN_ID_PARAMEDIC;
        // [Ph]il (One arm), [Ph]il (Robber)
        else if (b && b == 'h') {
            // [Ph]il ([O]ne ar[m])
            if (b == 'o' || (c && c == 'o') || (len >= 5 && str[4] == 'o') || d == 'm')
                id = SKIN_ID_PHIL_ONE_ARM;
            // [Ph]il ([R]obbe[r])
            else if (c && (c == 'r' || d == 'r' || (len >= 5 && str[4] == 'r')))
                id = SKIN_ID_PHIL_ROBBER;
            // [Phi]l
            else if (c && c == 'i')
                id = SKIN_ID_PHIL;
        }
        // [Pim][p]
        else if (b && b == 'i' && ((c && c == 'm') || d == 'p'))
            id = SKIN_ID_PIMP;
        // [Piz]zama[n]
        else if (b && b == 'i' && ((c && c == 'z') || d == 'n'))
            id = SKIN_ID_PIZZAMAN;
        // [Pr]ostitute (#1|A)/(#2|B)/(#2|C)/(#2|D)/(#3|D)/(#4|D)
        else if (b && b == 'r') {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_PROSTITUTE_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_PROSTITUTE_B;
                break;
            case 'c':
                id = SKIN_ID_PROSTITUTE_C;
                break;
            case 'd':
                id = SKIN_ID_PROSTITUTE_D;
                break;
            case '3':
            case 'e':
                id = SKIN_ID_PROSTITUTE_E;
                break;
            case '4':
            case 'f':
                id = SKIN_ID_PROSTITUTE_F;
                break;
            }
        }
        // [Pu]nk (#1|A)/(#2|B)/(#3|C)
        else if (b && b == 'u') {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_PUNK_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_PUNK_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_PUNK_C;
                break;
            }
        }
        break;
        // [R]ich guy, [R]ockstar guy
    case 'r':
        // [Ri]ch guy
        if (b && b == 'i')
            id = SKIN_ID_RICH_GUY;
        // [Ro]ckstar guy
        else if (b && b == 'o')
            id = SKIN_ID_ROCKSTAR_GUY;
        break;
        // [S]ailor (#1|A)/(#2|B)/(#3|C)
        // [S]hark (#1|A)/(#2|B)
        // [S]hopper (#1|A)/(#2|B)
        // [S]kate guy, [S]kate lady, [S]onny
        // [S]onny guy (#1|A)/(#2|B)/(#3|C)
        // [S]pandEx (#1|A)/(#2|B)
        // [S]panish guy
        // [S]panish lady (#1|A)/(#2|B)/(#3|C)/(#4|D)
        // [S]tore clerk
        // [S]tripper (#1|A)/(#2|B)/(#3|C)
        // [S]wat
    case 's':
        // [Sa]ilor (#1|A)/(#2|B)/(#3|C)
        if (b && b == 'a') {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SAILOR_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SAILOR_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_SAILOR_C;
                break;
            }
        }
        // [S]hark (#1|A)/(#2|B)
        else if (b && b == 'h' && (c && c == 'a')) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SHARK_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SHARK_B;
                break;
            }
        }
        // [S]hopper (#1|A)/(#2|B)
        else if (b && b == 'h' && (c && c == 'o')) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SHOPPER_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SHOPPER_B;
                break;
            }
        }
        // [Sk]ate [g]uy
        else if (b && b == 'k' && ((c && c == 'g') || (len >= 6 && str[5] == 'g')))
            id = SKIN_ID_SKATE_GUY;
        // [Sk]ate [l]ady
        else if (b && b == 'k' && ((c && c == 'l') || (len >= 6 && str[5] == 'l')))
            id = SKIN_ID_SKATE_LADY;
        // [So]nny
        // [So]nny guy (#1|A)/(#2|B)/(#3|C)
        else if (b && b == 'o') {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SONNY_GUY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SONNY_GUY_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_SONNY_GUY_C;
                break;
            }
        }
        else if (b && b == 'g') {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SONNY_GUY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SONNY_GUY_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_SONNY_GUY_C;
                break;
            }
        }
        // [Sp]andE[x] (#1|A)/(#2|B)
        else if (b && b == 'p' && ((c && c == 'x') || (len >= 7 && str[6] == 'x'))) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SPANDEX_GUY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SPANDEX_GUY_B;
                break;
            }
        }
        // [Sp]anish [g]uy
        else if (b && b == 'p' && ((c && c == 'g') || (len >= 8 && str[7] == 'g')))
            id = SKIN_ID_SPANISH_GUY;
        // [Sp]anish [l]ady (#1|A)/(#2|B)/(#3|C)/(#4|D)
        else if (b && b == 'p' && ((c && c == 'l') || (len >= 8 && str[7] == 'l'))) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_SPANISH_LADY_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_SPANISH_LADY_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_SPANISH_LADY_C;
                break;
            case '4':
            case 'd':
                id = SKIN_ID_SPANISH_LADY_D;
                break;
            }
        }
        // [Sto]re clerk
        else if ((b && b == 't') && (c && c == 'o'))
            id = SKIN_ID_STORE_CLERK;
        // [Str]ipper (#1|A)/(#2|B)/(#3|C)
        else if ((b && b == 't') && (c && c == 'r')) {
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_STRIPPER_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_STRIPPER_B;
                break;
            case '3':
            case 'c':
                id = SKIN_ID_STRIPPER_C;
                break;
            }
        }
        // [Sw]at
        else if (b && b == 'w')
            id = SKIN_ID_SWAT;
        break;
        // [T]axi driver (#1|A)/(#1|B)/(#2|C)/(#2|D)
        // [T]hug (#1|A)/(#2|B)
        // [T]ommy Vercetti
        // [T]ourist (#1|A)/(#2|B)
        // [T]ranny
    case 't':
        switch (b) {
            // [Ta]xi driver (#1|A)/(#1|B)/(#2|C)/(#2|D)
        case 'a':
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_TAXI_DRIVER_A;
                break;
            case '2':
            case 'b':
                id = SKIN_ID_TAXI_DRIVER_B;
                break;
            case 'c':
                id = SKIN_ID_TAXI_DRIVER_C;
                break;
            case 'd':
                id = SKIN_ID_TAXI_DRIVER_D;
                break;
            }
            break;
            // [Th]ug (#1|A)/(#2|B)
        case 'h':
            switch (d) {
            case '1':
            case 'a':
                id = SKIN_ID_THUG_A;
                break;
            case '5':
            case 'b':
                id = SKIN_ID_THUG_B;
                break;
            }
            break;
            // [To]mmy [V]ercetti
            // [To]urist (#1|A)/(#2|B)
        case 'v':
            id = SKIN_ID_TOMMY_VERCETTI;
            break;
        case 'o':
            if (c && c == 'm')
                id = SKIN_ID_TOMMY_VERCETTI;
            else if (c && c == 'u' && (d == '1' || d == 'a'))
                id = SKIN_ID_TOURIST_A;
            else if (c && c == 'u' && (d == '2' || d == 'b'))
                id = SKIN_ID_TOURIST_B;
            break;
        case 'r':
            id = SKIN_ID_TRANNY;
            break;
        }
        break;
        // [U]ndercover cop (#1|A)/(#2|B)/(#3|C)/(#4|D)/(#5|E)/(#6|F)
    case 'u':
        switch (d) {
        case '1':
        case 'a':
            id = SKIN_ID_UNDERCOVER_COP_A;
            break;
        case '2':
        case 'b':
            id = SKIN_ID_UNDERCOVER_COP_B;
            break;
        case '3':
        case 'c':
            id = SKIN_ID_UNDERCOVER_COP_C;
            break;
        case '4':
        case 'd':
            id = SKIN_ID_UNDERCOVER_COP_D;
            break;
        case '5':
        case 'e':
            id = SKIN_ID_UNDERCOVER_COP_E;
            break;
        case '6':
        case 'f':
            id = SKIN_ID_UNDERCOVER_COP_F;
            break;
        }
        break;
        // [V]ercetti guy (#1|A)/(#2|B)
    case 'v':
        switch (d) {
        case '1':
        case 'a':
            id = SKIN_ID_VERCETTI_GUY_A;
            break;
        case '2':
        case 'b':
            id = SKIN_ID_VERCETTI_GUY_B;
            break;
        }
        break;
        // [W]aitress (#1|A)/(#2|B)
    case 'w':
        switch (d) {
        case '1':
        case 'a':
            id = SKIN_ID_WAITRESS_A;
            break;
        case '2':
        case 'b':
            id = SKIN_ID_WAITRESS_B;
            break;
        }
        break;
    }
    // Free the previously allocated resources
    free(str);
    // Return the found ID
    return id + 1;
}

pybind11::str CGame::get_skin_name_from_model(int skinID)
{
    switch (skinID) {
    case 0:
        return "Tommy Vercetti";
    case 1:
        return "Cop";
    case 2:
        return "SWAT";
    case 3:
        return "FBI";
    case 4:
        return "Army";
    case 5:
        return "Paramedic";
    case 6:
        return "Firefighter";
    case 7:
        return "Golf Guy #1";
    case 8:
        return NULL;
    case 9:
        return "Bum Lady #1";
    case 10:
        return "Bum Lady #2";
    case 11:
        return "Punk #1";
    case 12:
        return "Lawyer";
    case 13:
        return "Spanish Lady #1";
    case 14:
        return "Spanish Lady #2";
    case 15:
        return "Cool Guy #1";
    case 16:
        return "Arabic Guy";
    case 17:
        return "Beach Lady #1";
    case 18:
        return "Beach Lady #2";
    case 19:
        return "Beach Guy #1";
    case 20:
        return "Beach Guy #2";
    case 21:
        return "Office Lady #1";
    case 22:
        return "Waitress #1";
    case 23:
        return "Food Lady";
    case 24:
        return "Prostitute #1";
    case 25:
        return "Bum Lady #3";
    case 26:
        return "Bum Guy #1";
    case 27:
        return "Garbageman #1";
    case 28:
        return "Taxi Driver #1";
    case 29:
        return "Haitian #1";
    case 30:
        return "Criminal #1";
    case 31:
        return "Hood Lady";
    case 32:
        return "Granny #1";
    case 33:
        return "Businessman #1";
    case 34:
        return "Church Guy";
    case 35:
        return "Club Lady";
    case 36:
        return "Church Lady";
    case 37:
        return "Pimp";
    case 38:
        return "Beach Lady #3";
    case 39:
        return "Beach Guy #3";
    case 40:
        return "Beach Lady #4";
    case 41:
        return "Beach Guy #4";
    case 42:
        return "Businessman #2";
    case 43:
        return "Prostitute #2";
    case 44:
        return "Bum Lady #4";
    case 45:
        return "Bum Guy #2";
    case 46:
        return "Haitian #2";
    case 47:
        return "Construction Worker #1";
    case 48:
        return "Punk #2";
    case 49:
        return "Prostitute #3";
    case 50:
        return "Granny #2";
    case 51:
        return "Punk #3";
    case 52:
        return "Businessman #3";
    case 53:
        return "Spanish Lady #3";
    case 54:
        return "Spanish Lady #4";
    case 55:
        return "Cool Guy #2";
    case 56:
        return "Businessman #4";
    case 57:
        return "Beach Lady #5";
    case 58:
        return "Beach Guy #5";
    case 59:
        return "Beach Lady #6";
    case 60:
        return "Beach Guy #6";
    case 61:
        return "Construction Worker #2";
    case 62:
        return "Golf Guy #2";
    case 63:
        return "Golf Lady";
    case 64:
        return "Golf Guy #3";
    case 65:
        return "Beach Lady #7";
    case 66:
        return "Beach Guy #7";
    case 67:
        return "Office Lady #2";
    case 68:
        return "Businessman #5";
    case 69:
        return "Businessman #6";
    case 70:
        return "Prostitute #2";
    case 71:
        return "Bum Lady #4";
    case 72:
        return "Bum Guy #3";
    case 73:
        return "Spanish Guy";
    case 74:
        return "Taxi Driver #2";
    case 75:
        return "Gym Lady";
    case 76:
        return "Gym Guy";
    case 77:
        return "Skate Lady";
    case 78:
        return "Skate Guy";
    case 79:
        return "Shopper #1";
    case 80:
        return "Shopper #2";
    case 81:
        return "Tourist #1";
    case 82:
        return "Tourist #2";
    case 83:
        return "Cuban #1";
    case 84:
        return "Cuban #2";
    case 85:
        return "Haitian #3";
    case 86:
        return "Haitian #4";
    case 87:
        return "Shark #1";
    case 88:
        return "Shark #2";
    case 89:
        return "Diaz Guy #1";
    case 90:
        return "Diaz Guy #2";
    case 91:
        return "DBP Security #1";
    case 92:
        return "DBP Security #2";
    case 93:
        return "Biker #1";
    case 94:
        return "Biker #2";
    case 95:
        return "Vercetti Guy #1";
    case 96:
        return "Vercetti Guy #2";
    case 97:
        return "Undercover Cop #1";
    case 98:
        return "Undercover Cop #2";
    case 99:
        return "Undercover Cop #3";
    case 100:
        return "Undercover Cop #4";
    case 101:
        return "Undercover Cop #5";
    case 102:
        return "Undercover Cop #6";
    case 103:
        return "Rich Guy";
    case 104:
        return "Cool Guy #3";
    case 105:
        return "Prostitute #3";
    case 106:
        return "Prostitute #4";
    case 107:
        return "Love Fist #1";
    case 108:
        return "Ken Rosenburg";
    case 109:
        return "Candy Suxx";
    case 110:
        return "Hilary";
    case 111:
        return "Love Fist #2";
    case 112:
        return "Phil";
    case 113:
        return "Rockstar Guy";
    case 114:
        return "Sonny";
    case 115:
        return "Lance";
    case 116:
        return "Mercedes";
    case 117:
        return "Love Fist #3";
    case 118:
        return "Alex Shrub";
    case 119:
        return "Lance (Cop)";
    case 120:
        return "Lance";
    case 121:
        return "Cortez";
    case 122:
        return "Love Fist #4";
    case 123:
        return "Columbian Guy #1";
    case 124:
        return "Hilary (Robber)";
    case 125:
        return "Mercedes";
    case 126:
        return "Cam";
    case 127:
        return "Cam (Robber)";
    case 128:
        return "Phil (One Arm)";
    case 129:
        return "Phil (Robber)";
    case 130:
        return "Cool Guy #4";
    case 131:
        return "Pizza Man";
    case 132:
        return "Taxi Driver #1";
    case 133:
        return "Taxi Driver #2";
    case 134:
        return "Sailor #1";
    case 135:
        return "Sailor #2";
    case 136:
        return "Sailor #3";
    case 137:
        return "Chef";
    case 138:
        return "Criminal #2";
    case 139:
        return "French Guy";
    case 140:
        return "Garbageman #2";
    case 141:
        return "Haitian #5";
    case 142:
        return "Waitress #2";
    case 143:
        return "Sonny Guy #1";
    case 144:
        return "Sonny Guy #2";
    case 145:
        return "Sonny Guy #3";
    case 146:
        return "Columbian Guy #2";
    case 147:
        return "Haitian #6";
    case 148:
        return "Beach Guy #8";
    case 149:
        return "Garbageman #3";
    case 150:
        return "Garbageman #4";
    case 151:
        return "Garbageman #5";
    case 152:
        return "Tranny";
    case 153:
        return "Thug #5";
    case 154:
        return "SpandEx Guy #1";
    case 155:
        return "SpandEx Guy #2";
    case 156:
        return "Stripper #1";
    case 157:
        return "Stripper #2";
    case 158:
        return "Stripper #3";
    case 159:
        return "Store Clerk";
    case 160:
        return NULL;
    case 161:
        return "Tommy with Suit";
    case 162:
        return "Worker Tommy";
    case 163:
        return "Golfer Tommy";
    case 164:
        return "Cuban Tommy";
    case 165:
        return "VCPD Tommy";
    case 166:
        return "Bank Robber Tommy";
    case 167:
        return "Street Tommy";
    case 168:
        return "Mafia Tommy";
    case 169:
        return "Jogger Tommy #1";
    case 170:
        return "Jogger Tommy #2";
    case 171:
        return "Guy With Suit #1";
    case 172:
        return "Guy With Suit #3";
    case 173:
        return "Prostitute #5";
    case 174:
        return "Rico";
    case 175:
        return "Prostitute #3";
    case 176:
        return "Club Lady";
    case 177:
        return "Prostitute #2";
    case 178:
        return "Skull T-Shirt Guy";
    case 179:
        return "Easter Egg Tommy";
    case 180:
        return "Diaz Gangster #1";
    case 181:
        return "Diaz Gangster #2";
    case 182:
        return "Hood Lady";
    case 183:
        return "Punk #1";
    case 184:
        return "Tray Lady";
    case 185:
        return "Kent Paul";
    case 186:
        return "Taxi Driver #1";
    case 187:
        return "Deformed Ken Rosenberg";
    case 188:
        return "Deformed Woman";
    case 189:
        return "Deformed Man";
    case 190:
        return "Deformed Cortez";
    case 191:
        return "Deformed Lance Vance";
    case 192:
        return "Thief #1";
    case 193:
        return "Thief #2";
    case 194:
        return "Thief #3";
    default:
        return NULL;
    }
}

int CGame::get_weapon_model_from_name(const char* name)
{
    if (name == NULL || strlen(name) < 1)
        return 0;

    // Get characters we might need
    char char1, char2, char3;
    char1 = 0;
    char2 = 0;
    char3 = 0;

    char1 = tolower(name[0]);
    if (strlen(name) >= 3) {
        char3 = tolower(name[2]);
        char2 = tolower(name[1]);
    }
    else if (strlen(name) >= 2)
        char2 = tolower(name[1]);

    switch (char1) {
        // [F]ists, [F]lamethrower
    case 'f': {
        // [Fi]sts
        if (char2 && char2 == 'i')
            return 0;

        // Default to flamethrower
        else
            return 31;

        break;
    }

    case 'b':
        // [Br]ass Knuckles
        if (char2 && char2 == 'r')
            return 1;

        // [Ba]seball Bat
        return 6;

        // [S]crewdriver, [S]hotgun, [S]PAS-12 Shotgun, [S]tubby/[S]awnoff Shotgun, [Si]lenced Ingram [S]niper Rifle
    case 's': {
        switch (char2) {
            // [Sc]rewdriver
        case 'c':
            return 2;

            // [Sh]otgun
        case 'h':
            return 19;

            // [SP]AS-12 / [Sp]az Shotgun
        case 'p':
            return 20;

            // [St]ubby / [Sa]wnoff Shotgun
        case 't':
        case 'a':
            return 21;

            // [Si]lenced Ingram
        case 'i':
            return 24;

            // [Sn]iper
        case 'n':
            return 28;

            // Default to screwdriver
        default:
            return 2;
        }
    }

            // [G]olf Club, [G]renade
    case 'g': {
        // [Go]lf Club
        if (char2 && char2 == 'o')
            return 3;

        // Grenades being more popular in servers, default to grenade
        else
            return 12;

        break;
    }

            // [N]ightstick
    case 'n':
        return 4;

        // [K]nife, [K]atana
    case 'k': {
        if (char2 && char2 == 'n') {
            // [Kn]ife
            if (char3 == 'i')
                return 5;
            // [Knu]ckles
            else if (char3 == 'u')
                return 1;
        }

        // Default to katana
        else
            return 10;

        break;
    }

            // [H]ammer
    case 'h':
        return 7;

        // [M]eat Cleaver, [M]achete, [M]olotov Cocktail, [M]P5, [M]4, [M]60, [M]inigun
    case 'm': {
        switch (char2) {
            // [Me]at Cleaver
        case 'e':
            return 8;

            // [Ma]chete
        case 'a':
            return 9;

            // [Mo]lotov Cocktail
        case 'o':
            return 15;

            // [MP]5
        case 'p':
            return 25;

            // [M4]
        case '4':
            return 26;

            // [M6]0
        case '6':
            return 32;

            // [Mi]nigun
        case 'i':
            return 33;

            // Default to M4
        default:
            return 26;
        }

        break;
    }

            // [C]leaver, [C]hainsaw, [C]olt .45
    case 'c': {
        switch (char2) {
            // [Cl]eaver
        case 'l':
            return 8;

            // [Ch]ainsaw
        case 'h':
            return 11;

            // Default to Colt .45
        default:
            return 17;
        }

        break;
    }

            // [R]emote Detonation Grenade, [R]uger, [R]ocket Launcher / [R]PG
    case 'r': {
        switch (char2) {
            // [Re]mote Detonation Grenade
        case 'e':
            return 13;

            // [Ro]cket Launcher, [RP]G
        case 'o':
        case 'p':
            return 30;

            // [Ru]ger
        case 'u':
            return 27;

            // Default to ruger
        default:
            return 27;
        }
    }

            // [T]ear Gas, [T]EC-9
    case 't': {
        // Both of them have E as a second character anyways.
        if (char2) {
            // [Tea]r Gas
            if (char3 && char3 == 'a')
                return 14;

            // Default to TEC-9
            else
                return 22;
        }

        // Default to TEC-9 if no second character exists.
        else
            return 22;

        break;
    }

            // [P]ython
    case 'p':
        return 18;

        // [U]zi
    case 'u':
        return 23;

        // [I]ngram
    case 'i':
        return 24;

        // [L]aserscope Sniper
    case 'l':
        return 29;

        // Default to fists
    default:
        return 255;
    }

    return 255;
}

bool CGame::set_weapon_data_value(int32_t weaponID, int32_t fieldID, double value)
{
    return (functions->SetWeaponDataValue(weaponID, fieldID, value) ? true : false);
}

double CGame::get_weapon_data_value(int32_t weaponID, int32_t fieldID)
{
    return functions->GetWeaponDataValue(weaponID, fieldID);
}

bool CGame::reset_weapon_data_value(int32_t weaponID, int32_t fieldID)
{
    return (functions->ResetWeaponDataValue(weaponID, fieldID) ? true : false);
}

bool CGame::is_weapon_data_modified(int32_t weaponID, int32_t fieldID)
{
    return (functions->IsWeaponDataValueModified(weaponID, fieldID) ? true : false);
}

bool CGame::reset_weapon_data(int32_t weaponID)
{
    return (functions->ResetWeaponData(weaponID) ? true : false);
}

void CGame::reset_all_weapon_data()
{
    return functions->ResetAllWeaponData();
}

inline void szlower(char* string)
{
    int i;
    for (i = 0; string[i]; i++)
        string[i] = tolower(string[i]);
}

int CGame::get_vehicle_model_from_name(char const* name)
{
    char* lowername = _strdup(name);
    szlower(lowername);

    int res = -1;
    if (lowername) {
        switch (lowername[0]) {
        case 'l': {
            if (strlen(lowername) >= 2) {
                if (lowername[1] == 'a')
                    res = 130; // landstalker
                else if (lowername[1] == 'i')
                    res = 133; // linerunner
                else if (lowername[1] == 'o')
                    res = 201; // love fist
            }

            break;
        }

        case 'i': {
            if (strlen(lowername) >= 2) {
                if (lowername[1] == 'd')
                    res = 131;
                else if (lowername[1] == 'n')
                    res = 141;
            }

            break;
        }

        case 's': {
            if (strlen(lowername) >= 3) {
                if (lowername[1] == 't') {
                    if (lowername[2] == 'i')
                        res = 132; // stinger
                    else if (lowername[2] == 'r')
                        res = 139; // stretch
                    else if (lowername[2] == 'a')
                        res = 169; // stallion
                }
                else if (lowername[1] == 'e') {
                    if (lowername[2] == 'c')
                        res = 158; // securicar
                    else if (lowername[2] == 'a')
                        res = 177; // sea sparrow
                    else if (strlen(lowername) > 8)
                        res = 174; // sentinel xs
                    else
                        res = 135; // sentinel
                }
                else if (lowername[1] == 'q')
                    res = 176; // squalo
                else if (lowername[1] == 'p') {
                    if (lowername[2] == 'e')
                        res = 182; // speeder
                    else if (lowername[2] == 'a') {
                        if (strlen(lowername) >= 4) {
                            if (lowername[3] == 'r')
                                res = 199; // sparrow
                            else if (lowername[3] == 'n')
                                res = 213; // spand express
                        }
                    }
                }
                else if (lowername[1] == 'k')
                    res = 190; // skimmer
                else if (lowername[1] == 'a') {
                    if (lowername[2] == 'n') {
                        if (strlen(lowername) >= 4) {
                            if (lowername[3] == 'c')
                                res = 198; // sanchez
                            else if (lowername[3] == 'd')
                                res = 225; // sandking
                        }
                    }
                    else if (lowername[2] == 'b' && strlen(lowername) > 5)
                        res = 206; // sabre turbo
                    else if (lowername[2] == 'b')
                        res = 205; // sabre
                }
            }

            break;
        }

        case 'p': {
            if (lowername[1] == 'e')
                res = 134; // perennial
            else if (lowername[1] == 'o') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'n')
                        res = 143; // pony
                    else if (strlen(lowername) > 6)
                        res = 227; // police maverick
                    else
                        res = 156; // police
                }
            }
            else if (lowername[1] == 'r')
                res = 160; // predator
            else if (lowername[1] == 'a') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'c')
                        res = 173; // packer
                    else if (lowername[2] == 't')
                        res = 200; // patriot
                }
            }
            else if (lowername[1] == 'i')
                res = 178; // pizza boy
            else if (lowername[1] == 'c')
                res = 191; // pcj-600
            else if (lowername[1] == 'h')
                res = 207; // phoenix

            break;
        }

        case 'r': {
            if (lowername[1] == 'i')
                res = 136; // rio
            else if (lowername[1] == 'h')
                res = 162; // rhino
            else if (lowername[1] == 'u')
                res = 170; // rumpo
            else if (lowername[1] == 'c') {
                if (lowername[2] == 'b') {
                    if (strlen(lowername) >= 5) {
                        if (lowername[4] == 'n')
                            res = 171; // rcbandit
                        else if (lowername[4] == 'r')
                            res = 194; // rcbaron
                    }
                }
                else if (lowername[2] == 'r')
                    res = 195; // rcraider
                else if (lowername[2] == 'g')
                    res = 231;
            }
            else if (lowername[1] == 'o')
                res = 172; // romero's hearse
            else if (lowername[1] == 'e') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'e')
                        res = 183; // reefer
                    else if (lowername[2] == 'g')
                        res = 209; // regina
                }
            }
            else if (lowername[1] == 'a')
                res = 219;

            break;
        }

        case 'f': {
            if (lowername[1] == 'i')
                res = 137; // firetruck
            else if (lowername[1] == 'b') {
                if (strlen(lowername) >= 5) {
                    if (lowername[4] == 'w')
                        res = 147; // fbi washington
                    else if (lowername[4] == 'r')
                        res = 220; // fbi rancher
                }
            }
            else if (lowername[1] == 'l')
                res = 185; // flatbed
            else if (lowername[1] == 'a')
                res = 192; // faggio
            else if (lowername[1] == 'r')
                res = 193; // freeway

            break;
        }

        case 't': {
            if (lowername[1] == 'r') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'a')
                        res = 138; // trashmaster
                    else if (lowername[2] == 'o')
                        res = 184; // tropic
                }
            }
            else if (lowername[1] == 'o')
                res = 189; // top fun
            else if (lowername[1] == 'a')
                res = 150; // taxi

            break;
        }

        case 'm': {
            if (lowername[1] == 'a') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'n')
                        res = 140; // manana
                    else if (lowername[2] == 'r')
                        res = 214; // marquis
                    else if (lowername[2] == 'v')
                        res = 217; // maverick
                }
            }
            else if (lowername[1] == 'u')
                res = 144; // mule
            else if (lowername[1] == 'r')
                res = 153; // mr. whoopee
            else if (lowername[1] == 'e')
                res = 230; // mesa grande
            else if (lowername[1] == 'o')
                res = 148; // moonbeam

            break;
        }

        case 'c': {
            if (lowername[1] == 'h')
                res = 145; // cheetah
            else if (lowername[1] == 'u') {
                if (strlen(lowername) >= 7) {
                    if (lowername[6] == 'h')
                        res = 164; // cuban hermes
                    else if (lowername[6] == 'j')
                        res = 223; // cuban jetmax
                }
            }
            else if (lowername[1] == 'o') {
                if (strlen(lowername) >= 3 && lowername[2] == 'm')
                    res = 210; // comet
                else if (strlen(lowername) >= 4) {
                    if (lowername[3] == 'c')
                        res = 167; // coach
                    else if (lowername[3] == 's')
                        res = 202; // coast guard
                }
            }
            else if (lowername[1] == 'a') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'b')
                        res = 168; // cabbie
                    else if (lowername[2] == 'd')
                        res = 187; // caddy
                }
            }

            break;
        }

        case 'a': {
            if (lowername[1] == 'm')
                res = 146; // ambulance
            else if (lowername[1] == 'n')
                res = 166; // angel
            else if (lowername[1] == 'd')
                res = 175; // admiral
            else if (lowername[1] == 'i')
                res = 180; // airtrain

            break;
        }

        case 'e': {
            if (lowername[1] == 's')
                res = 149; // esperanto
            else if (lowername[1] == 'n')
                res = 157; // enforcer

            break;
        }

        case 'w': {
            if (strlen(lowername) >= 3) {
                if (lowername[2] == 's')
                    res = 151; // washington
                else if (lowername[2] == 'l')
                    res = 208; // walton
            }

            break;
        }

        case 'b': {
            if (lowername[1] == 'o') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'b')
                        res = 152; // bobcat
                    else if (lowername[2] == 'x')
                        res = 228; // boxville
                }
            }
            else if (lowername[1] == 'a') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'r')
                        res = 163; // barracks ol
                    else if (lowername[2] == 'g')
                        res = 215; // baggage handler
                    else if (lowername[2] == 'n')
                        res = 159; // banshee
                }
            }
            else if (lowername[1] == 'u') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'r')
                        res = 212; // burrito
                    else if (lowername[2] == 's')
                        res = 161; // bus
                }
            }
            else if (lowername[1] == 'l') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'i')
                        res = 226; // blista compact
                    else if (lowername[2] == 'o') {
                        res = 234; // bloodra
                        if (strcmp(lowername, "bloodrb") == 0)
                            res = 235; // bloodrb
                    }
                }
            }
            else if (lowername[1] == 'e')
                res = 229; // benson
            else if (lowername[1] == 'f')
                res = 154; // bf injection

            break;
        }

        case 'h': {
            if (lowername[1] == 'u')
                res = 155; // hunter
            else if (lowername[1] == 'e') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'r')
                        res = 204; // hermes
                    else if (lowername[2] == 'l')
                        res = 165; // helicopter
                }
            }
            else if (lowername[1] == 'o') {
                res = 224; // hotring racer
                if (strcmp("hotrina", lowername) == 0)
                    res = 232; // hotrina
                else if (strcmp("hotrinb", lowername) == 0)
                    res = 233; // hotrinb
            }

            break;
        }

        case 'g': {
            if (lowername[1] == 'a')
                res = 179; // gang burrito
            else if (lowername[1] == 'l')
                res = 196; // glendale
            else if (lowername[1] == 'r')
                res = 222; // greenwood

            break;
        }

        case 'd': {
            if (lowername[1] == 'e')
                res = 211; // deluxo
            else if (lowername[1] == 'i')
                res = 203; // dinghy

            break;
        }

        case 'y':
            res = 186; // yankee
            break;

        case 'z':
            res = 188; // zebra cab
            break;

        case 'k':
            res = 216; // kaufman cab
            break;

        case 'o':
            res = 197; // oceanic
            break;

        case 'j':
            res = 223; // cuban [j]etmax
            break;

        case 'v': {
            if (lowername[1] == 'c')
                res = 218; // vcn maverick
            else if (lowername[1] == 'i') {
                if (strlen(lowername) >= 3) {
                    if (lowername[2] == 'r')
                        res = 221; // virgo
                    else if (lowername[2] == 'c')
                        res = 236; // vicechee
                }
            }
            else if (lowername[1] == 'o')
                res = 142; // voodoo

            break;
        }
        }

        free(lowername);
    }

    return res;
}

pybind11::str CGame::get_vehicle_name_from_model(int model)
{
    switch (model) {
    case 130:
        return "Landstalker";
    case 131:
        return "Idaho";
    case 132:
        return "Stinger";
    case 133:
        return "Linerunner";
    case 134:
        return "Perennial";
    case 135:
        return "Sentinel";
    case 136:
        return "Rio";
    case 137:
        return "Firetruck";
    case 138:
        return "Trashmaster";
    case 139:
        return "Stretch";
    case 140:
        return "Manana";
    case 141:
        return "Infernus";
    case 142:
        return "Voodoo";
    case 143:
        return "Pony";
    case 144:
        return "Mule";
    case 145:
        return "Cheetah";
    case 146:
        return "Ambulance";
    case 147:
        return "FBI Washington";
    case 148:
        return "Moonbeam";
    case 149:
        return "Esperanto";
    case 150:
        return "Taxi";
    case 151:
        return "Washington";
    case 152:
        return "Bobcat";
    case 153:
        return "Mr. Whoopee";
    case 154:
        return "BF Injection";
    case 155:
        return "Hunter";
    case 156:
        return "Police";
    case 157:
        return "Enforcer";
    case 158:
        return "Securicar";
    case 159:
        return "Banshee";
    case 160:
        return "Predator";
    case 161:
        return "Bus";
    case 162:
        return "Rhino";
    case 163:
        return "Barracks OL";
    case 164:
        return "Cuban Hermes";
    case 165:
        return "Helicopter";
    case 166:
        return "Angel";
    case 167:
        return "Coach";
    case 168:
        return "Cabbie";
    case 169:
        return "Stallion";
    case 170:
        return "Rumpo";
    case 171:
        return "RC Bandit";
    case 172:
        return "Romero's Hearse";
    case 173:
        return "Packer";
    case 174:
        return "Sentinel XS";
    case 175:
        return "Admiral";
    case 176:
        return "Squalo";
    case 177:
        return "Sea Sparrow";
    case 178:
        return "Pizza Boy";
    case 179:
        return "Gang Burrito";
    case 180:
        return "Airtrain";
    case 181:
        return "Deaddodo";
    case 182:
        return "Speeder";
    case 183:
        return "Reefer";
    case 184:
        return "Tropic";
    case 185:
        return "Flatbed";
    case 186:
        return "Yankee";
    case 187:
        return "Caddy";
    case 188:
        return "Zebra Cab";
    case 189:
        return "Top Fun";
    case 190:
        return "Skimmer";
    case 191:
        return "PCJ-600";
    case 192:
        return "Faggio";
    case 193:
        return "Freeway";
    case 194:
        return "RC Baron";
    case 195:
        return "RC Raider";
    case 196:
        return "Glendale";
    case 197:
        return "Oceanic";
    case 198:
        return "Sanchez";
    case 199:
        return "Sparrow";
    case 200:
        return "Patriot";
    case 201:
        return "Love Fist";
    case 202:
        return "Coast Guard";
    case 203:
        return "Dinghy";
    case 204:
        return "Hermes";
    case 205:
        return "Sabre";
    case 206:
        return "Sabre Turbo";
    case 207:
        return "Phoenix";
    case 208:
        return "Walton";
    case 209:
        return "Regina";
    case 210:
        return "Comet";
    case 211:
        return "Deluxo";
    case 212:
        return "Burrito";
    case 213:
        return "Spand Express";
    case 214:
        return "Marquis";
    case 215:
        return "Baggage Handler";
    case 216:
        return "Kaufman Cab";
    case 217:
        return "Maverick";
    case 218:
        return "VCN Maverick";
    case 219:
        return "Rancher";
    case 220:
        return "FBI Rancher";
    case 221:
        return "Virgo";
    case 222:
        return "Greenwood";
    case 223:
        return "Cuban Jetmax";
    case 224:
        return "Hotring Racer #1";
    case 225:
        return "Sandking";
    case 226:
        return "Blista Compact";
    case 227:
        return "Police Maverick";
    case 228:
        return "Boxville";
    case 229:
        return "Benson";
    case 230:
        return "Mesa Grande";
    case 231:
        return "RC Goblin";
    case 232:
        return "Hotring Racer #2";
    case 233:
        return "Hotring Racer #3";
    case 234:
        return "Bloodring Banger #1";
    case 235:
        return "Bloodring Banger #2";
    case 236:
        return "Vice Squad Cheetah";
    default:
        return NULL;
    }
}

PYBIND11_EMBEDDED_MODULE(vcmp_game, module)
{
    pybind11::class_<CGame>(module, "Game")
        .def("retrieve_player", &CGame::find_player_instance)
        .def("retrieve_pickup", &CGame::find_pickup_instance)
        .def("retrieve_object", &CGame::find_object_instance)
        .def("retrieve_vehicle", &CGame::find_vehicle_instance)
        .def("retrieve_checkpoint", &CGame::find_checkpoint_instance)

        .def("create_vehicle", &CGame::create_vehicle)
        .def("create_checkpoint", &CGame::create_checkpoint)
        .def("create_pickup", &CGame::create_pickup)
        .def("create_object", &CGame::create_object)

        .def_static("create_radio_stream", &CGame::create_radio)
        .def_static("destroy_radio", &CGame::destroy_radio)
        .def_static("create_blip", &CGame::create_blip)
        .def_static("destroy_blip", &CGame::destroy_blip)
        .def_static("create_explosion", &CGame::create_explosion)
        .def_static("play_sound", &CGame::play_sound)
        .def_static("play_sound_for_player", &CGame::play_sound_for_player)
        .def_static("play_sound_for_world", &CGame::play_sound_for_world)
        .def_static("get_time_rate", &CGame::get_time_rate)
        .def_static("set_time_rate", &CGame::set_time_rate)
        .def_static("get_hour", &CGame::get_hour)
        .def_static("set_hour", &CGame::set_hour)
        .def_static("get_minute", &CGame::get_minute)
        .def_static("set_minute", &CGame::set_minute)
        .def_static("get_weather", &CGame::get_weather)
        .def_static("set_weather", &CGame::set_weather)
        .def_static("get_gravity", &CGame::get_gravity)
        .def_static("set_gravity", &CGame::set_gravity)
        .def_static("get_game_speed", &CGame::get_game_speed)
        .def_static("set_game_speed", &CGame::set_game_speed)
        .def_static("get_water_level", &CGame::get_water_level)
        .def_static("set_water_level", &CGame::set_water_level)
        .def_static("get_max_flight_altitude", &CGame::get_max_flight_altitude)
        .def_static("set_max_flight_altitude", &CGame::set_max_flight_altitude)
        .def_static("get_fall_timer", &CGame::get_fall_timer)
        .def_static("set_fall_timer", &CGame::set_fall_timer)
        .def_static("get_kill_delay", &CGame::get_kill_delay)
        .def_static("set_kill_delay", &CGame::set_kill_delay)
        .def_static("is_sync_frame_limiter_enabled", &CGame::is_sync_frame_limiter_enabled)
        .def_static("toggle_sync_frame_limiter", &CGame::toggle_sync_frame_limiter)
        .def_static("is_frame_limiter_enabled", &CGame::is_frame_limiter_enabled)
        .def_static("toggle_frame_limiter", &CGame::toggle_frame_limiter)
        .def_static("is_taxi_boost_jump_enabled", &CGame::is_taxi_boost_jump_enabled)
        .def_static("toggle_taxi_boost_jump", &CGame::toggle_taxi_boost_jump)
        .def_static("is_drive_on_water_enabled", &CGame::is_drive_on_water_enabled)
        .def_static("toggle_drive_on_water", &CGame::toggle_drive_on_water)
        .def_static("is_fast_switch_enabled", &CGame::is_fast_switch_enabled)
        .def_static("toggle_fast_switch", &CGame::toggle_fast_switch)
        .def_static("is_friendly_fire_enabled", &CGame::is_friendly_fire_enabled)
        .def_static("toggle_friendly_fire", &CGame::toggle_friendly_fire)
        .def_static("is_drive_by_enabled", &CGame::is_drive_by_enabled)
        .def_static("toggle_disable_driveby", &CGame::toggle_disable_driveby)
        .def_static("is_perfect_handling_enabled", &CGame::is_perfect_handling_enabled)
        .def_static("toggle_perfect_handling", &CGame::toggle_perfect_handling)
        .def_static("is_flying_cars_enabled", &CGame::is_flying_cars_enabled)
        .def_static("toggle_flying_cars", &CGame::toggle_flying_cars)
        .def_static("is_jump_switch_enabled", &CGame::is_jump_switch_enabled)
        .def_static("toggle_jump_switch", &CGame::toggle_jump_switch)
        .def_static("is_show_on_radar_enabled", &CGame::is_show_on_radar_enabled)
        .def_static("toggle_show_on_radar", &CGame::toggle_show_on_radar)
        .def_static("is_show_only_team_markers_enabled", &CGame::is_show_only_team_markers_enabled)
        .def_static("toggle_only_show_team_markers", &CGame::toggle_only_show_team_markers)
        .def_static("is_stunt_bike_enabled", &CGame::is_stunt_bike_enabled)
        .def_static("toggle_stunt_bike", &CGame::toggle_stunt_bike)
        .def_static("is_shoot_in_air_enabled", &CGame::is_shoot_in_air_enabled)
        .def_static("toggle_shoot_in_air", &CGame::toggle_shoot_in_air)
        .def_static("is_show_name_tags_enabled", &CGame::is_show_name_tags_enabled)
        .def_static("toggle_show_name_tags", &CGame::toggle_show_name_tags)
        .def_static("is_join_messages_enabled", &CGame::is_join_messages_enabled)
        .def_static("toggle_join_messages", &CGame::toggle_join_messages)
        .def_static("is_death_messages_enabled", &CGame::is_death_messages_enabled)
        .def_static("toggle_death_messages", &CGame::toggle_death_messages)
        .def_static("is_wall_glitch_enabled", &CGame::is_wall_glitch_enabled)
        .def_static("toggle_wallglitch", &CGame::toggle_wallglitch)
        .def_static("is_disable_backface_culling_enabled", &CGame::is_disable_backface_culling_enabled)
        .def_static("toggle_disable_backface_culling", &CGame::toggle_disable_backface_culling)
        .def_static("is_disable_heli_blade_damage_enabled", &CGame::is_disable_heli_blade_damage_enabled)
        .def_static("toggle_disable_heli_blade_damage", &CGame::toggle_disable_heli_blade_damage)
        .def_static("is_using_player_classes", &CGame::is_using_player_classes)
        .def_static("toggle_use_player_classes", &CGame::toggle_use_player_classes)
        .def_static("add_player_class", &CGame::add_player_class)
        .def_static("set_spawn_player_position", &CGame::set_spawn_player_position)
        .def_static("set_spawn_camera_position", &CGame::set_spawn_camera_position)
        .def_static("set_spawn_camera_look_at", &CGame::set_spawn_camera_look_at)
        .def_static("is_world_compatible_with_player", &CGame::is_world_compatible_with_player)
        .def_static("get_world_bounds", &CGame::get_world_bounds)
        .def_static("set_world_bounds", &CGame::set_world_bounds)
        .def_static("get_wasted_settings", &CGame::get_wasted_settings)
        .def_static("set_wasted_settings", &CGame::set_wasted_settings)
        .def_static("raw_hide_map_object", &CGame::raw_hide_map_object)
        .def_static("hide_map_object", &CGame::hide_map_object)
        .def_static("show_map_object", &CGame::show_map_object)
        .def_static("show_all_map_objects", &CGame::show_all_map_objects)
        .def_static("force_select_all_players", &CGame::force_select_all_players)
        .def_static("reset_all_vehicle_handlings", &CGame::reset_all_vehicle_handlings)
        .def_static("is_handling_rule_set", &CGame::is_handling_rule_set)
        .def_static("get_handling_rule", &CGame::get_handling_rule)
        .def_static("set_handling_rule", &CGame::set_handling_rule)
        .def_static("reset_handling_rule", &CGame::reset_handling_rule)
        .def_static("reset_vehicle_handling", &CGame::reset_vehicle_handling)
        .def_static("get_cinematic_borders", &CGame::get_cinematic_borders)
        .def_static("set_cinematic_borders", &CGame::set_cinematic_borders)
        .def_static("get_white_scan_lines", &CGame::get_white_scan_lines)
        .def_static("set_white_scan_lines", &CGame::set_white_scan_lines)
        .def_static("get_green_scan_lines", &CGame::get_green_scan_lines)
        .def_static("set_green_scan_lines", &CGame::set_green_scan_lines)
        .def_static("get_weapon_name_from_model", &CGame::get_weapon_name_from_model)
        .def_static("get_weapon_model_from_name", &CGame::get_weapon_model_from_name)
        .def_static("get_skin_name_from_model", &CGame::get_skin_name_from_model)
        .def_static("get_skin_model_from_name", &CGame::get_skin_model_from_name)
        .def_static("get_district_name", &CGame::get_district_name)
        .def_static("set_weapon_data_value", &CGame::set_weapon_data_value)
        .def_static("get_weapon_data_value", &CGame::get_weapon_data_value)
        .def_static("reset_weapon_data_value", &CGame::reset_weapon_data_value)
        .def_static("is_weapon_data_modified", &CGame::is_weapon_data_modified)
        .def_static("reset_weapon_data", &CGame::reset_weapon_data)
        .def_static("get_vehicle_model_from_name", &CGame::get_vehicle_model_from_name)
        .def_static("get_vehicle_name_from_model", &CGame::get_vehicle_name_from_model);
}