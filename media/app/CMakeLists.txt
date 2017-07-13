cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library(
             media-native
             SHARED
             src/main/cpp/media-native.cpp
             src/main/cpp/Rtmp.cpp)

find_library(
              log-lib
              log )
add_library(rtmp SHARED IMPORTED)

set_target_properties(rtmp PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/librtmp.so)

target_link_libraries(
                       media-native
                       ${log-lib}
                       rtmp)

cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

add_library(
             speex-native
             SHARED
             src/main/cpp/speex_jni.cpp)


add_library(speex SHARED IMPORTED)

set_target_properties(speex PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}/libspeex.so)

target_link_libraries(
                       speex-native
                       ${log-lib}
                       speex)

