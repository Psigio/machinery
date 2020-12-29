message("External project: BLE-Range")

ExternalProject_Add(project_BLE-Range
  GIT_REPOSITORY https://github.com/Psigio/BLE-Range.git
  GIT_TAG HEAD
  SOURCE_DIR BLE-Range
  BINARY_DIR BLE-Range-build
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/thirdparty"
  BUILD_COMMAND make
  INSTALL_COMMAND make install
)
ExternalProject_Get_Property(project_BLE-Range install_dir)
add_library(BLE-Range STATIC IMPORTED)
set_property(TARGET BLE-Range PROPERTY IMPORTED_LOCATION ${install_dir}/lib/libBLE-Range.a)
add_dependencies(BLE-Range project_BLE-Range)

set(BLE-RANGE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/BLE-Range/lib/ ${CMAKE_BINARY_DIR}/BLE-Range/include/)
set(BLE-RANGE_LIBRARY_DIR ${CMAKE_BINARY_DIR}/BLE-Range/lib/ ${CMAKE_BINARY_DIR}/BLE-Range/lib/)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules (GOBJECT REQUIRED gobject-2.0)
pkg_check_modules (GIO REQUIRED gio-2.0)
set(THREADS_PREFER_PTHREAD_FLAG ON)
FIND_PACKAGE(Threads REQUIRED)

set(BLE-RANGE_LIBRARIES libBLE-Range.a ${GLIB_LIBRARIES} ${GOBJECT_LIBRARIES} ${GIO_LIBRARIES} Threads::Threads)

include_directories(${BLE-RANAGE_INCLUDE_DIR})
