cmake_minimum_required(VERSION 3.10)

project(keneric
  DESCRIPTION "keneric script based thumbnail generator for KDE")

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(WriteBasicConfigVersionFile)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF5 REQUIRED COMPONENTS KIO)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )

set(keneric_PART_SRCS keneric.cpp)

add_library(keneric MODULE ${keneric_PART_SRCS})

target_link_libraries(keneric Qt5::Gui KF5::KIOWidgets)

install(TARGETS keneric DESTINATION ${PLUGIN_INSTALL_DIR})
install(PROGRAMS scripts/keneric DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES desktop/kenericstl.desktop desktop/kenericstlb.desktop DESTINATION ${SERVICES_INSTALL_DIR})
