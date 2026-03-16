g++ \
    -std=c++17 \
    -Iinclude \
    src/main.cpp src/glad.c \
    -o run \
    -lglfw -lGL -ldl -lpthread -lX11 -lXrandr -lXi -lXxf86vm -lXcursor
