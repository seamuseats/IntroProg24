cmake_minimum_required(VERSION 3.13.0)

# HEY!  Need to add additional files to the project?  (cpp, header, etc)
# Scroll down to line 53 or so to see where

# TRYING TO DEPLOY?
# switch to a "release build"  then, on projects/build/build steps/details check the "package" checkbox
# so it looks like this: Build: cmake.exe --build C:/yadayada_MinGW_64_bit-Release --target all package

# Linux folks: 

# sudo apt install git
# sudo apt install build-essential
# sudo apt install cmake
# sudo apt install xorg-dev
# sudo apt install freeglut3-dev
# sudo apt install nasm
# sudo snap install --classic code

# Use project folder name as project name
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)
string(REPLACE " " "_" ProjectId ${PROJECT_NAME})

project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing -Wno-narrowing")

if(WIN32)
set(ADD_EX_EXTRA WIN32)
else()
set(ADD_EX_EXTRA "")
endif()

set(USE_TESTS FALSE)

set(INCLUDE_FMT TRUE)
set(INCLUDE_RANDOM TRUE)
set(INCLUDE_PATHS TRUE)
set(INCLUDE_ARRAY TRUE)
set(INCLUDE_VEC2D TRUE)
set(INCLUDE_GRAPHICS TRUE)   # TRUE to include graphics.h, etc (requires INCLUDE_ARRAY, INCLUDE_VEC2D, INCLUDE_PATHS)
set(INCLUDE_SOUND TRUE)      # TRUE to include audio/sound support
set(INCLUDE_SERIAL FALSE)    # TRUE to include serial port support
set(INCLUDE_SOCKETS TRUE)
set(INCLUDE_CAMERA FALSE)
set(INCLUDE_FILE_DLG FALSE)  
set(INCLUDE_JSON FALSE)
set(INCLUDE_FFMPEG FALSE)
set(INCLUDE_GTEST FALSE)

include_directories(botbattle)

add_executable(${PROJECT_NAME} ${ADD_EX_EXTRA}
    # Hey!  Add additional c, cpp, h files here:
    botbattle/botcmd.h
    botbattle/botmanager.cpp
    botbattle/botmanager.h
    botbattle/connectedbot.cpp
    botbattle/connectedbot.h
    botbattle/bot.cpp
    botbattle/bot.h
    botbattle/botai.cpp
    botbattle/botai.h
    botbattle/botcmd.cpp
    dylanTools.h
    world.cpp
    world.h
)

# STUDENTS:  Probably don't mess with anything below this point
#######################################################################################
#######################################################################################

if(INCLUDE_GTEST)
    include_directories(third_party/gtest)
    target_sources(${PROJECT_NAME} PUBLIC


        third_party/gtest/gtest-typed-test.h
        third_party/gtest/gtest.h
        third_party/gtest/gtest_pred_impl.h
        third_party/gtest/gtest_prod.h
        third_party/gtest/gtest-death-test.h
        third_party/gtest/gtest-matchers.h
        third_party/gtest/gtest-message.h
        third_party/gtest/gtest-param-test.h
        third_party/gtest/gtest-printers.h
        third_party/gtest/gtest-spi.h
        third_party/gtest/gtest-test-part.h
        third_party/gtest/src/gtest-typed-test.cc
        third_party/gtest/src/gtest.cc
        third_party/gtest/src/gtest-death-test.cc
        third_party/gtest/src/gtest-filepath.cc
        third_party/gtest/src/gtest-matchers.cc
        third_party/gtest/src/gtest-port.cc
        third_party/gtest/src/gtest-printers.cc
        third_party/gtest/src/gtest-test-part.cc
        third_party/gtest/internal/gtest-death-test-internal.h
        third_party/gtest/internal/gtest-filepath.h
        third_party/gtest/internal/gtest-internal.h
        third_party/gtest/internal/gtest-param-util.h
        third_party/gtest/internal/gtest-port.h
        third_party/gtest/internal/gtest-port-arch.h
        third_party/gtest/internal/gtest-string.h
        third_party/gtest/internal/gtest-type-util.h

    )
endif()


