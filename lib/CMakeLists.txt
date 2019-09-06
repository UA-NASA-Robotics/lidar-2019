#===============================================================================
# Pepperl+Fuchs Driver Library
#===============================================================================

# Create a variable containing root directory of pepperl_fuchs
# driver library

set(DRIVER_LIBRARY_DIR pepperl_fuchs/pepperl_fuchs_r2000)

# Since we are building the library for usage independent from
# ROS, we must perform this step:

if(EXISTS "${DRIVER_LIBRARY_DIR}/CMakeLists.txt.NO_ROS_LIB_ONLY")
	file(RENAME
		"${DRIVER_LIBRARY_DIR}/CMakeLists.txt.NO_ROS_LIB_ONLY"
		"${DRIVER_LIBRARY_DIR}/CMakeLists.txt"
	)
endif()

add_subdirectory(${DRIVER_LIBRARY_DIR})