cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    examples/virtual_operator.cpp
    Advantage.cpp
    Advantage.h
    Agent.cpp
    Agent.h
    AggressiveAgentStrategy.cpp
    AggressiveAgentStrategy.h
    DefaultAgentStrategy.h
    ErrorContext.cpp
    ErrorContext.h
    Exceptions.cpp
    Exceptions.h
    Food.cpp
    Food.h
    Game.cpp
    Game.h
    Gaming.h
    GamingTests.cpp
    GamingTests.h
    main.cpp
    Piece.cpp
    Piece.h
    Resource.cpp
    Resource.h
    Simple.cpp
    Simple.h
    Strategic.cpp
    Strategic.h
    Strategy.h DefaultAgentStrategy.cpp)

add_executable(ucd_csci2312_pa4 ${SOURCE_FILES} DefaultAgentStrategy.cpp)