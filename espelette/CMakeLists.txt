add_library(espelette
        include/espelette/draw.h
        src/draw.cpp
        include/espelette/image.h
        src/image.cpp
        include/espelette/app.h
        src/app.cpp
        src/vec.h
        src/vec.cpp
        src/draw_backend.cpp
        include/espelette.h
        src/stb_impl.cpp
        include/espelette/input.h
        src/input.cpp
        src/input_state.h
        src/draw_backend.h
        src/draw_list.h)

target_include_directories(espelette PUBLIC include PRIVATE include/espelette)

target_link_libraries(espelette PRIVATE glfw glad glm stb)