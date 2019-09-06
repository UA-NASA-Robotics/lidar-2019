#===============================================================================
# Pepperl+Fuchs Driver Library
#===============================================================================

set(DRIVER_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/lib/pepperl_fuchs/pepperl_fuchs_r2000)

# Replacing the default Pepperl+Fuchs CMakeLists.txt file

file(
	COPY
		"CMakeLists.txt.pepperl_fuchs"
	DESTINATION
		"${DRIVER_LIBRARY_DIR}"
)

file(
	RENAME
		"${DRIVER_LIBRARY_DIR}/CMakeLists.txt.pepperl_fuchs"
		"${DRIVER_LIBRARY_DIR}/CMakeLists.txt"
)

# Adding subdirectory for the R2000 driver library

add_subdirectory(${DRIVER_LIBRARY_DIR})