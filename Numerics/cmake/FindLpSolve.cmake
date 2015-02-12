#Please note that we are using lpsolve 5.5
FIND_PATH(LpSolve_INCLUDE_DIR lpsolve/lp_lib.h)
FIND_LIBRARY(LpSolve_LIBRARY lpsolve55)

IF (NOT LpSolve_INCLUDE_DIR)
  MESSAGE("Cannot find LPSOLVE headers!")
ENDIF (NOT LpSolve_INCLUDE_DIR)
IF (LpSolve_LIBRARY)
  GET_FILENAME_COMPONENT(LpSolve_LIBRARY_DIRS ${LpSolve_LIBRARY} PATH)
  GET_FILENAME_COMPONENT(LpSolve_LIBRARIES ${LpSolve_LIBRARY} NAME)
  GET_FILENAME_COMPONENT(LpSolve_LIBRARY_DIRS_DIR ${LpSolve_LIBRARY_DIRS} PATH)
  SET(LpSolve_FOUND 1)
ELSE(LpSolve_LIBRARY)
  MESSAGE("Cannot find LPSOLVE libraries!")
ENDIF (LpSolve_LIBRARY)
IF (NOT LpSolve_FIND_QUIETLY)
  MESSAGE(STATUS "Found LpSolve: ${LpSolve_LIBRARY}")
  MESSAGE(STATUS "LpSolve_LIBRARIES: ${LpSolve_LIBRARIES}")
ENDIF (NOT LpSolve_FIND_QUIETLY)