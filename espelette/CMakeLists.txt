add_executable(espelette src/main.cpp src/draw.h src/draw.cpp src/image.h src/image.cpp src/app.h src/app.cpp src/vec.h src/vec.cpp)
target_link_libraries(espelette PRIVATE glfw glad glm stb)