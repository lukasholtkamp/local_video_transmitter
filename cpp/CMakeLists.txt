cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project (local_video_transmitter)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable (sender sender.cpp)
add_executable (receiver receiver.cpp)

target_link_libraries(sender ${OpenCV_LIBS})
target_link_libraries(receiver ${OpenCV_LIBS})

