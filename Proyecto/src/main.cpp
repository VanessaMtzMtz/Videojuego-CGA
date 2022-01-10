#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

// contains new std::shuffle definition
#include <algorithm>
#include <random>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"

//Font rendering
#include "Headers/FontTypeRendering.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

// Include Colision headers functions
#include "Headers/Colisiones.h"

//Shadowbox include
#include "Headers/ShadowBox.h"

// OpenAL include
#include <AL/alut.h>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;
//Shader para visualizar buffer de profundidad
Shader shaderViewDepth;
//Shader dibujar el buffer de profundidad
Shader shaderDepth;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 12.0;

Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere sphereCollider(10, 10);
Box boxViewDepth;
Box boxLightViewBox;

ShadowBox* shadowBox;

// Objetos
Model modelLamp1;
Model modelMask;
Model modelVaccine;
Model modelVirus;
// Hierba
Model modelGrass;
//Edificios y casas
Model modelEdi1;
Model modelEdi2;
Model modelEdi3;
Model modelEdi4;
Model modelEdi5;
Model modelEdi6;
Model modelParque;
// Model animate instance
// Simi
Model simiModelAnimate;
//Person
Model personModelAnimate;
// Terrain model instance
Terrain terrain(-1, -1, 200, 8, "../Textures/heightmap.png");

GLuint textureCespedID;
GLuint textureTerrainBackgroundID, textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID;

// Modelo para el render del texto
FontTypeRendering::FontTypeRendering *modelText;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/mp_bloodvalley/blood-valley_ft.tga",
		"../Textures/mp_bloodvalley/blood-valley_bk.tga",
		"../Textures/mp_bloodvalley/blood-valley_up.tga",
		"../Textures/mp_bloodvalley/blood-valley_dn.tga",
		"../Textures/mp_bloodvalley/blood-valley_rt.tga",
		"../Textures/mp_bloodvalley/blood-valley_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

// Model matrix definitions
glm::mat4 matrixModelVaccine = glm::mat4(1.0);
glm::mat4 matrixModelVaccine2 = glm::mat4(1.0);
glm::mat4 modelMatrixSimi = glm::mat4(1.0f);
glm::mat4 modelMatrixPerson = glm::mat4(1.0f);
glm::mat4 modelMatrixEdi1 = glm::mat4(1.0f);
glm::mat4 modelMatrixEdi2 = glm::mat4(1.0f);
glm::mat4 modelMatrixEdi3 = glm::mat4(1.0f);
glm::mat4 modelMatrixEdi4 = glm::mat4(1.0f);
glm::mat4 modelMatrixEdi5 = glm::mat4(1.0f);
glm::mat4 modelMatrixEdi6 = glm::mat4(1.0f);
glm::mat4 modelMatrixParque = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus1 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus2 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus3 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus4 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus5 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus6 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus7 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus8 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus9 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus10 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus11 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus12 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus13 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus14 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus15 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus16 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus17 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus18 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus19 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus20 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus21 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus22 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus23 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus24 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus25 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus26 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus27 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus28 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus29 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus30 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus31 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus32 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus33 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus34 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus35 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus36 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus37 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus38 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus39 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus40 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus41 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus42 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus43 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus44 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus45 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus46 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus47 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus48 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus49 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus50 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus51 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus52 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus53 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus54 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus55 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus56 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus57 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus58 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus59 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus60 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus61 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus62 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus63 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus64 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus65 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus66 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus67 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus68 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus69 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus70 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus71 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus72 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus73 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus74 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus75 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus76 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus77 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus78 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus79 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus80 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus81 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus82 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus83 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus84 = glm::mat4(1.0f);

int animationIndex = 1;
int modelSelected = 2;
bool enableCountSelected = true;

int stateSimi = 0;

// Lamps positions
std::vector<glm::vec3> lamp1Position = { glm::vec3(-83.1, 0, -5.3), 
glm::vec3(-14.1, 0.0, -75.4), 
glm::vec3(74.0, 0.0, -38.5),
glm::vec3(66.3, 0.0, 70.0),
glm::vec3(-49.9, 0.0, 71.1)};
std::vector<float> lamp1Orientation = { 300.0, 200.0, 100.0 , 23.70, 200.0};
//Mask position
std::vector<glm::vec3> maskPosition = { glm::vec3(-66.1, 2.0, -48.5),
glm::vec3(-8.3, 2.0, -70.9),
glm::vec3(18.8, 2.0, 57.5),
glm::vec3(65.1, 2.0, -12.9)};

// Blending model unsorted
std::map<std::string, glm::vec3> blendingUnsorted = {
		{"farmacia", glm::vec3(-82.7f, 0.0f, 78.8f)},
		{"vacuna", glm::vec3(58.3, 0.0, 64.1)}
};

double deltaTime;
double currTime, lastTime;

// Jump variables
bool isJump = false;
float GRAVITY = 1.81;
double tmv = 0;
double startTimeJump = 0;

// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Framesbuffers
GLuint depthMap, depthMapFBO;

/**********************
 * OpenAL config
 ***********************/
