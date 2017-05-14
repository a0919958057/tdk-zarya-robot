cmake_minimum_required(VERSION 2.8.3)
project(zaryabot_rqt)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

find_package(catkin REQUIRED COMPONENTS rqt_gui rqt_gui_cpp image_transport sensor_msgs cv_bridge)

## FIND QT
find_package(Qt5Widgets REQUIRED)

## DEBUG IF NOT FOUND
IF($(Qt5Widgets_NOTFOUND))
  MESSAGE(FATAL_ERROR "QT5 Wasn't found")
ELSE($(Qt5Widgets_NOTFOUND))
  MESSAGE(STATUS "Found Qt5Widgets Library at: ${Qt5Widgets_LIBRARY}")
  MESSAGE(STATUS "Found Qt5Widgets Includes at: ${Qt5Widgets_INCLUDE_DIRS}")
ENDIF($(Qt5Widgets_NOTFOUND))


set(zaryabot_rqt_SRCS
  src/zaryabot_rqt/zpanel.cpp
  #src/rqt_image_view/ratio_layouted_frame.cpp
)

set(zaryabot_rqt_HDRS
  include/zaryabot_rqt/zpanel.h
  #include/rqt_image_view/ratio_layouted_frame.h
)

set(zaryabot_rqt_UIS
  src/zaryabot_rqt/zpanel.ui
)

set(zaryabot_rqt_INCLUDE_DIRECTORIES
  include
  ${CMAKE_CURRENT_BINARY_DIR}
)

catkin_package(
  INCLUDE_DIRS ${zaryabot_rqt_INCLUDE_DIRECTORIES}
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS rqt_gui rqt_gui_cpp # image_transport sensor_msgs cv_bridge
)

catkin_python_setup()

qt5_wrap_cpp(zaryabot_rqt_MOCS ${zaryabot_rqt_HDRS})
qt5_wrap_ui(zaryabot_rqt_UIS_H ${zaryabot_rqt_UIS})

include_directories(
  ${zaryabot_rqt_INCLUDE_DIRECTORIES}
  ${catkin_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  ${zaryabot_rqt_SRCS}
  ${zaryabot_rqt_MOCS}
  ${zaryabot_rqt_UIS_H}
)

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} Qt5::Widgets)

#find_package(class_loader)
#class_loader_hide_library_symbols(${PROJECT_NAME})

install(FILES plugin.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

install(PROGRAMS scripts/zaryabot_rqt
  DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)
install(PROGRAMS scripts/zaryabot_rqt
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
