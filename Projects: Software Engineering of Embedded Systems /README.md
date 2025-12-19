# S25-EmbeddedSecuritySystem
Security system developed by the Spring 2025 Software Engineering of Embedded Systems students.

## Embedded Modules

[Embedded Modules](embedded/README.md)

## REDIS Server

This project uses [REDIS](https://redis.io/) as middleware to communicate between the embedded modules and various "brain" functionalities.

### Configuration Parameters

Each module stores its configuration pameters in a REDIS hash set. Each module instance has a hashset key `config:<module-uuid>` which has the name/value configuration pairs for that module.

The script that interfaces between the embedded module (over serial) and the rest of the system will query these parameters and send them to the embedded moduel each time it starts up.

### Pub/Sub Channels

Communication in the system is achieved via several different channels with the following names:

* `error_msgs` - error messages produced by modules are published on this channel
* `debug_msgs` -- debug messages produced by modules are published on this channel
* `internal_msgs` - communication within the security system happens on this channel
* `external_msgs` - publication to entities outside the security system happens on this channel

## Utility Scripts

Utility scripts are stored in the [util](util/README.md) folder.

## Python Virtual Environment

Create a Python virtual environment with commands similar to this in the top-level project folder

```bash
$ python3 -m venv .venv
$ source .venv/bin/activate
(.venv) $ pip install -r requirements.txt
```

This creates a .venv folder in that directory, and installs the necessary Python dependencies.

VSCode will recognize this if you close and open the project folder again and load the python virtual environment automatically
