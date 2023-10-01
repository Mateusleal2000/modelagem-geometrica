cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)


include(CMakePrintHelpers)



project(modelagem LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Core Gui OpenGL OpenGLWidgets)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(modelagem main.cpp 
                  Box.cpp 
                  Node.cpp 
                  OctTree.cpp 
                  Sphere.cpp
                  Mesh.cpp
                  GLWidget.cpp
                  testGL.cpp
                  Mesh.cpp
                  Block.cpp
                  Triangle.cpp
                  Camera.cpp
                  MainWidget.cpp
                  OptionsWidget.cpp
                  resources.qrc
)

target_link_libraries(modelagem PRIVATE Qt6::Core Qt6::Gui Qt6::OpenGL Qt6::OpenGLWidgets)

