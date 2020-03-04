
set(srcs "epd2in9.cpp" "epdif.cpp" "epdpaint.cpp" "font8.cpp" "font12.cpp" "font16.cpp" "font20.cpp" "font24.cpp" "font40.cpp")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "include")
