/*---------------------------------------------------------*/
/* ----------------   Proyecto feria --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Alumno: Diaz Acosta Erika y Ortiz Martínez Brenda -----------------*/

/*-------------  Grupo4 -------------- */
/*---------------------Version visual 2017------------------------*/
/*---------Instrucciones-------------------------------------------*/
/*--------Use las teclas para mover el modelo----------------------*/
/*--------W acercar   S  alejar------------------------------------*/
/*--------Z Bajar   E  subir------------------------------------*/
/*--------A izquierda   D derecha------------------------------------*/
/*----------mouse: mover, scroll = acercar---------------*/
#define STB_IMAGE_IMPLEMENTATION
#include "esfera.h"
#include "camera.h"
#include <stb_image.h>

Esfera my_sphere(1.0f);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX= 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f;
//Texture
unsigned int texture1, texture2, texture3; //Indice que va a tener cada textura, i.e., 2 índices = 2 texturas

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}


void myData() //Recordemos que antes aquí teníamos un cubo, pero ahora hay un plano.
{
	float vertices[] = {
		// positions          // texture coords
												//front
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f,

		// Trasera
0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
0.5f,  0.5f, -0.5f,	1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,	0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

//Izq
-0.5f,  0.5f, 0.5f,		1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,	1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
-0.5f, -0.5f, 0.5f,		0.0f, 1.0f,

//Der
0.5f,  0.5f, 0.5f,		1.0f, 1.0f,
0.5f,  0.5f, -0.5f,		1.0f, 0.0f,
0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
0.5f, -0.5f, 0.5f,		0.0f, 1.0f,

//Sup
-0.5f, 0.5f, 0.5f,		2.0f, 2.0f,
 0.5f, 0.5f, 0.5f,		2.0f, 0.0f,
 0.5f, 0.5f, -0.5f,		0.0f, 0.0f,
-0.5f, 0.5f, -0.5f,		0.0f, 2.0f,

//Inf
-0.5f, -0.5f, 0.5f,		1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
 0.5f, -0.5f, 0.5f,		0.0f, 1.0f,

 //----entrada

		// positions          // texture coords
												//front
		0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f,		0.0f, 1.0f,

		// Trasera
0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
0.5f,  0.5f, -0.5f,	1.0f, 0.0f,
-0.5f,  0.5f, -0.5f,	0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

//Izq
-0.5f,  0.5f, 0.5f,		1.0f, 1.0f,
-0.5f,  0.5f, -0.5f,	1.0f, 0.0f,
-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
-0.5f, -0.5f, 0.5f,		0.0f, 1.0f,

//Der
0.5f,  0.5f, 0.5f,		1.0f, 1.0f,
0.5f,  0.5f, -0.5f,		1.0f, 0.0f,
0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
0.5f, -0.5f, 0.5f,		0.0f, 1.0f,

//Sup
-0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
 0.5f, 0.5f, 0.5f,		1.0f, 0.0f,
 0.5f, 0.5f, -0.5f,		0.0f, 0.0f,
-0.5f, 0.5f, -0.5f,		0.0f, 1.0f,

//Inf
-0.5f, -0.5f, 0.5f,		1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
 0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
 0.5f, -0.5f, 0.5f,		0.0f, 1.0f
	};
	unsigned int indices[] = {
		
		0, 1, 3, // primer triangulo
		1, 2, 3,  // segundo

		6, 7, 5,
		7, 4, 5,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23,

		24,25,26,
		24,26,27,

		28,29,30,
		28,30,31,

		31,32,33,
		31,33,34,

		35,36,37,
		35,37,38,

		39,40,41,
		39,41,42,

		43,44,45,
		43,45,46

		

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //El atributo 0 corresponde a la posicion
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //El atributo 1 corresponde a la textura
	glEnableVertexAttribArray(1);
	//---------------hereee textura2
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	// load and create a texture 
	// -------------------------

	// texture 1
	// ---------
	glGenTextures(1, &texture1); //Leemos una textura 
	glBindTexture(GL_TEXTURE_2D, texture1); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("texturas_feria/piedras.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture one" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(2, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/marmol.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture two" << std::endl;
	}
	stbi_image_free(data);
	// texture 3
	// ---------
	glGenTextures(3, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/marmol_colores.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture three" << std::endl;
	}
	stbi_image_free(data);
}

void animate(void)
{

}

void display(void)
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE);			//activar la textura a 0. 
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	Shader projectionShader("shaders/shader_texture.vs", "shaders/shader_texture.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	projectionShader.setInt("texture1", 0);


	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	glm::mat4 modelTemp = glm::mat4(1.0f);

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));

	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));


	// pass them to the shaders
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);

	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::scale(model, glm::vec3(20.0f, 0.05f, 20.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//entrada	

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	projectionShader.setInt("texture2", 1);
	
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(-42.0f, 2.0f, 26.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(15.0f, 4.0f, 4.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	//columna 1 lado izquierdo
	model = glm::translate(model, glm::vec3(-5.0f, 8.5f, 0.0f));
	model = glm::scale(model, glm::vec3(5.0f, 13.0f, 4.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 2 lado izquierdo
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 1 lado derecho
	model = glm::translate(model, glm::vec3(7.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 2 lado derecho
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	 
	//base bandera lado derecho columna 2
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture3);
	
	model = glm::translate(model, glm::vec3(0.0f, 0.5250f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 0.05f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//parte alta

	model = glm::translate(model, glm::vec3(-2.0f, 3.550f, 0.0f));
	model = glm::scale(model, glm::vec3(0.450f, 6.0f, 0.450f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(10.50f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);

}

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 8", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();

		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		movY += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		movY -= 0.05f;

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
