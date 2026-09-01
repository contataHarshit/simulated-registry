cmake_minimum_required(VERSION 3.10)

project(AFDX_UI_Framework)

enable_testing()

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(SOURCES
    src/main.cpp
    src/simulator/SimulatedAFDXReceiver.cpp
    src/shared_memory/SharedMemory.cpp
    src/parser/CommandParser.cpp
    src/parser/CommandRegistry.cpp
    src/runtime/RuntimeEngine.cpp
    src/variables/Variable.cpp
    src/variables/VariableStore.cpp
)

add_executable(
    afdx_ui_poc
    ${SOURCES}
)

configure_file(
    config/runtime_config.txt
    config/runtime_config.txt
    COPYONLY
)

set(CORE_SOURCES
    src/parser/CommandParser.cpp
    src/parser/CommandRegistry.cpp
    src/runtime/RuntimeEngine.cpp
    src/shared_memory/SharedMemory.cpp
    src/simulator/SimulatedAFDXReceiver.cpp
    src/variables/Variable.cpp
    src/variables/VariableStore.cpp
)

add_executable(command_parser_test
    tests/CommandParserTest.cpp
    ${CORE_SOURCES}
)

add_executable(variable_store_test
    tests/VariableStoreTest.cpp
    src/variables/Variable.cpp
    src/variables/VariableStore.cpp
)

add_executable(runtime_engine_test
    tests/RuntimeEngineTest.cpp
    src/runtime/RuntimeEngine.cpp
    src/variables/Variable.cpp
    src/variables/VariableStore.cpp
)

add_test(NAME command_parser_test COMMAND command_parser_test)
add_test(NAME variable_store_test COMMAND variable_store_test)
add_test(NAME runtime_engine_test COMMAND runtime_engine_test)