cmake_minimum_required(VERSION 3.5)

project(StarterSpring24 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing -Wno-narrowing")

add_executable(StarterSpring24
   main.cpp
)

include_directories(utility, third_party/fmt/include)
target_sources(${PROJECT_NAME} PUBLIC
    mssm.h
    utility/rand.h
    utility/rand.cpp
    utility/array.h
    utility/array.cpp

    third_party/fmt/include/fmt/core.h
    third_party/fmt/include/fmt/format.h
    third_party/fmt/include/fmt/format-inl.h
    third_party/fmt/src/format.cc
)

include_directories(utility third_party third_party/sago)
target_sources(${PROJECT_NAME} PUBLIC
    ${ASSETS}
    third_party/sago/platform_folders.cpp
    third_party/sago/platform_folders.h
    third_party/whereami.c
    third_party/whereami.h
    utility/paths.h
    utility/paths.cpp
)

set(ASSETS_SOURCE_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/assets")

file(GLOB_RECURSE ASSETS "${ASSETS_SOURCE_FOLDER}/*")

# Filter values through regex
#   filter_regex({INCLUDE | EXCLUDE} <regex> <listname> [items...])
#   Element will included into result list if
#     INCLUDE is specified and it matches with regex or
#     EXCLUDE is specified and it doesn't match with regex.
# Example:
#   filter_regex(INCLUDE "(a|c)" LISTOUT a b c d) => a c
#   filter_regex(EXCLUDE "(a|c)" LISTOUT a b c d) => b d
function(filter_regex _action _regex _listname)
    # check an action
    if("${_action}" STREQUAL "INCLUDE")
        set(has_include TRUE)
    elseif("${_action}" STREQUAL "EXCLUDE")
        set(has_include FALSE)
    else()
        message(FATAL_ERROR "Incorrect value for ACTION: ${_action}")
    endif()

    set(${_listname})
    foreach(element ${ARGN})
        string(REGEX MATCH ${_regex} result ${element})
        if(result)
            if(has_include)
                list(APPEND ${_listname} ${element})
            endif()
        else()
            if(NOT has_include)
                list(APPEND ${_listname} ${element})
            endif()
        endif()
    endforeach()

    # put result in parent scope variable
    set(${_listname} ${${_listname}} PARENT_SCOPE)
endfunction()

filter_regex(EXCLUDE "\\.DS_Store" ASSETS ${ASSETS})

set(ASSET_DEST_FILES "")

# loop over assets and make sure they get copied to the executable location
foreach (FILE ${ASSETS})

    # Get the relative path from the data-folder to the particular file.
    file(RELATIVE_PATH NEW_FILE "${ASSETS_SOURCE_FOLDER}" ${FILE})

    # Get the relative path to the file.
    get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)

    # MAC:  Set it's location inside the app package (under Resources).
    set_property(SOURCE ${FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${NEW_FILE_PATH}")

#    message("Setting property")

    if(NOT APPLE)
        set(OUTF "${CMAKE_CURRENT_BINARY_DIR}/assets/${NEW_FILE}")

        list(APPEND ASSET_DEST_FILES ${OUTF})

        get_filename_component(OUTF_DIR "${OUTF}" DIRECTORY)

#        message("Adding custom command")
        add_custom_command(
            OUTPUT "${OUTF}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTF_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FILE} ${OUTF}
            COMMENT "Copying ${FILE} to ${OUTF}"
            DEPENDS ${FILE}
            VERBATIM
        )
    endif()

    # Make sure it shows up in the IDE Assets folder
    source_group("Assets/${NEW_FILE_PATH}" FILES "${FILE}")

endforeach ()

if(NOT APPLE)
    add_custom_target(asset_dest_target
        DEPENDS
            ${ASSET_DEST_FILES}
    )

    add_dependencies(${PROJECT_NAME} asset_dest_target)
endif()


install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION assets)
