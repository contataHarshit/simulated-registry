# AFDX UI Framework

A lightweight C++ runtime prototype that demonstrates a configuration-driven command system for UI-like and industrial control flows. The project simulates a message pipeline where commands are parsed from a file, resolved through a registry, executed by a runtime engine, and then applied to a variable store.

This is a learning and prototype project, but it follows a realistic pattern:

- variables are declared and stored in a central state store
- commands are registered dynamically from config data
- command families provide inheritance-style behavior
- simulator messages are processed in sequence
- runtime actions update variables and notify observers

---

## What the project does

The program reads a configuration file, creates a `VariableStore`, registers commands, simulates incoming runtime messages, parses each command, and executes the resulting actions.

A typical run looks like this:

1. Variables are declared in the config file.
2. Command families and command inheritance are configured.
3. The simulator emits messages from the config.
4. The parser resolves each command name.
5. The runtime engine executes the mapped action.
6. Variable observers are notified when values change.
7. The final state is printed to the console.

This is a simple but effective model of a message-driven runtime system.

---

## Architecture overview

### 1. Variable store
Responsible for storing mutable runtime values.

Files:
- [include/variables/VariableStore.h](include/variables/VariableStore.h)
- [src/variables/VariableStore.cpp](src/variables/VariableStore.cpp)

Functions:
- declare variables
- set/get variable values
- check if a variable exists
- subscribe observers
- print current runtime values

### 2. Command registry and parser
Responsible for matching user commands to runtime behavior.

Files:
- [include/parser/ICommand.h](include/parser/ICommand.h)
- [include/parser/CommandRegistry.h](include/parser/CommandRegistry.h)
- [src/parser/CommandRegistry.cpp](src/parser/CommandRegistry.cpp)
- [include/parser/CommandParser.h](include/parser/CommandParser.h)
- [src/parser/CommandParser.cpp](src/parser/CommandParser.cpp)

Features:
- built-in command registration
- alias-based commands
- inherited commands
- command families such as `ACTION`, `NAVIGATION`, `NOTIFICATION`, and `STATE`

### 3. Runtime engine
Executes the parsed request and updates the variable store.

Files:
- [include/runtime/RuntimeEngine.h](include/runtime/RuntimeEngine.h)
- [src/runtime/RuntimeEngine.cpp](src/runtime/RuntimeEngine.cpp)

### 4. Simulated AFDX receiver
Emulates incoming message traffic from a config file.

Files:
- [include/simulator/SimulatedAFDXReceiver.h](include/simulator/SimulatedAFDXReceiver.h)
- [src/simulator/SimulatedAFDXReceiver.cpp](src/simulator/SimulatedAFDXReceiver.cpp)

### 5. Shared memory abstraction
Acts as a simple queue for simulator-to-runtime communication.

Files:
- [include/shared_memory/SharedMemory.h](include/shared_memory/SharedMemory.h)
- [src/shared_memory/SharedMemory.cpp](src/shared_memory/SharedMemory.cpp)

### 6. Application entry point
The main orchestrator.

File:
- [src/main.cpp](src/main.cpp)

It creates:
- the variable store
- the parser
- the runtime engine
- the simulator
- the observer subscriptions

Then it processes incoming messages until the queue is empty.

---

## Current command model

The system supports command families and inheritance-based behavior.

Built-in message families are:

- `ACTION` -> `EXECUTE`
- `NAVIGATION` -> `OPEN_PAGE`
- `NOTIFICATION` -> `SHOW_MESSAGE`
- `STATE` -> `UPDATE_VARIABLE`

This means a new command can inherit behavior from a predefined family instead of being hardcoded individually.

Example:

- `command START_ENGINE ACTION`
- `command GO_TO_CONFIGURATION NAVIGATION`
- `command ALERT NOTIFICATION`
- `command SET_ENGINE_MODE STATE`

So `START_ENGINE` behaves like an action command and resolves to `EXECUTE` semantics.

---

## Runtime config format

The active project config is here:
- [config/runtime_config.txt](config/runtime_config.txt)

Supported formats:

### Variable declaration
```text
variable <id> <string|int|double|bool>
```

Example:
```text
variable pilotName string
variable engineMode string
variable engineRPM int
```

### Family declaration
```text
family <family-name> <base-command>
```

Example:
```text
family ACTION EXECUTE
family NAVIGATION OPEN_PAGE
family NOTIFICATION SHOW_MESSAGE
family STATE UPDATE_VARIABLE
```

### Command registration
```text
command <new-command> <parent-command-or-family>
```

Example:
```text
command START_ENGINE ACTION
command GO_TO_CONFIGURATION NAVIGATION
command SET_ENGINE_MODE STATE
command ALERT NOTIFICATION
```

