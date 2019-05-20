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

//#define STB_IMAGE_IMPLEMENTATION
#include "esfera.h"
#include "camera.h"
#include "stb_image.h"
#include <glew.h>
#include <glfw3.h>
#include "Model.h"

Esfera my_sphere(1.0f);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor* monitors;
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
glm::vec3 lightPosition(1.20f, 3.0f, 0.0f);
glm::vec3 lightDirection(0.0f, 0.0f, -5.0f);

void myData(void);
void display(Model, Model, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
void circulos(void);
void circulos2(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
R = 0.90f,
G = 0.90f,
B = 0.90f,
LAMPARA = 0.0f,
rotY = 0.0f;


//rueda
float angRueda = 0.0f, angCanasta = 0.0f;
float movimiento = 0.0, colgando = 0.0;
//for model carrito 
//5.0f, 30.10f, -125.0f
float movKit_z = -112.0f,
movKit_x = 5.0f,
movKit_y = 28.0f,
rotKit_y = -90.0f;

int estado = 0;
bool play, play2, night;


//Texture
unsigned int texture1, texture2, texture3, texture4, texture5, texture6, texture7; //Indice que va a tener cada textura, i.e., 2 índices = 2 texturas
unsigned int texture8, texture9, texture10, texture11, texture12, texture13, texture14, texture15, texture16, texture17;
unsigned int texture18, texture19, texture20;

unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{

	
	texture1 = generateTextures("texturas_feria/piedras.jpg", 0);
	texture2 = generateTextures("texturas_feria/marmol.jpg", 0);
	texture3 = generateTextures("texturas_feria/estrellas1.jpg", 0);
	texture4 = generateTextures("texturas_feria/red_flag.jpg", 0);
	texture5 = generateTextures("texturas_feria/galaxia3.jpg", 0);
	texture6 = generateTextures("texturas_feria/cubos.jpg", 0);
	texture7 = generateTextures("texturas_feria/marciano2.jpg", 0);
	texture8 = generateTextures("texturas_feria/morado2.jpg", 0);
	texture9 = generateTextures("texturas_feria/blue.jpg", 0);
	texture10 = generateTextures("texturas_feria/verde.jpg", 0);
	texture11 = generateTextures("texturas_feria/letrero.jpg", 0);
	texture12 = generateTextures("texturas_feria/lego.jpg", 0);
	texture13 = generateTextures("texturas_feria/legoverde.jpg", 0);
	texture14 = generateTextures("texturas_feria/nubes.jpg", 0);
	texture15 = generateTextures("texturas_feria/nubes1000.jpg", 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture4);

	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture5);

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture6);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, texture10);

	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, texture11);

	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, texture12);
	
	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, texture13);

	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, texture14);

	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_2D, texture15);
	   
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	

}