if (INCLUDE_FFMPEG)
    # FFmpeg

    # install libraries from https://github.com/BtbN/FFmpeg-Builds/releases
    #  On windows, I'm using ffmpeg-master-latest-win64-lgpl-shared.zip   (lgpl license)

    #set(FFmpeg_ROOT "" CACHE PATH "C:/Users/hamling/Documents/Github/ffmpeg-master-latest-win64-lgpl-shared")

    #set(FFmpeg_ROOT "C:/Users/hamling/Documents/Github/ffmpeg-master-latest-win64-lgpl-shared")
    set(FFmpeg_ROOT "../../ffmpeg-master-latest-win64-lgpl-shared")

    FIND_PATH(FFMPEG_INCLUDE_DIR_AVUTIL NAMES libavutil/avutil.h PATHS ${FFmpeg_ROOT}/include)
    FIND_PATH(FFMPEG_INCLUDE_DIR_AVCODEC NAMES libavcodec/avcodec.h PATHS ${FFmpeg_ROOT}/include)
    FIND_PATH(FFMPEG_INCLUDE_DIR_AVFORMAT NAMES libavformat/avformat.h PATHS ${FFmpeg_ROOT}/include)
    FIND_PATH(FFMPEG_INCLUDE_DIR_AVDEVICE NAMES libavdevice/avdevice.h PATHS ${FFmpeg_ROOT}/include)
    FIND_PATH(FFMPEG_INCLUDE_DIR_AVFILTER NAMES libavfilter/avfilter.h PATHS ${FFmpeg_ROOT}/include)
    FIND_PATH(FFMPEG_INCLUDE_DIR_SWSCALE NAMES libswscale/swscale.h PATHS ${FFmpeg_ROOT}/include)
    FIND_PATH(FFMPEG_INCLUDE_DIR_SWRESAMPLE NAMES libswresample/swresample.h PATHS ${FFmpeg_ROOT}/include)

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${FFMPEG_INCLUDE_DIR_AVUTIL}
        ${FFMPEG_INCLUDE_DIR_AVCODEC}
        ${FFMPEG_INCLUDE_DIR_AVFORMAT}
        ${FFMPEG_INCLUDE_DIR_AVDEVICE}
        ${FFMPEG_INCLUDE_DIR_AVFILTER}
        ${FFMPEG_INCLUDE_DIR_SWSCALE}
        ${FFMPEG_INCLUDE_DIR_SWRESAMPLE}
    )

    FIND_LIBRARY(FFMPEG_AVUTIL_LIBRARY NAMES avutil PATHS ${FFmpeg_ROOT}/lib )
    FIND_LIBRARY(FFMPEG_AVCODEC_LIBRARY NAMES avcodec PATHS ${FFmpeg_ROOT}/lib )
    FIND_LIBRARY(FFMPEG_AVFORMAT_LIBRARY NAMES avformat PATHS ${FFmpeg_ROOT}/lib )
    FIND_LIBRARY(FFMPEG_AVDEVICE_LIBRARY NAMES avdevice PATHS ${FFmpeg_ROOT}/lib )
    FIND_LIBRARY(FFMPEG_AVFILTER_LIBRARY NAMES avfilter PATHS ${FFmpeg_ROOT}/lib )
    FIND_LIBRARY(FFMPEG_SWSCALE_LIBRARY NAMES swscale PATHS ${FFmpeg_ROOT}/lib )
    FIND_LIBRARY(FFMPEG_SWRESAMPLE_LIBRARY NAMES swresample PATHS ${FFmpeg_ROOT}/lib )

    target_link_libraries(${PROJECT_NAME}
        ${FFMPEG_AVUTIL_LIBRARY}
        ${FFMPEG_AVCODEC_LIBRARY}
        ${FFMPEG_AVFORMAT_LIBRARY}
        ${FFMPEG_AVDEVICE_LIBRARY}
        ${FFMPEG_AVFILTER_LIBRARY}
        ${FFMPEG_SWSCALE_LIBRARY}
        ${FFMPEG_SWRESAMPLE_LIBRARY}
    )
endif()


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/")

message("Before")
message(${CMAKE_INSTALL_PREFIX})

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
message(${CMAKE_INSTALL_PREFIX})
message("After")

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()



if(USE_TESTS)
    # override flags since we want to test everything
    set(INCLUDE_RANDOM TRUE)   # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_PATHS TRUE)    # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_ARRAY TRUE)    # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_VEC2D TRUE)    # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_GRAPHICS TRUE) # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_SOUND TRUE)    # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_SERIAL TRUE)   # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_SOCKETS TRUE)  # CHANGE THESE FLAGS ABOVE, NOT HERE!
    set(INCLUDE_FILE_DLG TRUE)  # CHANGE THESE FLAGS ABOVE, NOT HERE!

    target_sources(${PROJECT_NAME} PUBLIC
        tests.cpp
    )
