#include <include/rendering/shader.h>

#include <glad/glad.h> 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    //Las variables que guardan el shader
    string vertexCode;
    string fragmentCode;

    //Las variables del lector de datos
    ifstream vShaderFile;
    ifstream fShaderFile;

    //Permite que los ifstream objects puedan enviar excepciones
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        //abrir el archivo
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;

        //lee los buffers y los guarda en un stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //cierra los "hadlers" de los archivos
        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch (ifstream::failure e)
    {
        cout << "ERROR READING THE SHADER FILES" << endl;
    }

    //convierte las srings que almacenaban el codigo en un array de char (esto pq es como lo lee openGL
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //Guarda las "id" de los shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    //Compila el vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    //Comprueba si ha habido algun error
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
       glGetShaderInfoLog(vertex, 512, NULL, infoLog); 
       std::cout << "FALLO AL COMPILAR EL VERTEX SHADER\n" << infoLog << std::endl;
    };

    //Compila el vertex shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    //Comprueba si ha habido algun error
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
       glGetShaderInfoLog(fragment, 512, NULL, infoLog); 
       std::cout << "FALLO AL COMPILAR EL FRAGMENT SHADER\n" << infoLog << std::endl;
    };

    //Crea el program shader
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
};

void Shader::use(){
   glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
   glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
