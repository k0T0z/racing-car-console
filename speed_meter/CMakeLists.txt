file(GLOB_RECURSE SPEED_METER_LIB_SOURCES *.cpp *.h)

add_library(speedmeterlib ${SPEED_METER_LIB_SOURCES})

target_link_libraries(speedmeterlib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