else()
    target_sources(${PROJECT_NAME} PUBLIC
        main.cpp
    )
endif()

#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
#find_package(Threads REQUIRED)

#target_link_libraries(${PROJECT_NAME} Threads::Threads)

add_compile_definitions(CMAKE_PROJECT_NAME=${PROJECT_NAME})

add_compile_definitions(WITH_MINIAUDIO)

#add_compile_definitions(DISABLE_ARRAY_SAFETY_CHECKS)

#include_directories(
#    third_party/nanovg
#    third_party
#    third_party/glfw/include
#)

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

if(INCLUDE_CAMERA)
    include_directories(third_party/openpnp-capture/include)
    target_sources(${PROJECT_NAME} PUBLIC
        third_party/openpnp-capture/common/libmain.cpp
        third_party/openpnp-capture/common/context.cpp
        third_party/openpnp-capture/common/logging.cpp
        third_party/openpnp-capture/common/stream.cpp
        graphics/camera.h
        graphics/camera.cpp
    )
    if (WIN32)
        target_sources(${PROJECT_NAME} PUBLIC
            third_party/openpnp-capture/win/platformcontext.cpp
            third_party/openpnp-capture/win/platformstream.cpp
        )
        target_link_libraries(${PROJECT_NAME} strmiids)
    endif()
    if (APPLE)
        target_sources(${PROJECT_NAME} PUBLIC
            third_party/openpnp-capture/mac/platformcontext.mm
            third_party/openpnp-capture/mac/platformstream.mm
            third_party/openpnp-capture/mac/uvcctrl.mm
        )
    target_link_libraries(${PROJECT_NAME}
        "-framework AVFoundation"
        "-framework Foundation"
        "-framework CoreMedia"
        "-framework CoreVideo"
        "-framework Accelerate"
        "-framework IOKit"
        )
    endif()
    if (LINUX)

        include_directories(third_party/openpnp-capture/linux/contrib/libjpeg-turbo-dev)
        target_sources(${PROJECT_NAME} PUBLIC
            third_party/openpnp-capture/linux/platformcontext.cpp
            third_party/openpnp-capture/linux/platformstream.cpp
            third_party/openpnp-capture/linux/mjpeghelper.cpp            
            third_party/openpnp-capture/linux/yuvconverters.cpp
        )
                # force include directories for libjpeg-turbo
        #include_directories(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/linux/contrib/libjpeg-turbo-dev")
        # add pthreads library 
        set(THREADS_PREFER_PTHREAD_FLAG ON)
        find_package(Threads REQUIRED)    
        target_link_libraries(${PROJECT_NAME}  Threads::Threads)

        # add turbojpeg library
        find_package(PkgConfig REQUIRED)
        pkg_search_module(TurboJPEG libturbojpeg)
        if( TurboJPEG_FOUND )
            link_directories(${TurboJPEG_LIBDIR})
            target_include_directories(${PROJECT_NAME}  ${TurboJPEG_INCLUDE_DIRS})
            target_link_libraries(${PROJECT_NAME}  ${TurboJPEG_LIBRARIES})
        else()
            # compile libjpeg-turbo for MJPEG decoding support
            # right now, we need to disable SIMD because it
            # causes a compile problem.. we need to fix this
            # later...
            set(ENABLE_SHARED OFF)
            set(WITH_SIMD OFF)    
            set(TurboJPEG_LIBRARIES turbojpeg-static)  
            add_subdirectory(third_party/openpnp-capture/linux/contrib/libjpeg-turbo-dev)
            target_link_libraries(${PROJECT_NAME}  ${TurboJPEG_LIBRARIES})
        endif()
    endif()
endif()

if(INCLUDE_RANDOM)
    include_directories(utility)
    target_sources(${PROJECT_NAME} PUBLIC
        utility/rand.h
        utility/rand.cpp
    )
endif()

if(INCLUDE_PATHS)
    include_directories(utility third_party third_party/sago)
    target_sources(${PROJECT_NAME} PUBLIC
        ${ASSETS}
        third_party/sago/platform_folders.cpp
        third_party/sago/platform_folders.h
        third_party/whereami.c
        utility/paths.h
        utility/paths.cpp
    )
