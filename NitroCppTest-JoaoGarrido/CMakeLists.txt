cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    rectangle-intersection
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    rectangle-intersection_lib OBJECT
    source/Rectangle.cpp
)

target_include_directories(
    rectangle-intersection_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(rectangle-intersection_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(rectangle-intersection_exe source/main.cpp)
add_executable(rectangle-intersection::exe ALIAS rectangle-intersection_exe)

set_property(TARGET rectangle-intersection_exe PROPERTY OUTPUT_NAME rectangle-intersection)

target_compile_features(rectangle-intersection_exe PRIVATE cxx_std_20)

target_link_libraries(rectangle-intersection_exe PRIVATE rectangle-intersection_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT rectangle-intersection_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of rectangle-intersection"
  )
endif()

include(cmake/dev-mode.cmake)
