file(GLOB_RECURSE RPM_METER_LIB_SOURCES *.cpp *.h)

add_library(rpmmeterlib ${RPM_METER_LIB_SOURCES})

target_link_libraries(rpmmeterlib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