endif()

if(INCLUDE_FMT)
    include_directories(utility, third_party/fmt/include)
    target_sources(${PROJECT_NAME} PUBLIC
        utility/format_helper.h
        third_party/fmt/include/fmt/core.h
        third_party/fmt/include/fmt/format.h
        third_party/fmt/include/fmt/color.h
        third_party/fmt/include/fmt/format-inl.h
        third_party/fmt/src/format.cc

    )
endif()

if(INCLUDE_ARRAY)
    include_directories(utility)
    target_sources(${PROJECT_NAME} PUBLIC
        utility/array.h
        utility/array.cpp
    )
endif()

if(INCLUDE_VEC2D)
    include_directories(graphics)
    target_sources(${PROJECT_NAME} PUBLIC
        graphics/vec2d.cpp
        graphics/vec2d.h
    )

endif()

if(INCLUDE_GRAPHICS)
    include_directories(
        graphics
        third_party/nanovg
    #    third_party
        third_party/glfw/include
    )

    target_sources(${PROJECT_NAME} PUBLIC
        third_party/glfw/src/context.c
        third_party/glfw/src/init.c
        third_party/glfw/src/input.c
        third_party/glfw/src/monitor.c
        third_party/glfw/src/vulkan.c
        third_party/glfw/src/window.c
        third_party/glfw/src/platform.c
        third_party/glfw/src/null_platform.h
        third_party/glfw/src/null_init.c
        third_party/glfw/src/null_window.c
        third_party/glfw/src/null_monitor.c
        third_party/glfw/src/null_joystick.c
        third_party/nanovg/nanovg.c

        third_party/whereami.c

        third_party/glfw/include/GLFW/glfw3.h
        third_party/glfw/include/GLFW/glfw3native.h
        third_party/whereami.h
        third_party/nanovg/fontstash.h
        third_party/nanovg/nanovg.h
        third_party/nanovg/nanovg_gl.h
        third_party/nanovg/nanovg_gl_utils.h
        third_party/nanovg/stb_image.h
        third_party/stb_image_write.h
        third_party/nanovg/stb_truetype.h

        graphics/graphics.cpp
        graphics/graphics.h

        graphics/objcanvas.h
        graphics/objcanvas.cpp

        graphics/svgcanvas.h
        graphics/svgcanvas.cpp
    )
endif()

if(INCLUDE_SOUND)
    add_compile_definitions(INCLUDE_SOUND)
    include_directories(third_party/soloud/include)
    target_sources(${PROJECT_NAME}
        PUBLIC
        third_party/soloud/src/audiosource/wav/dr_impl.cpp
        third_party/soloud/src/audiosource/wav/soloud_wav.cpp
        third_party/soloud/src/audiosource/wav/soloud_wavstream.cpp
        third_party/soloud/src/audiosource/wav/stb_vorbis.c
        third_party/soloud/src/backend/miniaudio/soloud_miniaudio.cpp
        third_party/soloud/src/core/soloud.cpp
        third_party/soloud/src/core/soloud_audiosource.cpp
        third_party/soloud/src/core/soloud_bus.cpp
        third_party/soloud/src/core/soloud_core_3d.cpp
        third_party/soloud/src/core/soloud_core_basicops.cpp
        third_party/soloud/src/core/soloud_core_faderops.cpp
        third_party/soloud/src/core/soloud_core_filterops.cpp
        third_party/soloud/src/core/soloud_core_getters.cpp
        third_party/soloud/src/core/soloud_core_setters.cpp
        third_party/soloud/src/core/soloud_core_voicegroup.cpp
        third_party/soloud/src/core/soloud_core_voiceops.cpp
        third_party/soloud/src/core/soloud_fader.cpp
        third_party/soloud/src/core/soloud_fft.cpp
        third_party/soloud/src/core/soloud_fft_lut.cpp
        third_party/soloud/src/core/soloud_file.cpp
        third_party/soloud/src/core/soloud_filter.cpp
        third_party/soloud/src/core/soloud_misc.cpp
        third_party/soloud/src/core/soloud_queue.cpp
        third_party/soloud/src/core/soloud_thread.cpp
        third_party/soloud/include/soloud.h
        third_party/soloud/include/soloud_audiosource.h
        third_party/soloud/include/soloud_bassboostfilter.h
        third_party/soloud/include/soloud_biquadresonantfilter.h
        third_party/soloud/include/soloud_bus.h
        third_party/soloud/include/soloud_c.h
        third_party/soloud/include/soloud_dcremovalfilter.h
        third_party/soloud/include/soloud_echofilter.h
        third_party/soloud/include/soloud_error.h
        third_party/soloud/include/soloud_fader.h
        third_party/soloud/include/soloud_fft.h
        third_party/soloud/include/soloud_fftfilter.h
        third_party/soloud/include/soloud_file.h
        third_party/soloud/include/soloud_file_hack_off.h
        third_party/soloud/include/soloud_file_hack_on.h
        third_party/soloud/include/soloud_filter.h
        third_party/soloud/include/soloud_flangerfilter.h
        third_party/soloud/include/soloud_freeverbfilter.h
        third_party/soloud/include/soloud_internal.h
        third_party/soloud/include/soloud_lofifilter.h
        third_party/soloud/include/soloud_misc.h
        third_party/soloud/include/soloud_monotone.h
        third_party/soloud/include/soloud_noise.h
        third_party/soloud/include/soloud_openmpt.h
        third_party/soloud/include/soloud_queue.h
        third_party/soloud/include/soloud_robotizefilter.h
        third_party/soloud/include/soloud_sfxr.h
        third_party/soloud/include/soloud_speech.h
        third_party/soloud/include/soloud_tedsid.h
        third_party/soloud/include/soloud_thread.h
        third_party/soloud/include/soloud_vic.h
        third_party/soloud/include/soloud_vizsn.h
        third_party/soloud/include/soloud_wav.h
        third_party/soloud/include/soloud_waveshaperfilter.h
        third_party/soloud/include/soloud_wavstream.h
        third_party/soloud/src/audiosource/wav/dr_flac.h
        third_party/soloud/src/audiosource/wav/dr_mp3.h
        third_party/soloud/src/audiosource/wav/dr_wav.h
        third_party/soloud/src/audiosource/wav/stb_vorbis.h
        third_party/soloud/src/backend/miniaudio/miniaudio.h

        third_party/soloud/src/backend/portaudio/
        )
