add_library(${libcolor}
        include/termcolor.hpp
        )

target_include_directories(${libcolor}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )


target_link_libraries(${libcolor})

set_target_properties(${libcolor}
        PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 17
        )


install(TARGETS ${libcolor}
        ARCHIVE DESTINATION lib
        )

