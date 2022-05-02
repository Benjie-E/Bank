cmake_minimum_required(VERSION 3.17)
project(Module-11-Bank-Starter)

set(CMAKE_CXX_STANDARD 14)

add_executable(Module11-Bank-Starter
    main.cpp
    tellers.cpp
    accounts.cpp
    ui.cpp
    transaction.cpp
)

add_custom_command(
    TARGET Module11-Bank-Starter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying sample data ..."
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:Module11-Bank-Starter>/data
)