endif()



if (WIN32 AND INCLUDE_GRAPHICS)
    # add sources specific to Windows
target_sources(${PROJECT_NAME}
    PUBLIC
    third_party/glfw/src/win32_init.c
    third_party/glfw/src/win32_joystick.c
    third_party/glfw/src/win32_monitor.c
    third_party/glfw/src/win32_time.c
    third_party/glfw/src/win32_thread.c
    third_party/glfw/src/win32_window.c
    third_party/glfw/src/wgl_context.c
    third_party/glfw/src/egl_context.c
    third_party/glfw/src/osmesa_context.c
    third_party/glfw/src/win32_module.c
    third_party/glew.c
    third_party/glfw/src/win32_platform.h
    third_party/glfw/src/win32_joystick.h
    third_party/GL/eglew.h
    third_party/GL/glxew.h
    third_party/GL/wglew.h
    third_party/GL/glew.h
)
target_link_libraries(${PROJECT_NAME} gdi32 opengl32)
add_compile_definitions(_GLFW_WIN32 NANOVG_GLEW GLEW_STATIC PROVIDE_WINMAIN )
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)
endif()




if (APPLE AND INCLUDE_GRAPHICS)
    # add sources specific to macos
    target_sources(${PROJECT_NAME}
        PUBLIC
        third_party/glfw/src/cocoa_init.m
        third_party/glfw/src/cocoa_joystick.m
        third_party/glfw/src/cocoa_monitor.m
        third_party/glfw/src/cocoa_window.m
        third_party/glfw/src/cocoa_time.c
        third_party/glfw/src/posix_thread.c
        third_party/glfw/src/nsgl_context.m
        third_party/glfw/src/egl_context.c
        third_party/glfw/src/osmesa_context.c
        third_party/glfw/src/posix_module.c
        third_party/glfw/src/cocoa_platform.h
        third_party/glfw/src/cocoa_joystick.h
        third_party/glfw/src/posix_thread.h
    )
target_link_libraries(${PROJECT_NAME}
    "-framework Cocoa"
    "-framework IOKit"
    "-framework OpenGL")
add_compile_definitions(_GLFW_COCOA GL_SILENCE_DEPRECATION)

