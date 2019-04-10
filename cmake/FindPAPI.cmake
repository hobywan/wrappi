include(FindPackageHandleStandardArgs)

find_path(PAPI_PREFIX NAMES include/papi.h)

find_path(PAPI_INCLUDE_DIRS
        NAMES papi.h
        HINTS ${PAPI_PREFIX}/include)

find_library(PAPI_LIBRARIES
        NAMES libpapi.so libpapi.a papi
        HINTS ${PAPI_PREFIX}/lib)

find_package_handle_standard_args(PAPI
        DEFAULT_MSG
        PAPI_LIBRARIES
        PAPI_INCLUDE_DIRS)

mark_as_advanced(PAPI_PREFIX_DIRS PAPI_LIBRARIES PAPI_INCLUDE_DIRS)

