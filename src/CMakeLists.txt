

file(GLOB_RECURSE HEADER_LIST "${PROJECT_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_library (ph_color
	${SOURCE_LIST}  ${HEADER_LIST} 
)



# ph_precompile (TARGET ph_color PRIVATE PCH ${std_pch})

add_library (ph::color ALIAS ph_color)
# target_link_libraries (ph_color PRIVATE ${Boost_LIBRARIES})
target_include_directories (ph_color PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_include_directories (ph_color PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_features (ph_color PRIVATE cxx_std_20)


target_include_directories(ph_color PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/ph_color>
    $<INSTALL_INTERFACE:include/ph_color>
)

target_include_directories(ph_color PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

else()
    set_target_properties(${PROJECT_NAME}          PROPERTIES FOLDER "dependencies/${PROJECT_NAME}")
endif()