message("Switch to METAL on Mac at some point???")
    if (INCLUDE_CAMERA)
        set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_FRAMEWORK_IDENTIFIER org.mssm.${PROJECT_NAME}
        MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
        #  MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION}
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES
          MACOSX_BUNDLE TRUE
          MACOSX_FRAMEWORK_IDENTIFIER org.mssm.${PROJECT_NAME}
          MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
          #  MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION}
        )
    endif()
endif()



if (LINUX AND INCLUDE_GRAPHICS)
    # add sources specific to macos
    target_sources(${PROJECT_NAME}
        PUBLIC
       third_party/glfw/src/x11_init.c
       third_party/glfw/src/x11_monitor.c
       third_party/glfw/src/x11_window.c
       third_party/glfw/src/xkb_unicode.c
       third_party/glfw/src/posix_time.c
       third_party/glfw/src/posix_thread.c
       third_party/glfw/src/glx_context.c
       third_party/glfw/src/egl_context.c
       third_party/glfw/src/osmesa_context.c
       third_party/glfw/src/linux_joystick.c
       third_party/glew.c
       third_party/glfw/src/posix_module.c
       third_party/glfw/src/posix_poll.c
       third_party/glfw/src/posix_poll.h

       third_party/glfw/src/linux_joystick.h
       third_party/glfw/src/x11_platform.h
       third_party/glfw/src/xkb_unicode.h
       third_party/glfw/src/posix_time.h
       third_party/glfw/src/posix_thread.h
       third_party/GL/eglew.h
       third_party/GL/glxew.h
       third_party/GL/wglew.h
       third_party/GL/glew.h
    )

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(X11 REQUIRED)
    # x11 xrandr xi xxf86vm glew glfw3

    target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT ${CMAKE_DL_LIBS} ${X11_LIBRARIES} pthread)

    
    add_compile_definitions(_GLFW_X11 NANOVG_GLEW GLEW_STATIC)
endif()


if(INCLUDE_SOCKETS)
    add_compile_definitions(INCLUDE_SOCKETS ASIO_STANDALONE)
    include_directories(third_party/asio)

    target_sources(${PROJECT_NAME}
        PUBLIC
        comm/tcpserver.h
        comm/tcpserver.cpp
    )

    if(WIN32)
         target_link_libraries(${PROJECT_NAME} ws2_32 wsock32)
    elseif(APPLE)
         #apple specific stuff
    elseif(LINUX)
         #LINUX specific stuff
    endif()





endif()


if(INCLUDE_FILE_DLG)
    add_compile_definitions(INCLUDE_FILE_DLG)
    include_directories(third_party/nfd/include)



    if(WIN32)
        target_sources(${PROJECT_NAME}
            PUBLIC
            third_party/nfd/include/nfd.h
            third_party/nfd/include/nfd.hpp
            third_party/nfd/nfd_win.cpp
        )
    elseif(APPLE)
        #apple specific stuff
    elseif(LINUX)
        #LINUX specific stuff
    endif()

endif()


if(INCLUDE_JSON)
    add_compile_definitions(INCLUDE_JSON)
    include_directories(third_party/nlohmann)
    target_sources(${PROJECT_NAME}
        PUBLIC
        third_party/nlohmann/json.hpp
        third_party/nlohmann/json_fwd.hpp
    )
endif()


if(INCLUDE_SERIAL)
    add_compile_definitions(INCLUDE_SERIAL SP_PRIV=)
    include_directories(third_party/libserialport comm)
    target_sources(${PROJECT_NAME}
        PUBLIC
        third_party/libserialport/libserialport.h
        third_party/libserialport/libserialport_internal.h
        third_party/libserialport/serialport.c
        comm/serialport.h
        comm/serialport.cpp
    )

    if(WIN32)
        target_sources(${PROJECT_NAME}
            PUBLIC
            third_party/libserialport/windows.c
            third_party/libserialport/timing.c
        )
        target_link_libraries(${PROJECT_NAME} gdi32 opengl32 Cfgmgr32 SetupAPI)

    elseif(APPLE)
        target_sources(${PROJECT_NAME}
            PUBLIC
            third_party/libserialport/macosx.c
            third_party/libserialport/timing.c
        )

    elseif(LINUX)
        target_sources(${PROJECT_NAME}
            PUBLIC
            third_party/libserialport/linux.c
            third_party/libserialport/linux_termios.c
            third_party/libserialport/linux_termios.h
    #        third_party/libserialport/freebsd.c
                third_party/libserialport/timing.c

        )
    endif()
