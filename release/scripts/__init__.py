from vcmp_event_manager import *
from vcmp_server import *
from vcmp_logger import *

def initialise():
    Server.set_name("Python Test | VC-MP Server")
    Server.set_game_mode("Test (Python)")
    Server.set_password("test123")
    Server.set_max_players(50)

    name = Server.get_name()
    game_mode = Server.get_game_mode()
    password = Server.get_password()
    max_players = Server.get_max_players()

    Logger.info("Server name: " + name + " - Game mode: " + game_mode)
    Logger.info("Password: " + password)
    Logger.info("Max players: " + str(max_players))
Event.bind("on_server_initialise", initialise)

def on_connect(player):
    Logger.info(player.name + " has been connected! IP: " + player.ip)
Event.bind("on_player_connect", on_connect)

def on_incoming_connection(user_name, user_password, user_ip):
    Logger.info("Someone named as " + user_name + " is trying to connect to the server! IP: " + user_ip)
    
    if (user_name == "guest"):
        return False
    else:
        return True
Event.bind("on_player_incoming_connection", on_incoming_connection)