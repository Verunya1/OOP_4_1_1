cmake_minimum_required(VERSION 3.20)
project(OOP_4_1_1)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        base.h
        application.h

        base.cpp base.cpp base.h application.cpp application.h baseT.cpp baseT.h)
set(PROJECT_SOURCES
        main.cpp
        application.cpp

        base.cpp base.cpp base.h application.cpp application.h baseT.cpp baseT.h)
add_executable(untitled1 ${PROJECT_SOURCES} ${PROJECT_HEADERS} base.cpp)
add_executable(OOP_4_1_1 main.cpp base.cpp base.h application.cpp application.h baseT.cpp baseT.h)
