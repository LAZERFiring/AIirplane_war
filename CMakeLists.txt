cmake_minimum_required(VERSION 3.14)

project(QtGame LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(QtGame
  main.cpp
  Game.h
  Game.cpp
  Entity.h
  Manager.h
  Sprite.h
  Sprite.cpp

  Map.h
  Map.cpp
  PlayerPlane.h
  PlayerPlane.cpp
  Bullet.h
  Bullet.cpp
  Resource.qrc

  EnemyPlane.h
  EnemyPlane.cpp
  Global.h
  Animation.h
  Animation.cpp
)
target_link_libraries(QtGame Qt${QT_VERSION_MAJOR}::Widgets)