endif()


if(WIN32) # Check if we are on Windows
    if(MSVC) # Check if we are using the Visual Studio compiler
        set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES LINK_FLAGS "/ENTRY:mainCRTStartup" )
    elseif(CMAKE_COMPILER_IS_GNUCXX) #
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif(MSVC)
elseif(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE YES )
elseif(UNIX)
    # Nothing special required
else()
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)


#set(ASSETS ${CMAKE_SOURCE_DIR}/assets/Roboto-Bold.ttf)
#target_sources(${PROJECT_NAME} PRIVATE ${ASSETS})

#set_target_properties(${PROJECT_NAME} PROPERTIES
#  MACOSX_BUNDLE ON
#  MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
##  MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION}
#  RESOURCE "${ASSETS}"
#)

#message(${CMAKE_COMMAND})
#message(${CMAKE_CURRENT_BINARY_DIR})

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

install(TARGETS ${PROJECT_NAME} DESTINATION .)

if (APPLE)
    # not working? maybe the thing at: #look here asldfj was windows only??
set(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
set(CPACK_GENERATOR "DragNDrop")
else()
set(APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.exe")
endif()

set(DIRS ${CMAKE_BINARY_DIR})

message(${CMAKE_BINARY_DIR})

message(${CMAKE_COMMAND})

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION assets)

# removed recently (10/9/2022 gjh)
#install(CODE "include(BundleUtilities)
#fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")


#set(MINGW_PATH ${CMAKE_PREFIX_PATH})
#message(${MINGW_PATH})

#think more about this?
set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)


if(UNIX AND NOT APPLE)
    # not working? maybe the thing at: #look here asldfj was windows only??
    get_filename_component(GCC_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)
    find_library(LIBGCC NAMES libgcc_s.so.1 HINTS ${GCC_PATH}/../lib64)
    get_filename_component(LIBGCC_DIR ${LIBGCC} DIRECTORY)
    file(GLOB LIBGCC_ALL ${LIBGCC_DIR}/libgcc*.so.1)
    find_library(STDCPP NAMES libstdc++.so.6 HINTS ${GCC_PATH}/../lib64)
    file(GLOB STDCPP_ALL ${STDCPP}*)
    set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS
    ${LIBGCC_ALL}
    ${STDCPP_ALL})
endif()




if(WIN32 AND NOT MSVC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .dll) # important!
    GET_FILENAME_COMPONENT(GCC_PATH ${CMAKE_CXX_COMPILER} DIRECTORY)

#    foreach(RUNTIME
#        libstdc++-6.dll
#        libgcc_s_seh-1.dll
#        libwinpthread-1.dll
#        )
#        message(STATUS "Checking for ${RUNTIME}")
#        find_library(${RUNTIME}_LIB NAMES ${RUNTIME})
#        message(${${RUNTIME}_LIB})
#        message("Hey")
#        message(${RUNTIME}_LIB-FOUND)
#        if(${RUNTIME}_LIB-FOUND)
#            message(STATUS "runtime found: ${${RUNTIME}_LIB}")
#            list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${${RUNTIME}_LIB})
#        else()
#            message(STATUS "${RUNTIME} not found. Hope nothing breaks!")
#        endif()
#    endforeach()


    find_library (LIBGCC NAMES libgcc_s_seh-1 HINTS ${GCC_PATH})
    if (LIBGCC)
      message (STATUS "Found libgcc        at ${LIBGCC}")
      list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${LIBGCC})
    else ()
      message (SEND_ERROR "Could not find libgcc!")
    endif ()

    find_library (LIBSTDCPP libstdc++-6 HINTS ${GCC_PATH})
    if (LIBSTDCPP)
      message (STATUS "Found libstdc++     at ${LIBSTDCPP}")
      list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${LIBSTDCPP})
    else ()
      message (SEND_ERROR "Could not find libstdc++!")
    endif ()

    find_library (LIBWINPTHREAD libwinpthread-1 HINTS ${GCC_PATH})
    if (LIBWINPTHREAD)
      message (STATUS "Found libwinpthread at ${LIBWINPTHREAD}")
      list(APPEND CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${LIBWINPTHREAD})
    else ()
      message (SEND_ERROR "Could not find libwinpthread!")
    endif ()

endif()

message(STATUS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
message(STATUS ${GCC_PATH})

include( InstallRequiredSystemLibraries )


include(CPack)
