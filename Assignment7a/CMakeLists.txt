cmake_minimum_required(VERSION 3.16)
project(RPS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)
qt_standard_project_setup()

set(SOURCES
    main.cpp
    Choice.cpp
    ComputerPlayer.cpp
    HumanPlayer.cpp
    GUIHumanPlayer.cpp
    RandomStrategy.cpp
    SmartStrategy.cpp
    FrequencyStore.cpp
    GameEngine.cpp
    ConsoleGameEngine.cpp
    GUIGameEngine.cpp
    NetworkManager.cpp
    NetworkGameEngine.cpp
    MainWindow.cpp
)

qt_add_executable(rps
    ${SOURCES}
    MainWindow.ui
)

qt_add_resources(rps "images"
    PREFIX "/"
    FILES
        images/rock.jpeg
        images/paper.jpeg
        images/scissors.jpeg
)

target_link_libraries(rps PRIVATE Qt6::Widgets Qt6::Network)
