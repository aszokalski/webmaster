#Modules
add_subdirectory(source)
add_subdirectory(generator)

#Main
add_executable(spc main.cpp)
target_link_libraries(spc Source)
target_link_libraries(spc Generator)