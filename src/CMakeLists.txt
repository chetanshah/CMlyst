include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Our sources
set(cmlyst_SRCS
    ${TEMPLATES_SRC}
    libCMS/page.cpp
    libCMS/page_p.h
    libCMS/engine.cpp
    libCMS/engine_p.h
#    libCMS/fileengine.cpp
#    libCMS/fileengine_p.h
    libCMS/menu.cpp
    libCMS/menu_p.h
    libCMS/sqlengine.cpp
    sqluserstore.cpp
    cmengine.cpp
    cmdispatcher.cpp
    root.cpp
    admin.cpp
    adminsetup.cpp
    adminappearance.cpp
    adminpages.cpp
    adminposts.cpp
    adminmedia.cpp
    adminsettings.cpp
    cmlyst.cpp
    rsswriter.cpp
)

# C++11 rocks!
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Create the application
add_library(cmlyst SHARED ${cmlyst_SRCS})

# Link to Cutelyst
target_link_libraries(cmlyst
    Cutelyst::Core
    Cutelyst::View::Grantlee
    Cutelyst::Utils::Sql
    Cutelyst::Authentication
    Cutelyst::StatusMessage
    Cutelyst::Utils::Pagination
    Qt5::Core
    Qt5::Network
    Qt5::Sql
)

# TODO install to a place where uWSGI Cutelyst plugin searches for
install(TARGETS cmlyst DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
