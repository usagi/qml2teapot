cmake_minimum_required(VERSION 2.8.10)

project(gl_teapot)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(GLU REQUIRED)
find_package(GLUT REQUIRED)

add_library(gl_teapot SHARED
  gl_teapot_plugin.cxx
  gl_teapot.cxx
)
qt5_use_modules(gl_teapot Qml Quick)
target_link_libraries(gl_teapot ${GLU_LIBRARY} ${GLUT_LIBRARY})

execute_process(
  COMMAND awk "{print $2}" ${PROJECT_SOURCE_DIR}/qmldir
  COMMAND head -n1
  COMMAND tr . /
  COMMAND tr -d \n
  OUTPUT_VARIABLE qmldir_output
)
set(qmldir $ENV{QML2_IMPORT_PATH}/${qmldir_output})
message(STATUS "qmldir: ${qmldir}")

add_custom_command(TARGET gl_teapot POST_BUILD
  COMMAND mkdir -pv ${qmldir}
  COMMAND cp -uv ${PROJECT_SOURCE_DIR}/qmldir ${qmldir}/qmldir
  COMMAND mv -v *.so ${qmldir}/
  COMMAND cp -uv ${PROJECT_SOURCE_DIR}/test.qml .
)

