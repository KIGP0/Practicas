#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <stdlib.h>
#include <time.h>

//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 400;
GLuint VAO, VBO, shader;

//Vertex Shader
//Recibir color, Salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//Recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,1.0f,1.0f,1.0f);	 			\n\
}";

static float* RandomColor() {
	float* color = new float[3];
	color[0] = static_cast<float>(rand()) / RAND_MAX;
	color[1] = static_cast<float>(rand()) / RAND_MAX;
	color[2] = static_cast<float>(rand()) / RAND_MAX;
	return color;
}

void CrearTriangulo()
{
	GLfloat vertices[] = {
		//LETRA K
		-0.95f,0.8f,0.0f,	//A
		-0.95f,-0.8f,0.0f,	//B
		-0.75f,-0.8f,0.0f,	//C

		-0.95f,0.8f,0.0f,	//A
		-0.75f,0.8f,0.0f,	//D
		-0.75f,-0.8f,0.0f,	//C

		-0.75f,0.0f,0.0f,	//E
		-0.45f,0.8f,0.0f,	//F
		-0.25,0.8f,0.0f,	//H

		-0.75f,0.0f,0.0f,	//E
		-0.6f,0.0f,0.0f,	//E1
		-0.25,0.8f,0.0f,	//H

		-0.75f,0.0f,0.0f,	//E
		-0.45f,-0.8f,0.0f,	//G
		-0.25,-0.8f,0.0f,	//I

		-0.75f,0.0f,0.0f,	//E
		-0.6f,0.0f,0.0f,	//E1
		-0.25,-0.8f,0.0f,	//I

		//LETRA I
		-0.1f,0.8f,0.0f,	//L
		0.1f,0.8f,0.0f,		//M
		0.1f,-0.8f,0.0f,	//K

		-0.1f,0.8f,0.0f,	//L
		-0.1f,-0.8f,0.0f,	//J
		0.1f,-0.8f,0.0f,	//K

		//LETRA G
		0.25f,0.8f,0.0f,	//O
		0.95f,0.8f,0.0f,	//P
		0.95f,0.5f,0.0f,	//U

		0.25f,0.8f,0.0f,	//O
		0.45f,0.5f,0.0f,	//T
		0.95f,0.5f,0.0f,	//U

		0.25f,0.8f,0.0f,	//O
		0.45f,0.5f,0.0f,	//T
		0.25f,-0.8f,0.0f,	//N

		0.45f,-0.5f,0.0f,	//R
		0.45f,0.5f,0.0f,	//T
		0.25f,-0.8f,0.0f,	//N

		0.45f,-0.5f,0.0f,	//R
		0.95f,-0.8f,0.0f,	//Q
		0.25f,-0.8f,0.0f,	//N

		0.45f,-0.5f,0.0f,	//R
		0.95f,-0.8f,0.0f,	//Q
		0.95f,-0.5f,0.0f,	//V

		0.95f,0.1f,0.f,		//W
		0.95f,-0.5f,0.0f,	//V
		0.75f,-0.5f,0.f,	//R1

		0.95f,0.1f,0.f,		//W
		0.75f,-0.2f,0.0f,	//Z1
		0.75f,-0.5f,0.f,	//R1

		0.95f,0.1f,0.f,		//W
		0.75f,-0.2f,0.0f,	//Z1
		0.55f,-0.2f,0.f,	//Z

		0.95f,0.1f,0.f,		//W
		0.55f,0.1f,0.0f,	//S
		0.55f,-0.2f,0.f,	//Z
	};

	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader, 1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader = glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	//verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}
}

int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Funciones para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//CREANDO VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "P01", NULL, NULL);
	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);
	//Asignar el contexto
	glfwMakeContextCurrent(mainWindow);
	//Permitir nuevas extensiones
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	//Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);


	//CREANDO TRIANGULOS
	CrearTriangulo();
	CompileShaders();

	// Variables para manejar el tiempo
	double lastTime = glfwGetTime();
	double elapsedTime = 0.0;
	double colorChangeInterval = 2;//Cambio de color cada 2 seg..

	float* currentColor = RandomColor();

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
        // Recibir eventos del usuario
		glfwPollEvents();

		// Medir el tiempo transcurrido
		double currentTime = glfwGetTime();
		elapsedTime += currentTime - lastTime;
		lastTime = currentTime;

		srand(time(NULL));

        // Cambiar el color de fondo de la ventana cada 'colorChangeInterval' segundos
        if (elapsedTime >= colorChangeInterval)
        {
            // Cambiar a un color aleatorio
			// Liberar memoria del color actual antes de asignar uno nuevo
            delete[] currentColor;  
            currentColor = RandomColor();

            // Establecer el nuevo color de fondo
            glClearColor(currentColor[0], currentColor[1], currentColor[2], 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//Creando Letras
			glUseProgram(shader);
			glBindVertexArray(VAO);
			//54, porque son 54 triangulos, donde a cada triangulo le corresponde 3 arrays de cada vértice. 
			glDrawArrays(GL_TRIANGLES, 0, 54);
			glBindVertexArray(0);
			glUseProgram(0);

            glfwSwapBuffers(mainWindow);

            // Reiniciar el tiempo transcurrido
            elapsedTime = 0.0;
        }
	}
	return 0;
}