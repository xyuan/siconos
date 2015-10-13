if(WITH_TESTING)
  IF(CROSSCOMPILING_LINUX_TO_WINDOWS)
    SET(EMULATOR "wine")
    SET(DRIVE_LETTER "Z:")
  ELSE()
    SET(EMULATOR)
    SET(DRIVE_LETTER)
  ENDIF()
endif()

IF(CMAKE_SYSTEM_NAME MATCHES Windows)
  SET(VAR_SEPARATOR ";")
  APPEND_CXX_FLAGS("/bigobj")
ELSE()
  SET(VAR_SEPARATOR ":")
ENDIF()

IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
  STRING(REGEX REPLACE "\\\;" ";" ENV_PATH "$ENV{PATH}")
  STRING(REGEX REPLACE "/" "\\\\" SICONOS_NUMERICS_PATH "${SICONOS_NUMERICS_PATH}")
  # remove trailing backslash and quote for python
  STRING(REGEX REPLACE "\"" "" ENV_PATH_FOR_RUNTEST "${ENV_PATH}")
  STRING(REGEX REPLACE "\\\\$" "" ENV_PATH_FOR_RUNTEST "${ENV_PATH_FOR_RUNTEST}")
ENDIF()