void myData()
{
	float vertices[] = {
		// positions          // texture coords
												//front
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0,  1.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0,  0.0f,

		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		 -0.5f, -0.5f, 0.5f, 0.0f,  0.0f, 0.0f,		0.0f, 0.0f,
		-0.5f, 0.0f, 0.5f, 0.0f,  0.0f,  0.0f,		0.0f, 1.0f,
		0.7f, -0.3f, 0.5f, 0.0f,  0.0f,  0.0f,    1.0f, 0.0f,

 -0.3f, 0.0f, 0.5f,	0.0f,  0.0f,  0.0f,	0.0f, 0.0f,
 0.3f, 0.0f, 0.5f,	0.0f,  0.0f,  0.0f,	1.0f, 0.0f,
 0.0f, 0.8f, 0.5f,	0.0f,  0.0f,  0.0f,	0.50f, 1.0f


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

		//24,25,26,
		//27,28,29

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}


void circulos(void) {

	glPointSize(0.1);
	float x = 0.0f, y = 0.0f, z = 0.27f;
	glPointSize(15);
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
	movimiento = 0.05;
	colgando = -0.05;
	angRueda = angRueda + movimiento;
	angCanasta = angCanasta + colgando;
	if (angRueda >= 90)
	{
		movimiento = -0.1;
		if (angCanasta <= -80)
		{
			colgando = 0.20;
		}
	}
	if (angRueda <= -90)
	{
		movimiento = 0.1;
		if (angCanasta >= 80)
		{
			colgando = -0.20;
		}
	}


	/////PARA EL CARRITO EN LA MONTAÑA RUSA//////////

		if (play) {

		if (estado == 0) { //ESTADO A



			if (movKit_x > -9.0) {//
				movKit_x -= 1.0f;
				//printf("%f \n", movKit_z);

			}
			else {

				estado = 1;

			}
		}

		if (estado == 1) { //ESTADO b

			if (movKit_x > -18) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_y -= 0.07f;
				//printf("%f \n", movKit_x);
			}
			else {
				estado = 2;
			}
		}

		if (estado == 2) { //ESTADO b

			if (movKit_x > -45) {//SIGO EN EL ESTADO B    
				movKit_x -= 0.8;
				movKit_y -= 0.32f;
				//printf("%f \n", movKit_x);
			}
			else {
				estado = 3;
			}
		}
		if (estado == 3) { //ESTADO b

			if (movKit_x > -60) {//SIGO EN EL ESTADO B    
				movKit_x -= 0.9f;
				movKit_y += 0.09f;
				//printf("%f \n", movKit_x);
			}
			else {
				estado = 4;

			}
		}

		if (estado == 4) { //ESTADO b

			if (movKit_x > -75) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_z -= 0.2f;
				movKit_y += 0.6f;
				//printf("%f \n", movKit_x);
			}
			else {

				rotKit_y = 210.0f;
				estado = 5;
			}
		}

		if (estado == 5) { //ESTADO b

			if (movKit_x > -85) {//SIGO EN EL ESTADO B    
				movKit_x -= 0.5f;
				movKit_z -= 0.08f;
				movKit_y += 0.08f;
				//printf("%f \n", movKit_x);
			}
			else {

				rotKit_y = 180.0f;
				estado = 6;
			}
		}

		if (estado == 6) { //ESTADO b

			if (movKit_z > -145) {//SIGO EN EL ESTADO B    
				movKit_z -= 1.5;
				//printf("%f \n", movKit_x);
			}
			else {

				rotKit_y = 130.0f;
				estado = 7;
			}
		}

		if (estado == 7) { //ESTADO b

			if (movKit_x < -80) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;
				movKit_z -= 0.2f;
				movKit_y += 0.2;
				//printf("%f \n", movKit_x);
			}
			else {

				rotKit_y = 90.0f;
				estado = 8;
			}
		}
		if (estado == 8) { //ESTADO b

			if (movKit_x < -60) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y -= 0.1f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 9;
			}
		}


		if (estado == 9) { //ESTADO b

			if (movKit_x < -40) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.5f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 10;
			}
		}


		if (estado == 10) { //ESTADO b

			if (movKit_x < -24) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.01f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 11;
			}
		}

		if (estado == 11) { //ESTADO b

			if (movKit_x < -18) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.35f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 12;
			}
		}

		if (estado == 12) { //ESTADO b

			if (movKit_x < -16) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 1.3f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 13;

			}
		}

		if (estado == 13) { //ESTADO b

			if (movKit_x < -11) {//SIGO EN EL ESTADO B    
				movKit_x += 2.0f;

				movKit_y += 2.3f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 14;
			}
		}

		if (estado == 14) { //ESTADO b

			if (movKit_x < -8) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.5f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 15;
			}
		}
		if (estado == 15) { //ESTADO b

			if (movKit_x < 0.0) {//SIGO EN EL ESTADO B    
				movKit_x += 2.0f;

				movKit_y += 0.1f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 16;
			}
		}
		if (estado == 16) { //ESTADO b

			if (movKit_x < 10.0) {//SIGO EN EL ESTADO B    
				movKit_x += 1.0f;

				movKit_y += 0.0f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 17;
			}
		}

		if (estado == 17) { //ESTADO b

			if (movKit_x < 40.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.7f;

				movKit_y += -0.29f;
			}
			else {

				rotKit_y = 90.0f;
				estado = 18;
			}
		}
		if (estado == 18) { //ESTADO b

			if (movKit_x < 72.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.4f;


			}
			else {

				rotKit_y = 90.0f;
				estado = 19;
			}
		}
		if (estado == 19) { //ESTADO b

			if (movKit_x < 85.0) {//SIGO EN EL ESTADO B    
				movKit_x += 1.5f;
				movKit_y -= 2.0;

			}
			else {

				rotKit_y = 90.0f;
				estado = 20;
			}
		}
		if (estado == 20) { //ESTADO b

			if (movKit_x < 92.0) {//SIGO EN EL ESTADO B    
				movKit_x += 1.5f;
				//movKit_y -= 2.0;

			}
			else {

				rotKit_y = 90.0f;
				estado = 21;
			}
		}
		if (estado == 21) { //ESTADO b
			view = glm::rotate(view, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			view = glm::rotate(view, glm::radians(-25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			if (movKit_x < 94.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.8f;
				movKit_y -= 0.1;

			}
			else {

				rotKit_y = 90.0f;
				estado = 22;
			}
		}
		if (estado == 22) { //ESTADO b

			if (movKit_x < 110.0) {//SIGO EN EL ESTADO B    
				movKit_x += 0.8f;
				movKit_y -= 0.085;

			}
			else {

				rotKit_y = 10.0f;
				estado = 23;
			}
		}
		if (estado == 23) { //ESTADO b

			if (movKit_z < -124.0f) {//SIGO EN EL ESTADO B    
				movKit_y -= 0.3;
				movKit_z += 1.00f;

				printf("%f \n", movKit_z);
			}
			else {

				rotKit_y = 270.0f;
				estado = 24;
			}
		}


		if (estado == 24) { //ESTADO b

			if (movKit_x > 102.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_z += 1.0f;

				printf("%f \n", movKit_z);
			}
			else {

				rotKit_y = 270.0f;
				estado = 25;
			}
		}


		if (estado == 25) { //ESTADO b

			if (movKit_x > 87.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;


				printf("%f \n", movKit_z);
			}
			else {


				estado = 26;
			}
		}


		if (estado == 26) { //ESTADO b

			if (movKit_x > 57.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;
				movKit_y += 0.55f;

			}
			else {


				estado = 27;
			}
		}

		if (estado == 27) { //ESTADO b

			if (movKit_x > 0.0f) {//SIGO EN EL ESTADO B    
				movKit_x -= 1.0f;


			}
			else {
				estado = 0;

			}
		}



	}





}


void display(Model Tree, Model FoodCart, Model Soldado1, Model Carrito)
{
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	//Shader lightingShader("shaders/shader_texture_light_pos.vs", "shaders/shader_texture_light_pos.fs"); //Positional
	//Shader lightingShader("shaders/shader_texture_light_dir.vs", "shaders/shader_texture_light_dir.fs"); //Directional
	Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");

	//To Use Lighting
	if (LAMPARA == 0.0)
	{
		lightingShader.use();

	}
	else {
		if (LAMPARA == 1.0)
		{
			lampShader.use();

		}
	}

	//If the light is Directional, we send the direction of the light
			//lightingShader.setVec3("light.direction", lightDirection);
			//If the light is Positional, we send the position of the light
			//lightingShader.setVec3("light.position", lightPosition);
			//If the light is Spotlight, we put the light in the camera
	lightingShader.setVec3("light.position", camera.Position);
	lightingShader.setVec3("light.direction", camera.Front);
	lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));

	lightingShader.setVec3("viewPos", camera.Position);

	// light properties
	lightingShader.setVec3("light.ambient", R, G, B);
	lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	//For Positional and Spotlight
	lightingShader.setFloat("light.constant", 1.0f);
	lightingShader.setFloat("light.linear", 0.09f);
	lightingShader.setFloat("light.quadratic", 0.032f);

	// material properties
	lightingShader.setFloat("material_shininess", 32.0f);

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f);
	glm::mat4 modelTemp2 = glm::mat4(1.0f);
	glm::mat4 modelTemp3 = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));

	// pass them to the shaders
	//lightingShader.setVec3("viewPos", camera.Position);
	lightingShader.setMat4("model", model);
	lightingShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	lightingShader.setMat4("projection", projection);


	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//Colocar código aquí
	model = glm::scale(model, glm::vec3(20.0f, 0.05f, 20.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//---mudanza
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	///
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	
	
	
	
	//entrada	

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(-42.0f, 2.0f, 26.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(15.0f, 4.0f, 4.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	//lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	//lightingShader.setInt("material_diffuse", texture1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	//columna 1 lado izquierdo
	model = glm::translate(model, glm::vec3(-5.0f, 8.5f, 0.0f));
	model = glm::scale(model, glm::vec3(5.0f, 13.0f, 4.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 2 lado izquierdo
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 1 lado derecho
	model = glm::translate(model, glm::vec3(7.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//columna 2 lado derecho
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//base bandera lado derecho columna 2
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture3);
	lightingShader.setInt("material_diffuse", texture3);

	model = glm::translate(model, glm::vec3(0.0f, 0.5250f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 0.05f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-9.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//parte alta
	model = glm::translate(model, glm::vec3(-2.0f, 3.53f, 0.0f));
	model = glm::scale(model, glm::vec3(0.450f, 6.0f, 0.450f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(24.5f, 0.0f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-4.55f, 0.5f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-15.55f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//palito
	model = glm::translate(model, glm::vec3(0.0f, 0.75f, 0.0f));
	model = glm::scale(model, glm::vec3(0.2f, 0.50f, 0.20f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-22.0f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(99.7f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(22.7f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//banderas
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	lightingShader.setInt("material_diffuse", texture4);

	model = glm::translate(model, glm::vec3(5.3f, 0.50f, -0.20f));
	//modelTemp = model;
	model = glm::scale(model, glm::vec3(10.0f, 0.5f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 24, 3);
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-2.30f, 1.90f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 24, 3);
	//model = modelTemp;

	model = glm::translate(model, glm::vec3(-7.750f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 24, 3);

	model = glm::translate(model, glm::vec3(-2.18f, -1.9f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_TRIANGLES, 24, 3);


	//----------------letrero-------------------

	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, texture11);
	lightingShader.setInt("material_diffuse", texture11);

	model = glm::translate(model, glm::vec3(5.550f, -0.430f, 1.0f));
	model = glm::scale(model, glm::vec3(7.30, 3.10, 1.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.20f, 0.20f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//________________________MESA_________________________________
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.70, 1.50, 0.70));
	model = glm::translate(model, glm::vec3(-88.0f, 0.50f, -14.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.110f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.20, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.5490f, 0.0f));
	model = glm::scale(model, glm::vec3(2.50, 0.10, 2.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//mesa2
	model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.70, 1.50, 0.70));
	model = glm::translate(model, glm::vec3(-78.0f, 0.50f, -14.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.110f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.20, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.5490f, 0.0f));
	model = glm::scale(model, glm::vec3(2.50, 0.10, 2.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//mesa3
	model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.70, 1.50, 0.70));
	model = glm::translate(model, glm::vec3(-70.0f, 0.50f, -14.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.110f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.20, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.5490f, 0.0f));
	model = glm::scale(model, glm::vec3(2.50, 0.10, 2.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//mesa4
	model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.70, 1.50, 0.70));
	model = glm::translate(model, glm::vec3(-88.0f, 0.50f, -9.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.110f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.20, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.5490f, 0.0f));
	model = glm::scale(model, glm::vec3(2.50, 0.10, 2.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//mesa5
	model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.70, 1.50, 0.70));
	model = glm::translate(model, glm::vec3(-78.0f, 0.50f, -9.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.110f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.20, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.5490f, 0.0f));
	model = glm::scale(model, glm::vec3(2.50, 0.10, 2.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//mesa6
	model = glm::mat4(1.0f);

	model = glm::scale(model, glm::vec3(0.70, 1.50, 0.70));
	model = glm::translate(model, glm::vec3(-70.0f, 0.50f, -9.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.110f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.20, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.5490f, 0.0f));
	model = glm::scale(model, glm::vec3(2.50, 0.10, 2.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.10f, 0.80f, 0.80f);
	lightingShader.setVec3("diffuseColor", 0.90f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//Rueda de la fortuna////////////////////////////////////////////////////////////////
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture5);//galaxia
	lightingShader.setInt("material_diffuse", texture5);

	//base
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
	modelTemp = model;
	modelTemp3 = model;
	model = glm::scale(model, glm::vec3(35.0f, 0.50f, 15.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;

	//soporte
	model = glm::translate(model, glm::vec3(1.0f, 0.24f, 7.3));
	model = glm::scale(model, glm::vec3(15.0f, 25.0f, 0.33f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawArrays(GL_TRIANGLES, 27, 3);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -45.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawArrays(GL_TRIANGLES, 27, 3);

	//eje
	model = modelTemp;
	model = glm::translate(model, glm::vec3(1.0f, 18.0f, 0.0f));
	model = glm::rotate(model, glm::radians(angRueda), glm::vec3(0, 0, 1));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(0.5, 0.5, 14.8));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//barras que sostienen la rueda al eje
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(1.0, 25.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(1.0, 25.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(6.50f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(6.50f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(-6.50f, 0.0f, 3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-6.50f, 0.0f, -3.20f));
	model = glm::scale(model, glm::vec3(12.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.20f));
	model = glm::scale(model, glm::vec3(0.80, 25.50, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0, 0, 1));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.20f));
	model = glm::scale(model, glm::vec3(0.80, 25.50, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", texture5);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//circulos rueda
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.50f));
	model = glm::scale(model, glm::vec3(12.50, 12.50, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.50f));
	model = glm::scale(model, glm::vec3(12.50, 12.50, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos2();

	//barras entre las ruedas
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, -12.55f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 7.5));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(16.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-7.0f, 9.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(46.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 10.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-50.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(3.0f, 12.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(44.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-6.0f, 7.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-32.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 12.50f, 0.0f));
	model = glm::scale(model, glm::vec3(0.50, 0.50, 8.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	//esferas rueda de la fortuna
	//canasta1 Aros-------------------------------------------------------------------------
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, -12.350f, -0.20f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	//model = modelTemp2;
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta 
	//soporte
	model = modelTemp2;
	
	glActiveTexture(GL_TEXTURE2);
glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	//caja
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta2 Aros------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.0f, 12.350f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	//model = modelTemp2;
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	//model = modelTemp2;
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//canasta3 Aros-----------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(12.30f, -0.30f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//canasta 4  Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(-12.30f, -0.30f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 5  Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(8.320f, 9.40f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 0.0f, 1.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 0.0f, 1.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 6 Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(-8.320f, 9.40f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 7 Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(8.310f, -9.450f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	//canasta 8 Aros--------------------------------------------------------------------------------------
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = modelTemp;
	model = glm::translate(model, glm::vec3(-8.320f, -9.450f, 0.0f));
	model = glm::rotate(model, glm::radians(angCanasta), glm::vec3(0, 0, 1));
	modelTemp2 = model;
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	circulos();
	//canasta
	//soporte
	model = modelTemp2;
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	lightingShader.setInt("material_diffuse", texture2);

	model = glm::translate(model, glm::vec3(0.0f, -2.50f, 0.3f));
	model = glm::scale(model, glm::vec3(0.250, 2.50, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//techo canasta
	model = glm::translate(model, glm::vec3(0.0f, 0.45f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.10, 2.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	//piso canasta
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	lightingShader.setInt("material_diffuse", texture7);

	model = glm::translate(model, glm::vec3(0.0f, -8.05f, 0.0f));
	model = glm::scale(model, glm::vec3(3.50, 3.0, 3.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);

	model = glm::translate(model, glm::vec3(0.0f, -0.550f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.10, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE5);
	//asiento enfrente textura galaxia
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 1.80f, 0.39f));
	model = glm::scale(model, glm::vec3(0.80, 5.0, 0.20));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoatras
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.90f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 01.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoder
	model = glm::translate(model, glm::vec3(0.4950f, 0.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.250, 1.0, 2.500));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//asientoizq
	model = glm::translate(model, glm::vec3(-3.94950f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.00));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//disco azul
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(2.0f, 6.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 0.010, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	model = modelTemp;
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 7.50f));
	model = glm::scale(model, glm::vec3(2.0, 2.0, 0.150));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -101.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.010));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	my_sphere.render();
	glBindVertexArray(VAO);


	//escalera canastas
	model = modelTemp3;
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texture5);
	lightingShader.setInt("material_diffuse", texture5);

	model = glm::translate(model, glm::vec3(1.0f, 0.860f, 2.0f));
	model = glm::scale(model, glm::vec3(02.0, 1.40, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 01.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 0.750f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 0.50));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 01.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 01.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 01.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texture8);
	lightingShader.setInt("material_diffuse", texture8);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 01.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);
	model = glm::translate(model, glm::vec3(0.0f, -0.10, 1.0f));
	model = glm::scale(model, glm::vec3(01.0, 0.80, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 01.0f, 0.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//cercado
	model = modelTemp3;
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texture9);
	lightingShader.setInt("material_diffuse", texture9);

	model = glm::translate(model, glm::vec3(-18.0f, 1.010f, 12.0f));
	model = glm::scale(model, glm::vec3(0.40, 3.0, 0.40));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 10; i = i + 1)
	{

		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}



	//-------------------------------------------------------------------------------------------




	//-------------------------------------------------------------------------------------------

	//MONTAÑA RUSA 
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, texture14);
	lightingShader.setInt("material_diffuse", texture14);

	model = glm::mat4(1.0f);
	//modelTemp = model;
	model = glm::translate(model, glm::vec3(0.0f, 13.0f, -100.0f));
	model = glm::scale(model, glm::vec3(8, 25, 4));
	modelTemp2 = model;
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -6.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1, 1, 1));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//cabina plancha 
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, texture10);
	lightingShader.setInt("material_diffuse", texture10);


	model = glm::translate(model, glm::vec3(2.5f, 0.55f, 3.0f));
	model = glm::scale(model, glm::vec3(6.0, 0.1, 8.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//parte donde van los rieles en la plancha 
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, texture14);
	lightingShader.setInt("material_diffuse", texture14);

	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(1.0, 0.1, 0.5));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	//barandales de la plancha
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	lightingShader.setInt("material_diffuse", texture4);

	model = glm::translate(model, glm::vec3(-0.495f, 5.9f, 0.55f));
	model = glm::scale(model, glm::vec3(0.01, 12.0, 0.02));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -22.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, -11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}


	model = glm::translate(model, glm::vec3(19.0f, 0.0f, 11.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 37; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(-3.5f, 0.0f, -98.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 29; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(2.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(23.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(-98.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.5f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	//barandales de las rejas 
	model = glm::translate(model, glm::vec3(0.0f, 0.5f, 6.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.04, 23.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(98.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.2));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-19.0, 0.0f, 2.55f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 0.5));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 6; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.3f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.8));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(50.0f, 0.0f, 0.5f));
	model = glm::scale(model, glm::vec3(100.0, 1.0, 0.05));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-0.13f, 0.0f, -79.0f));
	model = glm::scale(model, glm::vec3(0.75, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//puertas 

	model = glm::translate(model, glm::vec3(-0.42f, -10.0f, 61.0f));
	model = glm::scale(model, glm::vec3(0.130, 20.0, 0.5));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(1.025f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.02, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//ESCALERAS 
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture4);
	lightingShader.setInt("material_diffuse", texture4);

	model = glm::translate(model, glm::vec3(0.6f, -6.4f, 16.0f));
	model = glm::scale(model, glm::vec3(0.3, 11.3, 40.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(1.0f, -0.05f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	for (int i = 0; i <= 25; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.0f, -0.05f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//escalera para bajar 
	model = glm::translate(model, glm::vec3(-30.0f, 7.5f, -3.6f));
	model = glm::scale(model, glm::vec3(3.5, 18.0, 0.3));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, -0.05f, -1.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	for (int i = 0; i <= 30; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0, -0.05f, -1.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}

	//--------------------Postes-Soporte----------------
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, texture14);
	lightingShader.setInt("material_diffuse", texture14);

	model = modelTemp2;

	//aqui los pones, escalalos y todo
	//ejemplo:
		//aqui los pones, escalalos y todo
	//ejemplo:
	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -3.1f));
	model = glm::scale(model, glm::vec3(0.25, 1.07, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.09f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.8, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.088f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.78, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.065f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.95, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-5.5f, -0.02f, -0.05f));
	model = glm::scale(model, glm::vec3(1.0, 1.32, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-8.0f, 0.18f, -0.05f));
	model = glm::scale(model, glm::vec3(2.0, 1.28, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.5f, 0.05f, -2.5f));
	model = glm::scale(model, glm::vec3(1.0, 1.2, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(0.0f, 0.00f, -3.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(2.5f, 0.0f, -2.5f));
	model = glm::scale(model, glm::vec3(1.0, 1.03, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	model = glm::translate(model, glm::vec3(3.7f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.05, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(6.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.4, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(4.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.1, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(5.0f, 0.07, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.25, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(7.0f, 0.065, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.64, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(7.0f, -0.02, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.9, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(8.0f, -0.25f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 0.59, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	//----------------Rieles-------------------Rieles-----------------Rieles-----------------------------------

	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, texture13);
	lightingShader.setInt("material_diffuse", texture13);

	model = modelTemp;

	model = glm::translate(model, glm::vec3(0.50f, 0.150f, 0.0f));
	model = glm::scale(model, glm::vec3(0.0250, 0.250, 0.15));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


	for (int i = 0; i <= 20; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		modelTemp = model;
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, -0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.0f, -0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = glm::translate(model, glm::vec3(0.0f, -0.50f, 0.0f));
	model = glm::rotate(model, glm::radians(-14.0f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.80f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(-1.60f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-3.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//-------------------giroooooo--------------------------------------	
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(21.0f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 1; i = i + 1) //giro
	{
		model = glm::translate(model, glm::vec3(-1.2, 0.07f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-8.50f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(-1.50f), glm::vec3(1, 0, 0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-64.0f, 1.0f, -5.50f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 3; i = i + 1) //giro 2 a la derecha 
	{
		model = glm::translate(model, glm::vec3(0.2f, 0.50f, -0.750f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-5.65f), glm::vec3(0, 1, 0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//middle
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-64.0f, 1.0f, -5.20f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 6; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.30f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//giro 1
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-64.0f, 1.0f, -2.50f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.015f, -0.520f, 1.40f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(4.50f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(3.50f), glm::vec3(1, 0, 0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//atras rampa
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-51.50f, 0.0f, -7.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	//model = glm::rotate(model, glm::radians(-8.50f), glm::vec3(0, 1, 0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	model = glm::translate(model, glm::vec3(-1.50f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::translate(model, glm::vec3(-1.50f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::translate(model, glm::vec3(-1.50f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	model = glm::translate(model, glm::vec3(-1.50f, 1.0f, 0.0001f));
	model = glm::rotate(model, glm::radians(10.50f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 0.60));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	//atras rampa
	model = modelTemp;//subida
	model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -7.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	for (int i = 0; i <= 8; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 8; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.80f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		//model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 7; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.80f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.20f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.70f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 1; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 6; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.70f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 9; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.20f, -0.60f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.80f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.40f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(0.80f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.60f, -0.40f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.40f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 7; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.20f, 0.750f, 0.0f));
		model = glm::scale(model, glm::vec3(1.00, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.10f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.10f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 7; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.60f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.10f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.70f, -1.20f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-1.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.80f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.30f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, 0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//giro de regreso
	model = glm::rotate(model, glm::radians(15.50f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.30f, 0.0f, 0.1f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-3.50f), glm::vec3(0, 1, 0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = modelTemp;
	model = glm::translate(model, glm::vec3(45.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 4; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.30f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -0.50f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 8; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.50f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(-2.50f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 2; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.640f, -0.850f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 3; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.80f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0, 0, 1));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	model = glm::rotate(model, glm::radians(4.0f), glm::vec3(0, 0, 1));

	for (int i = 0; i <= 5; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(1.90f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0; i <= 8; i = i + 1)//no
	{
		model = glm::translate(model, glm::vec3(1.30f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		model = glm::rotate(model, glm::radians(2.70f), glm::vec3(0, 1, 0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	model = modelTemp;
	model = glm::translate(model, glm::vec3(100.0f, -16.0f, -6.5f));
	model = glm::scale(model, glm::vec3(4.0, 1.0, 0.250));
	lightingShader.setMat4("model", model);
	lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	for (int i = 0; i <= 11; i = i + 1)
	{
		model = glm::translate(model, glm::vec3(0.0f, -0.50f, 1.30f));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
		lightingShader.setMat4("model", model);
		lightingShader.setVec3("ambientColor", 0.0f, 1.0f, 0.0f);
		lightingShader.setVec3("diffuseColor", 0.0f, 1.0f, 1.0f);
		lightingShader.setVec3("specularColor", 0.0f, 1.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}




	////FIN DE LOS RIELES---------------------------------------------------------

	//---------------------------------------MODELOS -------------------------------------------
	//arbol ////////////////

	modelShader.use();

	modelShader.setMat4("model", model);
	modelShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	modelShader.setMat4("projection", projection);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-60.0f, 0.10f, -25.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0150f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-55.0f, 0.10f, -15.0f));
	model = glm::scale(model, glm::vec3(01.350f, 01.350f, 01.350f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	FoodCart.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-45.0f, 0.10f, -15.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);
	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-45.0f, 0.10f, -10.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);
	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-45.0f, 0.10f, -5.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-35.0f, 0.10f, 20.0f));
	model = glm::scale(model, glm::vec3(0.50f, 0.5f, 0.50f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Soldado1.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);// 5.0f, 30.10f, -125.0f
	model = glm::translate(model, glm::vec3(movKit_x, movKit_y, movKit_z));
	model = glm::rotate(model, glm::radians(rotKit_y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.4f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Carrito.Draw(modelShader);


	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-35.0f, 0.10f, -40.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);
	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-50.0f, 0.10f, -45.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);
	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-23.0f, 0.10f, -50.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-50.0f, 0.10f, -90.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-80.0f, 0.10f, -80.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);

	model = glm::mat4(1.0f);
	modelShader.setMat4("model", model);
	model = glm::translate(model, glm::vec3(-83.0f, 0.10f, -90.0f));
	model = glm::scale(model, glm::vec3(0.0150f, 0.0250f, 0.0150f));
	modelShader.setMat4("model", model);
	modelShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	Tree.Draw(modelShader);


	//----------------------------------LUCES-------------------------------------------

	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-10.0f, 2.0f, -5.0f));
	model = glm::scale(model, glm::vec3(0.25f));
	lampShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));

	lampShader.setMat4("model", model);
	my_sphere.render();
	glBindVertexArray(VAO);





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

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 9", NULL, NULL);
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
	LoadTextures();
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);
	//-----------------------MODELOS-------------------------------------
	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	// Load models
	Model Tree = ((char*)"Models/arbol2/Tree_Conifer_1.obj");
	Model FoodCart = ((char*)"Models/Cart_food/street_cart_meetball.obj");
	Model Soldado = ((char*)"Models/Soldier_with_binoculars/SOLDADO.obj");
	Model Carrito = ((char*)"Models/carrito/wooden_model _truck.obj");


	//-------------------------------------------------------

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
		if (night) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else {
			glClearColor(0.5, 0.869, 0.869f, 1.0f);
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display(Tree, FoodCart, Soldado, Carrito);

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
void my_input(GLFWwindow * window)
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
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		play = true;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		night = true;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		night = false;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		R = 1.0;
		G = 0.0;
		B = 0.0;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		R = 0.0;
		G = 1.0;
		B = 0.0;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		R = 0.0;
		G = 0.0;
		B = 1.0;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		R = 1.0;
		G = 1.0;
		B = 1.0;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		LAMPARA = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		LAMPARA = 0.0f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow * window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow * window, double xpos, double ypos)
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
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