// OpenAL Defines
#define NUM_BUFFERS 4
#define NUM_SOURCES 4
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat source0Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = {true};

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);
void prepareScene();
void prepareDepthScene();
void renderScene(bool renderParticles = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
				glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
				nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation_shadow.vs", "../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs", "../Shaders/terrain_shadow.fs");
	shaderViewDepth.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs", "../Shaders/shadow_mapping_depth.fs");

	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	boxViewDepth.init();
	boxViewDepth.setShader(&shaderViewDepth);

	terrain.init();
	terrain.setShader(&shaderTerrain);
	terrain.setPosition(glm::vec3(100, 0, 100));
	
	//Object models
	modelLamp1.loadModel("../models/Poste/poste.obj");
	modelLamp1.setShader(&shaderMulLighting);
	modelMask.loadModel("../models/N95/n95.obj");
	modelMask.setShader(&shaderMulLighting);
	modelVaccine.loadModel("../models/Vaccine/model/Export/vaccine.obj");
	modelVaccine.setShader(&shaderMulLighting);
	modelVirus.loadModel("../models/Virus/virus.obj");
	modelVirus.setShader(&shaderMulLighting);

	//Grass
	modelGrass.loadModel("../models/grass/grassModel.obj");
	modelGrass.setShader(&shaderMulLighting);

	//Edificios
	modelEdi1.loadModel("../models/edificios/ladoA.obj");
	modelEdi1.setShader(&shaderMulLighting);
	modelEdi2.loadModel("../models/edificios/ladoB.obj");
	modelEdi2.setShader(&shaderMulLighting);
	modelEdi3.loadModel("../models/edificios/ladoC.obj");
	modelEdi3.setShader(&shaderMulLighting);
	modelEdi4.loadModel("../models/edificios/ladoD.obj");
	modelEdi4.setShader(&shaderMulLighting);
	modelEdi5.loadModel("../models/edificios/Kiosco/Kiosko.obj");
	modelEdi5.setShader(&shaderMulLighting);
	modelEdi6.loadModel("../models/edificios/ladoE.obj");
	modelEdi6.setShader(&shaderMulLighting);
	modelParque.loadModel("../models/parque/parque.obj");
	modelParque.setShader(&shaderMulLighting);
	//Simi
	simiModelAnimate.loadModel("../models/doctor-simi/simi.fbx");
	simiModelAnimate.setShader(&shaderMulLighting);

	//Person
	personModelAnimate.loadModel("../models/Person/Crying/Crying.dae");
	personModelAnimate.setShader(&shaderMulLighting);

	camera->setPosition(glm::vec3(0.0, 0.0, 15.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0);

	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	FIBITMAP *bitmap;
	unsigned char *data;

	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		FIBITMAP *bitmap = skyboxTexture.loadImage(true);
		unsigned char *data = skyboxTexture.convertToData(bitmap, imageWidth,
				imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		} else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

	// Definiendo la textura a utilizar
	Texture textureTerrainBackground("../Textures/grassy4.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBackground.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBackground.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBackgroundID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBackground.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainR("../Textures/brick.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainR.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainR.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainRID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainR.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainG("../Textures/broken.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainG.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainG.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainGID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainG.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainB("../Textures/asphalt.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainB.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainB.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainB.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainBlendMap("../Textures/blendMap.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBlendMap.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBlendMap.convertToData(bitmap, imageWidth,
			imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBlendMapID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBlendMap.freeImage(bitmap);

	/******************************************
	*Se inicializa el modelo de FontTypeRendering para dibujar texto
	*******************************************/
	modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
	modelText -> Initialize();

	/*******************************************
	 * OpenAL init
	 *******************************************/
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Config source 0
	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[0] = alutCreateBufferFromFile("../sounds/ambiente-ciudad.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR){
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}

	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}

	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, 2.0f);
	alSourcefv(source[0], AL_POSITION, source0Pos);
	alSourcefv(source[0], AL_VELOCITY, source0Vel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);
	alSourcef(source[0], AL_MAX_DISTANCE, 3000);

	/*******************************************
	 * Inicializacion del framebuffer para
	 * almacenar el buffer de profundidad
	 *******************************************/
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();

	// Basic objects Delete
	skyboxSphere.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();

	// Terrains objects Delete
	terrain.destroy();
	modelEdi1.destroy(); 
	modelEdi2.destroy();
	modelEdi3.destroy();
	modelEdi4.destroy();
	modelEdi5.destroy();
	modelEdi6.destroy();
	modelParque.destroy();

	// Objects Delete
	modelLamp1.destroy();
	modelMask.destroy();
	modelGrass.destroy();
	modelVaccine.destroy();
	modelVirus.destroy();

	// Custom objects animate
	simiModelAnimate.destroy();
	personModelAnimate.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureTerrainBackgroundID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainBlendMapID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset){
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}

	//Mapeo botones control XBOX
	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) {
		int axesCount, buttonCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

		if (fabs(axes[1]) > 0.2) {
			modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(0, 0, axes[1] * 0.1));
			animationIndex = 0;
		}
		if (fabs(axes[0]) > 0.2) {
			modelMatrixSimi = glm::rotate(modelMatrixSimi, glm::radians(-axes[0] * 0.5f), glm::vec3(0, 1, 0));
			animationIndex = 0;
		}
		if (fabs(axes[2]) > 0.2) {
			camera->mouseMoveCamera(axes[2], 0.0, deltaTime);
		}
		if (fabs(axes[3]) > 0.2) {
			camera->mouseMoveCamera(0.0, axes[3], deltaTime);
		}
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		//std::cout << "Numero de botones disponibles:=>" << buttonCount << std::endl;
		/*if (buttons[0] == GLFW_PRESS)
			std::cout << "Se presiona A:" << std::endl;*/
		if (!isJump && buttons[0] == GLFW_PRESS) {
			isJump = true;
			startTimeJump = currTime;
			tmv = 0;
		}

	}

	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);
	offsetX = 0;
	offsetY = 0;

	// Seleccionar modelo
	if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){
		enableCountSelected = false;
		modelSelected++;
		if(modelSelected > 2)
			modelSelected = 0;
		std::cout << "modelSelected:" << modelSelected << std::endl;
	}
	else if(glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;

	//Simi walking
	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		modelMatrixSimi = glm::rotate(modelMatrixSimi, glm::radians(1.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		modelMatrixSimi = glm::rotate(modelMatrixSimi, glm::radians(-1.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
		modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(0, 0, 0.3));
		//modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(0, 0, 0.02));
		animationIndex = 0;
	}else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(0, 0, -0.2));
		animationIndex = 0;
	}

	bool keySpaceStatus = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if(!isJump && keySpaceStatus){
		isJump = true;
		startTimeJump = currTime;
		tmv = 0;
	}

	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	glm::mat4 view;
	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;
	int stateVirus = 1;
	float advanceCountVirus = 0.0;
	int numberAdvanceVirus = 0;
	int maxAdvanceVirus = 20;

	matrixModelVaccine = glm::translate(matrixModelVaccine, glm::vec3(58.3, 0.0, 64.1));
	matrixModelVaccine = glm::rotate(matrixModelVaccine, glm::radians(90.0f), glm::vec3(0, 1, 0));
	matrixModelVaccine2 = glm::translate(matrixModelVaccine2, glm::vec3(65.1, 0.0, -65.5));
	matrixModelVaccine2 = glm::rotate(matrixModelVaccine2, glm::radians(90.0f), glm::vec3(0, 1, 0));

  modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(-68.0f, 0.0f, 72.7f));
	//modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(42.0f, 0.0f, -50.0f));
	modelMatrixSimi = glm::rotate(modelMatrixSimi, glm::radians(-180.0f), glm::vec3(0, 1, 0));

	modelMatrixPerson = glm::translate(modelMatrixPerson, glm::vec3(-75.0f, 0.0f, -74.3f));

	modelMatrixEdi1 = glm::translate(modelMatrixEdi1, glm::vec3(-82.7f, 0.0f, 78.8f));
	modelMatrixEdi2 = glm::translate(modelMatrixEdi2, glm::vec3(-82.7f, 0.0f, 78.8f));
	modelMatrixEdi3 = glm::translate(modelMatrixEdi3, glm::vec3(-82.7f, 0.0f, 75.0f));
	modelMatrixEdi4 = glm::translate(modelMatrixEdi4, glm::vec3(-82.7f, 0.0f, 78.8f));
	modelMatrixEdi5 = glm::translate(modelMatrixEdi5, glm::vec3(-50.0f, 0.0f, 56.5f));
	modelMatrixEdi6 = glm::translate(modelMatrixEdi6, glm::vec3(-82.7f, 0.0f, 78.8f));
	modelMatrixParque = glm::translate(modelMatrixParque, glm::vec3(-82.7f, 0.0f, 78.8f));

	//Camino 1
	modelMatrixVirus1 = glm::translate(modelMatrixVirus1, glm::vec3(-68.0f, 2.5f, 70.0f));
	modelMatrixVirus1 = glm::scale(modelMatrixVirus1, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus2 = glm::translate(modelMatrixVirus2, glm::vec3(-68.0f, 2.5f, 60.0f));
	modelMatrixVirus2 = glm::scale(modelMatrixVirus2, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus3 = glm::translate(modelMatrixVirus3, glm::vec3(-68.0f, 2.5f, 50.0f));
	modelMatrixVirus3 = glm::scale(modelMatrixVirus3, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus4 = glm::translate(modelMatrixVirus4, glm::vec3(-68.0f, 2.5f, 40.0f));
	modelMatrixVirus4 = glm::scale(modelMatrixVirus4, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus5 = glm::translate(modelMatrixVirus5, glm::vec3(-68.0f, 2.5f, 30.0f));
	modelMatrixVirus5 = glm::scale(modelMatrixVirus5, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus6 = glm::translate(modelMatrixVirus6, glm::vec3(-68.0f, 2.5f, 20.0f));
	modelMatrixVirus6 = glm::scale(modelMatrixVirus6, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus7 = glm::translate(modelMatrixVirus7, glm::vec3(-68.0f, 2.5f, 10.0f));
	modelMatrixVirus7 = glm::scale(modelMatrixVirus7, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus8 = glm::translate(modelMatrixVirus8, glm::vec3(-68.0f, 2.5f, 0.0f));
	modelMatrixVirus8 = glm::scale(modelMatrixVirus8, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus9 = glm::translate(modelMatrixVirus9, glm::vec3(-68.0f, 2.5f, -10.0f));
	modelMatrixVirus9 = glm::scale(modelMatrixVirus9, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus10 = glm::translate(modelMatrixVirus10, glm::vec3(-68.0f, 2.5f, -20.0f));
	modelMatrixVirus10 = glm::scale(modelMatrixVirus10, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus11 = glm::translate(modelMatrixVirus11, glm::vec3(-68.0f, 2.5f, -30.0f));
	modelMatrixVirus11 = glm::scale(modelMatrixVirus11, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus12 = glm::translate(modelMatrixVirus12, glm::vec3(-68.0f, 2.5f, -40.0f));
	modelMatrixVirus12 = glm::scale(modelMatrixVirus12, glm::vec3(3.0f, 3.0f, 3.0f));

	//Cruze1
	//FILA1
	modelMatrixVirus13 = glm::translate(modelMatrixVirus13, glm::vec3(-75.0f, 2.5f, -62.0f));
	modelMatrixVirus13 = glm::scale(modelMatrixVirus13, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus14 = glm::translate(modelMatrixVirus14, glm::vec3(-70.0f, 2.5f, -66.0f));
	modelMatrixVirus14 = glm::scale(modelMatrixVirus14, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus15 = glm::translate(modelMatrixVirus15, glm::vec3(-65.0f, 2.5f, -62.0f));
	modelMatrixVirus15 = glm::scale(modelMatrixVirus15, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus16 = glm::translate(modelMatrixVirus16, glm::vec3(-60.0f, 2.5f, -66.0f));
	modelMatrixVirus16 = glm::scale(modelMatrixVirus16, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus17 = glm::translate(modelMatrixVirus17, glm::vec3(-55.0f, 2.5f, -62.0f));
	modelMatrixVirus17 = glm::scale(modelMatrixVirus17, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus18 = glm::translate(modelMatrixVirus18, glm::vec3(-50.0f, 2.5f, -66.0f));
	modelMatrixVirus18 = glm::scale(modelMatrixVirus18, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus19 = glm::translate(modelMatrixVirus19, glm::vec3(-45.0f, 2.5f, -62.0f));
	modelMatrixVirus19 = glm::scale(modelMatrixVirus19, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus20 = glm::translate(modelMatrixVirus20, glm::vec3(-40.0f, 2.5f, -66.0f));
	modelMatrixVirus20 = glm::scale(modelMatrixVirus20, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus21 = glm::translate(modelMatrixVirus21, glm::vec3(-35.0f, 2.5f, -62.0f));
	modelMatrixVirus21 = glm::scale(modelMatrixVirus21, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus22 = glm::translate(modelMatrixVirus22, glm::vec3(-30.0f, 2.5f, -66.0f));
	modelMatrixVirus22 = glm::scale(modelMatrixVirus22, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus23 = glm::translate(modelMatrixVirus23, glm::vec3(-25.0f, 2.5f, -62.0f));
	modelMatrixVirus23 = glm::scale(modelMatrixVirus23, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus24 = glm::translate(modelMatrixVirus24, glm::vec3(-20.0f, 2.5f, -66.0f));
	modelMatrixVirus24 = glm::scale(modelMatrixVirus24, glm::vec3(3.0f, 3.0f, 3.0f));
	//FILA2
	modelMatrixVirus25 = glm::translate(modelMatrixVirus25, glm::vec3(-73.0f, 2.5f, -70.0f));
	modelMatrixVirus25 = glm::scale(modelMatrixVirus25, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus26 = glm::translate(modelMatrixVirus26, glm::vec3(-68.0f, 2.5f, -74.0f));
	modelMatrixVirus26 = glm::scale(modelMatrixVirus26, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus27 = glm::translate(modelMatrixVirus27, glm::vec3(-63.0f, 2.5f, -70.0f));
	modelMatrixVirus27 = glm::scale(modelMatrixVirus27, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus28 = glm::translate(modelMatrixVirus28, glm::vec3(-58.0f, 2.5f, -74.0f));
	modelMatrixVirus28 = glm::scale(modelMatrixVirus28, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus29 = glm::translate(modelMatrixVirus29, glm::vec3(-53.0f, 2.5f, -70.0f));
	modelMatrixVirus29 = glm::scale(modelMatrixVirus29, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus30 = glm::translate(modelMatrixVirus30, glm::vec3(-48.0f, 2.5f, -74.0f));
	modelMatrixVirus30 = glm::scale(modelMatrixVirus30, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus31 = glm::translate(modelMatrixVirus31, glm::vec3(-43.0f, 2.5f, -70.0f));
	modelMatrixVirus31 = glm::scale(modelMatrixVirus31, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus32 = glm::translate(modelMatrixVirus32, glm::vec3(-38.0f, 2.5f, -74.0f));
	modelMatrixVirus32 = glm::scale(modelMatrixVirus32, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus33 = glm::translate(modelMatrixVirus33, glm::vec3(-33.0f, 2.5f, -70.0f));
	modelMatrixVirus33 = glm::scale(modelMatrixVirus33, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus34 = glm::translate(modelMatrixVirus34, glm::vec3(-28.0f, 2.5f, -74.0f));
	modelMatrixVirus34 = glm::scale(modelMatrixVirus34, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus35 = glm::translate(modelMatrixVirus35, glm::vec3(-23.0f, 2.5f, -74.0f));
	modelMatrixVirus35 = glm::scale(modelMatrixVirus35, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus36 = glm::translate(modelMatrixVirus36, glm::vec3(-18.0f, 2.5f, -70.0f));
	modelMatrixVirus36 = glm::scale(modelMatrixVirus36, glm::vec3(2.0f, 2.0f, 2.0f));
	//FILA3
	modelMatrixVirus37 = glm::translate(modelMatrixVirus37, glm::vec3(-75.0f, 2.5f, -80.0f));
	modelMatrixVirus37 = glm::scale(modelMatrixVirus37, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus38 = glm::translate(modelMatrixVirus38, glm::vec3(-70.0f, 2.5f, -77.0f));
	modelMatrixVirus38 = glm::scale(modelMatrixVirus38, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus39 = glm::translate(modelMatrixVirus39, glm::vec3(-65.0f, 2.5f, -80.0f));
	modelMatrixVirus39 = glm::scale(modelMatrixVirus39, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus40 = glm::translate(modelMatrixVirus40, glm::vec3(-60.0f, 2.5f, -77.0f));
	modelMatrixVirus40 = glm::scale(modelMatrixVirus40, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus41 = glm::translate(modelMatrixVirus41, glm::vec3(-55.0f, 2.5f, -80.0f));
	modelMatrixVirus41 = glm::scale(modelMatrixVirus41, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus42 = glm::translate(modelMatrixVirus42, glm::vec3(-50.0f, 2.5f, -77.0f));
	modelMatrixVirus42 = glm::scale(modelMatrixVirus42, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus43 = glm::translate(modelMatrixVirus43, glm::vec3(-45.0f, 2.5f, -80.0f));
	modelMatrixVirus43 = glm::scale(modelMatrixVirus43, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus44 = glm::translate(modelMatrixVirus44, glm::vec3(-40.0f, 2.5f, -77.0f));
	modelMatrixVirus44 = glm::scale(modelMatrixVirus44, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus45 = glm::translate(modelMatrixVirus45, glm::vec3(-35.0f, 2.5f, -80.0f));
	modelMatrixVirus45 = glm::scale(modelMatrixVirus45, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus46 = glm::translate(modelMatrixVirus46, glm::vec3(-30.0f, 2.5f, -77.0f));
	modelMatrixVirus46 = glm::scale(modelMatrixVirus46, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus47 = glm::translate(modelMatrixVirus47, glm::vec3(-25.0f, 2.5f, -80.0f));
	modelMatrixVirus47 = glm::scale(modelMatrixVirus47, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus48 = glm::translate(modelMatrixVirus48, glm::vec3(-20.0f, 2.5f, -77.0f));
	modelMatrixVirus48 = glm::scale(modelMatrixVirus48, glm::vec3(3.0f, 3.0f, 3.0f));
	//Fila 4
	modelMatrixVirus49 = glm::translate(modelMatrixVirus49, glm::vec3(-73.0f, 2.5f, -85.0f));
	modelMatrixVirus49 = glm::scale(modelMatrixVirus49, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus50 = glm::translate(modelMatrixVirus50, glm::vec3(-68.0f, 2.5f, -82.0f));
	modelMatrixVirus50 = glm::scale(modelMatrixVirus50, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus51 = glm::translate(modelMatrixVirus51, glm::vec3(-63.0f, 2.5f, -85.0f));
	modelMatrixVirus51 = glm::scale(modelMatrixVirus51, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus52 = glm::translate(modelMatrixVirus52, glm::vec3(-58.0f, 2.5f, -82.0f));
	modelMatrixVirus52 = glm::scale(modelMatrixVirus52, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus53 = glm::translate(modelMatrixVirus53, glm::vec3(-53.0f, 2.5f, -85.0f));
	modelMatrixVirus53 = glm::scale(modelMatrixVirus53, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus54 = glm::translate(modelMatrixVirus54, glm::vec3(-48.0f, 2.5f, -82.0f));
	modelMatrixVirus54 = glm::scale(modelMatrixVirus54, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus55 = glm::translate(modelMatrixVirus55, glm::vec3(-43.0f, 2.5f, -85.0f));
	modelMatrixVirus55 = glm::scale(modelMatrixVirus55, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus56 = glm::translate(modelMatrixVirus56, glm::vec3(-38.0f, 2.5f, -82.0f));
	modelMatrixVirus56 = glm::scale(modelMatrixVirus56, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus57 = glm::translate(modelMatrixVirus57, glm::vec3(-33.0f, 2.5f, -85.0f));
	modelMatrixVirus57 = glm::scale(modelMatrixVirus57, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus58 = glm::translate(modelMatrixVirus58, glm::vec3(-28.0f, 2.5f, -82.0f));
	modelMatrixVirus58 = glm::scale(modelMatrixVirus58, glm::vec3(2.0f, 2.0f, 2.0f));
	modelMatrixVirus59 = glm::translate(modelMatrixVirus59, glm::vec3(-23.0f, 2.5f, -85.0f));
	modelMatrixVirus59 = glm::scale(modelMatrixVirus59, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus60 = glm::translate(modelMatrixVirus60, glm::vec3(-18.0f, 2.5f, -82.0f));
	modelMatrixVirus60 = glm::scale(modelMatrixVirus60, glm::vec3(2.0f, 2.0f, 2.0f));
	//Camino2
	modelMatrixVirus61 = glm::translate(modelMatrixVirus61, glm::vec3(-2.0f, 2.5f, -45.0f));
	modelMatrixVirus61 = glm::scale(modelMatrixVirus61, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus62 = glm::translate(modelMatrixVirus62, glm::vec3(-25.0f, 2.5f, -40.0f));
	modelMatrixVirus62 = glm::scale(modelMatrixVirus62, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus63 = glm::translate(modelMatrixVirus63, glm::vec3(-2.0f, 2.5f, -35.0f));
	modelMatrixVirus63 = glm::scale(modelMatrixVirus63, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus64 = glm::translate(modelMatrixVirus64, glm::vec3(-25.0f, 2.5f, -30.0f));
	modelMatrixVirus64 = glm::scale(modelMatrixVirus64, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus65 = glm::translate(modelMatrixVirus65, glm::vec3(-2.0f, 2.5f, -25.0f));
	modelMatrixVirus65 = glm::scale(modelMatrixVirus65, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus66 = glm::translate(modelMatrixVirus66, glm::vec3(-25.0f, 2.5f, -20.0f));
	modelMatrixVirus66 = glm::scale(modelMatrixVirus66, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus67 = glm::translate(modelMatrixVirus67, glm::vec3(-2.0f, 2.5f, -15.0f));
	modelMatrixVirus67 = glm::scale(modelMatrixVirus67, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus68 = glm::translate(modelMatrixVirus68, glm::vec3(-25.0f, 2.5f, -10.0f));
	modelMatrixVirus68 = glm::scale(modelMatrixVirus68, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus69 = glm::translate(modelMatrixVirus69, glm::vec3(-2.0f, 2.5f, -5.0f));
	modelMatrixVirus69 = glm::scale(modelMatrixVirus69, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus70 = glm::translate(modelMatrixVirus70, glm::vec3(-25.0f, 2.5f, 0.0f));
	modelMatrixVirus70 = glm::scale(modelMatrixVirus70, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus71 = glm::translate(modelMatrixVirus71, glm::vec3(-2.0f, 2.5f, 5.0f));
	modelMatrixVirus71 = glm::scale(modelMatrixVirus71, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus72 = glm::translate(modelMatrixVirus72, glm::vec3(-25.0f, 2.5f, 10.0f));
	modelMatrixVirus72 = glm::scale(modelMatrixVirus72, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus73 = glm::translate(modelMatrixVirus73, glm::vec3(-2.0f, 2.5f, 15.0f));
	modelMatrixVirus73 = glm::scale(modelMatrixVirus73, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus74 = glm::translate(modelMatrixVirus74, glm::vec3(-25.0f, 2.5f, 20.0f));
	modelMatrixVirus74 = glm::scale(modelMatrixVirus74, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus75 = glm::translate(modelMatrixVirus75, glm::vec3(-2.0f, 2.5f, 25.0f));
	modelMatrixVirus75 = glm::scale(modelMatrixVirus75, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus76 = glm::translate(modelMatrixVirus76, glm::vec3(-25.0f, 2.5f, 30.0f));
	modelMatrixVirus76 = glm::scale(modelMatrixVirus76, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus77 = glm::translate(modelMatrixVirus77, glm::vec3(-2.0f, 2.5f, 35.0f));
	modelMatrixVirus77 = glm::scale(modelMatrixVirus77, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus78 = glm::translate(modelMatrixVirus78, glm::vec3(-25.0f, 2.5f, 40.0f));
	modelMatrixVirus78 = glm::scale(modelMatrixVirus78, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus79 = glm::translate(modelMatrixVirus79, glm::vec3(-2.0f, 2.5f, 45.0f));
	modelMatrixVirus79 = glm::scale(modelMatrixVirus79, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus80 = glm::translate(modelMatrixVirus80, glm::vec3(-25.0f, 2.5f, 50.0f));
	modelMatrixVirus80 = glm::scale(modelMatrixVirus80, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus81 = glm::translate(modelMatrixVirus81, glm::vec3(-2.0f, 2.5f, 55.0f));
	modelMatrixVirus81 = glm::scale(modelMatrixVirus81, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus82 = glm::translate(modelMatrixVirus82, glm::vec3(-25.0f, 2.5f, 60.0f));
	modelMatrixVirus82 = glm::scale(modelMatrixVirus82, glm::vec3(3.0f, 3.0f, 3.0f));
	/*modelMatrixVirus83 = glm::translate(modelMatrixVirus83, glm::vec3(-2.0f, 2.5f, 65.0f));
	modelMatrixVirus83 = glm::scale(modelMatrixVirus83, glm::vec3(3.0f, 3.0f, 3.0f));
	modelMatrixVirus84 = glm::translate(modelMatrixVirus84, glm::vec3(-25.0f, 2.5f, 70.0f));
	modelMatrixVirus84 = glm::scale(modelMatrixVirus84, glm::vec3(3.0f, 3.0f, 3.0f));*/

	lastTime = TimeManager::Instance().GetTime(); 

	glm::vec3 lightPos = glm::vec3(10.0, 10.0, 0.0);
	shadowBox = new ShadowBox(-lightPos, camera.get(), 15.0f, 0.1f, 45.0f);

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if(currTime - lastTime < 0.016666667){
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		std::map<std::string, bool> collisionDetection;

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				(float) screenWidth / (float) screenHeight, 0.01f, 100.0f);

		if(modelSelected != 1){
			axis = glm::axis(glm::quat_cast(modelMatrixSimi));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixSimi));
			target = modelMatrixSimi[3];
		}

		if(std::isnan(angleTarget))
			angleTarget = 0.0;
		if(axis.y < 0)
			angleTarget = -angleTarget;
		if(modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		view = camera->getViewMatrix();

		//Projection light shadow mapping
		glm::mat4 lightProjection = glm::mat4(1.0f), lightView= glm::mat4(1.0f);
		shadowBox->update(screenWidth,screenHeight);
		glm::vec3 centerBox = shadowBox->getCenter();
		glm::mat4 lightSpaceMatrix;
		lightView = glm::lookAt(centerBox, centerBox + glm::normalize(-lightPos), glm::vec3(0.0, 1.0, 0.0));
		lightProjection[0][0] = 2.0f / shadowBox->getWidth();
		lightProjection[1][1] = 2.0f / shadowBox->getHeight();
		lightProjection[2][2] = -2.0f / shadowBox->getLength();
		lightProjection[3][3] = 1.0f;
		lightSpaceMatrix = lightProjection * lightView;
		shaderDepth.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
				glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderMulLighting.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		shaderTerrain.setMatrix4("lightSpaceMatrix", 1, false, glm::value_ptr(lightSpaceMatrix));

		/*******************************************
		 * Propiedades Neblina
		 *******************************************/
		shaderMulLighting.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.0, 0.5, 0.2)));
		//shaderMulLighting.setFloat("density", 0.02);
		shaderTerrain.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.0, 0.5, 0.2)));
		//shaderTerrain.setFloat("density", 0.02);
		shaderSkybox.setVectorFloat3("fogColor", glm::value_ptr(glm::vec3(0.0, 0.5, 0.2)));
		//shaderSkybox.setFloat("lowerLimit", 0.0);
		//shaderSkybox.setFloat("upperLimit", 0.04);

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));

		/*******************************************
		 * Propiedades Luz direccional Terrain
		 *******************************************/
		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/
		glm::vec3 spotPosition = modelMatrixEdi5 * glm::vec4(7.0f, 2.0f, -12.0f, 1.0f);
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderTerrain.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(glm::vec3(spotPosition)));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.0014);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.0001);
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(77.0f)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(77.0f)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(glm::vec3(spotPosition)));
		shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderTerrain.setFloat("spotLights[0].constant", 1.0);
		shaderTerrain.setFloat("spotLights[0].linear", 0.0014);
		shaderTerrain.setFloat("spotLights[0].quadratic", 0.0001);
		shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(77.0f)));
		shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(77.0f)));

		/*******************************************
		 * Propiedades PointLights
		 *******************************************/
		shaderMulLighting.setInt("pointLightCount", lamp1Position.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size());
		for (int i = 0; i < lamp1Position.size(); i++){
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5, 0.5, 0.5));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0, 10.3585, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 3.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.5, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.01);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 3.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.5, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
		}

		// Render del buffer de profundidad
		glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);
		prepareDepthScene();
		renderScene(false);
		glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Render de la escena normal 
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		prepareScene();
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shaderMulLighting.setInt("shadowMap", 10);
		shaderTerrain.setInt("shadowMap", 10);

		/*******************************************
		 * Skybox
		 *******************************************/
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);
		renderScene();
		
		/*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/

		// Lamps1 colliders
		for (int i = 0; i < lamp1Position.size(); i++){
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, lamp1Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp, glm::radians(lamp1Orientation[i]),
					glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp1-" + std::to_string(i), lampCollider, modelMatrixColliderLamp);
			// Set the orientation of collider before doing the scale
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp, glm::vec3(0.5, 0.5, 0.5));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp, modelLamp1.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = modelLamp1.getObb().e * glm::vec3(0.5, 0.5, 0.5);
			std::get<0>(collidersOBB.find("lamp1-" + std::to_string(i))->second) = lampCollider;
		}


		// Collider de simi
		AbstractModel::OBB simiCollider;
		glm::mat4 modelmatrixColliderSimi = glm::mat4(modelMatrixSimi);
		modelmatrixColliderSimi = glm::rotate(modelmatrixColliderSimi,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		simiCollider.u = glm::quat_cast(modelmatrixColliderSimi);
		modelmatrixColliderSimi = glm::scale(modelmatrixColliderSimi, glm::vec3(1.5f, 1.5f, 1.5f));
		modelmatrixColliderSimi = glm::translate(modelmatrixColliderSimi,
				glm::vec3(simiModelAnimate.getObb().c.x,
						simiModelAnimate.getObb().c.y - 0.5f,
						simiModelAnimate.getObb().c.z + 1.15f));
		simiCollider.e = simiModelAnimate.getObb().e * glm::vec3(2.0, 2.8, 7.5);
		simiCollider.c = glm::vec3(modelmatrixColliderSimi[3]);
		addOrUpdateColliders(collidersOBB, "simi", simiCollider, modelMatrixSimi);

		// Collider del edificio 1
		AbstractModel::OBB edi1Collider;
		glm::mat4 modelmatrixColliderEdi1 = glm::mat4(modelMatrixEdi1);
		modelmatrixColliderEdi1 = glm::rotate(modelmatrixColliderEdi1,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		edi1Collider.u = glm::quat_cast(modelmatrixColliderEdi1);
		modelmatrixColliderEdi1 = glm::scale(modelmatrixColliderEdi1, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderEdi1 = glm::translate(modelmatrixColliderEdi1,
				glm::vec3(modelEdi1.getObb().c.x,
						modelEdi1.getObb().c.y + 65.5,
						modelEdi1.getObb().c.z + 123.5));
		edi1Collider.e = modelEdi1.getObb().e * glm::vec3(1.0, 12.3, 0.025);
		edi1Collider.c = glm::vec3(modelmatrixColliderEdi1[3]);
		addOrUpdateColliders(collidersOBB, "edi1", edi1Collider, modelMatrixEdi1);

		// Collider del edificio 2
		AbstractModel::OBB edi2Collider;
		glm::mat4 modelmatrixColliderEdi2 = glm::mat4(modelMatrixEdi2);
		modelmatrixColliderEdi2 = glm::rotate(modelmatrixColliderEdi2,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		edi2Collider.u = glm::quat_cast(modelmatrixColliderEdi2);
		modelmatrixColliderEdi2 = glm::scale(modelmatrixColliderEdi2, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderEdi2 = glm::translate(modelmatrixColliderEdi2,
				glm::vec3(modelEdi2.getObb().c.x + 22.0,
						modelEdi2.getObb().c.y + 168.5,
						modelEdi2.getObb().c.z + 195.0));
		edi2Collider.e = modelEdi2.getObb().e * glm::vec3(1.1, 1.1, 0.3);
		edi2Collider.c = glm::vec3(modelmatrixColliderEdi2[3]);
		addOrUpdateColliders(collidersOBB, "edi2", edi2Collider, modelMatrixEdi2);

		// Collider del edificio 3
		AbstractModel::OBB edi3Collider;
		glm::mat4 modelmatrixColliderEdi3 = glm::mat4(modelMatrixEdi3);
		modelmatrixColliderEdi3 = glm::rotate(modelmatrixColliderEdi3,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		edi3Collider.u = glm::quat_cast(modelmatrixColliderEdi3);
		modelmatrixColliderEdi3 = glm::scale(modelmatrixColliderEdi3, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderEdi3 = glm::translate(modelmatrixColliderEdi3,
				glm::vec3(modelEdi3.getObb().c.x + 5.5, 
						modelEdi3.getObb().c.y + 49.6,
						modelEdi3.getObb().c.z + 82.0));
		edi3Collider.e = modelEdi3.getObb().e * glm::vec3(1.0, 10.85, 0.025);
		edi3Collider.c = glm::vec3(modelmatrixColliderEdi3[3]);
		addOrUpdateColliders(collidersOBB, "edi3", edi3Collider, modelMatrixEdi3);

		// Collider del edificio 4
		AbstractModel::OBB edi4Collider;
		glm::mat4 modelmatrixColliderEdi4 = glm::mat4(modelMatrixEdi4);
		modelmatrixColliderEdi4 = glm::rotate(modelmatrixColliderEdi4,
			glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		edi4Collider.u = glm::quat_cast(modelmatrixColliderEdi4);
		modelmatrixColliderEdi4 = glm::scale(modelmatrixColliderEdi4, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderEdi4 = glm::translate(modelmatrixColliderEdi4,
				glm::vec3(modelEdi4.getObb().c.x,
						modelEdi4.getObb().c.y + 84.7,
						modelEdi4.getObb().c.z + 110.0));
		edi4Collider.e = modelEdi4.getObb().e * glm::vec3(1.0, 5.9, 0.05);
		edi4Collider.c = glm::vec3(modelmatrixColliderEdi4[3]);
		addOrUpdateColliders(collidersOBB, "edi4", edi4Collider, modelMatrixEdi4);

		// Collider del edificio 6
		AbstractModel::OBB edi6Collider;
		glm::mat4 modelmatrixColliderEdi6 = glm::mat4(modelMatrixEdi6);
		modelmatrixColliderEdi6 = glm::rotate(modelmatrixColliderEdi6,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		edi6Collider.u = glm::quat_cast(modelmatrixColliderEdi6);
		modelmatrixColliderEdi6 = glm::scale(modelmatrixColliderEdi6, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderEdi6 = glm::translate(modelmatrixColliderEdi6,
			glm::vec3(modelEdi6.getObb().c.x,
				modelEdi6.getObb().c.y + 95.7,
				modelEdi6.getObb().c.z + 110.0));
		edi6Collider.e = modelEdi6.getObb().e * glm::vec3(1.0, 5.9, 0.05);
		edi6Collider.c = glm::vec3(modelmatrixColliderEdi6[3]);
		addOrUpdateColliders(collidersOBB, "edi6", edi6Collider, modelMatrixEdi6);

		//Collider del virus1
		AbstractModel::SBB virus1Collider;
		glm::mat4 modelMatrixColliderVirus1 = glm::mat4(modelMatrixVirus1);
		modelMatrixColliderVirus1 = glm::scale(modelMatrixColliderVirus1, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus1 = glm::translate(modelMatrixColliderVirus1, modelVirus.getSbb().c);
		virus1Collider.c = glm::vec3(modelMatrixColliderVirus1[3]);
		virus1Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "virus1", virus1Collider, modelMatrixVirus1);

		//Collider del virus2
		AbstractModel::SBB virus2Collider;
		glm::mat4 modelMatrixColliderVirus2 = glm::mat4(modelMatrixVirus2);
		modelMatrixColliderVirus2 = glm::scale(modelMatrixColliderVirus2, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus2 = glm::translate(modelMatrixColliderVirus2, modelVirus.getSbb().c);
		virus2Collider.c = glm::vec3(modelMatrixColliderVirus2[3]);
		virus2Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "virus2", virus2Collider, modelMatrixVirus2);

		//Collider del Virus3
		AbstractModel::SBB Virus3Collider;
		glm::mat4 modelMatrixColliderVirus3 = glm::mat4(modelMatrixVirus3);
		modelMatrixColliderVirus3 = glm::scale(modelMatrixColliderVirus3, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus3 = glm::translate(modelMatrixColliderVirus3, modelVirus.getSbb().c);
		Virus3Collider.c = glm::vec3(modelMatrixColliderVirus3[3]);
		Virus3Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus3", Virus3Collider, modelMatrixVirus3);
		//Collider del Virus4
		AbstractModel::SBB Virus4Collider;
		glm::mat4 modelMatrixColliderVirus4 = glm::mat4(modelMatrixVirus4);
		modelMatrixColliderVirus4 = glm::scale(modelMatrixColliderVirus4, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus4 = glm::translate(modelMatrixColliderVirus4, modelVirus.getSbb().c);
		Virus4Collider.c = glm::vec3(modelMatrixColliderVirus4[3]);
		Virus4Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus4", Virus4Collider, modelMatrixVirus4);
		//Collider del Virus5
		AbstractModel::SBB Virus5Collider;
		glm::mat4 modelMatrixColliderVirus5 = glm::mat4(modelMatrixVirus5);
		modelMatrixColliderVirus5 = glm::scale(modelMatrixColliderVirus5, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus5 = glm::translate(modelMatrixColliderVirus5, modelVirus.getSbb().c);
		Virus5Collider.c = glm::vec3(modelMatrixColliderVirus5[3]);
		Virus5Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus5", Virus5Collider, modelMatrixVirus5);
		//Collider del Virus6
		AbstractModel::SBB Virus6Collider;
		glm::mat4 modelMatrixColliderVirus6 = glm::mat4(modelMatrixVirus6);
		modelMatrixColliderVirus6 = glm::scale(modelMatrixColliderVirus6, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus6 = glm::translate(modelMatrixColliderVirus6, modelVirus.getSbb().c);
		Virus6Collider.c = glm::vec3(modelMatrixColliderVirus6[3]);
		Virus6Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus6", Virus6Collider, modelMatrixVirus6);
		//Collider del Virus7
		AbstractModel::SBB Virus7Collider;
		glm::mat4 modelMatrixColliderVirus7 = glm::mat4(modelMatrixVirus7);
		modelMatrixColliderVirus7 = glm::scale(modelMatrixColliderVirus7, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus7 = glm::translate(modelMatrixColliderVirus7, modelVirus.getSbb().c);
		Virus7Collider.c = glm::vec3(modelMatrixColliderVirus7[3]);
		Virus7Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus7", Virus7Collider, modelMatrixVirus7);
		//Collider del Virus8
		AbstractModel::SBB Virus8Collider;
		glm::mat4 modelMatrixColliderVirus8 = glm::mat4(modelMatrixVirus8);
		modelMatrixColliderVirus8 = glm::scale(modelMatrixColliderVirus8, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus8 = glm::translate(modelMatrixColliderVirus8, modelVirus.getSbb().c);
		Virus8Collider.c = glm::vec3(modelMatrixColliderVirus8[3]);
		Virus8Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus8", Virus8Collider, modelMatrixVirus8);
		//Collider del Virus9
		AbstractModel::SBB Virus9Collider;
		glm::mat4 modelMatrixColliderVirus9 = glm::mat4(modelMatrixVirus9);
		modelMatrixColliderVirus9 = glm::scale(modelMatrixColliderVirus9, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus9 = glm::translate(modelMatrixColliderVirus9, modelVirus.getSbb().c);
		Virus9Collider.c = glm::vec3(modelMatrixColliderVirus9[3]);
		Virus9Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus9", Virus9Collider, modelMatrixVirus9);
		//Collider del Virus10
		AbstractModel::SBB Virus10Collider;
		glm::mat4 modelMatrixColliderVirus10 = glm::mat4(modelMatrixVirus10);
		modelMatrixColliderVirus10 = glm::scale(modelMatrixColliderVirus10, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus10 = glm::translate(modelMatrixColliderVirus10, modelVirus.getSbb().c);
		Virus10Collider.c = glm::vec3(modelMatrixColliderVirus10[3]);
		Virus10Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus10", Virus10Collider, modelMatrixVirus10);

		//Collider del Virus11
		AbstractModel::SBB Virus11Collider;
		glm::mat4 modelMatrixColliderVirus11 = glm::mat4(modelMatrixVirus11);
		modelMatrixColliderVirus11 = glm::scale(modelMatrixColliderVirus11, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus11 = glm::translate(modelMatrixColliderVirus11, modelVirus.getSbb().c);
		Virus11Collider.c = glm::vec3(modelMatrixColliderVirus11[3]);
		Virus11Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus11", Virus11Collider, modelMatrixVirus11);

		//Collider del Virus12
		AbstractModel::SBB Virus12Collider;
		glm::mat4 modelMatrixColliderVirus12 = glm::mat4(modelMatrixVirus12);
		modelMatrixColliderVirus12 = glm::scale(modelMatrixColliderVirus12, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus12 = glm::translate(modelMatrixColliderVirus12, modelVirus.getSbb().c);
		Virus12Collider.c = glm::vec3(modelMatrixColliderVirus12[3]);
		Virus12Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus12", Virus12Collider, modelMatrixVirus12);

		//Collider del Virus13
		AbstractModel::SBB Virus13Collider;
		glm::mat4 modelMatrixColliderVirus13 = glm::mat4(modelMatrixVirus13);
		modelMatrixColliderVirus13 = glm::scale(modelMatrixColliderVirus13, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus13 = glm::translate(modelMatrixColliderVirus13, modelVirus.getSbb().c);
		Virus13Collider.c = glm::vec3(modelMatrixColliderVirus13[3]);
		Virus13Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus13", Virus13Collider, modelMatrixVirus13);
		//Collider del Virus14
		AbstractModel::SBB Virus14Collider;
		glm::mat4 modelMatrixColliderVirus14 = glm::mat4(modelMatrixVirus14);
		modelMatrixColliderVirus14 = glm::scale(modelMatrixColliderVirus14, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus14 = glm::translate(modelMatrixColliderVirus14, modelVirus.getSbb().c);
		Virus14Collider.c = glm::vec3(modelMatrixColliderVirus14[3]);
		Virus14Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus14", Virus14Collider, modelMatrixVirus14);
		//Collider del Virus15
		AbstractModel::SBB Virus15Collider;
		glm::mat4 modelMatrixColliderVirus15 = glm::mat4(modelMatrixVirus15);
		modelMatrixColliderVirus15 = glm::scale(modelMatrixColliderVirus15, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus15 = glm::translate(modelMatrixColliderVirus15, modelVirus.getSbb().c);
		Virus15Collider.c = glm::vec3(modelMatrixColliderVirus15[3]);
		Virus15Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus15", Virus15Collider, modelMatrixVirus15);
		//Collider del Virus16
		AbstractModel::SBB Virus16Collider;
		glm::mat4 modelMatrixColliderVirus16 = glm::mat4(modelMatrixVirus16);
		modelMatrixColliderVirus16 = glm::scale(modelMatrixColliderVirus16, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus16 = glm::translate(modelMatrixColliderVirus16, modelVirus.getSbb().c);
		Virus16Collider.c = glm::vec3(modelMatrixColliderVirus16[3]);
		Virus16Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus16", Virus16Collider, modelMatrixVirus16);
		//Collider del Virus17
		AbstractModel::SBB Virus17Collider;
		glm::mat4 modelMatrixColliderVirus17 = glm::mat4(modelMatrixVirus17);
		modelMatrixColliderVirus17 = glm::scale(modelMatrixColliderVirus17, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus17 = glm::translate(modelMatrixColliderVirus17, modelVirus.getSbb().c);
		Virus17Collider.c = glm::vec3(modelMatrixColliderVirus17[3]);
		Virus17Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus17", Virus17Collider, modelMatrixVirus17);
		//Collider del Virus18
		AbstractModel::SBB Virus18Collider;
		glm::mat4 modelMatrixColliderVirus18 = glm::mat4(modelMatrixVirus18);
		modelMatrixColliderVirus18 = glm::scale(modelMatrixColliderVirus18, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus18 = glm::translate(modelMatrixColliderVirus18, modelVirus.getSbb().c);
		Virus18Collider.c = glm::vec3(modelMatrixColliderVirus18[3]);
		Virus18Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus18", Virus18Collider, modelMatrixVirus18);
		//Collider del Virus19
		AbstractModel::SBB Virus19Collider;
		glm::mat4 modelMatrixColliderVirus19 = glm::mat4(modelMatrixVirus19);
		modelMatrixColliderVirus19 = glm::scale(modelMatrixColliderVirus19, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus19 = glm::translate(modelMatrixColliderVirus19, modelVirus.getSbb().c);
		Virus19Collider.c = glm::vec3(modelMatrixColliderVirus19[3]);
		Virus19Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus19", Virus19Collider, modelMatrixVirus19);
		//Collider del Virus20
		AbstractModel::SBB Virus20Collider;
		glm::mat4 modelMatrixColliderVirus20 = glm::mat4(modelMatrixVirus20);
		modelMatrixColliderVirus20 = glm::scale(modelMatrixColliderVirus20, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus20 = glm::translate(modelMatrixColliderVirus20, modelVirus.getSbb().c);
		Virus20Collider.c = glm::vec3(modelMatrixColliderVirus20[3]);
		Virus20Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus20", Virus20Collider, modelMatrixVirus20);
		//Collider del Virus21
		AbstractModel::SBB Virus21Collider;
		glm::mat4 modelMatrixColliderVirus21 = glm::mat4(modelMatrixVirus21);
		modelMatrixColliderVirus21 = glm::scale(modelMatrixColliderVirus21, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus21 = glm::translate(modelMatrixColliderVirus21, modelVirus.getSbb().c);
		Virus21Collider.c = glm::vec3(modelMatrixColliderVirus21[3]);
		Virus21Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus21", Virus21Collider, modelMatrixVirus21);
		//Collider del Virus22
		AbstractModel::SBB Virus22Collider;
		glm::mat4 modelMatrixColliderVirus22 = glm::mat4(modelMatrixVirus22);
		modelMatrixColliderVirus22 = glm::scale(modelMatrixColliderVirus22, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus22 = glm::translate(modelMatrixColliderVirus22, modelVirus.getSbb().c);
		Virus22Collider.c = glm::vec3(modelMatrixColliderVirus22[3]);
		Virus22Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus22", Virus22Collider, modelMatrixVirus22);
		//Collider del Virus23
		AbstractModel::SBB Virus23Collider;
		glm::mat4 modelMatrixColliderVirus23 = glm::mat4(modelMatrixVirus23);
		modelMatrixColliderVirus23 = glm::scale(modelMatrixColliderVirus23, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus23 = glm::translate(modelMatrixColliderVirus23, modelVirus.getSbb().c);
		Virus23Collider.c = glm::vec3(modelMatrixColliderVirus23[3]);
		Virus23Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus23", Virus23Collider, modelMatrixVirus23);
		//Collider del Virus24
		AbstractModel::SBB Virus24Collider;
		glm::mat4 modelMatrixColliderVirus24 = glm::mat4(modelMatrixVirus24);
		modelMatrixColliderVirus24 = glm::scale(modelMatrixColliderVirus24, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus24 = glm::translate(modelMatrixColliderVirus24, modelVirus.getSbb().c);
		Virus24Collider.c = glm::vec3(modelMatrixColliderVirus24[3]);
		Virus24Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus24", Virus24Collider, modelMatrixVirus24);
		//Collider del Virus25
		AbstractModel::SBB Virus25Collider;
		glm::mat4 modelMatrixColliderVirus25 = glm::mat4(modelMatrixVirus25);
		modelMatrixColliderVirus25 = glm::scale(modelMatrixColliderVirus25, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus25 = glm::translate(modelMatrixColliderVirus25, modelVirus.getSbb().c);
		Virus25Collider.c = glm::vec3(modelMatrixColliderVirus25[3]);
		Virus25Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus25", Virus25Collider, modelMatrixVirus25);
		//Collider del Virus26
		AbstractModel::SBB Virus26Collider;
		glm::mat4 modelMatrixColliderVirus26 = glm::mat4(modelMatrixVirus26);
		modelMatrixColliderVirus26 = glm::scale(modelMatrixColliderVirus26, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus26 = glm::translate(modelMatrixColliderVirus26, modelVirus.getSbb().c);
		Virus26Collider.c = glm::vec3(modelMatrixColliderVirus26[3]);
		Virus26Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus26", Virus26Collider, modelMatrixVirus26);
		//Collider del Virus27
		AbstractModel::SBB Virus27Collider;
		glm::mat4 modelMatrixColliderVirus27 = glm::mat4(modelMatrixVirus27);
		modelMatrixColliderVirus27 = glm::scale(modelMatrixColliderVirus27, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus27 = glm::translate(modelMatrixColliderVirus27, modelVirus.getSbb().c);
		Virus27Collider.c = glm::vec3(modelMatrixColliderVirus27[3]);
		Virus27Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus27", Virus27Collider, modelMatrixVirus27);
		//Collider del Virus28
		AbstractModel::SBB Virus28Collider;
		glm::mat4 modelMatrixColliderVirus28 = glm::mat4(modelMatrixVirus28);
		modelMatrixColliderVirus28 = glm::scale(modelMatrixColliderVirus28, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus28 = glm::translate(modelMatrixColliderVirus28, modelVirus.getSbb().c);
		Virus28Collider.c = glm::vec3(modelMatrixColliderVirus28[3]);
		Virus28Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus28", Virus28Collider, modelMatrixVirus28);
		//Collider del Virus29
		AbstractModel::SBB Virus29Collider;
		glm::mat4 modelMatrixColliderVirus29 = glm::mat4(modelMatrixVirus29);
		modelMatrixColliderVirus29 = glm::scale(modelMatrixColliderVirus29, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus29 = glm::translate(modelMatrixColliderVirus29, modelVirus.getSbb().c);
		Virus29Collider.c = glm::vec3(modelMatrixColliderVirus29[3]);
		Virus29Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus29", Virus29Collider, modelMatrixVirus29);
		//Collider del Virus30
		AbstractModel::SBB Virus30Collider;
		glm::mat4 modelMatrixColliderVirus30 = glm::mat4(modelMatrixVirus30);
		modelMatrixColliderVirus30 = glm::scale(modelMatrixColliderVirus30, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus30 = glm::translate(modelMatrixColliderVirus30, modelVirus.getSbb().c);
		Virus30Collider.c = glm::vec3(modelMatrixColliderVirus30[3]);
		Virus30Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus30", Virus30Collider, modelMatrixVirus30);
		//Collider del Virus31
		AbstractModel::SBB Virus31Collider;
		glm::mat4 modelMatrixColliderVirus31 = glm::mat4(modelMatrixVirus31);
		modelMatrixColliderVirus31 = glm::scale(modelMatrixColliderVirus31, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus31 = glm::translate(modelMatrixColliderVirus31, modelVirus.getSbb().c);
		Virus31Collider.c = glm::vec3(modelMatrixColliderVirus31[3]);
		Virus31Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus31", Virus31Collider, modelMatrixVirus31);
		//Collider del Virus32
		AbstractModel::SBB Virus32Collider;
		glm::mat4 modelMatrixColliderVirus32 = glm::mat4(modelMatrixVirus32);
		modelMatrixColliderVirus32 = glm::scale(modelMatrixColliderVirus32, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus32 = glm::translate(modelMatrixColliderVirus32, modelVirus.getSbb().c);
		Virus32Collider.c = glm::vec3(modelMatrixColliderVirus32[3]);
		Virus32Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus32", Virus32Collider, modelMatrixVirus32);
		//Collider del Virus33
		AbstractModel::SBB Virus33Collider;
		glm::mat4 modelMatrixColliderVirus33 = glm::mat4(modelMatrixVirus33);
		modelMatrixColliderVirus33 = glm::scale(modelMatrixColliderVirus33, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus33 = glm::translate(modelMatrixColliderVirus33, modelVirus.getSbb().c);
		Virus33Collider.c = glm::vec3(modelMatrixColliderVirus33[3]);
		Virus33Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus33", Virus33Collider, modelMatrixVirus33);
		//Collider del Virus34
		AbstractModel::SBB Virus34Collider;
		glm::mat4 modelMatrixColliderVirus34 = glm::mat4(modelMatrixVirus34);
		modelMatrixColliderVirus34 = glm::scale(modelMatrixColliderVirus34, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus34 = glm::translate(modelMatrixColliderVirus34, modelVirus.getSbb().c);
		Virus34Collider.c = glm::vec3(modelMatrixColliderVirus34[3]);
		Virus34Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus34", Virus34Collider, modelMatrixVirus34);
		//Collider del Virus35
		AbstractModel::SBB Virus35Collider;
		glm::mat4 modelMatrixColliderVirus35 = glm::mat4(modelMatrixVirus35);
		modelMatrixColliderVirus35 = glm::scale(modelMatrixColliderVirus35, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus35 = glm::translate(modelMatrixColliderVirus35, modelVirus.getSbb().c);
		Virus35Collider.c = glm::vec3(modelMatrixColliderVirus35[3]);
		Virus35Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus35", Virus35Collider, modelMatrixVirus35);
		//Collider del Virus36
		AbstractModel::SBB Virus36Collider;
		glm::mat4 modelMatrixColliderVirus36 = glm::mat4(modelMatrixVirus36);
		modelMatrixColliderVirus36 = glm::scale(modelMatrixColliderVirus36, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus36 = glm::translate(modelMatrixColliderVirus36, modelVirus.getSbb().c);
		Virus36Collider.c = glm::vec3(modelMatrixColliderVirus36[3]);
		Virus36Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus36", Virus36Collider, modelMatrixVirus36);
		//Collider del Virus37
		AbstractModel::SBB Virus37Collider;
		glm::mat4 modelMatrixColliderVirus37 = glm::mat4(modelMatrixVirus37);
		modelMatrixColliderVirus37 = glm::scale(modelMatrixColliderVirus37, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus37 = glm::translate(modelMatrixColliderVirus37, modelVirus.getSbb().c);
		Virus37Collider.c = glm::vec3(modelMatrixColliderVirus37[3]);
		Virus37Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus37", Virus37Collider, modelMatrixVirus37);
		//Collider del Virus38
		AbstractModel::SBB Virus38Collider;
		glm::mat4 modelMatrixColliderVirus38 = glm::mat4(modelMatrixVirus38);
		modelMatrixColliderVirus38 = glm::scale(modelMatrixColliderVirus38, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus38 = glm::translate(modelMatrixColliderVirus38, modelVirus.getSbb().c);
		Virus38Collider.c = glm::vec3(modelMatrixColliderVirus38[3]);
		Virus38Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus38", Virus38Collider, modelMatrixVirus38);
		//Collider del Virus39
		AbstractModel::SBB Virus39Collider;
		glm::mat4 modelMatrixColliderVirus39 = glm::mat4(modelMatrixVirus39);
		modelMatrixColliderVirus39 = glm::scale(modelMatrixColliderVirus39, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus39 = glm::translate(modelMatrixColliderVirus39, modelVirus.getSbb().c);
		Virus39Collider.c = glm::vec3(modelMatrixColliderVirus39[3]);
		Virus39Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus39", Virus39Collider, modelMatrixVirus39);
		//Collider del Virus40
		AbstractModel::SBB Virus40Collider;
		glm::mat4 modelMatrixColliderVirus40 = glm::mat4(modelMatrixVirus40);
		modelMatrixColliderVirus40 = glm::scale(modelMatrixColliderVirus40, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus40 = glm::translate(modelMatrixColliderVirus40, modelVirus.getSbb().c);
		Virus40Collider.c = glm::vec3(modelMatrixColliderVirus40[3]);
		Virus40Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus40", Virus40Collider, modelMatrixVirus40);
		//Collider del Virus41
		AbstractModel::SBB Virus41Collider;
		glm::mat4 modelMatrixColliderVirus41 = glm::mat4(modelMatrixVirus41);
		modelMatrixColliderVirus41 = glm::scale(modelMatrixColliderVirus41, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus41 = glm::translate(modelMatrixColliderVirus41, modelVirus.getSbb().c);
		Virus41Collider.c = glm::vec3(modelMatrixColliderVirus41[3]);
		Virus41Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus41", Virus41Collider, modelMatrixVirus41);
		//Collider del Virus42
		AbstractModel::SBB Virus42Collider;
		glm::mat4 modelMatrixColliderVirus42 = glm::mat4(modelMatrixVirus42);
		modelMatrixColliderVirus42 = glm::scale(modelMatrixColliderVirus42, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus42 = glm::translate(modelMatrixColliderVirus42, modelVirus.getSbb().c);
		Virus42Collider.c = glm::vec3(modelMatrixColliderVirus42[3]);
		Virus42Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus42", Virus42Collider, modelMatrixVirus42);
		//Collider del Virus43
		AbstractModel::SBB Virus43Collider;
		glm::mat4 modelMatrixColliderVirus43 = glm::mat4(modelMatrixVirus43);
		modelMatrixColliderVirus43 = glm::scale(modelMatrixColliderVirus43, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus43 = glm::translate(modelMatrixColliderVirus43, modelVirus.getSbb().c);
		Virus43Collider.c = glm::vec3(modelMatrixColliderVirus43[3]);
		Virus43Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus43", Virus43Collider, modelMatrixVirus43);
		//Collider del Virus44
		AbstractModel::SBB Virus44Collider;
		glm::mat4 modelMatrixColliderVirus44 = glm::mat4(modelMatrixVirus44);
		modelMatrixColliderVirus44 = glm::scale(modelMatrixColliderVirus44, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus44 = glm::translate(modelMatrixColliderVirus44, modelVirus.getSbb().c);
		Virus44Collider.c = glm::vec3(modelMatrixColliderVirus44[3]);
		Virus44Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus44", Virus44Collider, modelMatrixVirus44);
		//Collider del Virus45
		AbstractModel::SBB Virus45Collider;
		glm::mat4 modelMatrixColliderVirus45 = glm::mat4(modelMatrixVirus45);
		modelMatrixColliderVirus45 = glm::scale(modelMatrixColliderVirus45, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus45 = glm::translate(modelMatrixColliderVirus45, modelVirus.getSbb().c);
		Virus45Collider.c = glm::vec3(modelMatrixColliderVirus45[3]);
		Virus45Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus45", Virus45Collider, modelMatrixVirus45);
		//Collider del Virus46
		AbstractModel::SBB Virus46Collider;
		glm::mat4 modelMatrixColliderVirus46 = glm::mat4(modelMatrixVirus46);
		modelMatrixColliderVirus46 = glm::scale(modelMatrixColliderVirus46, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus46 = glm::translate(modelMatrixColliderVirus46, modelVirus.getSbb().c);
		Virus46Collider.c = glm::vec3(modelMatrixColliderVirus46[3]);
		Virus46Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus46", Virus46Collider, modelMatrixVirus46);
		//Collider del Virus47
		AbstractModel::SBB Virus47Collider;
		glm::mat4 modelMatrixColliderVirus47 = glm::mat4(modelMatrixVirus47);
		modelMatrixColliderVirus47 = glm::scale(modelMatrixColliderVirus47, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus47 = glm::translate(modelMatrixColliderVirus47, modelVirus.getSbb().c);
		Virus47Collider.c = glm::vec3(modelMatrixColliderVirus47[3]);
		Virus47Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus47", Virus47Collider, modelMatrixVirus47);
		//Collider del Virus48
		AbstractModel::SBB Virus48Collider;
		glm::mat4 modelMatrixColliderVirus48 = glm::mat4(modelMatrixVirus48);
		modelMatrixColliderVirus48 = glm::scale(modelMatrixColliderVirus48, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus48 = glm::translate(modelMatrixColliderVirus48, modelVirus.getSbb().c);
		Virus48Collider.c = glm::vec3(modelMatrixColliderVirus48[3]);
		Virus48Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus48", Virus48Collider, modelMatrixVirus48);
		//Collider del Virus49
		AbstractModel::SBB Virus49Collider;
		glm::mat4 modelMatrixColliderVirus49 = glm::mat4(modelMatrixVirus49);
		modelMatrixColliderVirus49 = glm::scale(modelMatrixColliderVirus49, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus49 = glm::translate(modelMatrixColliderVirus49, modelVirus.getSbb().c);
		Virus49Collider.c = glm::vec3(modelMatrixColliderVirus49[3]);
		Virus49Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus49", Virus49Collider, modelMatrixVirus49);
		//Collider del Virus50
		AbstractModel::SBB Virus50Collider;
		glm::mat4 modelMatrixColliderVirus50 = glm::mat4(modelMatrixVirus50);
		modelMatrixColliderVirus50 = glm::scale(modelMatrixColliderVirus50, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus50 = glm::translate(modelMatrixColliderVirus50, modelVirus.getSbb().c);
		Virus50Collider.c = glm::vec3(modelMatrixColliderVirus50[3]);
		Virus50Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus50", Virus50Collider, modelMatrixVirus50);
		//Collider del Virus51
		AbstractModel::SBB Virus51Collider;
		glm::mat4 modelMatrixColliderVirus51 = glm::mat4(modelMatrixVirus51);
		modelMatrixColliderVirus51 = glm::scale(modelMatrixColliderVirus51, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus51 = glm::translate(modelMatrixColliderVirus51, modelVirus.getSbb().c);
		Virus51Collider.c = glm::vec3(modelMatrixColliderVirus51[3]);
		Virus51Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus51", Virus51Collider, modelMatrixVirus51);
		//Collider del Virus52
		AbstractModel::SBB Virus52Collider;
		glm::mat4 modelMatrixColliderVirus52 = glm::mat4(modelMatrixVirus52);
		modelMatrixColliderVirus52 = glm::scale(modelMatrixColliderVirus52, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus52 = glm::translate(modelMatrixColliderVirus52, modelVirus.getSbb().c);
		Virus52Collider.c = glm::vec3(modelMatrixColliderVirus52[3]);
		Virus52Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus52", Virus52Collider, modelMatrixVirus52);
		//Collider del Virus53
		AbstractModel::SBB Virus53Collider;
		glm::mat4 modelMatrixColliderVirus53 = glm::mat4(modelMatrixVirus53);
		modelMatrixColliderVirus53 = glm::scale(modelMatrixColliderVirus53, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus53 = glm::translate(modelMatrixColliderVirus53, modelVirus.getSbb().c);
		Virus53Collider.c = glm::vec3(modelMatrixColliderVirus53[3]);
		Virus53Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus53", Virus53Collider, modelMatrixVirus53);
		//Collider del Virus54
		AbstractModel::SBB Virus54Collider;
		glm::mat4 modelMatrixColliderVirus54 = glm::mat4(modelMatrixVirus54);
		modelMatrixColliderVirus54 = glm::scale(modelMatrixColliderVirus54, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus54 = glm::translate(modelMatrixColliderVirus54, modelVirus.getSbb().c);
		Virus54Collider.c = glm::vec3(modelMatrixColliderVirus54[3]);
		Virus54Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus54", Virus54Collider, modelMatrixVirus54);
		//Collider del Virus55
		AbstractModel::SBB Virus55Collider;
		glm::mat4 modelMatrixColliderVirus55 = glm::mat4(modelMatrixVirus55);
		modelMatrixColliderVirus55 = glm::scale(modelMatrixColliderVirus55, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus55 = glm::translate(modelMatrixColliderVirus55, modelVirus.getSbb().c);
		Virus55Collider.c = glm::vec3(modelMatrixColliderVirus55[3]);
		Virus55Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus55", Virus55Collider, modelMatrixVirus55);
		//Collider del Virus56
		AbstractModel::SBB Virus56Collider;
		glm::mat4 modelMatrixColliderVirus56 = glm::mat4(modelMatrixVirus56);
		modelMatrixColliderVirus56 = glm::scale(modelMatrixColliderVirus56, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus56 = glm::translate(modelMatrixColliderVirus56, modelVirus.getSbb().c);
		Virus56Collider.c = glm::vec3(modelMatrixColliderVirus56[3]);
		Virus56Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus56", Virus56Collider, modelMatrixVirus56);
		//Collider del Virus57
		AbstractModel::SBB Virus57Collider;
		glm::mat4 modelMatrixColliderVirus57 = glm::mat4(modelMatrixVirus57);
		modelMatrixColliderVirus57 = glm::scale(modelMatrixColliderVirus57, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus57 = glm::translate(modelMatrixColliderVirus57, modelVirus.getSbb().c);
		Virus57Collider.c = glm::vec3(modelMatrixColliderVirus57[3]);
		Virus57Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus57", Virus57Collider, modelMatrixVirus57);
		//Collider del Virus58
		AbstractModel::SBB Virus58Collider;
		glm::mat4 modelMatrixColliderVirus58 = glm::mat4(modelMatrixVirus58);
		modelMatrixColliderVirus58 = glm::scale(modelMatrixColliderVirus58, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus58 = glm::translate(modelMatrixColliderVirus58, modelVirus.getSbb().c);
		Virus58Collider.c = glm::vec3(modelMatrixColliderVirus58[3]);
		Virus58Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus58", Virus58Collider, modelMatrixVirus58);
		//Collider del Virus59
		AbstractModel::SBB Virus59Collider;
		glm::mat4 modelMatrixColliderVirus59 = glm::mat4(modelMatrixVirus59);
		modelMatrixColliderVirus59 = glm::scale(modelMatrixColliderVirus59, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus59 = glm::translate(modelMatrixColliderVirus59, modelVirus.getSbb().c);
		Virus59Collider.c = glm::vec3(modelMatrixColliderVirus59[3]);
		Virus59Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus59", Virus59Collider, modelMatrixVirus59);
		//Collider del Virus60
		AbstractModel::SBB Virus60Collider;
		glm::mat4 modelMatrixColliderVirus60 = glm::mat4(modelMatrixVirus60);
		modelMatrixColliderVirus60 = glm::scale(modelMatrixColliderVirus60, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus60 = glm::translate(modelMatrixColliderVirus60, modelVirus.getSbb().c);
		Virus60Collider.c = glm::vec3(modelMatrixColliderVirus60[3]);
		Virus60Collider.ratio = modelVirus.getSbb().ratio * 2.0;
		addOrUpdateColliders(collidersSBB, "Virus60", Virus60Collider, modelMatrixVirus60);
		//Collider del Virus61
		AbstractModel::SBB Virus61Collider;
		glm::mat4 modelMatrixColliderVirus61 = glm::mat4(modelMatrixVirus61);
		modelMatrixColliderVirus61 = glm::scale(modelMatrixColliderVirus61, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus61 = glm::translate(modelMatrixColliderVirus61, modelVirus.getSbb().c);
		Virus61Collider.c = glm::vec3(modelMatrixColliderVirus61[3]);
		Virus61Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus61", Virus61Collider, modelMatrixVirus61);
		//Collider del Virus62
		AbstractModel::SBB Virus62Collider;
		glm::mat4 modelMatrixColliderVirus62 = glm::mat4(modelMatrixVirus62);
		modelMatrixColliderVirus62 = glm::scale(modelMatrixColliderVirus62, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus62 = glm::translate(modelMatrixColliderVirus62, modelVirus.getSbb().c);
		Virus62Collider.c = glm::vec3(modelMatrixColliderVirus62[3]);
		Virus62Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus62", Virus62Collider, modelMatrixVirus62);
		//Collider del Virus63
		AbstractModel::SBB Virus63Collider;
		glm::mat4 modelMatrixColliderVirus63 = glm::mat4(modelMatrixVirus63);
		modelMatrixColliderVirus63 = glm::scale(modelMatrixColliderVirus63, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus63 = glm::translate(modelMatrixColliderVirus63, modelVirus.getSbb().c);
		Virus63Collider.c = glm::vec3(modelMatrixColliderVirus63[3]);
		Virus63Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus63", Virus63Collider, modelMatrixVirus63);
		//Collider del Virus64
		AbstractModel::SBB Virus64Collider;
		glm::mat4 modelMatrixColliderVirus64 = glm::mat4(modelMatrixVirus64);
		modelMatrixColliderVirus64 = glm::scale(modelMatrixColliderVirus64, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus64 = glm::translate(modelMatrixColliderVirus64, modelVirus.getSbb().c);
		Virus64Collider.c = glm::vec3(modelMatrixColliderVirus64[3]);
		Virus64Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus64", Virus64Collider, modelMatrixVirus64);
		//Collider del Virus65
		AbstractModel::SBB Virus65Collider;
		glm::mat4 modelMatrixColliderVirus65 = glm::mat4(modelMatrixVirus65);
		modelMatrixColliderVirus65 = glm::scale(modelMatrixColliderVirus65, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus65 = glm::translate(modelMatrixColliderVirus65, modelVirus.getSbb().c);
		Virus65Collider.c = glm::vec3(modelMatrixColliderVirus65[3]);
		Virus65Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus65", Virus65Collider, modelMatrixVirus65);
		//Collider del Virus66
		AbstractModel::SBB Virus66Collider;
		glm::mat4 modelMatrixColliderVirus66 = glm::mat4(modelMatrixVirus66);
		modelMatrixColliderVirus66 = glm::scale(modelMatrixColliderVirus66, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus66 = glm::translate(modelMatrixColliderVirus66, modelVirus.getSbb().c);
		Virus66Collider.c = glm::vec3(modelMatrixColliderVirus66[3]);
		Virus66Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus66", Virus66Collider, modelMatrixVirus66);
		//Collider del Virus67
		AbstractModel::SBB Virus67Collider;
		glm::mat4 modelMatrixColliderVirus67 = glm::mat4(modelMatrixVirus67);
		modelMatrixColliderVirus67 = glm::scale(modelMatrixColliderVirus67, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus67 = glm::translate(modelMatrixColliderVirus67, modelVirus.getSbb().c);
		Virus67Collider.c = glm::vec3(modelMatrixColliderVirus67[3]);
		Virus67Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus67", Virus67Collider, modelMatrixVirus67);
		//Collider del Virus68
		AbstractModel::SBB Virus68Collider;
		glm::mat4 modelMatrixColliderVirus68 = glm::mat4(modelMatrixVirus68);
		modelMatrixColliderVirus68 = glm::scale(modelMatrixColliderVirus68, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus68 = glm::translate(modelMatrixColliderVirus68, modelVirus.getSbb().c);
		Virus68Collider.c = glm::vec3(modelMatrixColliderVirus68[3]);
		Virus68Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus68", Virus68Collider, modelMatrixVirus68);
		//Collider del Virus69
		AbstractModel::SBB Virus69Collider;
		glm::mat4 modelMatrixColliderVirus69 = glm::mat4(modelMatrixVirus69);
		modelMatrixColliderVirus69 = glm::scale(modelMatrixColliderVirus69, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus69 = glm::translate(modelMatrixColliderVirus69, modelVirus.getSbb().c);
		Virus69Collider.c = glm::vec3(modelMatrixColliderVirus69[3]);
		Virus69Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus69", Virus69Collider, modelMatrixVirus69);
		//Collider del Virus70
		AbstractModel::SBB Virus70Collider;
		glm::mat4 modelMatrixColliderVirus70 = glm::mat4(modelMatrixVirus70);
		modelMatrixColliderVirus70 = glm::scale(modelMatrixColliderVirus70, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus70 = glm::translate(modelMatrixColliderVirus70, modelVirus.getSbb().c);
		Virus70Collider.c = glm::vec3(modelMatrixColliderVirus70[3]);
		Virus70Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus70", Virus70Collider, modelMatrixVirus70);
		//Collider del Virus71
		AbstractModel::SBB Virus71Collider;
		glm::mat4 modelMatrixColliderVirus71 = glm::mat4(modelMatrixVirus71);
		modelMatrixColliderVirus71 = glm::scale(modelMatrixColliderVirus71, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus71 = glm::translate(modelMatrixColliderVirus71, modelVirus.getSbb().c);
		Virus71Collider.c = glm::vec3(modelMatrixColliderVirus71[3]);
		Virus71Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus71", Virus71Collider, modelMatrixVirus71);
		//Collider del Virus72
		AbstractModel::SBB Virus72Collider;
		glm::mat4 modelMatrixColliderVirus72 = glm::mat4(modelMatrixVirus72);
		modelMatrixColliderVirus72 = glm::scale(modelMatrixColliderVirus72, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus72 = glm::translate(modelMatrixColliderVirus72, modelVirus.getSbb().c);
		Virus72Collider.c = glm::vec3(modelMatrixColliderVirus72[3]);
		Virus72Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus72", Virus72Collider, modelMatrixVirus72);
		//Collider del Virus73
		AbstractModel::SBB Virus73Collider;
		glm::mat4 modelMatrixColliderVirus73 = glm::mat4(modelMatrixVirus73);
		modelMatrixColliderVirus73 = glm::scale(modelMatrixColliderVirus73, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus73 = glm::translate(modelMatrixColliderVirus73, modelVirus.getSbb().c);
		Virus73Collider.c = glm::vec3(modelMatrixColliderVirus73[3]);
		Virus73Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus73", Virus73Collider, modelMatrixVirus73);
		//Collider del Virus74
		AbstractModel::SBB Virus74Collider;
		glm::mat4 modelMatrixColliderVirus74 = glm::mat4(modelMatrixVirus74);
		modelMatrixColliderVirus74 = glm::scale(modelMatrixColliderVirus74, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus74 = glm::translate(modelMatrixColliderVirus74, modelVirus.getSbb().c);
		Virus74Collider.c = glm::vec3(modelMatrixColliderVirus74[3]);
		Virus74Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus74", Virus74Collider, modelMatrixVirus74);
		//Collider del Virus75
		AbstractModel::SBB Virus75Collider;
		glm::mat4 modelMatrixColliderVirus75 = glm::mat4(modelMatrixVirus75);
		modelMatrixColliderVirus75 = glm::scale(modelMatrixColliderVirus75, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus75 = glm::translate(modelMatrixColliderVirus75, modelVirus.getSbb().c);
		Virus75Collider.c = glm::vec3(modelMatrixColliderVirus75[3]);
		Virus75Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus75", Virus75Collider, modelMatrixVirus75);
		//Collider del Virus76
		AbstractModel::SBB Virus76Collider;
		glm::mat4 modelMatrixColliderVirus76 = glm::mat4(modelMatrixVirus76);
		modelMatrixColliderVirus76 = glm::scale(modelMatrixColliderVirus76, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus76 = glm::translate(modelMatrixColliderVirus76, modelVirus.getSbb().c);
		Virus76Collider.c = glm::vec3(modelMatrixColliderVirus76[3]);
		Virus76Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus76", Virus76Collider, modelMatrixVirus76);
		//Collider del Virus77
		AbstractModel::SBB Virus77Collider;
		glm::mat4 modelMatrixColliderVirus77 = glm::mat4(modelMatrixVirus77);
		modelMatrixColliderVirus77 = glm::scale(modelMatrixColliderVirus77, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus77 = glm::translate(modelMatrixColliderVirus77, modelVirus.getSbb().c);
		Virus77Collider.c = glm::vec3(modelMatrixColliderVirus77[3]);
		Virus77Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus77", Virus77Collider, modelMatrixVirus77);
		//Collider del Virus78
		AbstractModel::SBB Virus78Collider;
		glm::mat4 modelMatrixColliderVirus78 = glm::mat4(modelMatrixVirus78);
		modelMatrixColliderVirus78 = glm::scale(modelMatrixColliderVirus78, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus78 = glm::translate(modelMatrixColliderVirus78, modelVirus.getSbb().c);
		Virus78Collider.c = glm::vec3(modelMatrixColliderVirus78[3]);
		Virus78Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus78", Virus78Collider, modelMatrixVirus78);
		//Collider del Virus79
		AbstractModel::SBB Virus79Collider;
		glm::mat4 modelMatrixColliderVirus79 = glm::mat4(modelMatrixVirus79);
		modelMatrixColliderVirus79 = glm::scale(modelMatrixColliderVirus79, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus79 = glm::translate(modelMatrixColliderVirus79, modelVirus.getSbb().c);
		Virus79Collider.c = glm::vec3(modelMatrixColliderVirus79[3]);
		Virus79Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus79", Virus79Collider, modelMatrixVirus79);
		//Collider del Virus80
		AbstractModel::SBB Virus80Collider;
		glm::mat4 modelMatrixColliderVirus80 = glm::mat4(modelMatrixVirus80);
		modelMatrixColliderVirus80 = glm::scale(modelMatrixColliderVirus80, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus80 = glm::translate(modelMatrixColliderVirus80, modelVirus.getSbb().c);
		Virus80Collider.c = glm::vec3(modelMatrixColliderVirus80[3]);
		Virus80Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus80", Virus80Collider, modelMatrixVirus80);
		//Collider del Virus81
		AbstractModel::SBB Virus81Collider;
		glm::mat4 modelMatrixColliderVirus81 = glm::mat4(modelMatrixVirus81);
		modelMatrixColliderVirus81 = glm::scale(modelMatrixColliderVirus81, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus81 = glm::translate(modelMatrixColliderVirus81, modelVirus.getSbb().c);
		Virus81Collider.c = glm::vec3(modelMatrixColliderVirus81[3]);
		Virus81Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus81", Virus81Collider, modelMatrixVirus81);
		//Collider del Virus82
		AbstractModel::SBB Virus82Collider;
		glm::mat4 modelMatrixColliderVirus82 = glm::mat4(modelMatrixVirus82);
		modelMatrixColliderVirus82 = glm::scale(modelMatrixColliderVirus82, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus82 = glm::translate(modelMatrixColliderVirus82, modelVirus.getSbb().c);
		Virus82Collider.c = glm::vec3(modelMatrixColliderVirus82[3]);
		Virus82Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus82", Virus82Collider, modelMatrixVirus82);
		/*//Collider del Virus83
		AbstractModel::SBB Virus83Collider;
		glm::mat4 modelMatrixColliderVirus83 = glm::mat4(modelMatrixVirus83);
		modelMatrixColliderVirus83 = glm::scale(modelMatrixColliderVirus83, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus83 = glm::translate(modelMatrixColliderVirus83, modelVirus.getSbb().c);
		Virus83Collider.c = glm::vec3(modelMatrixColliderVirus83[3]);
		Virus83Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus83", Virus83Collider, modelMatrixVirus83);
		//Collider del Virus84
		AbstractModel::SBB Virus84Collider;
		glm::mat4 modelMatrixColliderVirus84 = glm::mat4(modelMatrixVirus84);
		modelMatrixColliderVirus84 = glm::scale(modelMatrixColliderVirus84, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus84 = glm::translate(modelMatrixColliderVirus84, modelVirus.getSbb().c);
		Virus84Collider.c = glm::vec3(modelMatrixColliderVirus84[3]);
		Virus84Collider.ratio = modelVirus.getSbb().ratio * 3.0;
		addOrUpdateColliders(collidersSBB, "Virus84", Virus84Collider, modelMatrixVirus84);*/
    
		// Collider del borde1
		AbstractModel::OBB bordeCollider1;
		glm::mat4 modelmatrixColliderBorde1 = glm::mat4(modelMatrixEdi2);
		modelmatrixColliderBorde1 = glm::rotate(modelmatrixColliderBorde1,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		bordeCollider1.u = glm::quat_cast(modelmatrixColliderBorde1);
		modelmatrixColliderBorde1 = glm::scale(modelmatrixColliderBorde1, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderBorde1 = glm::translate(modelmatrixColliderBorde1,
				glm::vec3(modelEdi2.getObb().c.x + 6.0,
						modelEdi2.getObb().c.y - 38.0,
						modelEdi2.getObb().c.z + 195.0));
		bordeCollider1.e = modelEdi2.getObb().e * glm::vec3(1.1, 1.1, 0.3);
		bordeCollider1.c = glm::vec3(modelmatrixColliderBorde1[3]);
		addOrUpdateColliders(collidersOBB, "borde1", bordeCollider1, modelMatrixEdi2);

		// Collider del borde 2
		AbstractModel::OBB bordeCollider2;
		glm::mat4 modelmatrixColliderBorde2 = glm::mat4(modelMatrixEdi3);
		modelmatrixColliderBorde2 = glm::rotate(modelmatrixColliderBorde2,
				glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		bordeCollider2.u = glm::quat_cast(modelmatrixColliderBorde2);
		modelmatrixColliderBorde2 = glm::scale(modelmatrixColliderBorde2, glm::vec3(1.0, 1.0, 0.1));
		modelmatrixColliderBorde2 = glm::translate(modelmatrixColliderBorde2,
				glm::vec3(modelEdi3.getObb().c.x + 20.5, 
						modelEdi3.getObb().c.y + 143.5,
						modelEdi3.getObb().c.z + 82.0));
		bordeCollider2.e = modelEdi3.getObb().e * glm::vec3(0.5, 1.6, 0.025);
		bordeCollider2.c = glm::vec3(modelmatrixColliderBorde2[3]);
		addOrUpdateColliders(collidersOBB, "borde2", bordeCollider2, modelMatrixEdi3);

		/*******************************************
		 * Render de colliders
		 *******************************************/
		for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
			matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
			boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			boxCollider.enableWireMode();
			boxCollider.render(matrixCollider);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			glm::mat4 matrixCollider = glm::mat4(1.0);
			matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
			matrixCollider = glm::scale(matrixCollider, glm::vec3(std::get<0>(it->second).ratio * 2.0f));
			sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
			sphereCollider.enableWireMode();
			sphereCollider.render(matrixCollider);
		}

		/*******************************************
		 * Test Colisions
		 *******************************************/
		for (std::map<std::string,
				std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
				collidersOBB.begin(); it != collidersOBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
					std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt
						&& testOBBOBB(std::get<0>(it->second),
								std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
							<< jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string,
					std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt
						&& testSphereSphereIntersection(std::get<0>(it->second),
								std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
							<< jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string,
				std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
				collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			std::map<std::string,
					std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersOBB.begin();
			for (; jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second),
								std::get<0>(jt->second))) {
					std::cout << "Colision " << it->first << " with "
							<< jt->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, jt->first, isCollision);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		std::map<std::string, bool>::iterator colIt;
		for (colIt = collisionDetection.begin(); colIt != collisionDetection.end();
				colIt++) {
			std::map<std::string,
					std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it =
					collidersSBB.find(colIt->first);
			std::map<std::string,
					std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt =
					collidersOBB.find(colIt->first);
			if (it != collidersSBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersSBB, it->first);
			}
			if (jt != collidersOBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersOBB, jt->first);
				else {
					if (jt->first.compare("simi") == 0){
						if (jt->first.compare("edi1") != 0){
							printf("\n*****NO COLLISION*****\n");
							modelMatrixSimi = std::get<1>(jt->second);
						}
						else{
							modelMatrixSimi = std::get<1>(jt->second);
							stateSimi += 1;
						}
					}
					
				}
			}
		}

		// Constantes de animaciones
		animationIndex = 1;

		/*******************************************
		 * State machines
		 *******************************************/

		 // State machine para movimiento de virus

		switch (stateVirus) {

		case 1:
			modelMatrixVirus1 = glm::translate(modelMatrixVirus1, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus2 = glm::translate(modelMatrixVirus2, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus3 = glm::translate(modelMatrixVirus3, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus4 = glm::translate(modelMatrixVirus4, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus5 = glm::translate(modelMatrixVirus5, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus6 = glm::translate(modelMatrixVirus6, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus7 = glm::translate(modelMatrixVirus7, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus8 = glm::translate(modelMatrixVirus8, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus9 = glm::translate(modelMatrixVirus9, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus10 = glm::translate(modelMatrixVirus10, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus11 = glm::translate(modelMatrixVirus11, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus12 = glm::translate(modelMatrixVirus12, glm::vec3(-0.15f, 0.0f, -0.0f));
			
			modelMatrixVirus61 = glm::translate(modelMatrixVirus61, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus62 = glm::translate(modelMatrixVirus62, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus63 = glm::translate(modelMatrixVirus63, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus64 = glm::translate(modelMatrixVirus64, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus65 = glm::translate(modelMatrixVirus65, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus66 = glm::translate(modelMatrixVirus66, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus67 = glm::translate(modelMatrixVirus67, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus68 = glm::translate(modelMatrixVirus68, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus69 = glm::translate(modelMatrixVirus69, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus70 = glm::translate(modelMatrixVirus70, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus71 = glm::translate(modelMatrixVirus71, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus72 = glm::translate(modelMatrixVirus72, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus73 = glm::translate(modelMatrixVirus73, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus74 = glm::translate(modelMatrixVirus74, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus75 = glm::translate(modelMatrixVirus75, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus76 = glm::translate(modelMatrixVirus76, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus77 = glm::translate(modelMatrixVirus77, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus78 = glm::translate(modelMatrixVirus78, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus79 = glm::translate(modelMatrixVirus79, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus80 = glm::translate(modelMatrixVirus80, glm::vec3(0.45f, 0.0f, -0.0f));
			modelMatrixVirus81 = glm::translate(modelMatrixVirus81, glm::vec3(-0.45f, 0.0f, -0.0f));
			modelMatrixVirus82 = glm::translate(modelMatrixVirus82, glm::vec3(0.45f, 0.0f, -0.0f));
			//modelMatrixVirus83 = glm::translate(modelMatrixVirus83, glm::vec3(-0.45f, 0.0f, -0.0f));
			//modelMatrixVirus84 = glm::translate(modelMatrixVirus84, glm::vec3(0.45f, 0.0f, -0.0f));

			advanceCountVirus += 0.9;
			if (advanceCountVirus > maxAdvanceVirus) {
				advanceCountVirus = 0;
				stateVirus = 2;
			}
			break;

		case 2:
			modelMatrixVirus1 = glm::translate(modelMatrixVirus1, glm::vec3(-0.15f, 0.0f, 0.0f));
			modelMatrixVirus2 = glm::translate(modelMatrixVirus2, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus3 = glm::translate(modelMatrixVirus3, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus4 = glm::translate(modelMatrixVirus4, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus5 = glm::translate(modelMatrixVirus5, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus6 = glm::translate(modelMatrixVirus6, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus7 = glm::translate(modelMatrixVirus7, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus8 = glm::translate(modelMatrixVirus8, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus9 = glm::translate(modelMatrixVirus9, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus10 = glm::translate(modelMatrixVirus10, glm::vec3(0.15f, 0.0f, 0.0f));
			modelMatrixVirus11 = glm::translate(modelMatrixVirus11, glm::vec3(-0.15f, 0.0f, -0.0f));
			modelMatrixVirus12 = glm::translate(modelMatrixVirus12, glm::vec3(0.15f, 0.0f, 0.0f));
			
			modelMatrixVirus61 = glm::translate(modelMatrixVirus61, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus62 = glm::translate(modelMatrixVirus62, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus63 = glm::translate(modelMatrixVirus63, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus64 = glm::translate(modelMatrixVirus64, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus65 = glm::translate(modelMatrixVirus65, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus66 = glm::translate(modelMatrixVirus66, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus67 = glm::translate(modelMatrixVirus67, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus68 = glm::translate(modelMatrixVirus68, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus69 = glm::translate(modelMatrixVirus69, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus70 = glm::translate(modelMatrixVirus70, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus71 = glm::translate(modelMatrixVirus71, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus72 = glm::translate(modelMatrixVirus72, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus73 = glm::translate(modelMatrixVirus73, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus74 = glm::translate(modelMatrixVirus74, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus75 = glm::translate(modelMatrixVirus75, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus76 = glm::translate(modelMatrixVirus76, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus77 = glm::translate(modelMatrixVirus77, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus78 = glm::translate(modelMatrixVirus78, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus79 = glm::translate(modelMatrixVirus79, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus80 = glm::translate(modelMatrixVirus80, glm::vec3(-0.45f, 0.0f, 0.0f));
			modelMatrixVirus81 = glm::translate(modelMatrixVirus81, glm::vec3(0.45f, 0.0f, 0.0f));
			modelMatrixVirus82 = glm::translate(modelMatrixVirus82, glm::vec3(-0.45f, 0.0f, 0.0f));
			//modelMatrixVirus83 = glm::translate(modelMatrixVirus83, glm::vec3(0.45f, 0.0f, 0.0f));
			//modelMatrixVirus84 = glm::translate(modelMatrixVirus84, glm::vec3(-0.45f, 0.0f, 0.0f));
			advanceCountVirus += 0.9;
			if (advanceCountVirus > maxAdvanceVirus) {
				advanceCountVirus = 0;
				stateVirus = 1;
			}
			break;
		default:
			break;
		}

		/*****************************
		* Configuracion del texto
		******************************/
		if (stateSimi >= 0 && stateSimi < 50){
			glEnable(GL_BLEND);
				/********************
				 * Texto
				 * Coordenadas
				 * Tamaño
				 * Color (r,g,b)
				 *******************/
				modelText -> render("Vida: 100%" , -0.1, -0.9, 50, 1.0, 1.0, 0.0);
				glDisable(GL_BLEND);
		}
		else if (stateSimi >= 50 && stateSimi < 100){
			glEnable(GL_BLEND);
			modelText -> render("Vida: 75%" , -0.1, -0.9, 50, 1.0, 1.0, 0.0);
			glDisable(GL_BLEND);
		}
		else if (stateSimi >= 100 && stateSimi < 150){
			glEnable(GL_BLEND);
			modelText -> render("Vida: 50%" , -0.1, -0.9, 50, 1.0, 1.0, 0.0);
			glDisable(GL_BLEND);
		}
		else if (stateSimi >= 150 && stateSimi < 200){
			glEnable(GL_BLEND);
			modelText -> render("Vida: 25%" , -0.1, -0.9, 50, 1.0, 1.0, 0.0);
			glDisable(GL_BLEND);
		}
		else if (stateSimi >= 200 && stateSimi < 250){
			glEnable(GL_BLEND);
			modelText -> render("El Dr. Simi murio" , -0.1, -0.9, 50, 1.0, 1.0, 0.0);
			glDisable(GL_BLEND);
		}
		else{
			modelMatrixSimi = glm::translate(modelMatrixSimi, glm::vec3(13.0f, 0.05f, -5.0f));
			stateSimi = 0;
		}
		
		glfwSwapBuffers(window);

		/****************************+
		 * Open AL sound data
		 */

		// Listener for the Thris person camera
		listenerPos[0] = modelMatrixSimi[3].x;
		listenerPos[1] = modelMatrixSimi[3].y;
		listenerPos[2] = modelMatrixSimi[3].z;
		alListenerfv(AL_POSITION, listenerPos);

		glm::vec3 upModel = glm::normalize(modelMatrixSimi[1]);
		glm::vec3 frontModel = glm::normalize(modelMatrixSimi[2]);

		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;
		alListenerfv(AL_ORIENTATION, listenerOri);

		for(unsigned int i = 0; i < sourcesPlay.size(); i++){
			if(sourcesPlay[i]){
				sourcesPlay[i] = false;
				alSourcePlay(source[i]);
			}
		}
	}
}

void prepareScene() {///Si se agregan otros objetos en la escena se debe setear su shader///

	skyboxSphere.setShader(&shaderSkybox);
	terrain.setShader(&shaderTerrain);

	//Object models
	modelLamp1.setShader(&shaderMulLighting);
	modelMask.setShader(&shaderMulLighting);
	modelVaccine.setShader(&shaderMulLighting);
	modelVirus.setShader(&shaderMulLighting);

	//Edificios
	modelEdi1.setShader(&shaderMulLighting);
	modelEdi2.setShader(&shaderMulLighting);
	modelEdi3.setShader(&shaderMulLighting);
	modelEdi4.setShader(&shaderMulLighting);
	modelEdi5.setShader(&shaderMulLighting);
	modelEdi6.setShader(&shaderMulLighting);
	modelParque.setShader(&shaderMulLighting);

	//Simi
	simiModelAnimate.setShader(&shaderMulLighting);

	//Person
	personModelAnimate.setShader(&shaderMulLighting);

	//Grass
	modelGrass.setShader(&shaderMulLighting);
}

void prepareDepthScene() {///Si se agregan otros objetos en la escena se debe setear su shader///

	skyboxSphere.setShader(&shaderDepth);
	terrain.setShader(&shaderDepth);

	//Object models
	modelLamp1.setShader(&shaderDepth);
	modelMask.setShader(&shaderDepth);
	modelVaccine.setShader(&shaderDepth);
	modelVirus.setShader(&shaderDepth);

	//Edificios
	modelEdi1.setShader(&shaderDepth);
	modelEdi2.setShader(&shaderDepth);
	modelEdi3.setShader(&shaderDepth);
	modelEdi4.setShader(&shaderDepth);
	modelEdi5.setShader(&shaderDepth);
	modelEdi6.setShader(&shaderDepth);
	modelParque.setShader(&shaderDepth);

	//Simi
	simiModelAnimate.setShader(&shaderDepth);

	//Person
	personModelAnimate.setShader(&shaderDepth);

	//Grass
	modelGrass.setShader(&shaderDepth);
}

void renderScene(bool renderParticles) {
	/*******************************************
		 * Terrain Cesped
		 *******************************************/
	glm::mat4 modelCesped = glm::mat4(1.0);
	modelCesped = glm::translate(modelCesped, glm::vec3(0.0, 0.0, 0.0));
	modelCesped = glm::scale(modelCesped, glm::vec3(200.0, 0.001, 200.0));
	// Se activa la textura del background
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	shaderTerrain.setInt("backgroundTexture", 0);
	// Se activa la textura de tierra
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	shaderTerrain.setInt("rTexture", 1);
	// Se activa la textura de hierba
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	shaderTerrain.setInt("gTexture", 2);
	// Se activa la textura del camino
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	shaderTerrain.setInt("bTexture", 3);
	// Se activa la textura del blend map
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	shaderTerrain.setInt("blendMapTexture", 4);
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(40, 40)));
	terrain.render();
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
	glBindTexture(GL_TEXTURE_2D, 0);

	/*******************************************
	 * Custom objects obj
	 *******************************************/
	//Edificios
	modelMatrixEdi2[3][1] = terrain.getHeightTerrain(modelMatrixEdi2[3][0], modelMatrixEdi2[3][2]);
	modelEdi2.render(modelMatrixEdi2);
	modelMatrixEdi3[3][1] = terrain.getHeightTerrain(modelMatrixEdi3[3][0], modelMatrixEdi3[3][2]);
	modelEdi3.render(modelMatrixEdi3);
	modelMatrixEdi4[3][1] = terrain.getHeightTerrain(modelMatrixEdi4[3][0], modelMatrixEdi4[3][2]);
	modelEdi4.render(modelMatrixEdi4);
	modelMatrixEdi5[3][1] = terrain.getHeightTerrain(modelMatrixEdi5[3][0], modelMatrixEdi5[3][2]);
	modelEdi5.render(modelMatrixEdi5);
	modelMatrixEdi6[3][1] = terrain.getHeightTerrain(modelMatrixEdi6[3][0], modelMatrixEdi6[3][2]);
	modelEdi6.render(modelMatrixEdi6);
	modelMatrixParque[3][1] = terrain.getHeightTerrain(modelMatrixParque[3][0], modelMatrixParque[3][2]);
	modelParque.render(modelMatrixParque);

	// Forze to enable the unit texture to 0 always ----------------- IMPORTANT
	glActiveTexture(GL_TEXTURE0);

	// Render the lamps
	for (int i = 0; i < lamp1Position.size(); i++) {
		lamp1Position[i].y = terrain.getHeightTerrain(lamp1Position[i].x, lamp1Position[i].z);
		modelLamp1.setPosition(lamp1Position[i]);
		modelLamp1.setScale(glm::vec3(0.5, 0.5, 0.5));
		modelLamp1.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
		modelLamp1.render();
	}

	//Render Masks
	for (int i = 0; i < maskPosition.size(); i++) {
		maskPosition[i].y = terrain.getHeightTerrain(maskPosition[i].x, maskPosition[i].z);
		modelMask.setPosition(maskPosition[i]);
		modelMask.setScale(glm::vec3(20.5, 20.5, 20.5));
		modelMask.render();
	}

	// Grass
	glDisable(GL_CULL_FACE);
	glm::vec3 grassPosition = glm::vec3(-82.7f, 0.0f, 78.8f);
	grassPosition.y = terrain.getHeightTerrain(grassPosition.x, grassPosition.z);
	modelGrass.setPosition(grassPosition);
	modelGrass.render();
	glEnable(GL_CULL_FACE);

	/*******************************************
	 * Custom Anim objects obj
	 *******************************************/
	modelMatrixSimi[3][1] = -GRAVITY * tmv * tmv + 3.5 * tmv + terrain.getHeightTerrain(modelMatrixSimi[3][0], modelMatrixSimi[3][2]);
	tmv = currTime - startTimeJump;
	if (modelMatrixSimi[3][1] < terrain.getHeightTerrain(modelMatrixSimi[3][0], modelMatrixSimi[3][2])) {
		isJump = false;
		modelMatrixSimi[3][1] = terrain.getHeightTerrain(modelMatrixSimi[3][0], modelMatrixSimi[3][2]);
	}
	glm::mat4 modelMatrixSimiBody = glm::mat4(modelMatrixSimi);
	modelMatrixSimiBody = glm::scale(modelMatrixSimiBody, glm::vec3(3.5f, 3.5f, 3.5f));
	simiModelAnimate.setAnimationIndex(animationIndex);
	simiModelAnimate.render(modelMatrixSimiBody);
	simiModelAnimate.setAnimationIndex(1);

	modelMatrixPerson[3][1] = terrain.getHeightTerrain(modelMatrixPerson[3][0], modelMatrixPerson[3][2]);
	glm::mat4 modelMatrixPersonBody = glm::mat4(modelMatrixPerson);
	modelMatrixPersonBody = glm::scale(modelMatrixPersonBody, glm::vec3(0.02f, 0.02f, 0.02f));
	personModelAnimate.render(modelMatrixPersonBody);

	//Render todos los virus
	modelVirus.render(modelMatrixVirus1);

	modelVirus.render(modelMatrixVirus2);
	modelVirus.render(modelMatrixVirus3);
	modelVirus.render(modelMatrixVirus4);

	modelVirus.render(modelMatrixVirus5);
	modelVirus.render(modelMatrixVirus6);
	modelVirus.render(modelMatrixVirus7);
	modelVirus.render(modelMatrixVirus8);

	modelVirus.render(modelMatrixVirus9);
	modelVirus.render(modelMatrixVirus10);
	modelVirus.render(modelMatrixVirus11);
	modelVirus.render(modelMatrixVirus12);

	modelVirus.render(modelMatrixVirus13);
	modelVirus.render(modelMatrixVirus14);
	modelVirus.render(modelMatrixVirus15);
	modelVirus.render(modelMatrixVirus16);
	modelVirus.render(modelMatrixVirus17);
	modelVirus.render(modelMatrixVirus18);
	modelVirus.render(modelMatrixVirus19);
	modelVirus.render(modelMatrixVirus20);
	modelVirus.render(modelMatrixVirus21);
	modelVirus.render(modelMatrixVirus22);
	modelVirus.render(modelMatrixVirus23);
	modelVirus.render(modelMatrixVirus24);

	modelVirus.render(modelMatrixVirus25);
	modelVirus.render(modelMatrixVirus26);

	modelVirus.render(modelMatrixVirus27);
	modelVirus.render(modelMatrixVirus28);
	modelVirus.render(modelMatrixVirus29);
	modelVirus.render(modelMatrixVirus30);
	modelVirus.render(modelMatrixVirus31);
	modelVirus.render(modelMatrixVirus32);
	modelVirus.render(modelMatrixVirus33);
	modelVirus.render(modelMatrixVirus34);
	modelVirus.render(modelMatrixVirus35);
	modelVirus.render(modelMatrixVirus36);
	modelVirus.render(modelMatrixVirus37);
	modelVirus.render(modelMatrixVirus38);
	modelVirus.render(modelMatrixVirus39);
	modelVirus.render(modelMatrixVirus40);
	modelVirus.render(modelMatrixVirus41);
	modelVirus.render(modelMatrixVirus42);
	modelVirus.render(modelMatrixVirus43);
	modelVirus.render(modelMatrixVirus44);
	modelVirus.render(modelMatrixVirus45);
	modelVirus.render(modelMatrixVirus46);
	modelVirus.render(modelMatrixVirus47);
	modelVirus.render(modelMatrixVirus48);
	modelVirus.render(modelMatrixVirus49);
	modelVirus.render(modelMatrixVirus50);
	modelVirus.render(modelMatrixVirus51);
	modelVirus.render(modelMatrixVirus52);
	modelVirus.render(modelMatrixVirus53);
	modelVirus.render(modelMatrixVirus54);
	modelVirus.render(modelMatrixVirus55);
	modelVirus.render(modelMatrixVirus56);
	modelVirus.render(modelMatrixVirus57);
	modelVirus.render(modelMatrixVirus58);
	modelVirus.render(modelMatrixVirus59);
	modelVirus.render(modelMatrixVirus60);
	modelVirus.render(modelMatrixVirus61);
	modelVirus.render(modelMatrixVirus62);
	modelVirus.render(modelMatrixVirus63);
	modelVirus.render(modelMatrixVirus64);
	modelVirus.render(modelMatrixVirus65);
	modelVirus.render(modelMatrixVirus66);
	modelVirus.render(modelMatrixVirus67);
	modelVirus.render(modelMatrixVirus68);
	modelVirus.render(modelMatrixVirus69);
	modelVirus.render(modelMatrixVirus70);
	modelVirus.render(modelMatrixVirus71);
	modelVirus.render(modelMatrixVirus72);
	modelVirus.render(modelMatrixVirus73);
	modelVirus.render(modelMatrixVirus74);
	modelVirus.render(modelMatrixVirus75);
	modelVirus.render(modelMatrixVirus76);
	modelVirus.render(modelMatrixVirus77);
	modelVirus.render(modelMatrixVirus78);
	modelVirus.render(modelMatrixVirus79);
	modelVirus.render(modelMatrixVirus80);
	modelVirus.render(modelMatrixVirus81);
	modelVirus.render(modelMatrixVirus82);
	modelVirus.render(modelMatrixVirus83);
	modelVirus.render(modelMatrixVirus84);

	/**********
		 * Update the position with alpha objects
		 */
		 // Update farmacia
	blendingUnsorted.find("farmacia")->second = glm::vec3(modelMatrixEdi1[3]);
	blendingUnsorted.find("vacuna")->second = glm::vec3(matrixModelVaccine[3]);

	/**********
	 * Sorter with alpha objects
	 */
	std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
	std::map<std::string, glm::vec3>::iterator itblend;
	for (itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end(); itblend++) {
		float distanceFromView = glm::length(camera->getPosition() - itblend->second);
		blendingSorted[distanceFromView] = std::make_pair(itblend->first, itblend->second);
	}

	/**********
	 * Render de las transparencias
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	for (std::map<float, std::pair<std::string, glm::vec3> >::reverse_iterator it = blendingSorted.rbegin(); it != blendingSorted.rend(); it++) {
		if (it->second.first.compare("farmacia") == 0) {
			// Farmacia
			glm::mat4 modelMatrixEdi1Blend = glm::mat4(modelMatrixEdi1);
			modelMatrixEdi1Blend[3][1] = terrain.getHeightTerrain(modelMatrixEdi1Blend[3][0], modelMatrixEdi1Blend[3][2]);
			modelEdi1.render(modelMatrixEdi1Blend);
		}
		if (it->second.first.compare("vacuna") == 0) {
			glm::mat4 modelMatrixVaccineBlend = glm::mat4(matrixModelVaccine);
			modelMatrixVaccineBlend[3][1] = terrain.getHeightTerrain(modelMatrixVaccineBlend[3][0], modelMatrixVaccineBlend[3][2]);
			modelVaccine.setScale(glm::vec3(0.2, 0.2, 0.2));
			modelVaccine.render(modelMatrixVaccineBlend);

			glm::mat4 modelMatrixVaccine2Blend = glm::mat4(matrixModelVaccine2);
			modelMatrixVaccine2Blend[3][1] = terrain.getHeightTerrain(modelMatrixVaccine2Blend[3][0], modelMatrixVaccine2Blend[3][2]);
			modelVaccine.render(modelMatrixVaccine2Blend);
		}
	}
	glEnable(GL_CULL_FACE);
}

int main(int argc, char **argv) {
	init(800, 700, "ZONA DE ALTO CONTAGIO", false);
	applicationLoop();
	destroy();
	return 1;
}
