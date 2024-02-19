# VC:MP Python Plugin

A plugin aimed at developers who love Python and VC:MP. Using this plugin it will be possible to develop VC:MP servers originally written in Python and its derived libraries.
The [wiki](https://github.com/razorn7/vcmp-python/wiki) is available for all information about functions, callbacks, structures, etc.

```python
def on_server_initialise():
    print("Hello world!")

Event.bind("on_server_initialise", on_server_initialise)
```

## Setting up the environment
### First steps
To setup the plugin on your desired server, simply [download](https://github.com/razorn7/vcmp-python/releases) the latest version of the plugin, place it in the `plugins/` folder on your server and launch `server64.exe`.
- Or just [get]() this blank server with everything prepared! (you will need to download the server executable separately).

### Configuration file
After completing the step above, a configuration file named `pyconfig.ini` will be created, if it does not exist, it will have some options and you will need to list which modules you want to import initially.

- Example of the configuration file:
```ini
[settings]
# Server environment settings
debug_messages = false						; Toggle debug messages (false/true)
enable_logger = true						; Toggle logger (false/true)
logger_file = server.log					; Defines the name of the file wich logger will write to
logger_timestamp = false					; Toggle whether the date and time on which the log line to be written will be shown
logger_timestamp_format = [%Y-%m-%d %X]		                ; Defines the format in which the date and time is shown. The following format is equivalent to [2024-01-01 00:00:00]

[modules]
# Here will be listed the modules you want to import into your environment
# moduleName = (false/true)
# false: will not be imported
# true: will be imported

scripts = true
#rpg = false
#deathmatch = false
#cnr = false
#ctf = false
```
