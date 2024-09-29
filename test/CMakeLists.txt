# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(rectangle-intersectionTests LANGUAGES CXX)

# ---- Tests ----

add_executable(rectangle-intersection_test source/rectangle-intersection_test.cpp)
target_link_libraries(rectangle-intersection_test PRIVATE rectangle-intersection_lib)
target_compile_features(rectangle-intersection_test PRIVATE cxx_std_20)

add_test(NAME rectangle-intersection_test COMMAND rectangle-intersection_test)

# ---- End-of-file commands ----

add_folders(Test)
