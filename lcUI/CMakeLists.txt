CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT (LC)
ADD_DEFINITIONS(-std=c++14)
ADD_DEFINITIONS("-Wall")
set(CMAKE_CXX_STANDARD 14)

message("***** LibreCAD Qt user interface *****")

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Designer)
find_package(Qt5Gui REQUIRED)
find_package(Qt5UiTools REQUIRED)

SET(QT_USE_QTDESIGNER ON)

# HEADERS
set(UI_hdrs
cadmdichild.h
const.h
luainterface.h
lcadviewer.h
lcadviewerproxy.h
lcadmodelviewerimpl.h
lcadpaperviewerimpl.h
lcadmodelviewer.h
lcadpaperviewer.h
widgets/clicommand.h
widgets/luascript.h
widgets/toolbar.h
widgets/toolbartab.h
widgets/layers.h
widgets/layermodel.h
widgets/linepatternselect.h
widgets/linepatternpainter.h
widgets/linepatternpathpart.h
widgets/linepatternmodel.h
widgets/linewidthselect.h
widgets/colorselect.h
lua/qtbridge.h
lua/luaqobject.h
dialogs/addlayerdialog.h
dialogs/addlinepatterndialog.h
dialogs/linepatternmanager.h
        managers/metainfomanager.cpp managers/metainfomanager.h)

set(UI_srcs
cadmdichild.cpp
main.cpp
luainterface.cpp
lcadviewer.cpp
lcadviewerproxy.cpp
lcadmodelviewerimpl.cpp
lcadpaperviewerimpl.cpp
lcadmodelviewer.cpp
lcadpaperviewer.cpp
widgets/clicommand.cpp
widgets/luascript.cpp
widgets/toolbar.cpp
widgets/toolbartab.cpp
widgets/layers.cpp
widgets/layermodel.cpp
widgets/linepatternselect.cpp
widgets/linepatternpainter.cpp
widgets/linepatternpathpart.cpp
widgets/linepatternmodel.cpp
widgets/linewidthselect.cpp
widgets/colorselect.cpp
lua/qtbridge.cpp
lua/luaqobject.cpp
dialogs/addlayerdialog.cpp
dialogs/addlinepatterndialog.cpp
dialogs/linepatternmanager.cpp
        managers/metainfomanager.cpp managers/metainfomanager.h)

QT5_WRAP_UI(UI_HEADERS
widgets/clicommand.ui
widgets/luascript.ui
widgets/toolbar.ui
widgets/toolbartab.ui
widgets/layers.ui
widgets/linepatternpathpart.ui
dialogs/addlayerdialog.ui
dialogs/addlinepatterndialog.ui
dialogs/linepatternmanager.ui)

qt5_add_resources(UI_RESOURCES
ui/resource.qrc)

# Eigen 3
find_package(Eigen3 REQUIRED)
if(CMAKE_COMPILER_IS_GNUCXX)
    include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
else()
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# Boost logging
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.54.0 REQUIRED COMPONENTS log)
FIND_PACKAGE ( Threads )
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

#Lua
find_package(Lua 5.2 REQUIRED)
include_directories(${LUA_INCLUDE_DIR})
link_directories(${LUA_LIBRARY_DIRS})

# BUILDING CONFIG
# SEPARATE BUILDING FLAG
set(SEPARATE_BUILD OFF)

# --------------------temporary-------------------

# OpenGL & GLEW library-------------------------

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(NOT ${OPENGL_FOUND})
    message("OPENGL not found")
endif()

# include directories----------------------------

include_directories(
    ${GLEW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    )

message(${OPENGL_INCLUDE_DIR})
#--------------------------------------------------



if (SEPARATE_BUILD STREQUAL "ON")
    include_directories("${CMAKE_SOURCE_DIR}/../lckernel")
    include_directories("${CMAKE_SOURCE_DIR}/../third_party")
    include_directories("${CMAKE_SOURCE_DIR}/../persistence")
    include_directories("${CMAKE_SOURCE_DIR}/../lcviewernoqt")
    include_directories("${CMAKE_SOURCE_DIR}/../lcviewerqt")
    include_directories("${CMAKE_SOURCE_DIR}/../lcadluascript")
    include_directories("${CMAKE_SOURCE_DIR}/../lcUI")
    include_directories("${CMAKE_SOURCE_DIR}/../third_party/kaguya/include")
else() 
    include_directories("${CMAKE_SOURCE_DIR}/lckernel")
    include_directories("${CMAKE_SOURCE_DIR}/third_party")
    include_directories("${CMAKE_SOURCE_DIR}/persistence")
    include_directories("${CMAKE_SOURCE_DIR}/lcviewernoqt")
    include_directories("${CMAKE_SOURCE_DIR}/lcviewerqt")
    include_directories("${CMAKE_SOURCE_DIR}/lcadluascript")
    include_directories("${CMAKE_SOURCE_DIR}/lcUI")
    include_directories("${CMAKE_SOURCE_DIR}/third_party/kaguya/include")
endif()

link_directories(${PANGO_LIBRARY_DIRS})

set(EXTRA_LIBS
        lcluascript
        lcviewernoqt
        persistence
        lckernel
        ${LUA_LIBRARIES}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::UiTools
        ${APR_LIBRARIES})

#Create library for unit tests
if(WITH_UNITTESTS)
    add_library(lcui SHARED ${UI_srcs} ${UI_hdrs} ${UI_HEADERS} ${UI_RESOURCES})
    target_link_libraries(lcui ${EXTRA_LIBS})
endif(WITH_UNITTESTS)

add_executable(librecad ${UI_srcs} ${UI_hdrs} ${UI_HEADERS} ${UI_RESOURCES})
target_link_libraries(librecad ${EXTRA_LIBS} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} -lboost_system
${OPENGL_LIBRARY}
${GLEW_LIBRARY})
