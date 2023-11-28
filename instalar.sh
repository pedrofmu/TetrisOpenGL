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

GLAD_DESTINATION="usr/include/glad/glad.h"  # Cambia esto al directorio donde quieras instalar GLAD

# Verificar si GLAD ya está instalado
if [ -d "$GLAD_DESTINATION" ]; then
    echo "GLAD ya está instalado en $GLAD_DESTINATION."
else
    echo "Descargando y configurando GLAD..."

    # Crear directorio si no existe
    mkdir -p "$GLAD_DESTINATION"

    # Descargar GLAD desde el repositorio web
    wget -O "$GLAD_DESTINATION/glad.zip" "https://glad.dav1d.de/generated/glad.zip"
    
    # Descomprimir el archivo descargado
    unzip "$GLAD_DESTINATION/glad.zip" -d "$GLAD_DESTINATION"

    echo "GLAD instalado correctamente en $GLAD_DESTINATION."
fi
