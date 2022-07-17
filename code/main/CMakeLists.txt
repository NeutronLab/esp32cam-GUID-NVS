FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/main/*.*)


idf_component_register(SRCS "esp32cam_GUID_NVS.cpp"
                    INCLUDE_DIRS ".")
