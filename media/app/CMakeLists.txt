cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library(
             fabric-lib
             SHARED
             src/main/cpp/Media_Jni.cpp
             src/main/cpp/Rtmp.cpp)

find_library(
              log-lib
              log )
add_library(rtmp SHARED IMPORTED)

set_target_properties(rtmp PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/librtmp.so)

target_link_libraries(
                       fabric-lib
                       ${log-lib}
                       rtmp)

cmake_minimum_required(VERSION 3.4.1)

add_library(
             speex-lib
             SHARED
             src/main/cpp/Speex_Jni.cpp)


add_library(speex SHARED IMPORTED)

set_target_properties(speex PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libspeex.so)

target_link_libraries(
                       speex-lib
                       ${log-lib}
                       speex)

add_library(
             yuv-lib
             SHARED
             src/main/cpp/Yuv420_Jni.cpp)


target_link_libraries(
                       yuv-lib
                       ${log-lib})