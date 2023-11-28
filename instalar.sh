#!/bin/bash

# Verificar si GLFW está instalado
if ! pkg-config --exists glfw3; then
    echo "GLFW no está instalado. Instalando..."
    sudo apt update
    sudo apt install -y libglfw3 libglfw3-dev
    echo "GLFW instalado correctamente."
else
    echo "GLFW ya está instalado."
fi

# Verificar si OpenGL está instalado
if ! pkg-config --exists gl; then
    echo "OpenGL no está instalado. Instalando..."
    sudo apt update
    sudo apt install -y mesa-utils
    echo "OpenGL instalado correctamente."
else
    echo "OpenGL ya está instalado."
fi

