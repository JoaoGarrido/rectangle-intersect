install(
    TARGETS rectangle-intersection_exe
    RUNTIME COMPONENT rectangle-intersection_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
