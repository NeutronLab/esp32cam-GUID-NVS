
idf_component_register(SRCS "guid-handler.cpp"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES "guid-generator"
                    REQUIRES nvs_flash)