### Runtime message
```text
message <runtime-command> <arguments...>
```

Example:
```text
message SET_ENGINE_MODE engineMode AUTO
message ALERT Engine started
message GO_TO_CONFIGURATION Configuration
message START_ENGINE SAVE_CONFIGURATION
```

---

## Real project scenario

The current [config/runtime_config.txt](config/runtime_config.txt) already demonstrates the inheritance scenario in action.

It contains entries like:

```text
family ACTION EXECUTE
family NAVIGATION OPEN_PAGE
family NOTIFICATION SHOW_MESSAGE
family STATE UPDATE_VARIABLE

command START_ENGINE ACTION
command GO_TO_CONFIGURATION NAVIGATION
command SET_ENGINE_MODE STATE
command ALERT NOTIFICATION
command RESTART_ENGINE ACTION

message SET_ENGINE_MODE engineMode AUTO
message SET_ENGINE_MODE pilotName Harshit
message RESTART_ENGINE SAVE_CONFIGURATION
message ALERT Engine started
message GO_TO_CONFIGURATION Configuration
message START_ENGINE SAVE_CONFIGURATION
```

This simulates a realistic UI/runtime event flow:

- update engine mode
- update pilot name
- trigger restart action
- show notification
- navigate to configuration screen
- start engine and save configuration

---

## Build steps

From the project root, run:

```powershell
$env:Path = "C:\mingw64\mingw64\bin;" + $env:Path
cd "C:\Users\Harshit Shrivastava\Desktop\projects\AFDX-UI-Framework"
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER="C:\mingw64\mingw64\bin\gcc.exe" -DCMAKE_CXX_COMPILER="C:\mingw64\mingw64\bin\g++.exe"
cmake --build build
```

This generates the build artifacts under the `build` directory.

---

## Run the app

After building, run the generated binary with the config file:

in
in? 
```

In this project, the real binary is the generated `afdx_ui_poc.exe` in the CMake build tree. The reliable way to run it is to list the build folder and launch the actual generated executable.

Example:

```powershell
Get-ChildItem .\uild\<generated-binary-name>.exe .\config\runtime_config.txt
```

In the verified workspace run, the app was executed successfully with:

in
in? .\config\runtime_config.txt
```

If your generated binary is visible in the build tree, use that exact path instead.

---

## Run the test suite

```powershell
ctest --test-dir build --output-on-failure
```

This checks the parser, variable store, and runtime engine behavior together.

---

## Example output

A successful run will print something like:

```text
[AFDX Simulator] Sending: SET_ENGINE_MODE engineMode AUTO
[AFDX Simulator] Sending: SET_ENGINE_MODE pilotName Harshit
[AFDX Simulator] Sending: RESTART_ENGINE SAVE_CONFIGURATION
[AFDX Simulator] Sending: ALERT Engine started
[AFDX Simulator] Sending: GO_TO_CONFIGURATION Configuration
[AFDX Simulator] Sending: START_ENGINE SAVE_CONFIGURATION

[Main] Received: SET_ENGINE_MODE engineMode AUTO
[RuntimeEngine] Updating variable: engineMode = AUTO
[Observer] engineMode changed to AUTO

[Main] Received: RESTART_ENGINE SAVE_CONFIGURATION
[RuntimeEngine] EXECUTE: SAVE_CONFIGURATION

[Main] Received: ALERT Engine started
[RuntimeEngine] MESSAGE: Engine started

[Main] Received: GO_TO_CONFIGURATION Configuration
[RuntimeEngine] OPEN_PAGE: Configuration

========== VARIABLE STORE ==========
engineMode = AUTO
pilotName = Harshit
===================================
```

This shows the real end-to-end flow:

message -> parser -> runtime engine -> variable update -> observer notification

---

## Current status

The project has been validated with a fresh build and test run.

Verified result:

```text
100% tests passed, 0 tests failed out of 3
```

---

## Repository structure

- [CMakeLists.txt](CMakeLists.txt)
- [Readme.md](Readme.md)
- [config/runtime_config.txt](config/runtime_config.txt)
- [include](include)
- [src](src)
- [tests](tests)

---

## Why this matters

This project is a good example of a dynamic, file-driven runtime architecture where commands can evolve without rewriting the entire parsing system. It demonstrates a practical inheritance model for real-world command systems and is a strong base for more advanced UI or automation frameworks.

---

## Suggested next steps

- add nested family chains
- add validation rules for command arguments
- add security or privilege metadata
- extend the runtime engine with richer action execution
- replace the console-only output with a GUI or web UI layer
