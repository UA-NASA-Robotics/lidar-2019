set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.40 COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(main
	main.cpp
)

target_link_libraries(main
	PUBLIC
	r2000_driver
	${Boost_LIBRARIES}
)

target_compile_options(main PRIVATE -lpthread -lboost_thread)