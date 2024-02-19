# VC:MP Python Plugin

A plugin aimed at developers who love Python and VC:MP. Using this plugin it will be possible to develop VC:MP servers originally written in Python and its derived libraries.
The [wiki](https://github.com/razorn7/vcmp-python/wiki) is available for all information about functions, callbacks, structures, etc.

## Setting up the environment
### First steps
To setup the plugin on your desired server, simply download the latest version of the plugin, place it in the `plugins/` folder on your server and launch `server64.exe`.
- [releases]()

### Configuration file
After completing the step above, a configuration file named `pyconfig.ini` will be created, if it does not exist, it will have some options and you will need to list which modules you want to import initially.

- Example of the configuration file:
```ini
[settings]
# Toggle debug messages [false/true]
debug_messages = false

# Toggle plugin logger [false/true]
enable_logger = true

# Defines the name of the file wich logger will write to
logger_file = server.log

# Toggle whether the date and time on which the log line to be written will be shown
logger_timestamp = false

# Defines the format in which the date and time is shown
# The format below means [2024-01-01 00:00:00]
logger_timestamp_format = [%Y-%m-%d %X]

# Here will be listed the modules you want to import into your environment
[modules]
# moduleName = [false/true] (false: will not be imported | true: will be imported)
scripts = true
```
