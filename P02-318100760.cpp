//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//SHADERS NUEVOS.
static const char* vShaderVerdeO = "shaders/shaderVerdeO.vert";	// Color Verde obscuro
static const char* vShaderVerde = "shaders/shaderVerde.vert";	// Color Verde 
static const char* vShaderAzul = "shaders/shaderAzul.vert";		// Color Azul
static const char* vShaderRojo = "shaders/shaderRojo.vert";		// Color Rojo
static const char* vShaderCafe = "shaders/shaderCafe.vert";		// Color Café

float angulo = 0.0f;

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,	//Cara frontal
		1,3,2,	//Cara lateral derecha
		3,0,2,	//Cara lateral izquierda
		1,0,3	//Cara Lateral de enfrente
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat letra_K[] = {
		-0.95f,0.8f,0.0f,	1.0f,0.0f,1.0f,
		-0.95f,-0.8f,0.0f,	1.0f,0.0f,1.0f,
		-0.75f,-0.8f,0.0f,	1.0f,0.0f,1.0f,

		-0.95f,0.8f,0.0f,	1.0f,0.0f,1.0f,
		-0.75f,0.8f,0.0f,	1.0f,0.0f,1.0f,
		-0.75f,-0.8f,0.0f,	1.0f,0.0f,1.0f,

		-0.75f,0.0f,0.0f,	1.0f,0.0f,1.0f,
		-0.45f,0.8f,0.0f,	1.0f,0.0f,1.0f,
		-0.25,0.8f,0.0f,	1.0f,0.0f,1.0f,

		-0.75f,0.0f,0.0f,	1.0f,0.0f,1.0f,
		-0.6f,0.0f,0.0f,	1.0f,0.0f,1.0f,
		-0.25,0.8f,0.0f,	1.0f,0.0f,1.0f,

		-0.75f,0.0f,0.0f,	1.0f,0.0f,1.0f,
		-0.45f,-0.8f,0.0f,	1.0f,0.0f,1.0f,
		-0.25,-0.8f,0.0f,	1.0f,0.0f,1.0f,

		-0.75f,0.0f,0.0f,	1.0f,0.0f,1.0f,
		-0.6f,0.0f,0.0f,	1.0f,0.0f,1.0f,
		-0.25,-0.8f,0.0f,	1.0f,0.0f,1.0f,
	};
	MeshColor *letraK = new MeshColor();
	letraK->CreateMeshColor(letra_K,108);
	meshColorList.push_back(letraK);

	GLfloat letra_I[] = {
		-0.1f,0.8f,0.0f,	0.0f,1.0f,0.0f,
		0.1f,0.8f,0.0f,		0.0f,1.0f,0.0f,
		0.1f,-0.8f,0.0f,	0.0f,1.0f,0.0f,

		-0.1f,0.8f,0.0f,	0.0f,1.0f,0.0f,
		-0.1f,-0.8f,0.0f,	0.0f,1.0f,0.0f,
		0.1f,-0.8f,0.0f,	0.0f,1.0f,0.0f,
	};
	MeshColor *letrasI = new MeshColor();
	letrasI->CreateMeshColor(letra_I, 36);
	meshColorList.push_back(letrasI);

	GLfloat letra_G[] = {
		0.25f,0.8f,0.0f,	0.0f,1.0f,1.0f,
		0.95f,0.8f,0.0f,	0.0f,1.0f,1.0f,
		0.95f,0.5f,0.0f,	0.0f,1.0f,1.0f,

		0.25f,0.8f,0.0f,	0.0f,1.0f,1.0f,
		0.45f,0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.95f,0.5f,0.0f,	0.0f,1.0f,1.0f,

		0.25f,0.8f,0.0f,	0.0f,1.0f,1.0f,
		0.45f,0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.25f,-0.8f,0.0f,	0.0f,1.0f,1.0f,

		0.45f,-0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.45f,0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.25f,-0.8f,0.0f,	0.0f,1.0f,1.0f,

		0.45f,-0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.95f,-0.8f,0.0f,	0.0f,1.0f,1.0f,
		0.25f,-0.8f,0.0f,	0.0f,1.0f,1.0f,

		0.45f,-0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.95f,-0.8f,0.0f,	0.0f,1.0f,1.0f,
		0.95f,-0.5f,0.0f,	0.0f,1.0f,1.0f,

		0.95f,0.1f,0.f,		0.0f,1.0f,1.0f,
		0.95f,-0.5f,0.0f,	0.0f,1.0f,1.0f,
		0.75f,-0.5f,0.f,	0.0f,1.0f,1.0f,

		0.95f,0.1f,0.f,		0.0f,1.0f,1.0f,
		0.75f,-0.2f,0.0f,	0.0f,1.0f,1.0f,
		0.75f,-0.5f,0.f,	0.0f,1.0f,1.0f,

		0.95f,0.1f,0.f,		0.0f,1.0f,1.0f,
		0.75f,-0.2f,0.0f,	0.0f,1.0f,1.0f,
		0.55f,-0.2f,0.f,	0.0f,1.0f,1.0f,

		0.95f,0.1f,0.f,		0.0f,1.0f,1.0f,
		0.55f,0.1f,0.0f,	0.0f,1.0f,1.0f,
		0.55f,-0.2f,0.f,	0.0f,1.0f,1.0f,
	};
	MeshColor* letrasG = new MeshColor();
	letrasG->CreateMeshColor(letra_G, 180);
	meshColorList.push_back(letrasG);
}

void CreateShaders(){

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader COLOR VERDE OSCURO
	shader3->CreateFromFiles(vShaderVerdeO, fShader);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader COLOR VERDE 
	shader4->CreateFromFiles(vShaderVerde, fShader);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader COLOR AZUL
	shader5->CreateFromFiles(vShaderAzul, fShader);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader(); //shader COLOR Rojo
	shader6->CreateFromFiles(vShaderRojo, fShader);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader(); //shader COLOR Café
	shader7->CreateFromFiles(vShaderCafe, fShader);
	shaderList.push_back(*shader7);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;

	//PARA QUE SE VEA EN 3D.
	glm::mat4 projection = glm::perspective(glm::radians(60.0f),mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		/*EJERCICIO 01: LETRAS*/
		//LETRA K
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, -1.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[0]->RenderMeshColor();
		//LETRA I
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[1]->RenderMeshColor();
		//LETRA G
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, -1.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshColorList[2]->RenderMeshColor();

		/*EJERCICIO 02: CASA 3D*/

		//PUERTAS Y VENTANAS
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		//VENTANA DE IZQUIERDA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.3f, 0.2f, -2.5f)); 
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//VENTANA DE DERECHA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.3f, 0.2f, -2.5f)); 
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PUERTA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, -2.4f)); 
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//TECHO
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.2f, -3.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//CASA
		shaderList[5].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -3.0f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//TRONCOS
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		//TRONCO IZQUIERDO
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(-2.5f, -1.1f, -5.5f));
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		//TRONCO DERECHO
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(2.5f, -1.1f, -5.5f));
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//COPA DE ÁRBOL
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		//COPA DE ÁRBOL IZQUIERDA
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(-1.4f, 0.1f, -3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//COPA DE ÁRBOL DERECHA
		model = glm::mat4(1.0); 
		model = glm::translate(model, glm::vec3(1.4f, 0.1f, -3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
				

		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}