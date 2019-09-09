project(trianglepp C CXX)


add_library(tpp STATIC
	tpp_impl.cpp
)
set_target_properties(tpp PROPERTIES LINKER_LANGUAGE CXX)

add_executable(tppexe
 	trpp_example.cpp
)
target_link_libraries(tppexe
 	tpp
)