############################################################################
# CMakeLists.txt file for building ROOT montecarlo/pythia8 package
# @author Pere Mato, CERN
############################################################################

include_directories(${PYTHIA8_INCLUDE_DIR})

ROOT_ADD_CXX_FLAG(CMAKE_CXX_FLAGS -Wno-overloaded-virtual)
ROOT_ADD_CXX_FLAG(CMAKE_CXX_FLAGS -Wno-misleading-indentation)

ROOT_STANDARD_LIBRARY_PACKAGE(EGPythia8
                              LIBRARIES ${PYTHIA8_LIBRARIES}
                              DEPENDENCIES Core EG Graf VMC Physics)
