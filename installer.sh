#!/bin/bash

# Verificar si GLFW está instalado
if ! pkg-config --exists glfw3; then
    echo "GLFW no está instalado. Instalando..."
    sudo apt update
    sudo apt install libglfw3 libglfw3-dev
    echo "GLFW instalado correctamente."
else
    echo "GLFW ya está instalado."
fi

# Verificar si OpenGL está instalado
if ! pkg-config --exists gl; then
    echo "OpenGL no está instalado. Instalando..."
    sudo apt update
    sudo apt install mesa-utils
    echo "OpenGL instalado correctamente."
else
    echo "OpenGL ya está instalado."
fi

GLAD_DESTINATION="/usr/include/glad"  # Cambia esto al directorio donde quieras instalar GLAD

# Verificar si GLAD ya está instalado
if [ -d "$GLAD_DESTINATION" ]; then
    echo "GLAD ya está instalado"
else
    echo "GLAD no está instalado en $GLAD_DESTINATION. Instálalo en: https://glad.dav1d.de/"
fi

