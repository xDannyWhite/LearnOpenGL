g++ \
    -std=c++17 \
    -Iinclude \
    src/main.cpp src/glad.c src/shader.cpp src/Assetmanager.cpp \
    -o run \
    -lglfw -lGL -ldl -lpthread -lX11 -lXrandr -lXi -lXxf86vm -lXcursor
