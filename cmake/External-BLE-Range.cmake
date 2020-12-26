message("External project: BLE-Range")

ExternalProject_Add(project_BLE-Range
  GIT_REPOSITORY git@github.com:Psigio/BLE-Range.git
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

set(BLE-RANGE_LIBRARIES libBLE-Range.a)

include_directories(${BLE-RANAGE_INCLUDE_DIR})
