add_executable(portarrays
    main.cpp
)

target_include_directories(portarrays
    PRIVATE ${SYSTEMC_INCLUDE}
)

target_link_libraries(portarrays
    PRIVATE ${SYSTEMC_LIBRARY}
)

find_library(SYSTEMC_LIBRARY 
    NAMES systemc
    PATHS $ENV{SYSTEMC_HOME}/lib-$ENV{SYSTEMC_TARGET_ARCH}/
)

