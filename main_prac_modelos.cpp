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
double	lastX = 0.0f,
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
void circulos(void);
//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f;

//rueda
float angRueda = 0.0f, angCanasta = 0.0f;
float ang1 = 0.4f;
float movimiento = 0.2, colgando=0.0;
//float rotX = 0.7068f;





//Texture
unsigned int texture1, texture2, texture3, texture4, texture5; //Indice que va a tener cada textura, i.e., 2 índices = 2 texturas

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

 -0.5f, -0.5f, 0.5f,	0.0f, 0.0f,
-0.5f, 0.0f, 0.5f,		0.0f, 1.0f,
0.7f, -0.3f, 0.5f,      1.0f, 0.0f,

 -0.3f, 0.0f, 0.5f,		0.0f, 0.0f,
 0.3f, 0.0f, 0.5f,		1.0f, 0.0f,
 0.0f, 0.8f, 0.5f,		0.50f, 1.0f


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
		27,28,29

		/*		24,25,26,
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
				43,45,46*/



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

	data = stbi_load("texturas_feria/estrellas1.jpg", &width, &height, &nrChannels, 0);
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

	// texture 4 banderas
	// ---------
	glGenTextures(4, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4); //tipo 2D 
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //filtro 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("texturas_feria/red_flag.jpg", &width, &height, &nrChannels, 0);
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


	// texture 5 metal
	glGenTextures(5, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5); //tipo 2D 
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

void circulos(void) {
	
	glPointSize(15);
	float x = 0.0f, y = 0.0f, z = 0.27f;
	
	for (double i = 0; i <= 360;) {
		glBegin(GL_POINTS); {
				x = 1*cos(i);
				y = 1*sin(i);

				glVertex3f(x, y, z);
				i = i + 0.05;
				x = 1 *cos(i);
				y = 1 *sin(i);

				glVertex3f(x, y, z);
				glVertex3f(0, 0, 0);
			}
		i = i + 0.05;
		}
	glEnd();
}

void circulos2(void) {

	glPointSize(15);
	float x = 0.0f, y = 0.0f, z = -0.25f;

	for (double i = 0; i <= 360;) {
		glBegin(GL_POINTS); {
			x = 1 * cos(i);
			y = 1 * sin(i);

			glVertex3f(x, y, z);
			i = i + 0.05;
			x = 1 * cos(i);
			y = 1 * sin(i);

			glVertex3f(x, y, z);
			glVertex3f(0, 0, 0);
		}
		i = i + 0.05;
	}
	glEnd();
}
void animate(void)
{
	angRueda = angRueda + movimiento;
	angCanasta = angCanasta + colgando;
	if (angRueda >= 90)
	{
		movimiento = -0.1;
		if (angCanasta <= 90)
		{
			colgando = 0.20;
		}
	}
	if (angRueda <= -90)
	{
		movimiento = 0.1;
		if (angCanasta >= 90)
		{
			colgando = -0.20;
		}
	}
	
	
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
	glm::mat4 modelTemp2 = glm::mat4(1.0f);
	//	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));

	//	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));


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
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-2.0f, 3.53f, 0.0f));
	model = glm::scale(model, glm::vec3(0.450f, 6.0f, 0.450f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(24.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-4.55f, 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 2.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-15.55f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//palito
	model = glm::translate(model, glm::vec3(0.0f, 0.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.50f, 0.20f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(99.7f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(22.7f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 1.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//banderas
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture4);

	model = glm::translate(model, glm::vec3(5.3f, 0.50f, -0.20f));
	//modelTemp = model;
	model = glm::scale(model, glm::vec3(10.0f, 0.5f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-2.30f, 1.90f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-7.750f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);

	model = glm::translate(model, glm::vec3(-2.18f, -1.9f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 24, 3);


	//Rueda de la fortuna
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture5);
	//base
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(35.0f, 0.50f, 15.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;

	//soporte
	model = glm::translate(model, glm::vec3(1.0f, 0.24f, 7.3));
	model = glm::scale(model, glm::vec3(15.0f, 25.0f, 0.33f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 27, 3);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -45.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_TRIANGLES, 27, 3);
	
	//eje
	model = modelTemp;
	model = glm::translate(model, glm::vec3(1.0f, 18.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angRueda), glm::vec3(0, 0, 1));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.5, 0.5, 14.8));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	//barras que sostienen la rueda al eje
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(1.0, 25.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(1.0, 25.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(6.50f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(6.50f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(-6.50f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-6.50f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	model = modelTemp;
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.20f));
	model = glm::scale(model, glm::vec3(0.80, 25.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.20f));
	model = glm::scale(model, glm::vec3(0.80, 25.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	
	
	//circulos rueda
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.50f));
	model = glm::scale(model, glm::vec3(12.50, 12.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	circulos();
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.50f));
	model = glm::scale(model, glm::vec3(12.50, 12.50, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	circulos2();
	

	//barras entre las ruedas
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f,-12.55f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 7.5));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(16.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-7.0f, 9.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(46.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 10.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(3.0f, 12.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(44.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-6.0f, 7.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 12.50f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50, 0.50, 8.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	

	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//esferas rueda de la fortuna
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, -12.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
	//model = modelTemp2;
	model = glm::scale(model, glm::vec3(1.0, 2.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//esfera1
	/*
	model = glm::translate(model, glm::vec3(0.0f, -14.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 2.0, 2.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	my_sphere.render();
	
	//puertita
	
/*
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 5.0f));
	model = glm::scale(model, glm::vec3(1.0, 2.0, 0.40));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	/*
	//esfera2
	model = modelTemp;
	model = glm::translate(model, glm::vec3(9.0f, 7.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	my_sphere.render();
	//puertita
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 4.0f));
	model = glm::scale(model, glm::vec3(1.0, 2.0, 0.30));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//esfera3
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-20.0f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	my_sphere.render();
	//puertita
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture2);
	model = glm::translate(model, glm::vec3(0.0f, -1.0f, 2.0f));
	model = glm::scale(model, glm::vec3(1.0, 2.0, 0.010));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 0.0f));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0*/
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
