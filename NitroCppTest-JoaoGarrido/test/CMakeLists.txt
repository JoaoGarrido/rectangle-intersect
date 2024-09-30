# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(rectangle-intersectionTests LANGUAGES CXX)

# ---- Tests ----

set(DOWNLOAD_EXTRACT_TIMESTAMP true)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        b514bdc898e2951020cbdca1304b75f5950d1f59 # release-1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  rectangle-intersection_test
  source/rectangle-intersection_test.cpp
)
target_link_libraries(
  rectangle-intersection_test
  GTest::gtest_main
  rectangle-intersection_lib
)

include(GoogleTest)
gtest_discover_tests(rectangle-intersection_test)

