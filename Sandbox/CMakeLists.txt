add_executable(Sandbox)

file(GLOB_RECURSE SANDBOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(Sandbox PRIVATE ${SANDBOX_SOURCES})

target_link_libraries(Sandbox PRIVATE Engine)
