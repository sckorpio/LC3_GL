# - Try to find Pango
# Once done, this will define
#
#  PANGO_FOUND - system has Pango
#  PANGO_INCLUDE_DIRS - the Pango include directories
#  PANGO_LIBRARIES - link these to use Pango
#  PANGO_DEFINITIONS - compiler flags
#  PANGOCAIRO_FOUND - system has Pangocairo
#  PANGOFT2_FOUND - system has Pangoft2

FIND_PACKAGE(PkgConfig)

# pango main library
PKG_CHECK_MODULES(PC_PANGO QUIET pango)
SET(PANGO_DEFINITIONS ${PC_PANGO_CFLAGS_OTHER})

SET(PANGO_INCLUDE_HINTS
        ${PC_PANGO_INCLUDEDIR}
        ${PC_PANGO_INCLUDE_DIRS}
        $ENV{PANGO_HOME}/include
        $ENV{PANGO_ROOT}/include
        /usr/local/include
        /usr/include
        /usr/lib #For glibconfig.h
        /pango/include
        ${PROJECT_SOURCE_DIR}/../third_party/pango
        )
FIND_PATH(PANGO_INCLUDE_DIR
        NAMES pango/pango.h
        HINTS ${PANGO_INCLUDE_HINTS}
        PATH_SUFFIXES pango pango-1.0 pango1.0
        )
FIND_PATH(GLIB_INCLUDE_DIR
        NAMES glib.h
        HINTS ${PANGO_INCLUDE_HINTS}
        PATH_SUFFIXES glib glib-2 glib-2.0
        )
FIND_PATH(GLIBCONFIG_INCLUDE_DIR
        NAMES glibconfig.h
        HINTS ${PANGO_INCLUDE_HINTS}
        PATH_SUFFIXES glib glib-2 glib-2.0 glib/include glib-2/include glib-2.0/include
        )

SET(PANGO_LIBRARY_HINTS
        ${PC_PANGO_LIBDIR}
        ${PC_PANGO_LIBRARY_DIRS}
        $ENV{PANGO_HOME}/lib
        $ENV{PANGO_ROOT}/lib
        /usr/local/lib
        /usr/lib
        /lib
        /pango/lib
        ${PROJECT_SOURCE_DIR}/../third_party/pango/lib
        )
FIND_LIBRARY(PANGO_LIBRARY
        NAMES pango PANGO PANGO-1.0 pango-1.0 libpango-1.0.0
        HINTS ${PANGO_LIBRARY_HINTS}
        PATH_SUFFIXES pango pango-1.0 pango1.0
        )

SET(PANGO_INCLUDE_DIRS ${PANGO_INCLUDE_DIR} ${GLIB_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR})
SET(PANGO_LIBRARIES ${PANGO_LIBRARY})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pango DEFAULT_MSG PANGO_INCLUDE_DIRS PANGO_LIBRARIES)
MARK_AS_ADVANCED(PANGO_INCLUDE_DIR PANGO_LIBRARY)

IF(PANGO_FOUND)
    message(STATUS "Found Pango include dir: ${PANGO_INCLUDE_DIRS}")
    message(STATUS "Found Pango library: ${PANGO_LIBRARY}")
    # pangocairo
    PKG_CHECK_MODULES(PC_PANGOCAIRO QUIET pangocairo)
    FIND_PATH(PANGOCAIRO_INCLUDE_DIRS
            NAMES pango/pangocairo.h
            HINTS ${PC_PANGOCAIRO_INCLUDEDIR}
            ${PC_PANGOCAIRO_INCLUDE_DIRS}
            $ENV{PANGOCAIRO_HOME}/include
            $ENV{PANGOCAIRO_ROOT}/include
            /pangocairo/include
            ${PANGO_INCLUDE_HINTS}
            PATH_SUFFIXES pango pangocairo libpangocairo-1.0 pangocairo1.0
            )
    IF(PANGOCAIRO_INCLUDE_DIRS)
        SET(PANGO_INCLUDE_DIRS ${PANGO_INCLUDE_DIRS} ${PANGOCAIRO_INCLUDE_DIRS})
    ENDIF()
    FIND_LIBRARY(PANGOCAIRO_LIBRARIES
            NAMES pangocairo PANGOcairo PANGOcairo-1.0 pangocairo-1.0 libpangocairo-1.0
            HINTS ${PC_PANGOCAIRO_LIBDIR}
            ${PC_PANGOCAIRO_LIBRARY_DIRS}
            $ENV{PANGOCAIRO_HOME}/lib
            $ENV{PANGOCAIRO_ROOT}/lib
            ${PANGO_LIBRARY_HINTS}
            PATH_SUFFIXES pango pangocairo libpangocairo-1.0 pangocairo1.0
            )
    IF(PANGOCAIRO_LIBRARIES)
        SET(PANGO_LIBRARIES ${PANGO_LIBRARIES} ${PANGOCAIRO_LIBRARIES})
    ENDIF()
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pangocairo DEFAULT_MSG PANGOCAIRO_INCLUDE_DIRS PANGOCAIRO_LIBRARIES)

    # pangoft2
    PKG_CHECK_MODULES(PC_PANGOFT2 QUIET pangoft2)
    FIND_PATH(PANGOFT2_INCLUDE_DIRS
            NAMES pango/pangoft2.h
            HINTS ${PC_PANGOFT2_INCLUDEDIR}
            ${PC_PANGOFT2_INCLUDE_DIRS}
            $ENV{PANGOFT2_HOME}/include
            $ENV{PANGOFT2_ROOT}/include
            /pangoft2/include
            ${PANGO_INCLUDE_HINTS}
            PATH_SUFFIXES pango pangoft2 libpangoft2-1.0 pangoft21.0
            )
    IF(PANGOFT2_INCLUDE_DIRS)
        SET(PANGO_INCLUDE_DIRS ${PANGO_INCLUDE_DIRS} ${PANGOFT2_INCLUDE_DIRS})
    ENDIF()
    FIND_LIBRARY(PANGOFT2_LIBRARIES
            NAMES pangoft2 pangoft2-1.0 libpangoft2-1.0
            HINTS ${PC_PANGOFT2_LIBDIR}
            ${PC_PANGOFT2_LIBRARY_DIRS}
            $ENV{PANGOFT2_HOME}/lib
            $ENV{PANGOFT2_ROOT}/lib
            ${PANGO_LIBRARY_HINTS}
            PATH_SUFFIXES pango pangoft2 libpangoft2-1.0 pangoft21.0
            )
    IF(PANGOFT2_LIBRARIES)
        SET(PANGO_LIBRARIES ${PANGO_LIBRARIES} ${PANGOFT2_LIBRARIES})
    ENDIF()
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pangoft2 DEFAULT_MSG PANGOFT2_INCLUDE_DIRS PANGOFT2_LIBRARIES)

    MARK_AS_ADVANCED(PANGOCAIRO_INCLUDE_DIRS PANGOCAIRO_LIBRARIES PANGOFT2_INCLUDE_DIRS PANGOFT2_LIBRARIES)
ENDIF()