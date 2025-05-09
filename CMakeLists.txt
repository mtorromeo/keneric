cmake_minimum_required(VERSION 3.16)

project(keneric
  DESCRIPTION "keneric script based thumbnail generator for KDE")

set(QT_REQUIRED_VERSION "6.5.0")
set(KF_MIN_VERSION "6.0.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH}  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui)
find_package(KF${QT_MAJOR_VERSION} ${KF_MIN_VERSION} REQUIRED COMPONENTS KIO)

set(KDE_COMPILERSETTINGS_LEVEL "6.0")
ecm_set_disabled_deprecation_versions(QT 6.5.0 KF 6.0.0)

kcoreaddons_add_plugin(keneric SOURCES keneric.cpp INSTALL_NAMESPACE "kf${QT_MAJOR_VERSION}/thumbcreator")

target_link_libraries(keneric
  Qt::Core
  Qt::Gui
  KF${QT_MAJOR_VERSION}::KIOWidgets
  KF${QT_MAJOR_VERSION}::KIOCore
)

ecm_qt_declare_logging_category(keneric
  HEADER keneric_debug.h
  IDENTIFIER KENERIC_DEBUG
  CATEGORY_NAME keneric
  DESCRIPTION "keneric thumbnail generator"
  EXPORT PLASMAWORKSPACE
)


install(PROGRAMS scripts/keneric DESTINATION ${CMAKE_INSTALL_BINDIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
