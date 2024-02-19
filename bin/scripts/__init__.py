'''
Vice City Multiplayer 0.4 (04rel006) Blank Server (by Seby).
Rewritten in Python by razorn7 (Razor#7311).

You can use it to script your own server. Here you can find all events developed.

- VC:MP Official: www.vc-mp.org
- Forum: forum.vc-mp.org
- Wiki: wiki.vc-mp.org
- Python plugin: https://github.com/razorn7/vcmp-python
'''

# Essential libraries
from vcmp_server import *
from vcmp_logger import *
from vcmp_game import *
from vcmp_utility import *
from vcmp_stream import* 

class Messages:
    def send_global(text):
        for i in range(Server.get_max_players()):
            player = Game.retrieve_player(i)
            if player:
                player.send_message(RGBA(200, 200, 150, 255), f"*> {text}")

class Settings:
    name = "[0.4] Python Server" #Server.get_name()
    password = "" #Server.get_password()
    mode = "simple (Python)" #Server.get_game_mode()

'''
Creating a connection between client and server scripts
I'm using bytes for identification, because they are the most waste-less for the designated task
This must be the same in both, client-side and server-side.
'''
class StreamType:
    ServerName = 0x01

# =========================================== S E R V E R   E V E N T S ==============================================

'''
def onServerStart():
    pass
    
def onServerStop():
    pass
'''

def on_server_initialise():
    # server info is printed in the console
    Server.set_name(Settings.name)
    Server.set_game_mode(Settings.mode)
    Logger.info("------------------------------------")
    Logger.info("Server name: " + Settings.name)
    Logger.info("Game mode: " + Settings.mode)
    
    if (Settings.password != ""):
        Logger.info( "Password: " + Settings.password)

    Logger.info("------------------------------------")

def on_server_shutdown():
    pass
    
#def on_server_frame(elapsed_time):
#    pass

# =========================================== P L A Y E R   E V E N T S ==============================================

def on_player_incoming_connection(user_name, user_password, user_ip):
    return True

def on_client_script_data(player):
    stream = Stream()
    string = stream.read_string()
    integer = stream.read_integer()

    Logger.info(f"String: [{string}]\nInteger: [{integer}]")

def on_player_connect(player):
    Logger.info(f"[{player.ID}] {player.name} connected.")
    Messages.send_global(f"{player.name} has been connected.")

def on_player_disconnect(player, reason):
    pass

def on_player_request_class(player, offset):
    return True

def on_player_request_spawn(player):
    return True

def on_player_spawn(player):
    pass

def on_player_death(player, killer, reason, body_part):
    pass

def on_player_update(player, update_type):
    pass

def on_player_request_enter_vehicle(player, vehicle, slot_index):
    return True

def on_player_enter_vehicle(player, vehicle, slot_index):
    pass

def on_player_exit_vehicle(player, vehicle):
    pass

def on_player_name_changeable(player, old_name, new_name):
    pass

def on_player_state_changeable(player, old_state, new_state):
    pass
 
def on_player_action_changeable(player, old_action, new_action):
    pass

def on_player_on_fire_changeable(player, is_on_fire):
    pass

def on_player_crouch_changeable(player, is_crouching):
    pass

def on_player_game_keys_changeable(player, old_keys, new_keys):
    pass

def on_player_begin_typing(player):
    player.send_announcement(1, "You are typing something...")
    pass

def on_player_end_typing(player):
    player.send_announcement(1, "")
    pass

def on_player_away_changeable(player, is_away):
    pass

def on_player_message(player, message):
    return True


def on_player_private_message(player, target, message):
    return True

def on_player_issue_command(player, cmd, text):
    if (cmd == "teste"):
        send_data_to_client(player, 15, "abc")
    return True

def on_player_key_press(player, bind_id):
    pass

def on_player_key_release(player, bind_id):
    pass

def on_player_spectate(player, target):
    pass

def on_player_crash_report(player, report):
    pass

def on_player_module_list(player, module):
    pass
    
# =========================================== V E H I C L E   E V E N T S ==============================================

def on_vehicle_update(vehicle, update_type):
    pass

def on_vehicle_explode(vehicle):
    pass

def on_vehicle_respawn(vehicle):
    pass

# =========================================== P I C K U P   E V E N T S ==============================================

def on_pickup_pick_attempt(player, pickup):
	return True

def on_pickup_picked(player, pickup):
    pass

def on_pickup_respawn(pickup):
    pass

# ========================================== O B J E C T   E V E N T S ==============================================

def on_object_shot(object, player, weapon):
    pass

def on_object_touch(object, player):
    pass

# ====================================== C H E C K P O I N T   E V E N T S ==========================================

def on_checkpoint_enter(player, checkpoint):
    pass

def on_checkpoint_exit(player, checkpoint):
    pass

# =========================================== B I N D   E V E N T S =================================================

def on_player_key_press(player, key):
    pass

def on_player_key_release(player, key):
    pass

# ================================== E N D   OF   O F F I C I A L   E V E N T S ======================================

def send_data_to_client(player, *argv):
    if argv[0]:
        byte = argv[0]
        length = len(argv)
                
        if 1 > length:
            Logger.info("ToClient <" + byte + "> No params specified.")
        else:
            MyStream = Stream()
            MyStream.start_write()
            MyStream.write_byte(byte)

            for i in range(1, length):
                type_ = str(type(argv[i]))
                if type_ == "<class 'int'>": 
                    MyStream.write_integer(argv[i])
                elif type_ == "<class 'str'>": 
                    MyStream.write_string(argv[i])
                elif type_ == "<class 'float'>": 
                    MyStream.write_float(argv[i])
            MyStream.send(player)
    else:
        Logger.info("ToClient: Even the byte wasn't specified...")
        
from . import binds