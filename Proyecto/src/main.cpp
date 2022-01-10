#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

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

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 7.0;

Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere sphereCollider(10, 10);

// Models complex instances
Model modelRock;
Model modelAircraft;
Model modelHeliChasis;
Model modelHeliHeli;
Model modelLambo;
Model modelLamboLeftDor;
Model modelLamboRightDor;
Model modelLamboFrontLeftWheel;
Model modelLamboFrontRightWheel;
Model modelLamboRearLeftWheel;
Model modelLamboRearRightWheel;
// Dart lego
Model modelDartLegoBody;
Model modelDartLegoHead;
Model modelDartLegoMask;
Model modelDartLegoLeftArm;
Model modelDartLegoRightArm;
Model modelDartLegoLeftHand;
Model modelDartLegoRightHand;
Model modelDartLegoLeftLeg;
Model modelDartLegoRightLeg;
// Lamps
Model modelLamp1;
Model modelLamp2;
Model modelLampPost2;
// Model animate instance
// Mayow
Model mayowModelAnimate;
Model modelVirus;
// Terrain model instance
Terrain terrain(-1, -1, 200, 8, "../Textures/heightmap3.png");

GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
GLuint textureTerrainBackgroundID, textureTerrainRID, textureTerrainGID, textureTerrainBID, textureTerrainBlendMapID;
GLuint skyboxTextureID;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/corona/corona_ft.tga",
		"../Textures/corona/corona_bk.tga",
		"../Textures/corona/corona_up.tga",
		"../Textures/corona/corona_dn.tga",
		"../Textures/corona/corona_rt.tga",
		"../Textures/corona/corona_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

// Model matrix definitions
glm::mat4 matrixModelRock = glm::mat4(1.0);
glm::mat4 modelMatrixHeli = glm::mat4(1.0f);
glm::mat4 modelMatrixLambo = glm::mat4(1.0);
glm::mat4 modelMatrixAircraft = glm::mat4(1.0);
glm::mat4 modelMatrixDart = glm::mat4(1.0f);
glm::mat4 modelMatrixMayow = glm::mat4(1.0f);
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
glm::mat4 modelMatrixVirus18= glm::mat4(1.0f);
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
glm::mat4 modelMatrixVirus42= glm::mat4(1.0f);
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
glm::mat4 modelMatrixVirus85 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus86 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus87 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus88 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus89 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus90 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus91 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus92 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus93 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus94 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus95 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus96 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus97 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus98 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus99 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus100 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus101 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus102 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus103 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus104 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus105 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus106 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus107 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus108 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus109 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus110 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus111 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus112 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus113 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus114 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus115 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus116 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus117 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus118 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus119 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus120 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus121 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus122 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus123 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus124 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus125 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus126 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus127 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus128 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus129 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus130 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus131 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus132 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus133 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus134 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus135 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus136 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus137 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus138 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus139 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus140 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus141 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus142 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus143 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus144 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus145 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus146 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus147 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus148 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus149 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus150 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus151 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus152 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus153 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus154 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus155 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus156 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus157 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus158 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus159 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus160 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus161 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus162 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus163 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus164 = glm::mat4(1.0f);
glm::mat4 modelMatrixVirus165 = glm::mat4(1.0f);
int animationIndex = 1;
float rotDartHead = 0.0, rotDartLeftArm = 0.0, rotDartLeftHand = 0.0, rotDartRightArm = 0.0, rotDartRightHand = 0.0, rotDartLeftLeg = 0.0, rotDartRightLeg = 0.0;
int modelSelected = 2;
bool enableCountSelected = true;

// Variables to animations keyframes
bool saveFrame = false, availableSave = true;
std::ofstream myfile;
std::string fileName = "";
bool record = false;

// Joints interpolations Dart Lego
std::vector<std::vector<float>> keyFramesDartJoints;
std::vector<std::vector<glm::mat4>> keyFramesDart;
int indexFrameDartJoints = 0;
int indexFrameDartJointsNext = 1;
float interpolationDartJoints = 0.0;
int maxNumPasosDartJoints = 20;
int numPasosDartJoints = 0;
int indexFrameDart = 0;
int indexFrameDartNext = 1;
float interpolationDart = 0.0;
int maxNumPasosDart = 200;
int numPasosDart = 0;

// Var animate helicopter
float rotHelHelY = 0.0;

// Var animate lambo dor
int stateDoor = 0;
float dorRotCount = 0.0;

// Lamps positions
std::vector<glm::vec3> lamp1Position = { glm::vec3(-7.03, 0, -19.14), glm::vec3(
		24.41, 0, -34.57), glm::vec3(-10.15, 0, -54.10) };
std::vector<float> lamp1Orientation = { -17.0, -82.67, 23.70 };
std::vector<glm::vec3> lamp2Position = { glm::vec3(-36.52, 0, -23.24),
		glm::vec3(-52.73, 0, -3.90) };
std::vector<float> lamp2Orientation = { 21.37 + 90, -65.0 + 90 };

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
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_textura_animation.vs", "../Shaders/multipleLights.fs");
	shaderTerrain.initialize("../Shaders/terrain.vs", "../Shaders/terrain.fs");

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

	modelRock.loadModel("../models/rock/rock.obj");
	modelRock.setShader(&shaderMulLighting);

	modelAircraft.loadModel("../models/Aircraft_obj/E 45 Aircraft_obj.obj");
	modelAircraft.setShader(&shaderMulLighting);

	terrain.init();
	terrain.setShader(&shaderTerrain);
	terrain.setPosition(glm::vec3(100, 0, 100));

	// Helicopter
	modelHeliChasis.loadModel("../models/Helicopter/Mi_24_chasis.obj");
	modelHeliChasis.setShader(&shaderMulLighting);
	modelHeliHeli.loadModel("../models/Helicopter/Mi_24_heli.obj");
	modelHeliHeli.setShader(&shaderMulLighting);
	// Lamborginhi
	modelLambo.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_chasis.obj");
	modelLambo.setShader(&shaderMulLighting);
	modelLamboLeftDor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_left_dor.obj");
	modelLamboLeftDor.setShader(&shaderMulLighting);
	modelLamboRightDor.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_right_dor.obj");
	modelLamboRightDor.setShader(&shaderMulLighting);
	modelLamboFrontLeftWheel.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_front_left_wheel.obj");
	modelLamboFrontLeftWheel.setShader(&shaderMulLighting);
	modelLamboFrontRightWheel.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_front_right_wheel.obj");
	modelLamboFrontRightWheel.setShader(&shaderMulLighting);
	modelLamboRearLeftWheel.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_rear_left_wheel.obj");
	modelLamboRearLeftWheel.setShader(&shaderMulLighting);
	modelLamboRearRightWheel.loadModel("../models/Lamborginhi_Aventador_OBJ/Lamborghini_Aventador_rear_right_wheel.obj");
	modelLamboRearRightWheel.setShader(&shaderMulLighting);

	// Dart Lego
	modelDartLegoBody.loadModel("../models/LegoDart/LeoDart_body.obj");
	modelDartLegoBody.setShader(&shaderMulLighting);
	modelDartLegoMask.loadModel("../models/LegoDart/LeoDart_mask.obj");
	modelDartLegoMask.setShader(&shaderMulLighting);
	modelDartLegoHead.loadModel("../models/LegoDart/LeoDart_head.obj");
	modelDartLegoHead.setShader(&shaderMulLighting);
	modelDartLegoLeftArm.loadModel("../models/LegoDart/LeoDart_left_arm.obj");
	modelDartLegoLeftArm.setShader(&shaderMulLighting);
	modelDartLegoRightArm.loadModel("../models/LegoDart/LeoDart_right_arm.obj");
	modelDartLegoRightArm.setShader(&shaderMulLighting);
	modelDartLegoLeftHand.loadModel("../models/LegoDart/LeoDart_left_hand.obj");
	modelDartLegoLeftHand.setShader(&shaderMulLighting);
	modelDartLegoRightHand.loadModel("../models/LegoDart/LeoDart_right_hand.obj");
	modelDartLegoRightHand.setShader(&shaderMulLighting);
	modelDartLegoLeftLeg.loadModel("../models/LegoDart/LeoDart_left_leg.obj");
	modelDartLegoLeftLeg.setShader(&shaderMulLighting);
	modelDartLegoRightLeg.loadModel("../models/LegoDart/LeoDart_right_leg.obj");
	modelDartLegoRightLeg.setShader(&shaderMulLighting);

	//Lamp models
	modelLamp1.loadModel("../models/Street-Lamp-Black/objLamp.obj");
	modelLamp1.setShader(&shaderMulLighting);
	modelLamp2.loadModel("../models/Street_Light/Lamp.obj");
	modelLamp2.setShader(&shaderMulLighting);
	modelLampPost2.loadModel("../models/Street_Light/LampPost.obj");
	modelLampPost2.setShader(&shaderMulLighting);

	//Mayow
	mayowModelAnimate.loadModel("../models/mayow/personaje2.fbx");
	mayowModelAnimate.setShader(&shaderMulLighting);

	modelVirus.loadModel("../models/Virus/Sencillo.fbx");
	modelVirus.setShader(&shaderMulLighting);

	camera->setPosition(glm::vec3(0.0, 0.0, 10.0));
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
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

	// Definiendo la textura a utilizar
	Texture textureCesped("../Textures/cesped.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureCesped.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureCesped.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureCespedID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureCesped.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureWall("../Textures/whiteWall.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureWall.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureWall.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureWallID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureWallID);
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureWall.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureWindow("../Textures/ventana.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureWindow.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureWindow.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureWindowID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureWindowID);
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureWindow.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureHighway("../Textures/highway.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureHighway.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureHighway.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureHighwayID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureHighwayID);
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureHighway.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureLandingPad("../Textures/landingPad.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureLandingPad.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureLandingPad.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureLandingPadID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureLandingPadID);
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureLandingPad.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainBackground("../Textures/grassy2.png");
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBackground.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainR("../Textures/mud.png");
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainR.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainG("../Textures/grassFlowers.png");
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainG.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainB("../Textures/path.png");
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
	}
	else
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
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBlendMap.freeImage(bitmap);
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

	// Custom objects Delete
	modelAircraft.destroy();
	modelDartLegoBody.destroy();
	modelDartLegoHead.destroy();
	modelDartLegoLeftArm.destroy();
	modelDartLegoLeftHand.destroy();
	modelDartLegoLeftLeg.destroy();
	modelDartLegoMask.destroy();
	modelDartLegoRightArm.destroy();
	modelDartLegoRightHand.destroy();
	modelDartLegoRightLeg.destroy();
	modelHeliChasis.destroy();
	modelHeliHeli.destroy();
	modelLambo.destroy();
	modelLamboFrontLeftWheel.destroy();
	modelLamboFrontRightWheel.destroy();
	modelLamboLeftDor.destroy();
	modelLamboRearLeftWheel.destroy();
	modelLamboRearRightWheel.destroy();
	modelLamboRightDor.destroy();
	modelRock.destroy();
	modelLamp1.destroy();
	modelLamp2.destroy();
	modelLampPost2.destroy();
	modelVirus.destroy();
	// Custom objects animate
	mayowModelAnimate.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureWallID);
	glDeleteTextures(1, &textureWindowID);
	glDeleteTextures(1, &textureHighwayID);
	glDeleteTextures(1, &textureLandingPadID);
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

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
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

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);
	offsetX = 0;
	offsetY = 0;

	// Seleccionar modelo
	if (enableCountSelected && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		enableCountSelected = false;
		modelSelected++;
		if (modelSelected > 2)
			modelSelected = 0;
		if (modelSelected == 1)
			fileName = "../animaciones/animation_dart_joints.txt";
		if (modelSelected == 2)
			fileName = "../animaciones/animation_dart.txt";
		std::cout << "modelSelected:" << modelSelected << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		enableCountSelected = true;

	// Guardar key frames
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
		&& glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		record = true;
		if (myfile.is_open())
			myfile.close();
		myfile.open(fileName);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE
		&& glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		record = false;
		myfile.close();
		if (modelSelected == 1)
			keyFramesDartJoints = getKeyRotFrames(fileName);
		if (modelSelected == 2)
			keyFramesDart = getKeyFrames(fileName);
	}
	if (availableSave && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
		saveFrame = true;
		availableSave = false;
	}if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_RELEASE)
		availableSave = true;

	// Dart Lego model movements
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotDartHead += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rotDartHead -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotDartLeftArm += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rotDartLeftArm -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotDartRightArm += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		rotDartRightArm -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotDartLeftHand += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		rotDartLeftHand -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		rotDartRightHand += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		rotDartRightHand -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		rotDartLeftLeg += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		rotDartLeftLeg -= 0.02;
	if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotDartRightLeg += 0.02;
	else if (modelSelected == 1 && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		rotDartRightLeg -= 0.02;
	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		modelMatrixDart = glm::rotate(modelMatrixDart, 0.02f, glm::vec3(0, 1, 0));
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		modelMatrixDart = glm::rotate(modelMatrixDart, -0.02f, glm::vec3(0, 1, 0));
	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(-0.02, 0.0, 0.0));
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(0.02, 0.0, 0.0));

	if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(1.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-1.0f), glm::vec3(0, 1, 0));
		animationIndex = 0;
	}if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, 0.02));
		animationIndex = 0;
	}
	else if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(0, 0, -0.02));
		animationIndex = 0;
	}

	bool keySpaceStatus = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (!isJump && keySpaceStatus) {
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
	int stateVirus2 = 1;
	float advanceCountVirus2 = 0.0;
	int numberAdvanceVirus2 = 0;
	int maxAdvanceVirus2 = 20;
	int stateVirus3 = 1;
	float advanceCountVirus3 = 0.0;
	int numberAdvanceVirus3 = 0;
	int maxAdvanceVirus3 = 20;
	matrixModelRock = glm::translate(matrixModelRock, glm::vec3(-3.0, 0.0, 2.0));

	modelMatrixHeli = glm::translate(modelMatrixHeli, glm::vec3(5.0, 10.0, -5.0));

	modelMatrixAircraft = glm::translate(modelMatrixAircraft, glm::vec3(10.0, 2.0, -17.5));

	modelMatrixLambo = glm::translate(modelMatrixLambo, glm::vec3(23.0, 0.0, 0.0));

	modelMatrixDart = glm::translate(modelMatrixDart, glm::vec3(3.0, 0.0, 20.0));

	modelMatrixMayow = glm::translate(modelMatrixMayow, glm::vec3(43.5f, 2.5f, -42.0f));
	modelMatrixMayow = glm::rotate(modelMatrixMayow, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	//Camino 1
	modelMatrixVirus1 = glm::translate(modelMatrixVirus1, glm::vec3(-68.0f, 2.5f, 70.0f));
	modelMatrixVirus2 = glm::translate(modelMatrixVirus2, glm::vec3(-68.0f, 2.5f, 60.0f));
	modelMatrixVirus3 = glm::translate(modelMatrixVirus3, glm::vec3(-68.0f, 2.5f, 50.0f));
	modelMatrixVirus4 = glm::translate(modelMatrixVirus4, glm::vec3(-68.0f, 2.5f, 40.0f));
	modelMatrixVirus5 = glm::translate(modelMatrixVirus5, glm::vec3(-68.0f, 2.5f, 30.0f));
	modelMatrixVirus6 = glm::translate(modelMatrixVirus6, glm::vec3(-68.0f, 2.5f, 20.0f));
	modelMatrixVirus7 = glm::translate(modelMatrixVirus7, glm::vec3(-68.0f, 2.5f, 10.0f));
	modelMatrixVirus8 = glm::translate(modelMatrixVirus8, glm::vec3(-68.0f, 2.5f, 0.0f));
	modelMatrixVirus9 = glm::translate(modelMatrixVirus9, glm::vec3(-68.0f, 2.5f, -10.0f));
	modelMatrixVirus10 = glm::translate(modelMatrixVirus10, glm::vec3(-68.0f, 2.5f, -20.0f));
	modelMatrixVirus11 = glm::translate(modelMatrixVirus11, glm::vec3(-68.0f, 2.5f, -30.0f));
	modelMatrixVirus12 = glm::translate(modelMatrixVirus12, glm::vec3(-68.0f, 2.5f, -40.0f));

	//Cruze1
	//FILA1
	modelMatrixVirus13 = glm::translate(modelMatrixVirus13, glm::vec3(-75.0f, 2.5f, -50.0f));
	modelMatrixVirus14 = glm::translate(modelMatrixVirus14, glm::vec3(-70.0f, 2.5f, -50.0f));
	modelMatrixVirus15 = glm::translate(modelMatrixVirus15, glm::vec3(-65.0f, 2.5f, -50.0f));
	modelMatrixVirus16 = glm::translate(modelMatrixVirus16, glm::vec3(-60.0f, 2.5f, -50.0f));
	modelMatrixVirus17 = glm::translate(modelMatrixVirus17, glm::vec3(-55.0f, 2.5f, -50.0f));
	modelMatrixVirus18 = glm::translate(modelMatrixVirus18, glm::vec3(-50.0f, 2.5f, -50.0f));
	modelMatrixVirus19 = glm::translate(modelMatrixVirus19, glm::vec3(-45.0f, 2.5f, -50.0f));
	modelMatrixVirus20 = glm::translate(modelMatrixVirus20, glm::vec3(-40.0f, 2.5f, -50.0f));
	modelMatrixVirus21 = glm::translate(modelMatrixVirus21, glm::vec3(-35.0f, 2.5f, -50.0f));
	modelMatrixVirus22 = glm::translate(modelMatrixVirus22, glm::vec3(-30.0f, 2.5f, -50.0f));
	modelMatrixVirus23 = glm::translate(modelMatrixVirus23, glm::vec3(-25.0f, 2.5f, -50.0f));
	modelMatrixVirus24 = glm::translate(modelMatrixVirus24, glm::vec3(-20.0f, 2.5f, -50.0f));
	//FILA2
	modelMatrixVirus25 = glm::translate(modelMatrixVirus25, glm::vec3(-73.0f, 2.5f, -55.0f));
	modelMatrixVirus26 = glm::translate(modelMatrixVirus26, glm::vec3(-68.0f, 2.5f, -55.0f));
	modelMatrixVirus27 = glm::translate(modelMatrixVirus27, glm::vec3(-63.0f, 2.5f, -55.0f));
	modelMatrixVirus28 = glm::translate(modelMatrixVirus28, glm::vec3(-58.0f, 2.5f, -55.0f));
	modelMatrixVirus29 = glm::translate(modelMatrixVirus29, glm::vec3(-53.0f, 2.5f, -55.0f));
	modelMatrixVirus30 = glm::translate(modelMatrixVirus30, glm::vec3(-48.0f, 2.5f, -55.0f));
	modelMatrixVirus31 = glm::translate(modelMatrixVirus31, glm::vec3(-43.0f, 2.5f, -55.0f));
	modelMatrixVirus32 = glm::translate(modelMatrixVirus32, glm::vec3(-38.0f, 2.5f, -55.0f));
	modelMatrixVirus33 = glm::translate(modelMatrixVirus33, glm::vec3(-33.0f, 2.5f, -55.0f));
	modelMatrixVirus34 = glm::translate(modelMatrixVirus34, glm::vec3(-28.0f, 2.5f, -55.0f));
	modelMatrixVirus35 = glm::translate(modelMatrixVirus35, glm::vec3(-23.0f, 2.5f, -55.0f));
	modelMatrixVirus36 = glm::translate(modelMatrixVirus36, glm::vec3(-18.0f, 2.5f, -55.0f));
	//FILA3
	modelMatrixVirus37 = glm::translate(modelMatrixVirus37, glm::vec3(-75.0f, 2.5f, -60.0f));
	modelMatrixVirus38 = glm::translate(modelMatrixVirus38, glm::vec3(-70.0f, 2.5f, -60.0f));
	modelMatrixVirus39 = glm::translate(modelMatrixVirus39, glm::vec3(-65.0f, 2.5f, -60.0f));
	modelMatrixVirus40 = glm::translate(modelMatrixVirus40, glm::vec3(-60.0f, 2.5f, -60.0f));
	modelMatrixVirus41 = glm::translate(modelMatrixVirus41, glm::vec3(-55.0f, 2.5f, -60.0f));
	modelMatrixVirus42 = glm::translate(modelMatrixVirus42, glm::vec3(-50.0f, 2.5f, -60.0f));
	modelMatrixVirus43 = glm::translate(modelMatrixVirus43, glm::vec3(-45.0f, 2.5f, -60.0f));
	modelMatrixVirus44 = glm::translate(modelMatrixVirus44, glm::vec3(-40.0f, 2.5f, -60.0f));
	modelMatrixVirus45 = glm::translate(modelMatrixVirus45, glm::vec3(-35.0f, 2.5f, -60.0f));
	modelMatrixVirus46 = glm::translate(modelMatrixVirus46, glm::vec3(-30.0f, 2.5f, -60.0f));
	modelMatrixVirus47 = glm::translate(modelMatrixVirus47, glm::vec3(-25.0f, 2.5f, -60.0f));
	modelMatrixVirus48 = glm::translate(modelMatrixVirus48, glm::vec3(-20.0f, 2.5f, -60.0f));
	//Fila 4
	modelMatrixVirus49 = glm::translate(modelMatrixVirus49, glm::vec3(-73.0f, 2.5f, -65.0f));
	modelMatrixVirus50 = glm::translate(modelMatrixVirus50, glm::vec3(-68.0f, 2.5f, -65.0f));
	modelMatrixVirus51 = glm::translate(modelMatrixVirus51, glm::vec3(-63.0f, 2.5f, -65.0f));
	modelMatrixVirus52 = glm::translate(modelMatrixVirus52, glm::vec3(-58.0f, 2.5f, -65.0f));
	modelMatrixVirus53 = glm::translate(modelMatrixVirus53, glm::vec3(-53.0f, 2.5f, -65.0f));
	modelMatrixVirus54 = glm::translate(modelMatrixVirus54, glm::vec3(-48.0f, 2.5f, -65.0f));
	modelMatrixVirus55 = glm::translate(modelMatrixVirus55, glm::vec3(-43.0f, 2.5f, -65.0f));
	modelMatrixVirus56 = glm::translate(modelMatrixVirus56, glm::vec3(-38.0f, 2.5f, -65.0f));
	modelMatrixVirus57 = glm::translate(modelMatrixVirus57, glm::vec3(-33.0f, 2.5f, -65.0f));
	modelMatrixVirus58 = glm::translate(modelMatrixVirus58, glm::vec3(-28.0f, 2.5f, -65.0f));
	modelMatrixVirus59 = glm::translate(modelMatrixVirus59, glm::vec3(-23.0f, 2.5f, -65.0f));
	modelMatrixVirus60 = glm::translate(modelMatrixVirus60, glm::vec3(-18.0f, 2.5f, -65.0f));
	//Camino2
	modelMatrixVirus61 = glm::translate(modelMatrixVirus61, glm::vec3(-2.0f, 2.5f, -45.0f));
	modelMatrixVirus62 = glm::translate(modelMatrixVirus62, glm::vec3(-25.0f, 2.5f, -40.0f));
	modelMatrixVirus63 = glm::translate(modelMatrixVirus63, glm::vec3(-2.0f, 2.5f, -35.0f));
	modelMatrixVirus64 = glm::translate(modelMatrixVirus64, glm::vec3(-25.0f, 2.5f, -30.0f));
	modelMatrixVirus65 = glm::translate(modelMatrixVirus65, glm::vec3(-2.0f, 2.5f, -25.0f));
	modelMatrixVirus66 = glm::translate(modelMatrixVirus66, glm::vec3(-25.0f, 2.5f, -20.0f));
	modelMatrixVirus67 = glm::translate(modelMatrixVirus67, glm::vec3(-2.0f, 2.5f, -15.0f));
	modelMatrixVirus68 = glm::translate(modelMatrixVirus68, glm::vec3(-25.0f, 2.5f, -10.0f));
	modelMatrixVirus69 = glm::translate(modelMatrixVirus69, glm::vec3(-2.0f, 2.5f, -5.0f));
	modelMatrixVirus70 = glm::translate(modelMatrixVirus70, glm::vec3(-25.0f, 2.5f, 0.0f));
	modelMatrixVirus71 = glm::translate(modelMatrixVirus71, glm::vec3(-2.0f, 2.5f, 5.0f));
	modelMatrixVirus72 = glm::translate(modelMatrixVirus72, glm::vec3(-25.0f, 2.5f, 10.0f));
	modelMatrixVirus73 = glm::translate(modelMatrixVirus73, glm::vec3(-2.0f, 2.5f, 15.0f));
	modelMatrixVirus74 = glm::translate(modelMatrixVirus74, glm::vec3(-25.0f, 2.5f, 20.0f));
	modelMatrixVirus75 = glm::translate(modelMatrixVirus75, glm::vec3(-2.0f, 2.5f, 25.0f));
	modelMatrixVirus76 = glm::translate(modelMatrixVirus76, glm::vec3(-25.0f, 2.5f, 30.0f));
	modelMatrixVirus77 = glm::translate(modelMatrixVirus77, glm::vec3(-2.0f, 2.5f, 35.0f));
	modelMatrixVirus78 = glm::translate(modelMatrixVirus78, glm::vec3(-25.0f, 2.5f, 40.0f));
	modelMatrixVirus79 = glm::translate(modelMatrixVirus79, glm::vec3(-2.0f, 2.5f, 45.0f));
	modelMatrixVirus80 = glm::translate(modelMatrixVirus80, glm::vec3(-25.0f, 2.5f, 50.0f));
	modelMatrixVirus81 = glm::translate(modelMatrixVirus81, glm::vec3(-2.0f, 2.5f, 55.0f));
	modelMatrixVirus82 = glm::translate(modelMatrixVirus82, glm::vec3(-25.0f, 2.5f, 60.0f));
	//Pasillo 2
	//Bordes
	modelMatrixVirus83 = glm::translate(modelMatrixVirus83, glm::vec3(58.0f, 1.3f, 50.0f));
	modelMatrixVirus84 = glm::translate(modelMatrixVirus84, glm::vec3(58.0f, 1.3f, 64.0f));
	modelMatrixVirus85 = glm::translate(modelMatrixVirus85, glm::vec3(10.0f, 1.3f, 50.0f));
	modelMatrixVirus86 = glm::translate(modelMatrixVirus86, glm::vec3(10.0f, 1.3f, 64.0f));
	//Relleno
	modelMatrixVirus87 = glm::translate(modelMatrixVirus87, glm::vec3(52.0f, 1.3f, 58.0f));
	modelMatrixVirus88 = glm::translate(modelMatrixVirus88, glm::vec3(48.0f, 1.3f, 57.0f));
	modelMatrixVirus89 = glm::translate(modelMatrixVirus89, glm::vec3(35.0f, 1.3f, 54.0f));
	modelMatrixVirus90 = glm::translate(modelMatrixVirus90, glm::vec3(29.0f, 1.3f, 55.0f));
	modelMatrixVirus91 = glm::translate(modelMatrixVirus91, glm::vec3(27.0f, 1.3f, 53.0f));
	modelMatrixVirus92 = glm::translate(modelMatrixVirus92, glm::vec3(12.0f, 1.3f, 61.0f));
	modelMatrixVirus93 = glm::translate(modelMatrixVirus93, glm::vec3(14.0f, 1.3f, 61.0f));
	modelMatrixVirus94 = glm::translate(modelMatrixVirus94, glm::vec3(16.0f, 1.3f, 51.0f));
	modelMatrixVirus95 = glm::translate(modelMatrixVirus95, glm::vec3(17.0f, 1.3f, 56.0f));
	modelMatrixVirus96 = glm::translate(modelMatrixVirus96, glm::vec3(41.0f, 1.3f, 54.0f));
	modelMatrixVirus97 = glm::translate(modelMatrixVirus97, glm::vec3(36.0f, 1.3f, 52.0f));
	modelMatrixVirus98 = glm::translate(modelMatrixVirus98, glm::vec3(35.0f, 1.3f, 60.0f));
	modelMatrixVirus99 = glm::translate(modelMatrixVirus99, glm::vec3(14.0f, 1.3f, 59.0f));
	modelMatrixVirus100 = glm::translate(modelMatrixVirus100, glm::vec3(17.0f, 1.3f, 58.0f));
	modelMatrixVirus101 = glm::translate(modelMatrixVirus101, glm::vec3(22.0f, 1.3f, 58.0f));
	modelMatrixVirus102 = glm::translate(modelMatrixVirus102, glm::vec3(29.0f, 1.3f, 53.0f));
	modelMatrixVirus103 = glm::translate(modelMatrixVirus103, glm::vec3(27.0f, 1.3f, 54.0f));
	modelMatrixVirus104 = glm::translate(modelMatrixVirus104, glm::vec3(31.0f, 1.3f, 55.0f));
	modelMatrixVirus105 = glm::translate(modelMatrixVirus105, glm::vec3(36.0f, 1.3f, 51.0f));
	modelMatrixVirus106 = glm::translate(modelMatrixVirus106, glm::vec3(41.0f, 1.3f, 52.0f));
	modelMatrixVirus107 = glm::translate(modelMatrixVirus107, glm::vec3(50.0f, 1.3f, 63.0f));
	modelMatrixVirus108 = glm::translate(modelMatrixVirus108, glm::vec3(52.0f, 1.3f, 62.0f));
	modelMatrixVirus109 = glm::translate(modelMatrixVirus109, glm::vec3(56.0f, 1.3f, 55.0f));
	modelMatrixVirus110 = glm::translate(modelMatrixVirus110, glm::vec3(19.0f, 1.3f, 54.0f));
	modelMatrixVirus111 = glm::translate(modelMatrixVirus111, glm::vec3(25.0f, 1.3f, 58.0f));
	modelMatrixVirus112 = glm::translate(modelMatrixVirus112, glm::vec3(27.0f, 1.3f, 59.0f));
	modelMatrixVirus113 = glm::translate(modelMatrixVirus113, glm::vec3(37.0f, 1.3f, 60.0f));
	modelMatrixVirus114 = glm::translate(modelMatrixVirus114, glm::vec3(41.0f, 1.3f, 56.0f));
	modelMatrixVirus115 = glm::translate(modelMatrixVirus115, glm::vec3(18.0f, 1.3f, 64.0f));
	modelMatrixVirus116 = glm::translate(modelMatrixVirus116, glm::vec3(25.0f, 1.3f, 64.0f));
	modelMatrixVirus117 = glm::translate(modelMatrixVirus117, glm::vec3(27.0f, 1.3f, 64.0f));
	modelMatrixVirus118 = glm::translate(modelMatrixVirus118, glm::vec3(32.0f, 1.3f, 64.0f));
	modelMatrixVirus119 = glm::translate(modelMatrixVirus119, glm::vec3(35.0f, 1.3f, 64.0f));
	modelMatrixVirus120 = glm::translate(modelMatrixVirus120, glm::vec3(45.0f, 1.3f, 64.0f));
	modelMatrixVirus121 = glm::translate(modelMatrixVirus121, glm::vec3(19.0f, 1.3f, 58.0f));
	modelMatrixVirus122 = glm::translate(modelMatrixVirus122, glm::vec3(25.0f, 1.3f, 60.0f));
	modelMatrixVirus123 = glm::translate(modelMatrixVirus123, glm::vec3(28.0f, 1.3f, 54.0f));
	modelMatrixVirus124 = glm::translate(modelMatrixVirus124, glm::vec3(36.0f, 1.3f, 57.0f));
	modelMatrixVirus125 = glm::translate(modelMatrixVirus125, glm::vec3(34.0f, 1.3f, 55.0f));
	modelMatrixVirus126 = glm::translate(modelMatrixVirus126, glm::vec3(45.0f, 1.3f, 63.0f));
	modelMatrixVirus127 = glm::translate(modelMatrixVirus127, glm::vec3(47.0f, 1.3f, 61.0f));
	modelMatrixVirus128 = glm::translate(modelMatrixVirus128, glm::vec3(49.0f, 1.3f, 60.0f));
	modelMatrixVirus129 = glm::translate(modelMatrixVirus129, glm::vec3(52.0f, 1.3f, 55.0f));
	modelMatrixVirus130 = glm::translate(modelMatrixVirus130, glm::vec3(55.0f, 1.3f, 63.0f));
	//Camino 4
	modelMatrixVirus131 = glm::translate(modelMatrixVirus131, glm::vec3(59.0f, 2.5f, 45.0f));
	modelMatrixVirus132 = glm::translate(modelMatrixVirus132, glm::vec3(40.0f, 2.5f, 42.0f));
	modelMatrixVirus133 = glm::translate(modelMatrixVirus133, glm::vec3(59.0f, 2.5f, 39.0f));
	modelMatrixVirus134 = glm::translate(modelMatrixVirus134, glm::vec3(40.0f, 2.5f, 36.0f));
	modelMatrixVirus135 = glm::translate(modelMatrixVirus135, glm::vec3(59.0f, 2.5f, 33.0f));
	modelMatrixVirus136 = glm::translate(modelMatrixVirus136, glm::vec3(40.0f, 2.5f, 30.0f));
	modelMatrixVirus137 = glm::translate(modelMatrixVirus137, glm::vec3(59.0f, 2.5f, 27.0f));
	modelMatrixVirus138 = glm::translate(modelMatrixVirus138, glm::vec3(40.0f, 2.5f, 24.0f));
	modelMatrixVirus139 = glm::translate(modelMatrixVirus139, glm::vec3(59.0f, 2.5f, 21.0f));
	modelMatrixVirus140 = glm::translate(modelMatrixVirus140, glm::vec3(40.0f, 2.5f, 18.0f));
	modelMatrixVirus141 = glm::translate(modelMatrixVirus141, glm::vec3(59.0f, 2.5f, 15.0f));
	modelMatrixVirus142 = glm::translate(modelMatrixVirus142, glm::vec3(40.0f, 2.5f, 12.0f));
	modelMatrixVirus143 = glm::translate(modelMatrixVirus143, glm::vec3(59.0f, 2.5f, 9.0f));
	modelMatrixVirus144 = glm::translate(modelMatrixVirus144, glm::vec3(40.0f, 2.5f, 6.0f));
	modelMatrixVirus145 = glm::translate(modelMatrixVirus145, glm::vec3(59.0f, 2.5f, 3.0f));
	modelMatrixVirus146 = glm::translate(modelMatrixVirus146, glm::vec3(40.0f, 2.5f, 0.0f));
	modelMatrixVirus147 = glm::translate(modelMatrixVirus147, glm::vec3(59.0f, 2.5f, -3.0f));
	modelMatrixVirus148 = glm::translate(modelMatrixVirus148, glm::vec3(40.0f, 2.5f, -6.0f));
	modelMatrixVirus149 = glm::translate(modelMatrixVirus149, glm::vec3(59.0f, 2.5f, -9.0f));
	modelMatrixVirus150 = glm::translate(modelMatrixVirus150, glm::vec3(40.0f, 2.5f, -12.0f));
	modelMatrixVirus151 = glm::translate(modelMatrixVirus151, glm::vec3(59.0f, 2.5f, -15.0f));
	modelMatrixVirus152 = glm::translate(modelMatrixVirus152, glm::vec3(40.0f, 2.5f, -18.0f));
	modelMatrixVirus153 = glm::translate(modelMatrixVirus153, glm::vec3(59.0f, 2.5f, -21.0f));
	modelMatrixVirus154 = glm::translate(modelMatrixVirus154, glm::vec3(40.0f, 2.5f, -24.0f));
	modelMatrixVirus155 = glm::translate(modelMatrixVirus155, glm::vec3(59.0f, 2.5f, -27.0f));
	modelMatrixVirus156 = glm::translate(modelMatrixVirus156, glm::vec3(40.0f, 2.5f, -30.0f));
	modelMatrixVirus157 = glm::translate(modelMatrixVirus157, glm::vec3(59.0f, 2.5f, -33.0f));
	modelMatrixVirus158 = glm::translate(modelMatrixVirus158, glm::vec3(40.0f, 2.5f, -36.0f));
	modelMatrixVirus159 = glm::translate(modelMatrixVirus159, glm::vec3(59.0f, 2.5f, -39.0f));
	modelMatrixVirus160 = glm::translate(modelMatrixVirus160, glm::vec3(40.0f, 2.5f, -42.0f));
	modelMatrixVirus161 = glm::translate(modelMatrixVirus161, glm::vec3(59.0f, 2.5f, -45.0f));
	modelMatrixVirus162 = glm::translate(modelMatrixVirus162, glm::vec3(40.0f, 2.5f, -48.0f));
	modelMatrixVirus163 = glm::translate(modelMatrixVirus163, glm::vec3(59.0f, 2.5f, -51.0f));
	modelMatrixVirus164 = glm::translate(modelMatrixVirus164, glm::vec3(40.0f, 2.5f, -54.0f));
	modelMatrixVirus165 = glm::translate(modelMatrixVirus165, glm::vec3(59.0f, 2.5f, -57.0f));


	// Variables to interpolation key frames
	fileName = "../animaciones/animation_dart_joints.txt";
	keyFramesDartJoints = getKeyRotFrames(fileName);
	keyFramesDart = getKeyFrames("../animaciones/animation_dart.txt");

	lastTime = TimeManager::Instance().GetTime();

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if (currTime - lastTime < 0.016666667) {
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		std::map<std::string, bool> collisionDetection;

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		std::vector<float> matrixDartJoints;
		std::vector<glm::mat4> matrixDart;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.01f, 100.0f);

		if (modelSelected == 1) {
			axis = glm::axis(glm::quat_cast(modelMatrixDart));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixDart));
			target = modelMatrixDart[3];
		}
		else {
			axis = glm::axis(glm::quat_cast(modelMatrixMayow));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixMayow));
			target = modelMatrixMayow[3];
		}

		if (std::isnan(angleTarget))
			angleTarget = 0.0;
		if (axis.y < 0)
			angleTarget = -angleTarget;
		if (modelSelected == 1)
			angleTarget -= glm::radians(90.0f);
		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		view = camera->getViewMatrix();

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
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
			glm::value_ptr(view));

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
		glm::vec3 spotPosition = glm::vec3(modelMatrixHeli * glm::vec4(0.32437, 0.226053, 1.79149, 1.0));
		shaderMulLighting.setInt("spotLightCount", 1);
		shaderTerrain.setInt("spotLightCount", 1);
		shaderMulLighting.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.3, 0.2)));
		shaderMulLighting.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderMulLighting.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderMulLighting.setFloat("spotLights[0].constant", 1.0);
		shaderMulLighting.setFloat("spotLights[0].linear", 0.074);
		shaderMulLighting.setFloat("spotLights[0].quadratic", 0.03);
		shaderMulLighting.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderMulLighting.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.ambient", glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.diffuse", glm::value_ptr(glm::vec3(0.2, 0.3, 0.2)));
		shaderTerrain.setVectorFloat3("spotLights[0].light.specular", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("spotLights[0].position", glm::value_ptr(spotPosition));
		shaderTerrain.setVectorFloat3("spotLights[0].direction", glm::value_ptr(glm::vec3(0, -1, 0)));
		shaderTerrain.setFloat("spotLights[0].constant", 1.0);
		shaderTerrain.setFloat("spotLights[0].linear", 0.074);
		shaderTerrain.setFloat("spotLights[0].quadratic", 0.03);
		shaderTerrain.setFloat("spotLights[0].cutOff", cos(glm::radians(12.5f)));
		shaderTerrain.setFloat("spotLights[0].outerCutOff", cos(glm::radians(15.0f)));

		/*******************************************
		 * Propiedades PointLights
		 *******************************************/
		shaderMulLighting.setInt("pointLightCount", lamp1Position.size() + lamp2Orientation.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size() + lamp2Orientation.size());
		for (int i = 0; i < lamp1Position.size(); i++) {
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5, 0.5, 0.5));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0, 10.3585, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.01);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
		}
		for (int i = 0; i < lamp2Position.size(); i++) {
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp2Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0, 1.0, 1.0));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.759521, 5.00174, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.01);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
		}

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

		/*******************************************
		 * Custom Anim objects obj
		 *******************************************/
		modelMatrixMayow[3][1] = -GRAVITY * tmv * tmv + 3.5 * tmv + terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
		tmv = currTime - startTimeJump;
		if (modelMatrixMayow[3][1] < terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2])) {
			isJump = false;
			modelMatrixMayow[3][1] = terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
		}
		//modelMatrixMayow[3][1] = terrain.getHeightTerrain(modelMatrixMayow[3][0], modelMatrixMayow[3][2]);
		glm::mat4 modelMatrixMayowBody = glm::mat4(modelMatrixMayow);
		modelMatrixMayowBody = glm::scale(modelMatrixMayowBody, glm::vec3(0.021, 0.021, 0.021));
		mayowModelAnimate.setAnimationIndex(animationIndex);
		mayowModelAnimate.render(modelMatrixMayowBody);


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
		modelVirus.render(modelMatrixVirus85);
		modelVirus.render(modelMatrixVirus86);
		modelVirus.render(modelMatrixVirus87);
		modelVirus.render(modelMatrixVirus88);
		modelVirus.render(modelMatrixVirus89);
		modelVirus.render(modelMatrixVirus90);
		modelVirus.render(modelMatrixVirus91);
		modelVirus.render(modelMatrixVirus92);
		modelVirus.render(modelMatrixVirus93);
		modelVirus.render(modelMatrixVirus94);
		modelVirus.render(modelMatrixVirus95);
		modelVirus.render(modelMatrixVirus96);
		modelVirus.render(modelMatrixVirus97);
		modelVirus.render(modelMatrixVirus98);
		modelVirus.render(modelMatrixVirus99);

		modelVirus.render(modelMatrixVirus100);
		modelVirus.render(modelMatrixVirus101);
		modelVirus.render(modelMatrixVirus102);
		modelVirus.render(modelMatrixVirus103);
		modelVirus.render(modelMatrixVirus104);
		modelVirus.render(modelMatrixVirus105);
		modelVirus.render(modelMatrixVirus106);
		modelVirus.render(modelMatrixVirus107);
		modelVirus.render(modelMatrixVirus108);
		modelVirus.render(modelMatrixVirus109);


		modelVirus.render(modelMatrixVirus110);
		modelVirus.render(modelMatrixVirus111);
		modelVirus.render(modelMatrixVirus112);
		modelVirus.render(modelMatrixVirus113);
		modelVirus.render(modelMatrixVirus114);
		modelVirus.render(modelMatrixVirus115);
		modelVirus.render(modelMatrixVirus116);
		modelVirus.render(modelMatrixVirus117);
		modelVirus.render(modelMatrixVirus118);
		modelVirus.render(modelMatrixVirus119);


		modelVirus.render(modelMatrixVirus120);
		modelVirus.render(modelMatrixVirus121);
		modelVirus.render(modelMatrixVirus122);
		modelVirus.render(modelMatrixVirus123);
		modelVirus.render(modelMatrixVirus124);
		modelVirus.render(modelMatrixVirus125);
		modelVirus.render(modelMatrixVirus126);
		modelVirus.render(modelMatrixVirus127);
		modelVirus.render(modelMatrixVirus128);
		modelVirus.render(modelMatrixVirus129);

		modelVirus.render(modelMatrixVirus130);
		modelVirus.render(modelMatrixVirus131);
		modelVirus.render(modelMatrixVirus132);
		modelVirus.render(modelMatrixVirus133);
		modelVirus.render(modelMatrixVirus134);
		modelVirus.render(modelMatrixVirus135);
		modelVirus.render(modelMatrixVirus136);
		modelVirus.render(modelMatrixVirus137);
		modelVirus.render(modelMatrixVirus138);
		modelVirus.render(modelMatrixVirus139);

		modelVirus.render(modelMatrixVirus140);
		modelVirus.render(modelMatrixVirus141);
		modelVirus.render(modelMatrixVirus142);
		modelVirus.render(modelMatrixVirus143);
		modelVirus.render(modelMatrixVirus144);
		modelVirus.render(modelMatrixVirus145);
		modelVirus.render(modelMatrixVirus146);
		modelVirus.render(modelMatrixVirus147);
		modelVirus.render(modelMatrixVirus148);
		modelVirus.render(modelMatrixVirus149);

		modelVirus.render(modelMatrixVirus150);
		modelVirus.render(modelMatrixVirus151);
		modelVirus.render(modelMatrixVirus152);
		modelVirus.render(modelMatrixVirus153);
		modelVirus.render(modelMatrixVirus154);
		modelVirus.render(modelMatrixVirus155);
		modelVirus.render(modelMatrixVirus156);
		modelVirus.render(modelMatrixVirus157);
		modelVirus.render(modelMatrixVirus158);
		modelVirus.render(modelMatrixVirus159);

		modelVirus.render(modelMatrixVirus160);
		modelVirus.render(modelMatrixVirus161);
		modelVirus.render(modelMatrixVirus162);
		modelVirus.render(modelMatrixVirus163);
		modelVirus.render(modelMatrixVirus164);
		modelVirus.render(modelMatrixVirus165);
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

		/*******************************************
		 * Creacion de colliders
		 * IMPORTANT do this before interpolations
		 *******************************************/
		 // Collider del dart vader lego
		glm::mat4 modelmatrixColliderDart = glm::mat4(modelMatrixDart);
		AbstractModel::OBB dartLegoBodyCollider;
		// Set the orientation of collider before doing the scale
		dartLegoBodyCollider.u = glm::quat_cast(modelMatrixDart);
		modelmatrixColliderDart = glm::scale(modelmatrixColliderDart, glm::vec3(0.5, 0.5, 0.5));
		modelmatrixColliderDart = glm::translate(modelmatrixColliderDart,
			glm::vec3(modelDartLegoBody.getObb().c.x,
				modelDartLegoBody.getObb().c.y,
				modelDartLegoBody.getObb().c.z));
		dartLegoBodyCollider.c = glm::vec3(modelmatrixColliderDart[3]);
		dartLegoBodyCollider.e = modelDartLegoBody.getObb().e * glm::vec3(0.5, 0.5, 0.5);
		addOrUpdateColliders(collidersOBB, "dart", dartLegoBodyCollider, modelMatrixDart);

		// Collider del aricraft
		glm::mat4 modelMatrixColliderAircraft = glm::mat4(modelMatrixAircraft);
		AbstractModel::OBB aircraftCollider;
		// Set the orientation of collider before doing the scale
		aircraftCollider.u = glm::quat_cast(modelMatrixAircraft);
		modelMatrixColliderAircraft = glm::scale(modelMatrixColliderAircraft,
			glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderAircraft = glm::translate(
			modelMatrixColliderAircraft, modelAircraft.getObb().c);
		aircraftCollider.c = glm::vec3(modelMatrixColliderAircraft[3]);
		aircraftCollider.e = modelAircraft.getObb().e * glm::vec3(1.0, 1.0, 1.0);
		addOrUpdateColliders(collidersOBB, "aircraft", aircraftCollider, modelMatrixAircraft);


		//Collider del virus1
		AbstractModel::SBB virus1Collider;
		glm::mat4 modelMatrixColliderVirus1 = glm::mat4(modelMatrixVirus1);
		modelMatrixColliderVirus1 = glm::scale(modelMatrixColliderVirus1, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus1 = glm::translate(modelMatrixColliderVirus1, modelVirus.getSbb().c);
		virus1Collider.c = glm::vec3(modelMatrixColliderVirus1[3]);
		virus1Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "virus1", virus1Collider, modelMatrixVirus1);

		//Collider del virus2
		AbstractModel::SBB virus2Collider;
		glm::mat4 modelMatrixColliderVirus2 = glm::mat4(modelMatrixVirus2);
		modelMatrixColliderVirus2 = glm::scale(modelMatrixColliderVirus2, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus2 = glm::translate(modelMatrixColliderVirus2, modelVirus.getSbb().c);
		virus2Collider.c = glm::vec3(modelMatrixColliderVirus2[3]);
		virus2Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "virus2", virus2Collider, modelMatrixVirus2);

		//Collider del Virus3
		AbstractModel::SBB Virus3Collider;
		glm::mat4 modelMatrixColliderVirus3 = glm::mat4(modelMatrixVirus3);
		modelMatrixColliderVirus3 = glm::scale(modelMatrixColliderVirus3, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus3 = glm::translate(modelMatrixColliderVirus3, modelVirus.getSbb().c);
		Virus3Collider.c = glm::vec3(modelMatrixColliderVirus3[3]);
		Virus3Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus3", Virus3Collider, modelMatrixVirus3);
		//Collider del Virus4
		AbstractModel::SBB Virus4Collider;
		glm::mat4 modelMatrixColliderVirus4 = glm::mat4(modelMatrixVirus4);
		modelMatrixColliderVirus4 = glm::scale(modelMatrixColliderVirus4, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus4 = glm::translate(modelMatrixColliderVirus4, modelVirus.getSbb().c);
		Virus4Collider.c = glm::vec3(modelMatrixColliderVirus4[3]);
		Virus4Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus4", Virus4Collider, modelMatrixVirus4);
		//Collider del Virus5
		AbstractModel::SBB Virus5Collider;
		glm::mat4 modelMatrixColliderVirus5 = glm::mat4(modelMatrixVirus5);
		modelMatrixColliderVirus5 = glm::scale(modelMatrixColliderVirus5, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus5 = glm::translate(modelMatrixColliderVirus5, modelVirus.getSbb().c);
		Virus5Collider.c = glm::vec3(modelMatrixColliderVirus5[3]);
		Virus5Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus5", Virus5Collider, modelMatrixVirus5);
		//Collider del Virus6
		AbstractModel::SBB Virus6Collider;
		glm::mat4 modelMatrixColliderVirus6 = glm::mat4(modelMatrixVirus6);
		modelMatrixColliderVirus6 = glm::scale(modelMatrixColliderVirus6, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus6 = glm::translate(modelMatrixColliderVirus6, modelVirus.getSbb().c);
		Virus6Collider.c = glm::vec3(modelMatrixColliderVirus6[3]);
		Virus6Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus6", Virus6Collider, modelMatrixVirus6);
		//Collider del Virus7
		AbstractModel::SBB Virus7Collider;
		glm::mat4 modelMatrixColliderVirus7 = glm::mat4(modelMatrixVirus7);
		modelMatrixColliderVirus7 = glm::scale(modelMatrixColliderVirus7, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus7 = glm::translate(modelMatrixColliderVirus7, modelVirus.getSbb().c);
		Virus7Collider.c = glm::vec3(modelMatrixColliderVirus7[3]);
		Virus7Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus7", Virus7Collider, modelMatrixVirus7);
		//Collider del Virus8
		AbstractModel::SBB Virus8Collider;
		glm::mat4 modelMatrixColliderVirus8 = glm::mat4(modelMatrixVirus8);
		modelMatrixColliderVirus8 = glm::scale(modelMatrixColliderVirus8, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus8 = glm::translate(modelMatrixColliderVirus8, modelVirus.getSbb().c);
		Virus8Collider.c = glm::vec3(modelMatrixColliderVirus8[3]);
		Virus8Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus8", Virus8Collider, modelMatrixVirus8);
		//Collider del Virus9
		AbstractModel::SBB Virus9Collider;
		glm::mat4 modelMatrixColliderVirus9 = glm::mat4(modelMatrixVirus9);
		modelMatrixColliderVirus9 = glm::scale(modelMatrixColliderVirus9, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus9 = glm::translate(modelMatrixColliderVirus9, modelVirus.getSbb().c);
		Virus9Collider.c = glm::vec3(modelMatrixColliderVirus9[3]);
		Virus9Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus9", Virus9Collider, modelMatrixVirus9);
		//Collider del Virus10
		AbstractModel::SBB Virus10Collider;
		glm::mat4 modelMatrixColliderVirus10 = glm::mat4(modelMatrixVirus10);
		modelMatrixColliderVirus10 = glm::scale(modelMatrixColliderVirus10, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus10 = glm::translate(modelMatrixColliderVirus10, modelVirus.getSbb().c);
		Virus10Collider.c = glm::vec3(modelMatrixColliderVirus10[3]);
		Virus10Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus10", Virus10Collider, modelMatrixVirus10);
		
		//Collider del Virus11
		AbstractModel::SBB Virus11Collider;
		glm::mat4 modelMatrixColliderVirus11 = glm::mat4(modelMatrixVirus11);
		modelMatrixColliderVirus11 = glm::scale(modelMatrixColliderVirus11, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus11 = glm::translate(modelMatrixColliderVirus11, modelVirus.getSbb().c);
		Virus11Collider.c = glm::vec3(modelMatrixColliderVirus11[3]);
		Virus11Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus11", Virus11Collider, modelMatrixVirus11);
		
		//Collider del Virus12
		AbstractModel::SBB Virus12Collider;
		glm::mat4 modelMatrixColliderVirus12 = glm::mat4(modelMatrixVirus12);
		modelMatrixColliderVirus12 = glm::scale(modelMatrixColliderVirus12, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus12 = glm::translate(modelMatrixColliderVirus12, modelVirus.getSbb().c);
		Virus12Collider.c = glm::vec3(modelMatrixColliderVirus12[3]);
		Virus12Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus12", Virus12Collider, modelMatrixVirus12);

		//Collider del Virus13
		AbstractModel::SBB Virus13Collider;
		glm::mat4 modelMatrixColliderVirus13 = glm::mat4(modelMatrixVirus13);
		modelMatrixColliderVirus13 = glm::scale(modelMatrixColliderVirus13, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus13 = glm::translate(modelMatrixColliderVirus13, modelVirus.getSbb().c);
		Virus13Collider.c = glm::vec3(modelMatrixColliderVirus13[3]);
		Virus13Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus13", Virus13Collider, modelMatrixVirus13);
		//Collider del Virus1
		AbstractModel::SBB Virus14Collider;
		glm::mat4 modelMatrixColliderVirus14 = glm::mat4(modelMatrixVirus14);
		modelMatrixColliderVirus14 = glm::scale(modelMatrixColliderVirus14, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus14 = glm::translate(modelMatrixColliderVirus14, modelVirus.getSbb().c);
		Virus14Collider.c = glm::vec3(modelMatrixColliderVirus14[3]);
		Virus14Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus14", Virus14Collider, modelMatrixVirus14);
		//Collider del Virus15
		AbstractModel::SBB Virus15Collider;
		glm::mat4 modelMatrixColliderVirus15 = glm::mat4(modelMatrixVirus15);
		modelMatrixColliderVirus15 = glm::scale(modelMatrixColliderVirus15, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus15 = glm::translate(modelMatrixColliderVirus15, modelVirus.getSbb().c);
		Virus15Collider.c = glm::vec3(modelMatrixColliderVirus15[3]);
		Virus15Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus15", Virus15Collider, modelMatrixVirus15);
		//Collider del Virus16
		AbstractModel::SBB Virus16Collider;
		glm::mat4 modelMatrixColliderVirus16 = glm::mat4(modelMatrixVirus16);
		modelMatrixColliderVirus16 = glm::scale(modelMatrixColliderVirus16, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus16 = glm::translate(modelMatrixColliderVirus16, modelVirus.getSbb().c);
		Virus16Collider.c = glm::vec3(modelMatrixColliderVirus16[3]);
		Virus16Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus16", Virus16Collider, modelMatrixVirus16);
		//Collider del Virus17
		AbstractModel::SBB Virus17Collider;
		glm::mat4 modelMatrixColliderVirus17 = glm::mat4(modelMatrixVirus17);
		modelMatrixColliderVirus17 = glm::scale(modelMatrixColliderVirus17, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus17 = glm::translate(modelMatrixColliderVirus17, modelVirus.getSbb().c);
		Virus17Collider.c = glm::vec3(modelMatrixColliderVirus17[3]);
		Virus17Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus17", Virus17Collider, modelMatrixVirus17);
		//Collider del Virus18
		AbstractModel::SBB Virus18Collider;
		glm::mat4 modelMatrixColliderVirus18 = glm::mat4(modelMatrixVirus18);
		modelMatrixColliderVirus18 = glm::scale(modelMatrixColliderVirus18, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus18 = glm::translate(modelMatrixColliderVirus18, modelVirus.getSbb().c);
		Virus18Collider.c = glm::vec3(modelMatrixColliderVirus18[3]);
		Virus18Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus18", Virus18Collider, modelMatrixVirus18);
		//Collider del Virus19
		AbstractModel::SBB Virus19Collider;
		glm::mat4 modelMatrixColliderVirus19 = glm::mat4(modelMatrixVirus19);
		modelMatrixColliderVirus19 = glm::scale(modelMatrixColliderVirus19, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus19 = glm::translate(modelMatrixColliderVirus19, modelVirus.getSbb().c);
		Virus19Collider.c = glm::vec3(modelMatrixColliderVirus19[3]);
		Virus19Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus19", Virus19Collider, modelMatrixVirus19);
		//Collider del Virus20
		AbstractModel::SBB Virus20Collider;
		glm::mat4 modelMatrixColliderVirus20 = glm::mat4(modelMatrixVirus20);
		modelMatrixColliderVirus20 = glm::scale(modelMatrixColliderVirus20, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus20 = glm::translate(modelMatrixColliderVirus20, modelVirus.getSbb().c);
		Virus20Collider.c = glm::vec3(modelMatrixColliderVirus20[3]);
		Virus20Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus20", Virus20Collider, modelMatrixVirus20);
		//Collider del Virus21
		AbstractModel::SBB Virus21Collider;
		glm::mat4 modelMatrixColliderVirus21 = glm::mat4(modelMatrixVirus21);
		modelMatrixColliderVirus21 = glm::scale(modelMatrixColliderVirus21, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus21 = glm::translate(modelMatrixColliderVirus21, modelVirus.getSbb().c);
		Virus21Collider.c = glm::vec3(modelMatrixColliderVirus21[3]);
		Virus21Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus21", Virus21Collider, modelMatrixVirus21);
		//Collider del Virus22
		AbstractModel::SBB Virus22Collider;
		glm::mat4 modelMatrixColliderVirus22 = glm::mat4(modelMatrixVirus22);
		modelMatrixColliderVirus22 = glm::scale(modelMatrixColliderVirus22, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus22 = glm::translate(modelMatrixColliderVirus22, modelVirus.getSbb().c);
		Virus22Collider.c = glm::vec3(modelMatrixColliderVirus22[3]);
		Virus22Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus22", Virus22Collider, modelMatrixVirus22);
		//Collider del Virus23
		AbstractModel::SBB Virus23Collider;
		glm::mat4 modelMatrixColliderVirus23 = glm::mat4(modelMatrixVirus23);
		modelMatrixColliderVirus23 = glm::scale(modelMatrixColliderVirus23, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus23 = glm::translate(modelMatrixColliderVirus23, modelVirus.getSbb().c);
		Virus23Collider.c = glm::vec3(modelMatrixColliderVirus23[3]);
		Virus23Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus23", Virus23Collider, modelMatrixVirus23);
		//Collider del Virus24
		AbstractModel::SBB Virus24Collider;
		glm::mat4 modelMatrixColliderVirus24 = glm::mat4(modelMatrixVirus24);
		modelMatrixColliderVirus24 = glm::scale(modelMatrixColliderVirus24, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus24 = glm::translate(modelMatrixColliderVirus24, modelVirus.getSbb().c);
		Virus24Collider.c = glm::vec3(modelMatrixColliderVirus24[3]);
		Virus24Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus24", Virus24Collider, modelMatrixVirus24);
		//Collider del Virus25
		AbstractModel::SBB Virus25Collider;
		glm::mat4 modelMatrixColliderVirus25 = glm::mat4(modelMatrixVirus25);
		modelMatrixColliderVirus25 = glm::scale(modelMatrixColliderVirus25, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus25 = glm::translate(modelMatrixColliderVirus25, modelVirus.getSbb().c);
		Virus25Collider.c = glm::vec3(modelMatrixColliderVirus25[3]);
		Virus25Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus25", Virus25Collider, modelMatrixVirus25);
		//Collider del Virus26
		AbstractModel::SBB Virus26Collider;
		glm::mat4 modelMatrixColliderVirus26 = glm::mat4(modelMatrixVirus26);
		modelMatrixColliderVirus26 = glm::scale(modelMatrixColliderVirus26, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus26 = glm::translate(modelMatrixColliderVirus26, modelVirus.getSbb().c);
		Virus26Collider.c = glm::vec3(modelMatrixColliderVirus26[3]);
		Virus26Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus26", Virus26Collider, modelMatrixVirus26);
		//Collider del Virus27
		AbstractModel::SBB Virus27Collider;
		glm::mat4 modelMatrixColliderVirus27 = glm::mat4(modelMatrixVirus27);
		modelMatrixColliderVirus27 = glm::scale(modelMatrixColliderVirus27, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus27 = glm::translate(modelMatrixColliderVirus27, modelVirus.getSbb().c);
		Virus27Collider.c = glm::vec3(modelMatrixColliderVirus27[3]);
		Virus27Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus27", Virus27Collider, modelMatrixVirus27);
		//Collider del Virus28
		AbstractModel::SBB Virus28Collider;
		glm::mat4 modelMatrixColliderVirus28 = glm::mat4(modelMatrixVirus28);
		modelMatrixColliderVirus28 = glm::scale(modelMatrixColliderVirus28, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus28 = glm::translate(modelMatrixColliderVirus28, modelVirus.getSbb().c);
		Virus28Collider.c = glm::vec3(modelMatrixColliderVirus28[3]);
		Virus28Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus28", Virus28Collider, modelMatrixVirus28);
		//Collider del Virus29
		AbstractModel::SBB Virus29Collider;
		glm::mat4 modelMatrixColliderVirus29 = glm::mat4(modelMatrixVirus29);
		modelMatrixColliderVirus29 = glm::scale(modelMatrixColliderVirus29, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus29 = glm::translate(modelMatrixColliderVirus29, modelVirus.getSbb().c);
		Virus29Collider.c = glm::vec3(modelMatrixColliderVirus29[3]);
		Virus29Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus29", Virus29Collider, modelMatrixVirus29);
		//Collider del Virus30
		AbstractModel::SBB Virus30Collider;
		glm::mat4 modelMatrixColliderVirus30 = glm::mat4(modelMatrixVirus30);
		modelMatrixColliderVirus30 = glm::scale(modelMatrixColliderVirus30, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus30 = glm::translate(modelMatrixColliderVirus30, modelVirus.getSbb().c);
		Virus30Collider.c = glm::vec3(modelMatrixColliderVirus30[3]);
		Virus30Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus30", Virus30Collider, modelMatrixVirus30);
		//Collider del Virus31
		AbstractModel::SBB Virus31Collider;
		glm::mat4 modelMatrixColliderVirus31 = glm::mat4(modelMatrixVirus31);
		modelMatrixColliderVirus31 = glm::scale(modelMatrixColliderVirus31, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus31 = glm::translate(modelMatrixColliderVirus31, modelVirus.getSbb().c);
		Virus31Collider.c = glm::vec3(modelMatrixColliderVirus31[3]);
		Virus31Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus31", Virus31Collider, modelMatrixVirus31);
		//Collider del Virus32
		AbstractModel::SBB Virus32Collider;
		glm::mat4 modelMatrixColliderVirus32 = glm::mat4(modelMatrixVirus32);
		modelMatrixColliderVirus32 = glm::scale(modelMatrixColliderVirus32, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus32 = glm::translate(modelMatrixColliderVirus32, modelVirus.getSbb().c);
		Virus32Collider.c = glm::vec3(modelMatrixColliderVirus32[3]);
		Virus32Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus32", Virus32Collider, modelMatrixVirus32);
		//Collider del Virus33
		AbstractModel::SBB Virus33Collider;
		glm::mat4 modelMatrixColliderVirus33 = glm::mat4(modelMatrixVirus33);
		modelMatrixColliderVirus33 = glm::scale(modelMatrixColliderVirus33, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus33 = glm::translate(modelMatrixColliderVirus33, modelVirus.getSbb().c);
		Virus33Collider.c = glm::vec3(modelMatrixColliderVirus33[3]);
		Virus33Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus33", Virus33Collider, modelMatrixVirus33);
		//Collider del Virus34
		AbstractModel::SBB Virus34Collider;
		glm::mat4 modelMatrixColliderVirus34 = glm::mat4(modelMatrixVirus34);
		modelMatrixColliderVirus34 = glm::scale(modelMatrixColliderVirus34, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus34 = glm::translate(modelMatrixColliderVirus34, modelVirus.getSbb().c);
		Virus34Collider.c = glm::vec3(modelMatrixColliderVirus34[3]);
		Virus34Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus34", Virus34Collider, modelMatrixVirus34);
		//Collider del Virus35
		AbstractModel::SBB Virus35Collider;
		glm::mat4 modelMatrixColliderVirus35 = glm::mat4(modelMatrixVirus35);
		modelMatrixColliderVirus35 = glm::scale(modelMatrixColliderVirus35, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus35 = glm::translate(modelMatrixColliderVirus35, modelVirus.getSbb().c);
		Virus35Collider.c = glm::vec3(modelMatrixColliderVirus35[3]);
		Virus35Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus35", Virus35Collider, modelMatrixVirus35);
		//Collider del Virus36
		AbstractModel::SBB Virus36Collider;
		glm::mat4 modelMatrixColliderVirus36 = glm::mat4(modelMatrixVirus36);
		modelMatrixColliderVirus36 = glm::scale(modelMatrixColliderVirus36, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus36 = glm::translate(modelMatrixColliderVirus36, modelVirus.getSbb().c);
		Virus36Collider.c = glm::vec3(modelMatrixColliderVirus36[3]);
		Virus36Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus36", Virus36Collider, modelMatrixVirus36);
		//Collider del Virus37
		AbstractModel::SBB Virus37Collider;
		glm::mat4 modelMatrixColliderVirus37 = glm::mat4(modelMatrixVirus37);
		modelMatrixColliderVirus37 = glm::scale(modelMatrixColliderVirus37, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus37 = glm::translate(modelMatrixColliderVirus37, modelVirus.getSbb().c);
		Virus37Collider.c = glm::vec3(modelMatrixColliderVirus37[3]);
		Virus37Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus37", Virus37Collider, modelMatrixVirus37);
		//Collider del Virus38
		AbstractModel::SBB Virus38Collider;
		glm::mat4 modelMatrixColliderVirus38 = glm::mat4(modelMatrixVirus38);
		modelMatrixColliderVirus38 = glm::scale(modelMatrixColliderVirus38, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus38 = glm::translate(modelMatrixColliderVirus38, modelVirus.getSbb().c);
		Virus38Collider.c = glm::vec3(modelMatrixColliderVirus38[3]);
		Virus38Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus38", Virus38Collider, modelMatrixVirus38);
		//Collider del Virus39
		AbstractModel::SBB Virus39Collider;
		glm::mat4 modelMatrixColliderVirus39 = glm::mat4(modelMatrixVirus39);
		modelMatrixColliderVirus39 = glm::scale(modelMatrixColliderVirus39, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus39 = glm::translate(modelMatrixColliderVirus39, modelVirus.getSbb().c);
		Virus39Collider.c = glm::vec3(modelMatrixColliderVirus39[3]);
		Virus39Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus39", Virus39Collider, modelMatrixVirus39);
		//Collider del Virus40
		AbstractModel::SBB Virus40Collider;
		glm::mat4 modelMatrixColliderVirus40 = glm::mat4(modelMatrixVirus40);
		modelMatrixColliderVirus40 = glm::scale(modelMatrixColliderVirus40, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus40 = glm::translate(modelMatrixColliderVirus40, modelVirus.getSbb().c);
		Virus40Collider.c = glm::vec3(modelMatrixColliderVirus40[3]);
		Virus40Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus40", Virus40Collider, modelMatrixVirus40);
		//Collider del Virus41
		AbstractModel::SBB Virus41Collider;
		glm::mat4 modelMatrixColliderVirus41 = glm::mat4(modelMatrixVirus41);
		modelMatrixColliderVirus41 = glm::scale(modelMatrixColliderVirus41, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus41 = glm::translate(modelMatrixColliderVirus41, modelVirus.getSbb().c);
		Virus41Collider.c = glm::vec3(modelMatrixColliderVirus41[3]);
		Virus41Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus41", Virus41Collider, modelMatrixVirus41);
		//Collider del Virus42
		AbstractModel::SBB Virus42Collider;
		glm::mat4 modelMatrixColliderVirus42 = glm::mat4(modelMatrixVirus42);
		modelMatrixColliderVirus42 = glm::scale(modelMatrixColliderVirus42, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus42 = glm::translate(modelMatrixColliderVirus42, modelVirus.getSbb().c);
		Virus42Collider.c = glm::vec3(modelMatrixColliderVirus42[3]);
		Virus42Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus42", Virus42Collider, modelMatrixVirus42);
		//Collider del Virus43
		AbstractModel::SBB Virus43Collider;
		glm::mat4 modelMatrixColliderVirus43 = glm::mat4(modelMatrixVirus43);
		modelMatrixColliderVirus43 = glm::scale(modelMatrixColliderVirus43, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus43 = glm::translate(modelMatrixColliderVirus43, modelVirus.getSbb().c);
		Virus43Collider.c = glm::vec3(modelMatrixColliderVirus43[3]);
		Virus43Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus43", Virus43Collider, modelMatrixVirus43);
		//Collider del Virus44
		AbstractModel::SBB Virus44Collider;
		glm::mat4 modelMatrixColliderVirus44 = glm::mat4(modelMatrixVirus44);
		modelMatrixColliderVirus44 = glm::scale(modelMatrixColliderVirus44, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus44 = glm::translate(modelMatrixColliderVirus44, modelVirus.getSbb().c);
		Virus44Collider.c = glm::vec3(modelMatrixColliderVirus44[3]);
		Virus44Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus44", Virus44Collider, modelMatrixVirus44);
		//Collider del Virus45
		AbstractModel::SBB Virus45Collider;
		glm::mat4 modelMatrixColliderVirus45 = glm::mat4(modelMatrixVirus45);
		modelMatrixColliderVirus45 = glm::scale(modelMatrixColliderVirus45, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus45 = glm::translate(modelMatrixColliderVirus45, modelVirus.getSbb().c);
		Virus45Collider.c = glm::vec3(modelMatrixColliderVirus45[3]);
		Virus45Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus45", Virus45Collider, modelMatrixVirus45);
		//Collider del Virus46
		AbstractModel::SBB Virus46Collider;
		glm::mat4 modelMatrixColliderVirus46 = glm::mat4(modelMatrixVirus46);
		modelMatrixColliderVirus46 = glm::scale(modelMatrixColliderVirus46, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus46 = glm::translate(modelMatrixColliderVirus46, modelVirus.getSbb().c);
		Virus46Collider.c = glm::vec3(modelMatrixColliderVirus46[3]);
		Virus46Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus46", Virus46Collider, modelMatrixVirus46);
		//Collider del Virus47
		AbstractModel::SBB Virus47Collider;
		glm::mat4 modelMatrixColliderVirus47 = glm::mat4(modelMatrixVirus47);
		modelMatrixColliderVirus47 = glm::scale(modelMatrixColliderVirus47, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus47 = glm::translate(modelMatrixColliderVirus47, modelVirus.getSbb().c);
		Virus47Collider.c = glm::vec3(modelMatrixColliderVirus47[3]);
		Virus47Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus47", Virus47Collider, modelMatrixVirus47);
		//Collider del Virus48
		AbstractModel::SBB Virus48Collider;
		glm::mat4 modelMatrixColliderVirus48 = glm::mat4(modelMatrixVirus48);
		modelMatrixColliderVirus48 = glm::scale(modelMatrixColliderVirus48, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus48 = glm::translate(modelMatrixColliderVirus48, modelVirus.getSbb().c);
		Virus48Collider.c = glm::vec3(modelMatrixColliderVirus48[3]);
		Virus48Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus48", Virus48Collider, modelMatrixVirus48);
		//Collider del Virus49
		AbstractModel::SBB Virus49Collider;
		glm::mat4 modelMatrixColliderVirus49 = glm::mat4(modelMatrixVirus49);
		modelMatrixColliderVirus49 = glm::scale(modelMatrixColliderVirus49, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus49 = glm::translate(modelMatrixColliderVirus49, modelVirus.getSbb().c);
		Virus49Collider.c = glm::vec3(modelMatrixColliderVirus49[3]);
		Virus49Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus49", Virus49Collider, modelMatrixVirus49);
		//Collider del Virus50
		AbstractModel::SBB Virus50Collider;
		glm::mat4 modelMatrixColliderVirus50 = glm::mat4(modelMatrixVirus50);
		modelMatrixColliderVirus50 = glm::scale(modelMatrixColliderVirus50, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus50 = glm::translate(modelMatrixColliderVirus50, modelVirus.getSbb().c);
		Virus50Collider.c = glm::vec3(modelMatrixColliderVirus50[3]);
		Virus50Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus50", Virus50Collider, modelMatrixVirus50);
		//Collider del Virus51
		AbstractModel::SBB Virus51Collider;
		glm::mat4 modelMatrixColliderVirus51 = glm::mat4(modelMatrixVirus51);
		modelMatrixColliderVirus51 = glm::scale(modelMatrixColliderVirus51, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus51 = glm::translate(modelMatrixColliderVirus51, modelVirus.getSbb().c);
		Virus51Collider.c = glm::vec3(modelMatrixColliderVirus51[3]);
		Virus51Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus51", Virus51Collider, modelMatrixVirus51);
		//Collider del Virus52
		AbstractModel::SBB Virus52Collider;
		glm::mat4 modelMatrixColliderVirus52 = glm::mat4(modelMatrixVirus52);
		modelMatrixColliderVirus52 = glm::scale(modelMatrixColliderVirus52, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus52 = glm::translate(modelMatrixColliderVirus52, modelVirus.getSbb().c);
		Virus52Collider.c = glm::vec3(modelMatrixColliderVirus52[3]);
		Virus52Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus52", Virus52Collider, modelMatrixVirus52);
		//Collider del Virus53
		AbstractModel::SBB Virus53Collider;
		glm::mat4 modelMatrixColliderVirus53 = glm::mat4(modelMatrixVirus53);
		modelMatrixColliderVirus53 = glm::scale(modelMatrixColliderVirus53, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus53 = glm::translate(modelMatrixColliderVirus53, modelVirus.getSbb().c);
		Virus53Collider.c = glm::vec3(modelMatrixColliderVirus53[3]);
		Virus53Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus53", Virus53Collider, modelMatrixVirus53);
		//Collider del Virus54
		AbstractModel::SBB Virus54Collider;
		glm::mat4 modelMatrixColliderVirus54 = glm::mat4(modelMatrixVirus54);
		modelMatrixColliderVirus54 = glm::scale(modelMatrixColliderVirus54, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus54 = glm::translate(modelMatrixColliderVirus54, modelVirus.getSbb().c);
		Virus54Collider.c = glm::vec3(modelMatrixColliderVirus54[3]);
		Virus54Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus54", Virus54Collider, modelMatrixVirus54);
		//Collider del Virus55
		AbstractModel::SBB Virus55Collider;
		glm::mat4 modelMatrixColliderVirus55 = glm::mat4(modelMatrixVirus55);
		modelMatrixColliderVirus55 = glm::scale(modelMatrixColliderVirus55, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus55 = glm::translate(modelMatrixColliderVirus55, modelVirus.getSbb().c);
		Virus55Collider.c = glm::vec3(modelMatrixColliderVirus55[3]);
		Virus55Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus55", Virus55Collider, modelMatrixVirus55);
		//Collider del Virus56
		AbstractModel::SBB Virus56Collider;
		glm::mat4 modelMatrixColliderVirus56 = glm::mat4(modelMatrixVirus56);
		modelMatrixColliderVirus56 = glm::scale(modelMatrixColliderVirus56, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus56 = glm::translate(modelMatrixColliderVirus56, modelVirus.getSbb().c);
		Virus56Collider.c = glm::vec3(modelMatrixColliderVirus56[3]);
		Virus56Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus56", Virus56Collider, modelMatrixVirus56);
		//Collider del Virus57
		AbstractModel::SBB Virus57Collider;
		glm::mat4 modelMatrixColliderVirus57 = glm::mat4(modelMatrixVirus57);
		modelMatrixColliderVirus57 = glm::scale(modelMatrixColliderVirus57, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus57 = glm::translate(modelMatrixColliderVirus57, modelVirus.getSbb().c);
		Virus57Collider.c = glm::vec3(modelMatrixColliderVirus57[3]);
		Virus57Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus57", Virus57Collider, modelMatrixVirus57);
		//Collider del Virus58
		AbstractModel::SBB Virus58Collider;
		glm::mat4 modelMatrixColliderVirus58 = glm::mat4(modelMatrixVirus58);
		modelMatrixColliderVirus58 = glm::scale(modelMatrixColliderVirus58, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus58 = glm::translate(modelMatrixColliderVirus58, modelVirus.getSbb().c);
		Virus58Collider.c = glm::vec3(modelMatrixColliderVirus58[3]);
		Virus58Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus58", Virus58Collider, modelMatrixVirus58);
		//Collider del Virus59
		AbstractModel::SBB Virus59Collider;
		glm::mat4 modelMatrixColliderVirus59 = glm::mat4(modelMatrixVirus59);
		modelMatrixColliderVirus59 = glm::scale(modelMatrixColliderVirus59, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus59 = glm::translate(modelMatrixColliderVirus59, modelVirus.getSbb().c);
		Virus59Collider.c = glm::vec3(modelMatrixColliderVirus59[3]);
		Virus59Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus59", Virus59Collider, modelMatrixVirus59);
		//Collider del Virus60
		AbstractModel::SBB Virus60Collider;
		glm::mat4 modelMatrixColliderVirus60 = glm::mat4(modelMatrixVirus60);
		modelMatrixColliderVirus60 = glm::scale(modelMatrixColliderVirus60, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus60 = glm::translate(modelMatrixColliderVirus60, modelVirus.getSbb().c);
		Virus60Collider.c = glm::vec3(modelMatrixColliderVirus60[3]);
		Virus60Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus60", Virus60Collider, modelMatrixVirus60);
		//Collider del Virus61
		AbstractModel::SBB Virus61Collider;
		glm::mat4 modelMatrixColliderVirus61 = glm::mat4(modelMatrixVirus61);
		modelMatrixColliderVirus61 = glm::scale(modelMatrixColliderVirus61, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus61 = glm::translate(modelMatrixColliderVirus61, modelVirus.getSbb().c);
		Virus61Collider.c = glm::vec3(modelMatrixColliderVirus61[3]);
		Virus61Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus61", Virus61Collider, modelMatrixVirus61);
		//Collider del Virus62
		AbstractModel::SBB Virus62Collider;
		glm::mat4 modelMatrixColliderVirus62 = glm::mat4(modelMatrixVirus62);
		modelMatrixColliderVirus62 = glm::scale(modelMatrixColliderVirus62, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus62 = glm::translate(modelMatrixColliderVirus62, modelVirus.getSbb().c);
		Virus62Collider.c = glm::vec3(modelMatrixColliderVirus62[3]);
		Virus62Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus62", Virus62Collider, modelMatrixVirus62);
		//Collider del Virus63
		AbstractModel::SBB Virus63Collider;
		glm::mat4 modelMatrixColliderVirus63 = glm::mat4(modelMatrixVirus63);
		modelMatrixColliderVirus63 = glm::scale(modelMatrixColliderVirus63, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus63 = glm::translate(modelMatrixColliderVirus63, modelVirus.getSbb().c);
		Virus63Collider.c = glm::vec3(modelMatrixColliderVirus63[3]);
		Virus63Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus63", Virus63Collider, modelMatrixVirus63);
		//Collider del Virus64
		AbstractModel::SBB Virus64Collider;
		glm::mat4 modelMatrixColliderVirus64 = glm::mat4(modelMatrixVirus64);
		modelMatrixColliderVirus64 = glm::scale(modelMatrixColliderVirus64, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus64 = glm::translate(modelMatrixColliderVirus64, modelVirus.getSbb().c);
		Virus64Collider.c = glm::vec3(modelMatrixColliderVirus64[3]);
		Virus64Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus64", Virus64Collider, modelMatrixVirus64);
		//Collider del Virus65
		AbstractModel::SBB Virus65Collider;
		glm::mat4 modelMatrixColliderVirus65 = glm::mat4(modelMatrixVirus65);
		modelMatrixColliderVirus65 = glm::scale(modelMatrixColliderVirus65, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus65 = glm::translate(modelMatrixColliderVirus65, modelVirus.getSbb().c);
		Virus65Collider.c = glm::vec3(modelMatrixColliderVirus65[3]);
		Virus65Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus65", Virus65Collider, modelMatrixVirus65);
		//Collider del Virus66
		AbstractModel::SBB Virus66Collider;
		glm::mat4 modelMatrixColliderVirus66 = glm::mat4(modelMatrixVirus66);
		modelMatrixColliderVirus66 = glm::scale(modelMatrixColliderVirus66, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus66 = glm::translate(modelMatrixColliderVirus66, modelVirus.getSbb().c);
		Virus66Collider.c = glm::vec3(modelMatrixColliderVirus66[3]);
		Virus66Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus66", Virus66Collider, modelMatrixVirus66);
		//Collider del Virus67
		AbstractModel::SBB Virus67Collider;
		glm::mat4 modelMatrixColliderVirus67 = glm::mat4(modelMatrixVirus67);
		modelMatrixColliderVirus67 = glm::scale(modelMatrixColliderVirus67, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus67 = glm::translate(modelMatrixColliderVirus67, modelVirus.getSbb().c);
		Virus67Collider.c = glm::vec3(modelMatrixColliderVirus67[3]);
		Virus67Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus67", Virus67Collider, modelMatrixVirus67);
		//Collider del Virus68
		AbstractModel::SBB Virus68Collider;
		glm::mat4 modelMatrixColliderVirus68 = glm::mat4(modelMatrixVirus68);
		modelMatrixColliderVirus68 = glm::scale(modelMatrixColliderVirus68, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus68 = glm::translate(modelMatrixColliderVirus68, modelVirus.getSbb().c);
		Virus68Collider.c = glm::vec3(modelMatrixColliderVirus68[3]);
		Virus68Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus68", Virus68Collider, modelMatrixVirus68);
		//Collider del Virus69
		AbstractModel::SBB Virus69Collider;
		glm::mat4 modelMatrixColliderVirus69 = glm::mat4(modelMatrixVirus69);
		modelMatrixColliderVirus69 = glm::scale(modelMatrixColliderVirus69, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus69 = glm::translate(modelMatrixColliderVirus69, modelVirus.getSbb().c);
		Virus69Collider.c = glm::vec3(modelMatrixColliderVirus69[3]);
		Virus69Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus69", Virus69Collider, modelMatrixVirus69);
		//Collider del Virus70
		AbstractModel::SBB Virus70Collider;
		glm::mat4 modelMatrixColliderVirus70 = glm::mat4(modelMatrixVirus70);
		modelMatrixColliderVirus70 = glm::scale(modelMatrixColliderVirus70, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus70 = glm::translate(modelMatrixColliderVirus70, modelVirus.getSbb().c);
		Virus70Collider.c = glm::vec3(modelMatrixColliderVirus70[3]);
		Virus70Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus70", Virus70Collider, modelMatrixVirus70);
		//Collider del Virus71
		AbstractModel::SBB Virus71Collider;
		glm::mat4 modelMatrixColliderVirus71 = glm::mat4(modelMatrixVirus71);
		modelMatrixColliderVirus71 = glm::scale(modelMatrixColliderVirus71, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus71 = glm::translate(modelMatrixColliderVirus71, modelVirus.getSbb().c);
		Virus71Collider.c = glm::vec3(modelMatrixColliderVirus71[3]);
		Virus71Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus71", Virus71Collider, modelMatrixVirus71);
		//Collider del Virus72
		AbstractModel::SBB Virus72Collider;
		glm::mat4 modelMatrixColliderVirus72 = glm::mat4(modelMatrixVirus72);
		modelMatrixColliderVirus72 = glm::scale(modelMatrixColliderVirus72, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus72 = glm::translate(modelMatrixColliderVirus72, modelVirus.getSbb().c);
		Virus72Collider.c = glm::vec3(modelMatrixColliderVirus72[3]);
		Virus72Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus72", Virus72Collider, modelMatrixVirus72);
		//Collider del Virus73
		AbstractModel::SBB Virus73Collider;
		glm::mat4 modelMatrixColliderVirus73 = glm::mat4(modelMatrixVirus73);
		modelMatrixColliderVirus73 = glm::scale(modelMatrixColliderVirus73, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus73 = glm::translate(modelMatrixColliderVirus73, modelVirus.getSbb().c);
		Virus73Collider.c = glm::vec3(modelMatrixColliderVirus73[3]);
		Virus73Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus73", Virus73Collider, modelMatrixVirus73);
		//Collider del Virus74
		AbstractModel::SBB Virus74Collider;
		glm::mat4 modelMatrixColliderVirus74 = glm::mat4(modelMatrixVirus74);
		modelMatrixColliderVirus74 = glm::scale(modelMatrixColliderVirus74, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus74 = glm::translate(modelMatrixColliderVirus74, modelVirus.getSbb().c);
		Virus74Collider.c = glm::vec3(modelMatrixColliderVirus74[3]);
		Virus74Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus74", Virus74Collider, modelMatrixVirus74);
		//Collider del Virus75
		AbstractModel::SBB Virus75Collider;
		glm::mat4 modelMatrixColliderVirus75 = glm::mat4(modelMatrixVirus75);
		modelMatrixColliderVirus75 = glm::scale(modelMatrixColliderVirus75, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus75 = glm::translate(modelMatrixColliderVirus75, modelVirus.getSbb().c);
		Virus75Collider.c = glm::vec3(modelMatrixColliderVirus75[3]);
		Virus75Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus75", Virus75Collider, modelMatrixVirus75);
		//Collider del Virus76
		AbstractModel::SBB Virus76Collider;
		glm::mat4 modelMatrixColliderVirus76 = glm::mat4(modelMatrixVirus76);
		modelMatrixColliderVirus76 = glm::scale(modelMatrixColliderVirus76, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus76 = glm::translate(modelMatrixColliderVirus76, modelVirus.getSbb().c);
		Virus76Collider.c = glm::vec3(modelMatrixColliderVirus76[3]);
		Virus76Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus76", Virus76Collider, modelMatrixVirus76);
		//Collider del Virus77
		AbstractModel::SBB Virus77Collider;
		glm::mat4 modelMatrixColliderVirus77 = glm::mat4(modelMatrixVirus77);
		modelMatrixColliderVirus77 = glm::scale(modelMatrixColliderVirus77, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus77 = glm::translate(modelMatrixColliderVirus77, modelVirus.getSbb().c);
		Virus77Collider.c = glm::vec3(modelMatrixColliderVirus77[3]);
		Virus77Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus77", Virus77Collider, modelMatrixVirus77);
		//Collider del Virus78
		AbstractModel::SBB Virus78Collider;
		glm::mat4 modelMatrixColliderVirus78 = glm::mat4(modelMatrixVirus78);
		modelMatrixColliderVirus78 = glm::scale(modelMatrixColliderVirus78, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus78 = glm::translate(modelMatrixColliderVirus78, modelVirus.getSbb().c);
		Virus78Collider.c = glm::vec3(modelMatrixColliderVirus78[3]);
		Virus78Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus78", Virus78Collider, modelMatrixVirus78);
		//Collider del Virus79
		AbstractModel::SBB Virus79Collider;
		glm::mat4 modelMatrixColliderVirus79 = glm::mat4(modelMatrixVirus79);
		modelMatrixColliderVirus79 = glm::scale(modelMatrixColliderVirus79, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus79 = glm::translate(modelMatrixColliderVirus79, modelVirus.getSbb().c);
		Virus79Collider.c = glm::vec3(modelMatrixColliderVirus79[3]);
		Virus79Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus79", Virus79Collider, modelMatrixVirus79);
		//Collider del Virus80
		AbstractModel::SBB Virus80Collider;
		glm::mat4 modelMatrixColliderVirus80 = glm::mat4(modelMatrixVirus80);
		modelMatrixColliderVirus80 = glm::scale(modelMatrixColliderVirus80, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus80 = glm::translate(modelMatrixColliderVirus80, modelVirus.getSbb().c);
		Virus80Collider.c = glm::vec3(modelMatrixColliderVirus80[3]);
		Virus80Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus80", Virus80Collider, modelMatrixVirus80);
		//Collider del Virus81
		AbstractModel::SBB Virus81Collider;
		glm::mat4 modelMatrixColliderVirus81 = glm::mat4(modelMatrixVirus81);
		modelMatrixColliderVirus81 = glm::scale(modelMatrixColliderVirus81, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus81 = glm::translate(modelMatrixColliderVirus81, modelVirus.getSbb().c);
		Virus81Collider.c = glm::vec3(modelMatrixColliderVirus81[3]);
		Virus81Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus81", Virus81Collider, modelMatrixVirus81);
		//Collider del Virus82
		AbstractModel::SBB Virus82Collider;
		glm::mat4 modelMatrixColliderVirus82 = glm::mat4(modelMatrixVirus82);
		modelMatrixColliderVirus82 = glm::scale(modelMatrixColliderVirus82, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus82 = glm::translate(modelMatrixColliderVirus82, modelVirus.getSbb().c);
		Virus82Collider.c = glm::vec3(modelMatrixColliderVirus82[3]);
		Virus82Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus82", Virus82Collider, modelMatrixVirus82);
		//Collider del Virus83
		AbstractModel::SBB Virus83Collider;
		glm::mat4 modelMatrixColliderVirus83 = glm::mat4(modelMatrixVirus83);
		modelMatrixColliderVirus83 = glm::scale(modelMatrixColliderVirus83, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus83 = glm::translate(modelMatrixColliderVirus83, modelVirus.getSbb().c);
		Virus83Collider.c = glm::vec3(modelMatrixColliderVirus83[3]);
		Virus83Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus83", Virus83Collider, modelMatrixVirus83);
		//Collider del Virus84
		AbstractModel::SBB Virus84Collider;
		glm::mat4 modelMatrixColliderVirus84 = glm::mat4(modelMatrixVirus84);
		modelMatrixColliderVirus84 = glm::scale(modelMatrixColliderVirus84, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus84 = glm::translate(modelMatrixColliderVirus84, modelVirus.getSbb().c);
		Virus84Collider.c = glm::vec3(modelMatrixColliderVirus84[3]);
		Virus84Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus84", Virus84Collider, modelMatrixVirus84);
		//Collider del Virus85
		AbstractModel::SBB Virus85Collider;
		glm::mat4 modelMatrixColliderVirus85 = glm::mat4(modelMatrixVirus85);
		modelMatrixColliderVirus85 = glm::scale(modelMatrixColliderVirus85, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus85 = glm::translate(modelMatrixColliderVirus85, modelVirus.getSbb().c);
		Virus85Collider.c = glm::vec3(modelMatrixColliderVirus85[3]);
		Virus85Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus85", Virus85Collider, modelMatrixVirus85);
		//Collider del Virus86
		AbstractModel::SBB Virus86Collider;
		glm::mat4 modelMatrixColliderVirus86 = glm::mat4(modelMatrixVirus86);
		modelMatrixColliderVirus86 = glm::scale(modelMatrixColliderVirus86, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus86 = glm::translate(modelMatrixColliderVirus86, modelVirus.getSbb().c);
		Virus86Collider.c = glm::vec3(modelMatrixColliderVirus86[3]);
		Virus86Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus86", Virus86Collider, modelMatrixVirus86);
		//Collider del Virus87
		AbstractModel::SBB Virus87Collider;
		glm::mat4 modelMatrixColliderVirus87 = glm::mat4(modelMatrixVirus87);
		modelMatrixColliderVirus87 = glm::scale(modelMatrixColliderVirus87, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus87 = glm::translate(modelMatrixColliderVirus87, modelVirus.getSbb().c);
		Virus87Collider.c = glm::vec3(modelMatrixColliderVirus87[3]);
		Virus87Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus87", Virus87Collider, modelMatrixVirus87);
		//Collider del Virus88
		AbstractModel::SBB Virus88Collider;
		glm::mat4 modelMatrixColliderVirus88 = glm::mat4(modelMatrixVirus88);
		modelMatrixColliderVirus88 = glm::scale(modelMatrixColliderVirus88, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus88 = glm::translate(modelMatrixColliderVirus88, modelVirus.getSbb().c);
		Virus88Collider.c = glm::vec3(modelMatrixColliderVirus88[3]);
		Virus88Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus88", Virus88Collider, modelMatrixVirus88);
		//Collider del Virus89
		AbstractModel::SBB Virus89Collider;
		glm::mat4 modelMatrixColliderVirus89 = glm::mat4(modelMatrixVirus89);
		modelMatrixColliderVirus89 = glm::scale(modelMatrixColliderVirus89, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus89 = glm::translate(modelMatrixColliderVirus89, modelVirus.getSbb().c);
		Virus89Collider.c = glm::vec3(modelMatrixColliderVirus89[3]);
		Virus89Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus89", Virus89Collider, modelMatrixVirus89);
		//Collider del Virus90
		AbstractModel::SBB Virus90Collider;
		glm::mat4 modelMatrixColliderVirus90 = glm::mat4(modelMatrixVirus90);
		modelMatrixColliderVirus90 = glm::scale(modelMatrixColliderVirus90, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus90 = glm::translate(modelMatrixColliderVirus90, modelVirus.getSbb().c);
		Virus90Collider.c = glm::vec3(modelMatrixColliderVirus90[3]);
		Virus90Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus90", Virus90Collider, modelMatrixVirus90);
		//Collider del Virus91
		AbstractModel::SBB Virus91Collider;
		glm::mat4 modelMatrixColliderVirus91 = glm::mat4(modelMatrixVirus91);
		modelMatrixColliderVirus91 = glm::scale(modelMatrixColliderVirus91, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus91 = glm::translate(modelMatrixColliderVirus91, modelVirus.getSbb().c);
		Virus91Collider.c = glm::vec3(modelMatrixColliderVirus91[3]);
		Virus91Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus91", Virus91Collider, modelMatrixVirus91);
		//Collider del Virus92
		AbstractModel::SBB Virus92Collider;
		glm::mat4 modelMatrixColliderVirus92 = glm::mat4(modelMatrixVirus92);
		modelMatrixColliderVirus92 = glm::scale(modelMatrixColliderVirus92, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus92 = glm::translate(modelMatrixColliderVirus92, modelVirus.getSbb().c);
		Virus92Collider.c = glm::vec3(modelMatrixColliderVirus92[3]);
		Virus92Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus92", Virus92Collider, modelMatrixVirus92);
		//Collider del Virus93
		AbstractModel::SBB Virus93Collider;
		glm::mat4 modelMatrixColliderVirus93 = glm::mat4(modelMatrixVirus93);
		modelMatrixColliderVirus93 = glm::scale(modelMatrixColliderVirus93, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus93 = glm::translate(modelMatrixColliderVirus93, modelVirus.getSbb().c);
		Virus93Collider.c = glm::vec3(modelMatrixColliderVirus93[3]);
		Virus93Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus93", Virus93Collider, modelMatrixVirus93);
		//Collider del Virus94
		AbstractModel::SBB Virus94Collider;
		glm::mat4 modelMatrixColliderVirus94 = glm::mat4(modelMatrixVirus94);
		modelMatrixColliderVirus94 = glm::scale(modelMatrixColliderVirus94, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus94 = glm::translate(modelMatrixColliderVirus94, modelVirus.getSbb().c);
		Virus94Collider.c = glm::vec3(modelMatrixColliderVirus94[3]);
		Virus94Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus94", Virus94Collider, modelMatrixVirus94);
		//Collider del Virus95
		AbstractModel::SBB Virus95Collider;
		glm::mat4 modelMatrixColliderVirus95 = glm::mat4(modelMatrixVirus95);
		modelMatrixColliderVirus95 = glm::scale(modelMatrixColliderVirus95, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus95 = glm::translate(modelMatrixColliderVirus95, modelVirus.getSbb().c);
		Virus95Collider.c = glm::vec3(modelMatrixColliderVirus95[3]);
		Virus95Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus95", Virus95Collider, modelMatrixVirus95);
		//Collider del Virus96
		AbstractModel::SBB Virus96Collider;
		glm::mat4 modelMatrixColliderVirus96 = glm::mat4(modelMatrixVirus96);
		modelMatrixColliderVirus96 = glm::scale(modelMatrixColliderVirus96, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus96 = glm::translate(modelMatrixColliderVirus96, modelVirus.getSbb().c);
		Virus96Collider.c = glm::vec3(modelMatrixColliderVirus96[3]);
		Virus96Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus96", Virus96Collider, modelMatrixVirus96);
		//Collider del Virus97
		AbstractModel::SBB Virus97Collider;
		glm::mat4 modelMatrixColliderVirus97 = glm::mat4(modelMatrixVirus97);
		modelMatrixColliderVirus97 = glm::scale(modelMatrixColliderVirus97, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus97 = glm::translate(modelMatrixColliderVirus97, modelVirus.getSbb().c);
		Virus97Collider.c = glm::vec3(modelMatrixColliderVirus97[3]);
		Virus97Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus97", Virus97Collider, modelMatrixVirus97);
		//Collider del Virus98
		AbstractModel::SBB Virus98Collider;
		glm::mat4 modelMatrixColliderVirus98 = glm::mat4(modelMatrixVirus98);
		modelMatrixColliderVirus98 = glm::scale(modelMatrixColliderVirus98, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus98 = glm::translate(modelMatrixColliderVirus98, modelVirus.getSbb().c);
		Virus98Collider.c = glm::vec3(modelMatrixColliderVirus98[3]);
		Virus98Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus98", Virus98Collider, modelMatrixVirus98);
		//Collider del Virus99
		AbstractModel::SBB Virus99Collider;
		glm::mat4 modelMatrixColliderVirus99 = glm::mat4(modelMatrixVirus99);
		modelMatrixColliderVirus99 = glm::scale(modelMatrixColliderVirus99, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus99 = glm::translate(modelMatrixColliderVirus99, modelVirus.getSbb().c);
		Virus99Collider.c = glm::vec3(modelMatrixColliderVirus99[3]);
		Virus99Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus99", Virus99Collider, modelMatrixVirus99);
		//Collider del Virus100
		AbstractModel::SBB Virus100Collider;
		glm::mat4 modelMatrixColliderVirus100 = glm::mat4(modelMatrixVirus100);
		modelMatrixColliderVirus100 = glm::scale(modelMatrixColliderVirus100, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus100 = glm::translate(modelMatrixColliderVirus100, modelVirus.getSbb().c);
		Virus100Collider.c = glm::vec3(modelMatrixColliderVirus100[3]);
		Virus100Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus100", Virus100Collider, modelMatrixVirus100);

		//Collider del Virus101
		AbstractModel::SBB Virus101Collider;
		glm::mat4 modelMatrixColliderVirus101 = glm::mat4(modelMatrixVirus101);
		modelMatrixColliderVirus101 = glm::scale(modelMatrixColliderVirus101, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus101 = glm::translate(modelMatrixColliderVirus101, modelVirus.getSbb().c);
		Virus101Collider.c = glm::vec3(modelMatrixColliderVirus101[3]);
		Virus101Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus101", Virus101Collider, modelMatrixVirus101);
		//Collider del Virus102
		AbstractModel::SBB Virus102Collider;
		glm::mat4 modelMatrixColliderVirus102 = glm::mat4(modelMatrixVirus102);
		modelMatrixColliderVirus102 = glm::scale(modelMatrixColliderVirus102, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus102 = glm::translate(modelMatrixColliderVirus102, modelVirus.getSbb().c);
		Virus102Collider.c = glm::vec3(modelMatrixColliderVirus102[3]);
		Virus102Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus102", Virus102Collider, modelMatrixVirus102);
		//Collider del Virus103
		AbstractModel::SBB Virus103Collider;
		glm::mat4 modelMatrixColliderVirus103 = glm::mat4(modelMatrixVirus103);
		modelMatrixColliderVirus103 = glm::scale(modelMatrixColliderVirus103, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus103 = glm::translate(modelMatrixColliderVirus103, modelVirus.getSbb().c);
		Virus103Collider.c = glm::vec3(modelMatrixColliderVirus103[3]);
		Virus103Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus103", Virus103Collider, modelMatrixVirus103);
		//Collider del Virus104
		AbstractModel::SBB Virus104Collider;
		glm::mat4 modelMatrixColliderVirus104 = glm::mat4(modelMatrixVirus104);
		modelMatrixColliderVirus104 = glm::scale(modelMatrixColliderVirus104, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus104 = glm::translate(modelMatrixColliderVirus104, modelVirus.getSbb().c);
		Virus104Collider.c = glm::vec3(modelMatrixColliderVirus104[3]);
		Virus104Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus104", Virus104Collider, modelMatrixVirus104);
		//Collider del Virus105
		AbstractModel::SBB Virus105Collider;
		glm::mat4 modelMatrixColliderVirus105 = glm::mat4(modelMatrixVirus105);
		modelMatrixColliderVirus105 = glm::scale(modelMatrixColliderVirus105, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus105 = glm::translate(modelMatrixColliderVirus105, modelVirus.getSbb().c);
		Virus105Collider.c = glm::vec3(modelMatrixColliderVirus105[3]);
		Virus105Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus105", Virus105Collider, modelMatrixVirus105);
		//Collider del Virus106
		AbstractModel::SBB Virus106Collider;
		glm::mat4 modelMatrixColliderVirus106 = glm::mat4(modelMatrixVirus106);
		modelMatrixColliderVirus106 = glm::scale(modelMatrixColliderVirus106, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus106 = glm::translate(modelMatrixColliderVirus106, modelVirus.getSbb().c);
		Virus106Collider.c = glm::vec3(modelMatrixColliderVirus106[3]);
		Virus106Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus106", Virus106Collider, modelMatrixVirus106);
		//Collider del Virus107
		AbstractModel::SBB Virus107Collider;
		glm::mat4 modelMatrixColliderVirus107 = glm::mat4(modelMatrixVirus107);
		modelMatrixColliderVirus107 = glm::scale(modelMatrixColliderVirus107, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus107 = glm::translate(modelMatrixColliderVirus107, modelVirus.getSbb().c);
		Virus107Collider.c = glm::vec3(modelMatrixColliderVirus107[3]);
		Virus107Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus107", Virus107Collider, modelMatrixVirus107);
		//Collider del Virus108
		AbstractModel::SBB Virus108Collider;
		glm::mat4 modelMatrixColliderVirus108 = glm::mat4(modelMatrixVirus108);
		modelMatrixColliderVirus108 = glm::scale(modelMatrixColliderVirus108, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus108 = glm::translate(modelMatrixColliderVirus108, modelVirus.getSbb().c);
		Virus108Collider.c = glm::vec3(modelMatrixColliderVirus108[3]);
		Virus108Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus108", Virus108Collider, modelMatrixVirus108);
		//Collider del Virus109
		AbstractModel::SBB Virus109Collider;
		glm::mat4 modelMatrixColliderVirus109 = glm::mat4(modelMatrixVirus109);
		modelMatrixColliderVirus109 = glm::scale(modelMatrixColliderVirus109, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus109 = glm::translate(modelMatrixColliderVirus109, modelVirus.getSbb().c);
		Virus109Collider.c = glm::vec3(modelMatrixColliderVirus109[3]);
		Virus109Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus109", Virus109Collider, modelMatrixVirus109);
		//Collider del Virus110
		AbstractModel::SBB Virus110Collider;
		glm::mat4 modelMatrixColliderVirus110 = glm::mat4(modelMatrixVirus110);
		modelMatrixColliderVirus110 = glm::scale(modelMatrixColliderVirus110, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus110 = glm::translate(modelMatrixColliderVirus110, modelVirus.getSbb().c);
		Virus110Collider.c = glm::vec3(modelMatrixColliderVirus110[3]);
		Virus110Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus110", Virus110Collider, modelMatrixVirus110);
		//Collider del Virus111
		AbstractModel::SBB Virus111Collider;
		glm::mat4 modelMatrixColliderVirus111 = glm::mat4(modelMatrixVirus111);
		modelMatrixColliderVirus111 = glm::scale(modelMatrixColliderVirus111, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus111 = glm::translate(modelMatrixColliderVirus111, modelVirus.getSbb().c);
		Virus111Collider.c = glm::vec3(modelMatrixColliderVirus111[3]);
		Virus111Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus111", Virus111Collider, modelMatrixVirus111);
		//Collider del Virus112
		AbstractModel::SBB Virus112Collider;
		glm::mat4 modelMatrixColliderVirus112 = glm::mat4(modelMatrixVirus112);
		modelMatrixColliderVirus112 = glm::scale(modelMatrixColliderVirus112, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus112 = glm::translate(modelMatrixColliderVirus112, modelVirus.getSbb().c);
		Virus112Collider.c = glm::vec3(modelMatrixColliderVirus112[3]);
		Virus112Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus112", Virus112Collider, modelMatrixVirus112);
		//Collider del Virus113
		AbstractModel::SBB Virus113Collider;
		glm::mat4 modelMatrixColliderVirus113 = glm::mat4(modelMatrixVirus113);
		modelMatrixColliderVirus113 = glm::scale(modelMatrixColliderVirus113, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus113 = glm::translate(modelMatrixColliderVirus113, modelVirus.getSbb().c);
		Virus113Collider.c = glm::vec3(modelMatrixColliderVirus113[3]);
		Virus113Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus113", Virus113Collider, modelMatrixVirus113);
		//Collider del Virus114
		AbstractModel::SBB Virus114Collider;
		glm::mat4 modelMatrixColliderVirus114 = glm::mat4(modelMatrixVirus114);
		modelMatrixColliderVirus114 = glm::scale(modelMatrixColliderVirus114, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus114 = glm::translate(modelMatrixColliderVirus114, modelVirus.getSbb().c);
		Virus114Collider.c = glm::vec3(modelMatrixColliderVirus114[3]);
		Virus114Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus114", Virus114Collider, modelMatrixVirus114);
		//Collider del Virus115
		AbstractModel::SBB Virus115Collider;
		glm::mat4 modelMatrixColliderVirus115 = glm::mat4(modelMatrixVirus115);
		modelMatrixColliderVirus115 = glm::scale(modelMatrixColliderVirus115, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus115 = glm::translate(modelMatrixColliderVirus115, modelVirus.getSbb().c);
		Virus115Collider.c = glm::vec3(modelMatrixColliderVirus115[3]);
		Virus115Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus115", Virus115Collider, modelMatrixVirus115);
		//Collider del Virus116
		AbstractModel::SBB Virus116Collider;
		glm::mat4 modelMatrixColliderVirus116 = glm::mat4(modelMatrixVirus116);
		modelMatrixColliderVirus116 = glm::scale(modelMatrixColliderVirus116, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus116 = glm::translate(modelMatrixColliderVirus116, modelVirus.getSbb().c);
		Virus116Collider.c = glm::vec3(modelMatrixColliderVirus116[3]);
		Virus116Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus116", Virus116Collider, modelMatrixVirus116);
		//Collider del Virus117
		AbstractModel::SBB Virus117Collider;
		glm::mat4 modelMatrixColliderVirus117 = glm::mat4(modelMatrixVirus117);
		modelMatrixColliderVirus117 = glm::scale(modelMatrixColliderVirus117, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus117 = glm::translate(modelMatrixColliderVirus117, modelVirus.getSbb().c);
		Virus117Collider.c = glm::vec3(modelMatrixColliderVirus117[3]);
		Virus117Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus117", Virus117Collider, modelMatrixVirus117);
		//Collider del Virus118
		AbstractModel::SBB Virus118Collider;
		glm::mat4 modelMatrixColliderVirus118 = glm::mat4(modelMatrixVirus118);
		modelMatrixColliderVirus118 = glm::scale(modelMatrixColliderVirus118, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus118 = glm::translate(modelMatrixColliderVirus118, modelVirus.getSbb().c);
		Virus118Collider.c = glm::vec3(modelMatrixColliderVirus118[3]);
		Virus118Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus118", Virus118Collider, modelMatrixVirus118);
		//Collider del Virus119
		AbstractModel::SBB Virus119Collider;
		glm::mat4 modelMatrixColliderVirus119 = glm::mat4(modelMatrixVirus119);
		modelMatrixColliderVirus119 = glm::scale(modelMatrixColliderVirus119, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus119 = glm::translate(modelMatrixColliderVirus119, modelVirus.getSbb().c);
		Virus119Collider.c = glm::vec3(modelMatrixColliderVirus119[3]);
		Virus119Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus119", Virus119Collider, modelMatrixVirus119);
		
		//Collider del Virus120
		AbstractModel::SBB Virus120Collider;
		glm::mat4 modelMatrixColliderVirus120 = glm::mat4(modelMatrixVirus120);
		modelMatrixColliderVirus120 = glm::scale(modelMatrixColliderVirus120, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus120 = glm::translate(modelMatrixColliderVirus120, modelVirus.getSbb().c);
		Virus120Collider.c = glm::vec3(modelMatrixColliderVirus120[3]);
		Virus120Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus120", Virus120Collider, modelMatrixVirus120);
		//Collider del Virus121
		AbstractModel::SBB Virus121Collider;
		glm::mat4 modelMatrixColliderVirus121 = glm::mat4(modelMatrixVirus121);
		modelMatrixColliderVirus121 = glm::scale(modelMatrixColliderVirus121, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus121 = glm::translate(modelMatrixColliderVirus121, modelVirus.getSbb().c);
		Virus121Collider.c = glm::vec3(modelMatrixColliderVirus121[3]);
		Virus121Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus121", Virus121Collider, modelMatrixVirus121);
		//Collider del Virus122
		AbstractModel::SBB Virus122Collider;
		glm::mat4 modelMatrixColliderVirus122 = glm::mat4(modelMatrixVirus122);
		modelMatrixColliderVirus122 = glm::scale(modelMatrixColliderVirus122, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus122 = glm::translate(modelMatrixColliderVirus122, modelVirus.getSbb().c);
		Virus122Collider.c = glm::vec3(modelMatrixColliderVirus122[3]);
		Virus122Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus122", Virus122Collider, modelMatrixVirus122);
		//Collider del Virus123
		AbstractModel::SBB Virus123Collider;
		glm::mat4 modelMatrixColliderVirus123 = glm::mat4(modelMatrixVirus123);
		modelMatrixColliderVirus123 = glm::scale(modelMatrixColliderVirus123, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus123 = glm::translate(modelMatrixColliderVirus123, modelVirus.getSbb().c);
		Virus123Collider.c = glm::vec3(modelMatrixColliderVirus123[3]);
		Virus123Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus123", Virus123Collider, modelMatrixVirus123);
		//Collider del Virus124
		AbstractModel::SBB Virus124Collider;
		glm::mat4 modelMatrixColliderVirus124 = glm::mat4(modelMatrixVirus124);
		modelMatrixColliderVirus124 = glm::scale(modelMatrixColliderVirus124, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus124 = glm::translate(modelMatrixColliderVirus124, modelVirus.getSbb().c);
		Virus124Collider.c = glm::vec3(modelMatrixColliderVirus124[3]);
		Virus124Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus124", Virus124Collider, modelMatrixVirus124);
		//Collider del Virus125
		AbstractModel::SBB Virus125Collider;
		glm::mat4 modelMatrixColliderVirus125 = glm::mat4(modelMatrixVirus125);
		modelMatrixColliderVirus125 = glm::scale(modelMatrixColliderVirus125, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus125 = glm::translate(modelMatrixColliderVirus125, modelVirus.getSbb().c);
		Virus125Collider.c = glm::vec3(modelMatrixColliderVirus125[3]);
		Virus125Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus125", Virus125Collider, modelMatrixVirus125);
		//Collider del Virus126
		AbstractModel::SBB Virus126Collider;
		glm::mat4 modelMatrixColliderVirus126 = glm::mat4(modelMatrixVirus126);
		modelMatrixColliderVirus126 = glm::scale(modelMatrixColliderVirus126, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus126 = glm::translate(modelMatrixColliderVirus126, modelVirus.getSbb().c);
		Virus126Collider.c = glm::vec3(modelMatrixColliderVirus126[3]);
		Virus126Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus126", Virus126Collider, modelMatrixVirus126);
		//Collider del Virus127
		AbstractModel::SBB Virus127Collider;
		glm::mat4 modelMatrixColliderVirus127 = glm::mat4(modelMatrixVirus127);
		modelMatrixColliderVirus127 = glm::scale(modelMatrixColliderVirus127, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus127 = glm::translate(modelMatrixColliderVirus127, modelVirus.getSbb().c);
		Virus127Collider.c = glm::vec3(modelMatrixColliderVirus127[3]);
		Virus127Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus127", Virus127Collider, modelMatrixVirus127);
		//Collider del Virus128
		AbstractModel::SBB Virus128Collider;
		glm::mat4 modelMatrixColliderVirus128 = glm::mat4(modelMatrixVirus128);
		modelMatrixColliderVirus128 = glm::scale(modelMatrixColliderVirus128, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus128 = glm::translate(modelMatrixColliderVirus128, modelVirus.getSbb().c);
		Virus128Collider.c = glm::vec3(modelMatrixColliderVirus128[3]);
		Virus128Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus128", Virus128Collider, modelMatrixVirus128);
		//Collider del Virus129
		AbstractModel::SBB Virus129Collider;
		glm::mat4 modelMatrixColliderVirus129 = glm::mat4(modelMatrixVirus129);
		modelMatrixColliderVirus129 = glm::scale(modelMatrixColliderVirus129, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus129 = glm::translate(modelMatrixColliderVirus129, modelVirus.getSbb().c);
		Virus129Collider.c = glm::vec3(modelMatrixColliderVirus129[3]);
		Virus129Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus129", Virus129Collider, modelMatrixVirus129);
		//Collider del Virus130
		AbstractModel::SBB Virus130Collider;
		glm::mat4 modelMatrixColliderVirus130 = glm::mat4(modelMatrixVirus130);
		modelMatrixColliderVirus130 = glm::scale(modelMatrixColliderVirus130, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus130 = glm::translate(modelMatrixColliderVirus130, modelVirus.getSbb().c);
		Virus130Collider.c = glm::vec3(modelMatrixColliderVirus130[3]);
		Virus130Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus130", Virus130Collider, modelMatrixVirus130);
		//Collider del Virus131
		AbstractModel::SBB Virus131Collider;
		glm::mat4 modelMatrixColliderVirus131 = glm::mat4(modelMatrixVirus131);
		modelMatrixColliderVirus131 = glm::scale(modelMatrixColliderVirus131, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus131 = glm::translate(modelMatrixColliderVirus131, modelVirus.getSbb().c);
		Virus131Collider.c = glm::vec3(modelMatrixColliderVirus131[3]);
		Virus131Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus131", Virus131Collider, modelMatrixVirus131);
		//Collider del Virus132
		AbstractModel::SBB Virus132Collider;
		glm::mat4 modelMatrixColliderVirus132 = glm::mat4(modelMatrixVirus132);
		modelMatrixColliderVirus132 = glm::scale(modelMatrixColliderVirus132, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus132 = glm::translate(modelMatrixColliderVirus132, modelVirus.getSbb().c);
		Virus132Collider.c = glm::vec3(modelMatrixColliderVirus132[3]);
		Virus132Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus132", Virus132Collider, modelMatrixVirus132);
		//Collider del Virus133
		AbstractModel::SBB Virus133Collider;
		glm::mat4 modelMatrixColliderVirus133 = glm::mat4(modelMatrixVirus133);
		modelMatrixColliderVirus133 = glm::scale(modelMatrixColliderVirus133, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus133 = glm::translate(modelMatrixColliderVirus133, modelVirus.getSbb().c);
		Virus133Collider.c = glm::vec3(modelMatrixColliderVirus133[3]);
		Virus133Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus133", Virus133Collider, modelMatrixVirus133);
		//Collider del Virus134
		AbstractModel::SBB Virus134Collider;
		glm::mat4 modelMatrixColliderVirus134 = glm::mat4(modelMatrixVirus134);
		modelMatrixColliderVirus134 = glm::scale(modelMatrixColliderVirus134, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus134 = glm::translate(modelMatrixColliderVirus134, modelVirus.getSbb().c);
		Virus134Collider.c = glm::vec3(modelMatrixColliderVirus134[3]);
		Virus134Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus134", Virus134Collider, modelMatrixVirus134);
		//Collider del Virus135
		AbstractModel::SBB Virus135Collider;
		glm::mat4 modelMatrixColliderVirus135 = glm::mat4(modelMatrixVirus135);
		modelMatrixColliderVirus135 = glm::scale(modelMatrixColliderVirus135, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus135 = glm::translate(modelMatrixColliderVirus135, modelVirus.getSbb().c);
		Virus135Collider.c = glm::vec3(modelMatrixColliderVirus135[3]);
		Virus135Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus135", Virus135Collider, modelMatrixVirus135);
		//Collider del Virus136
		AbstractModel::SBB Virus136Collider;
		glm::mat4 modelMatrixColliderVirus136 = glm::mat4(modelMatrixVirus136);
		modelMatrixColliderVirus136 = glm::scale(modelMatrixColliderVirus136, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus136 = glm::translate(modelMatrixColliderVirus136, modelVirus.getSbb().c);
		Virus136Collider.c = glm::vec3(modelMatrixColliderVirus136[3]);
		Virus136Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus136", Virus136Collider, modelMatrixVirus136);
		//Collider del Virus137
		AbstractModel::SBB Virus137Collider;
		glm::mat4 modelMatrixColliderVirus137 = glm::mat4(modelMatrixVirus137);
		modelMatrixColliderVirus137 = glm::scale(modelMatrixColliderVirus137, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus137 = glm::translate(modelMatrixColliderVirus137, modelVirus.getSbb().c);
		Virus137Collider.c = glm::vec3(modelMatrixColliderVirus137[3]);
		Virus137Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus137", Virus137Collider, modelMatrixVirus137);
		//Collider del Virus138
		AbstractModel::SBB Virus138Collider;
		glm::mat4 modelMatrixColliderVirus138 = glm::mat4(modelMatrixVirus138);
		modelMatrixColliderVirus138 = glm::scale(modelMatrixColliderVirus138, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus138 = glm::translate(modelMatrixColliderVirus138, modelVirus.getSbb().c);
		Virus138Collider.c = glm::vec3(modelMatrixColliderVirus138[3]);
		Virus138Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus138", Virus138Collider, modelMatrixVirus138);
		//Collider del Virus139
		AbstractModel::SBB Virus139Collider;
		glm::mat4 modelMatrixColliderVirus139 = glm::mat4(modelMatrixVirus139);
		modelMatrixColliderVirus139 = glm::scale(modelMatrixColliderVirus139, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus139 = glm::translate(modelMatrixColliderVirus139, modelVirus.getSbb().c);
		Virus139Collider.c = glm::vec3(modelMatrixColliderVirus139[3]);
		Virus139Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus139", Virus139Collider, modelMatrixVirus139);
		//Collider del Virus140
		AbstractModel::SBB Virus140Collider;
		glm::mat4 modelMatrixColliderVirus140 = glm::mat4(modelMatrixVirus140);
		modelMatrixColliderVirus140 = glm::scale(modelMatrixColliderVirus140, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus140 = glm::translate(modelMatrixColliderVirus140, modelVirus.getSbb().c);
		Virus140Collider.c = glm::vec3(modelMatrixColliderVirus140[3]);
		Virus140Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus140", Virus140Collider, modelMatrixVirus140);
		//Collider del Virus141
		AbstractModel::SBB Virus141Collider;
		glm::mat4 modelMatrixColliderVirus141 = glm::mat4(modelMatrixVirus141);
		modelMatrixColliderVirus141 = glm::scale(modelMatrixColliderVirus141, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus141 = glm::translate(modelMatrixColliderVirus141, modelVirus.getSbb().c);
		Virus141Collider.c = glm::vec3(modelMatrixColliderVirus141[3]);
		Virus141Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus141", Virus141Collider, modelMatrixVirus141);
		//Collider del Virus142
		AbstractModel::SBB Virus142Collider;
		glm::mat4 modelMatrixColliderVirus142 = glm::mat4(modelMatrixVirus142);
		modelMatrixColliderVirus142 = glm::scale(modelMatrixColliderVirus142, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus142 = glm::translate(modelMatrixColliderVirus142, modelVirus.getSbb().c);
		Virus142Collider.c = glm::vec3(modelMatrixColliderVirus142[3]);
		Virus142Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus142", Virus142Collider, modelMatrixVirus142);
		//Collider del Virus143
		AbstractModel::SBB Virus143Collider;
		glm::mat4 modelMatrixColliderVirus143 = glm::mat4(modelMatrixVirus143);
		modelMatrixColliderVirus143 = glm::scale(modelMatrixColliderVirus143, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus143 = glm::translate(modelMatrixColliderVirus143, modelVirus.getSbb().c);
		Virus143Collider.c = glm::vec3(modelMatrixColliderVirus143[3]);
		Virus143Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus143", Virus143Collider, modelMatrixVirus143);
		//Collider del Virus144
		AbstractModel::SBB Virus144Collider;
		glm::mat4 modelMatrixColliderVirus144 = glm::mat4(modelMatrixVirus144);
		modelMatrixColliderVirus144 = glm::scale(modelMatrixColliderVirus144, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus144 = glm::translate(modelMatrixColliderVirus144, modelVirus.getSbb().c);
		Virus144Collider.c = glm::vec3(modelMatrixColliderVirus144[3]);
		Virus144Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus144", Virus144Collider, modelMatrixVirus144);
		//Collider del Virus145
		AbstractModel::SBB Virus145Collider;
		glm::mat4 modelMatrixColliderVirus145 = glm::mat4(modelMatrixVirus145);
		modelMatrixColliderVirus145 = glm::scale(modelMatrixColliderVirus145, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus145 = glm::translate(modelMatrixColliderVirus145, modelVirus.getSbb().c);
		Virus145Collider.c = glm::vec3(modelMatrixColliderVirus145[3]);
		Virus145Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus145", Virus145Collider, modelMatrixVirus145);
		//Collider del Virus146
		AbstractModel::SBB Virus146Collider;
		glm::mat4 modelMatrixColliderVirus146 = glm::mat4(modelMatrixVirus146);
		modelMatrixColliderVirus146 = glm::scale(modelMatrixColliderVirus146, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus146 = glm::translate(modelMatrixColliderVirus146, modelVirus.getSbb().c);
		Virus146Collider.c = glm::vec3(modelMatrixColliderVirus146[3]);
		Virus146Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus146", Virus146Collider, modelMatrixVirus146);
		//Collider del Virus147
		AbstractModel::SBB Virus147Collider;
		glm::mat4 modelMatrixColliderVirus147 = glm::mat4(modelMatrixVirus147);
		modelMatrixColliderVirus147 = glm::scale(modelMatrixColliderVirus147, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus147 = glm::translate(modelMatrixColliderVirus147, modelVirus.getSbb().c);
		Virus147Collider.c = glm::vec3(modelMatrixColliderVirus147[3]);
		Virus147Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus147", Virus147Collider, modelMatrixVirus147);
		//Collider del Virus148
		AbstractModel::SBB Virus148Collider;
		glm::mat4 modelMatrixColliderVirus148 = glm::mat4(modelMatrixVirus148);
		modelMatrixColliderVirus148 = glm::scale(modelMatrixColliderVirus148, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus148 = glm::translate(modelMatrixColliderVirus148, modelVirus.getSbb().c);
		Virus148Collider.c = glm::vec3(modelMatrixColliderVirus148[3]);
		Virus148Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus148", Virus148Collider, modelMatrixVirus148);
		//Collider del Virus149
		AbstractModel::SBB Virus149Collider;
		glm::mat4 modelMatrixColliderVirus149 = glm::mat4(modelMatrixVirus149);
		modelMatrixColliderVirus149 = glm::scale(modelMatrixColliderVirus149, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus149 = glm::translate(modelMatrixColliderVirus149, modelVirus.getSbb().c);
		Virus149Collider.c = glm::vec3(modelMatrixColliderVirus149[3]);
		Virus149Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus149", Virus149Collider, modelMatrixVirus149);
		//Collider del Virus150
		AbstractModel::SBB Virus150Collider;
		glm::mat4 modelMatrixColliderVirus150 = glm::mat4(modelMatrixVirus150);
		modelMatrixColliderVirus150 = glm::scale(modelMatrixColliderVirus150, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus150 = glm::translate(modelMatrixColliderVirus150, modelVirus.getSbb().c);
		Virus150Collider.c = glm::vec3(modelMatrixColliderVirus150[3]);
		Virus150Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus150", Virus150Collider, modelMatrixVirus150);
		//Collider del Virus151
		AbstractModel::SBB Virus151Collider;
		glm::mat4 modelMatrixColliderVirus151 = glm::mat4(modelMatrixVirus151);
		modelMatrixColliderVirus151 = glm::scale(modelMatrixColliderVirus151, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus151 = glm::translate(modelMatrixColliderVirus151, modelVirus.getSbb().c);
		Virus151Collider.c = glm::vec3(modelMatrixColliderVirus151[3]);
		Virus151Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus151", Virus151Collider, modelMatrixVirus151);
		//Collider del Virus152
		AbstractModel::SBB Virus152Collider;
		glm::mat4 modelMatrixColliderVirus152 = glm::mat4(modelMatrixVirus152);
		modelMatrixColliderVirus152 = glm::scale(modelMatrixColliderVirus152, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus152 = glm::translate(modelMatrixColliderVirus152, modelVirus.getSbb().c);
		Virus152Collider.c = glm::vec3(modelMatrixColliderVirus152[3]);
		Virus152Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus152", Virus152Collider, modelMatrixVirus152);
		//Collider del Virus153
		AbstractModel::SBB Virus153Collider;
		glm::mat4 modelMatrixColliderVirus153 = glm::mat4(modelMatrixVirus153);
		modelMatrixColliderVirus153 = glm::scale(modelMatrixColliderVirus153, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus153 = glm::translate(modelMatrixColliderVirus153, modelVirus.getSbb().c);
		Virus153Collider.c = glm::vec3(modelMatrixColliderVirus153[3]);
		Virus153Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus153", Virus153Collider, modelMatrixVirus153);
		//Collider del Virus154
		AbstractModel::SBB Virus154Collider;
		glm::mat4 modelMatrixColliderVirus154 = glm::mat4(modelMatrixVirus154);
		modelMatrixColliderVirus154 = glm::scale(modelMatrixColliderVirus154, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus154 = glm::translate(modelMatrixColliderVirus154, modelVirus.getSbb().c);
		Virus154Collider.c = glm::vec3(modelMatrixColliderVirus154[3]);
		Virus154Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus154", Virus154Collider, modelMatrixVirus154);
		//Collider del Virus155
		AbstractModel::SBB Virus155Collider;
		glm::mat4 modelMatrixColliderVirus155 = glm::mat4(modelMatrixVirus155);
		modelMatrixColliderVirus155 = glm::scale(modelMatrixColliderVirus155, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus155 = glm::translate(modelMatrixColliderVirus155, modelVirus.getSbb().c);
		Virus155Collider.c = glm::vec3(modelMatrixColliderVirus155[3]);
		Virus155Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus155", Virus155Collider, modelMatrixVirus155);
		//Collider del Virus156
		AbstractModel::SBB Virus156Collider;
		glm::mat4 modelMatrixColliderVirus156 = glm::mat4(modelMatrixVirus156);
		modelMatrixColliderVirus156 = glm::scale(modelMatrixColliderVirus156, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus156 = glm::translate(modelMatrixColliderVirus156, modelVirus.getSbb().c);
		Virus156Collider.c = glm::vec3(modelMatrixColliderVirus156[3]);
		Virus156Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus156", Virus156Collider, modelMatrixVirus156);
		//Collider del Virus157
		AbstractModel::SBB Virus157Collider;
		glm::mat4 modelMatrixColliderVirus157 = glm::mat4(modelMatrixVirus157);
		modelMatrixColliderVirus157 = glm::scale(modelMatrixColliderVirus157, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus157 = glm::translate(modelMatrixColliderVirus157, modelVirus.getSbb().c);
		Virus157Collider.c = glm::vec3(modelMatrixColliderVirus157[3]);
		Virus157Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus157", Virus157Collider, modelMatrixVirus157);
		//Collider del Virus158
		AbstractModel::SBB Virus158Collider;
		glm::mat4 modelMatrixColliderVirus158 = glm::mat4(modelMatrixVirus158);
		modelMatrixColliderVirus158 = glm::scale(modelMatrixColliderVirus158, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus158 = glm::translate(modelMatrixColliderVirus158, modelVirus.getSbb().c);
		Virus158Collider.c = glm::vec3(modelMatrixColliderVirus158[3]);
		Virus158Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus158", Virus158Collider, modelMatrixVirus158);
		//Collider del Virus159
		AbstractModel::SBB Virus159Collider;
		glm::mat4 modelMatrixColliderVirus159 = glm::mat4(modelMatrixVirus159);
		modelMatrixColliderVirus159 = glm::scale(modelMatrixColliderVirus159, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus159 = glm::translate(modelMatrixColliderVirus159, modelVirus.getSbb().c);
		Virus159Collider.c = glm::vec3(modelMatrixColliderVirus159[3]);
		Virus159Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus159", Virus159Collider, modelMatrixVirus159);
		//Collider del Virus160
		AbstractModel::SBB Virus160Collider;
		glm::mat4 modelMatrixColliderVirus160 = glm::mat4(modelMatrixVirus160);
		modelMatrixColliderVirus160 = glm::scale(modelMatrixColliderVirus160, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus160 = glm::translate(modelMatrixColliderVirus160, modelVirus.getSbb().c);
		Virus160Collider.c = glm::vec3(modelMatrixColliderVirus160[3]);
		Virus160Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus160", Virus160Collider, modelMatrixVirus160);
		//Collider del Virus161
		AbstractModel::SBB Virus161Collider;
		glm::mat4 modelMatrixColliderVirus161 = glm::mat4(modelMatrixVirus161);
		modelMatrixColliderVirus161 = glm::scale(modelMatrixColliderVirus161, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus161 = glm::translate(modelMatrixColliderVirus161, modelVirus.getSbb().c);
		Virus161Collider.c = glm::vec3(modelMatrixColliderVirus161[3]);
		Virus161Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus161", Virus161Collider, modelMatrixVirus161);
		//Collider del Virus162
		AbstractModel::SBB Virus162Collider;
		glm::mat4 modelMatrixColliderVirus162 = glm::mat4(modelMatrixVirus162);
		modelMatrixColliderVirus162 = glm::scale(modelMatrixColliderVirus162, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus162 = glm::translate(modelMatrixColliderVirus162, modelVirus.getSbb().c);
		Virus162Collider.c = glm::vec3(modelMatrixColliderVirus162[3]);
		Virus162Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus162", Virus162Collider, modelMatrixVirus162);
		//Collider del Virus163
		AbstractModel::SBB Virus163Collider;
		glm::mat4 modelMatrixColliderVirus163 = glm::mat4(modelMatrixVirus163);
		modelMatrixColliderVirus163 = glm::scale(modelMatrixColliderVirus163, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus163 = glm::translate(modelMatrixColliderVirus163, modelVirus.getSbb().c);
		Virus163Collider.c = glm::vec3(modelMatrixColliderVirus163[3]);
		Virus163Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus163", Virus163Collider, modelMatrixVirus163);
		//Collider del Virus164
		AbstractModel::SBB Virus164Collider;
		glm::mat4 modelMatrixColliderVirus164 = glm::mat4(modelMatrixVirus164);
		modelMatrixColliderVirus164 = glm::scale(modelMatrixColliderVirus164, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus164 = glm::translate(modelMatrixColliderVirus164, modelVirus.getSbb().c);
		Virus164Collider.c = glm::vec3(modelMatrixColliderVirus164[3]);
		Virus164Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus164", Virus164Collider, modelMatrixVirus164);
		//Collider del Virus165
		AbstractModel::SBB Virus165Collider;
		glm::mat4 modelMatrixColliderVirus165 = glm::mat4(modelMatrixVirus165);
		modelMatrixColliderVirus165 = glm::scale(modelMatrixColliderVirus165, glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderVirus165 = glm::translate(modelMatrixColliderVirus165, modelVirus.getSbb().c);
		Virus165Collider.c = glm::vec3(modelMatrixColliderVirus165[3]);
		Virus165Collider.ratio = modelVirus.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "Virus165", Virus165Collider, modelMatrixVirus165);


		
		// Collider de mayow
		AbstractModel::OBB mayowCollider;
		glm::mat4 modelmatrixColliderMayow = glm::mat4(modelMatrixMayow);
		modelmatrixColliderMayow = glm::rotate(modelmatrixColliderMayow,
			glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Set the orientation of collider before doing the scale
		mayowCollider.u = glm::quat_cast(modelmatrixColliderMayow);
		modelmatrixColliderMayow = glm::scale(modelmatrixColliderMayow, glm::vec3(0.021, 0.021, 0.021));
		modelmatrixColliderMayow = glm::translate(modelmatrixColliderMayow,
			glm::vec3(mayowModelAnimate.getObb().c.x,
				mayowModelAnimate.getObb().c.y,
				mayowModelAnimate.getObb().c.z));
		mayowCollider.e = mayowModelAnimate.getObb().e * glm::vec3(0.021, 0.021, 0.021) * glm::vec3(0.787401574, 0.787401574, 0.787401574);
		mayowCollider.c = glm::vec3(modelmatrixColliderMayow[3]);
		addOrUpdateColliders(collidersOBB, "mayow", mayowCollider, modelMatrixMayow);

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

		// Esto es para ilustrar la transformacion inversa de los coliders
		/*glm::vec3 cinv = glm::inverse(mayowCollider.u) * glm::vec4(rockCollider.c, 1.0);
		glm::mat4 invColliderS = glm::mat4(1.0);
		invColliderS = glm::translate(invColliderS, cinv);
		invColliderS =  invColliderS * glm::mat4(mayowCollider.u);
		invColliderS = glm::scale(invColliderS, glm::vec3(rockCollider.ratio * 2.0, rockCollider.ratio * 2.0, rockCollider.ratio * 2.0));
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		sphereCollider.enableWireMode();
		sphereCollider.render(invColliderS);
		glm::vec3 cinv2 = glm::inverse(mayowCollider.u) * glm::vec4(mayowCollider.c, 1.0);
		glm::mat4 invColliderB = glm::mat4(1.0);
		invColliderB = glm::translate(invColliderB, cinv2);
		invColliderB = glm::scale(invColliderB, mayowCollider.e * 2.0f);
		boxCollider.setColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		boxCollider.enableWireMode();
		boxCollider.render(invColliderB);
		// Se regresa el color blanco
		sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
		boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));*/

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
					if (jt->first.compare("mayow") == 0)
						modelMatrixMayow = std::get<1>(jt->second);
					if (jt->first.compare("dart") == 0)
						modelMatrixDart = std::get<1>(jt->second);
				}
			}
		}

		/*******************************************
		 * Interpolation key frames with disconect objects
		 *******************************************/
		if (record && modelSelected == 1) {
			matrixDartJoints.push_back(rotDartHead);
			matrixDartJoints.push_back(rotDartLeftArm);
			matrixDartJoints.push_back(rotDartLeftHand);
			matrixDartJoints.push_back(rotDartRightArm);
			matrixDartJoints.push_back(rotDartRightHand);
			matrixDartJoints.push_back(rotDartLeftLeg);
			matrixDartJoints.push_back(rotDartRightLeg);
			if (saveFrame) {
				appendFrame(myfile, matrixDartJoints);
				saveFrame = false;
			}
		}
		else if (keyFramesDartJoints.size() > 0) {
			// Para reproducir el frame
			interpolationDartJoints = numPasosDartJoints / (float)maxNumPasosDartJoints;
			numPasosDartJoints++;
			if (interpolationDartJoints > 1.0) {
				numPasosDartJoints = 0;
				interpolationDartJoints = 0;
				indexFrameDartJoints = indexFrameDartJointsNext;
				indexFrameDartJointsNext++;
			}
			if (indexFrameDartJointsNext > keyFramesDartJoints.size() - 1)
				indexFrameDartJointsNext = 0;
			rotDartHead = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 0, interpolationDartJoints);
			rotDartLeftArm = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 1, interpolationDartJoints);
			rotDartLeftHand = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 2, interpolationDartJoints);
			rotDartRightArm = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 3, interpolationDartJoints);
			rotDartRightHand = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 4, interpolationDartJoints);
			rotDartLeftLeg = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 5, interpolationDartJoints);
			rotDartRightLeg = interpolate(keyFramesDartJoints, indexFrameDartJoints, indexFrameDartJointsNext, 6, interpolationDartJoints);
		}

		if (record && modelSelected == 2) {
			matrixDart.push_back(modelMatrixDart);
			if (saveFrame) {
				appendFrame(myfile, matrixDart);
				saveFrame = false;
			}
		}
		else if (keyFramesDart.size() > 0) {
			// Para reproducir el frame
			interpolationDart = numPasosDart / (float)maxNumPasosDart;
			numPasosDart++;
			if (interpolationDart > 1.0) {
				numPasosDart = 0;
				interpolationDart = 0;
				indexFrameDart = indexFrameDartNext;
				indexFrameDartNext++;
			}
			if (indexFrameDartNext > keyFramesDart.size() - 1)
				indexFrameDartNext = 0;
			modelMatrixDart = interpolate(keyFramesDart, indexFrameDart, indexFrameDartNext, 0, interpolationDart);
		}

		// Constantes de animaciones
		rotHelHelY += 0.5;
		animationIndex = 1;

		/*******************************************
		 * State machines
		 *******************************************/

		 // State machine para movimiento de virus

		switch (stateVirus) {

		case 1:
			modelMatrixVirus1 = glm::translate(modelMatrixVirus1, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus2 = glm::translate(modelMatrixVirus2, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus3 = glm::translate(modelMatrixVirus3, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus4 = glm::translate(modelMatrixVirus4, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus5 = glm::translate(modelMatrixVirus5, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus6 = glm::translate(modelMatrixVirus6, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus7 = glm::translate(modelMatrixVirus7, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus8 = glm::translate(modelMatrixVirus8, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus9 = glm::translate(modelMatrixVirus9, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus10 = glm::translate(modelMatrixVirus10, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus11 = glm::translate(modelMatrixVirus11, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus12 = glm::translate(modelMatrixVirus12, glm::vec3(-0.1f, 0.0f, -0.0f));
			advanceCountVirus += 0.2;
			if (advanceCountVirus > maxAdvanceVirus) {
				advanceCountVirus = 0;
				stateVirus = 2;
			}
			break;

		case 2:
			modelMatrixVirus1 = glm::translate(modelMatrixVirus1, glm::vec3(-0.1f, 0.0f, 0.0f));
			modelMatrixVirus2 = glm::translate(modelMatrixVirus2, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus3 = glm::translate(modelMatrixVirus3, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus4 = glm::translate(modelMatrixVirus4, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus5 = glm::translate(modelMatrixVirus5, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus6 = glm::translate(modelMatrixVirus6, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus7 = glm::translate(modelMatrixVirus7, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus8 = glm::translate(modelMatrixVirus8, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus9 = glm::translate(modelMatrixVirus9, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus10 = glm::translate(modelMatrixVirus10, glm::vec3(0.1f, 0.0f, 0.0f));
			modelMatrixVirus11 = glm::translate(modelMatrixVirus11, glm::vec3(-0.1f, 0.0f, -0.0f));
			modelMatrixVirus12 = glm::translate(modelMatrixVirus12, glm::vec3(0.1f, 0.0f, 0.0f));

			advanceCountVirus += 0.2;
			if (advanceCountVirus > maxAdvanceVirus) {
				advanceCountVirus = 0;
				stateVirus = 1;
			}
			break;
		default:
			break;
		}
	//Segunda Machine
		switch (stateVirus2) {

		case 1:
			modelMatrixVirus61 = glm::translate(modelMatrixVirus61, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus62 = glm::translate(modelMatrixVirus62, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus63 = glm::translate(modelMatrixVirus63, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus64 = glm::translate(modelMatrixVirus64, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus65 = glm::translate(modelMatrixVirus65, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus66 = glm::translate(modelMatrixVirus66, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus67 = glm::translate(modelMatrixVirus67, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus68 = glm::translate(modelMatrixVirus68, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus69 = glm::translate(modelMatrixVirus69, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus70 = glm::translate(modelMatrixVirus70, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus71 = glm::translate(modelMatrixVirus71, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus72 = glm::translate(modelMatrixVirus72, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus73 = glm::translate(modelMatrixVirus73, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus74 = glm::translate(modelMatrixVirus74, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus75 = glm::translate(modelMatrixVirus75, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus76 = glm::translate(modelMatrixVirus76, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus77 = glm::translate(modelMatrixVirus77, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus78 = glm::translate(modelMatrixVirus78, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus79 = glm::translate(modelMatrixVirus79, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus80 = glm::translate(modelMatrixVirus80, glm::vec3(0.5f, 0.0f, -0.0f));
			modelMatrixVirus81 = glm::translate(modelMatrixVirus81, glm::vec3(-0.5f, 0.0f, -0.0f));
			modelMatrixVirus82 = glm::translate(modelMatrixVirus82, glm::vec3(0.5f, 0.0f, -0.0f));

			advanceCountVirus2 += 0.5;
			if (advanceCountVirus2 > maxAdvanceVirus2) {
				advanceCountVirus2 = 0;
				stateVirus2 = 2;
			}
			break;

		case 2:
			modelMatrixVirus61 = glm::translate(modelMatrixVirus61, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus62 = glm::translate(modelMatrixVirus62, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus63 = glm::translate(modelMatrixVirus63, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus64 = glm::translate(modelMatrixVirus64, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus65 = glm::translate(modelMatrixVirus65, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus66 = glm::translate(modelMatrixVirus66, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus67 = glm::translate(modelMatrixVirus67, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus68 = glm::translate(modelMatrixVirus68, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus69 = glm::translate(modelMatrixVirus69, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus70 = glm::translate(modelMatrixVirus70, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus71 = glm::translate(modelMatrixVirus71, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus72 = glm::translate(modelMatrixVirus72, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus73 = glm::translate(modelMatrixVirus73, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus74 = glm::translate(modelMatrixVirus74, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus75 = glm::translate(modelMatrixVirus75, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus76 = glm::translate(modelMatrixVirus76, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus77 = glm::translate(modelMatrixVirus77, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus78 = glm::translate(modelMatrixVirus78, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus79 = glm::translate(modelMatrixVirus79, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus80 = glm::translate(modelMatrixVirus80, glm::vec3(-0.5f, 0.0f, 0.0f));
			modelMatrixVirus81 = glm::translate(modelMatrixVirus81, glm::vec3(0.5f, 0.0f, 0.0f));
			modelMatrixVirus82 = glm::translate(modelMatrixVirus82, glm::vec3(-0.5f, 0.0f, 0.0f));

			advanceCountVirus2 += 0.5;
			if (advanceCountVirus2 > maxAdvanceVirus2) {
				advanceCountVirus2 = 0;
				stateVirus2 = 1;
			}
			break;
		default:
			break;
		}

		
	switch (stateVirus3) {

	case 1:
		modelMatrixVirus131 = glm::translate(modelMatrixVirus131, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus132 = glm::translate(modelMatrixVirus132, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus133 = glm::translate(modelMatrixVirus133, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus134 = glm::translate(modelMatrixVirus134, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus135 = glm::translate(modelMatrixVirus135, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus136 = glm::translate(modelMatrixVirus136, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus137 = glm::translate(modelMatrixVirus137, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus138 = glm::translate(modelMatrixVirus138, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus139 = glm::translate(modelMatrixVirus139, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus140 = glm::translate(modelMatrixVirus140, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus141 = glm::translate(modelMatrixVirus141, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus142 = glm::translate(modelMatrixVirus142, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus143 = glm::translate(modelMatrixVirus143, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus144 = glm::translate(modelMatrixVirus144, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus145 = glm::translate(modelMatrixVirus145, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus146 = glm::translate(modelMatrixVirus146, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus147 = glm::translate(modelMatrixVirus147, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus148 = glm::translate(modelMatrixVirus148, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus149 = glm::translate(modelMatrixVirus149, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus150 = glm::translate(modelMatrixVirus150, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus151 = glm::translate(modelMatrixVirus151, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus152 = glm::translate(modelMatrixVirus152, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus153 = glm::translate(modelMatrixVirus153, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus154 = glm::translate(modelMatrixVirus154, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus155 = glm::translate(modelMatrixVirus155, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus156 = glm::translate(modelMatrixVirus156, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus157 = glm::translate(modelMatrixVirus157, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus158 = glm::translate(modelMatrixVirus158, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus159 = glm::translate(modelMatrixVirus159, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus160 = glm::translate(modelMatrixVirus160, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus161 = glm::translate(modelMatrixVirus161, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus162 = glm::translate(modelMatrixVirus162, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus163 = glm::translate(modelMatrixVirus163, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus164 = glm::translate(modelMatrixVirus164, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus165 = glm::translate(modelMatrixVirus165, glm::vec3(-0.7f, 0.0f, -0.0f));

		advanceCountVirus3 += 0.7;
		if (advanceCountVirus3 > maxAdvanceVirus3) {
			advanceCountVirus3 = 0;
			stateVirus3 = 2;
		}
		break;

	case 2:
		modelMatrixVirus131 = glm::translate(modelMatrixVirus131, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus132 = glm::translate(modelMatrixVirus132, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus133 = glm::translate(modelMatrixVirus133, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus134 = glm::translate(modelMatrixVirus134, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus135 = glm::translate(modelMatrixVirus135, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus136 = glm::translate(modelMatrixVirus136, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus137 = glm::translate(modelMatrixVirus137, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus138 = glm::translate(modelMatrixVirus138, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus139 = glm::translate(modelMatrixVirus139, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus140 = glm::translate(modelMatrixVirus140, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus141 = glm::translate(modelMatrixVirus141, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus142 = glm::translate(modelMatrixVirus142, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus143 = glm::translate(modelMatrixVirus143, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus144 = glm::translate(modelMatrixVirus144, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus145 = glm::translate(modelMatrixVirus145, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus146 = glm::translate(modelMatrixVirus146, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus147 = glm::translate(modelMatrixVirus147, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus148 = glm::translate(modelMatrixVirus148, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus149 = glm::translate(modelMatrixVirus149, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus150 = glm::translate(modelMatrixVirus150, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus151 = glm::translate(modelMatrixVirus151, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus152 = glm::translate(modelMatrixVirus152, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus153 = glm::translate(modelMatrixVirus153, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus154 = glm::translate(modelMatrixVirus154, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus155 = glm::translate(modelMatrixVirus155, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus157 = glm::translate(modelMatrixVirus157, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus158 = glm::translate(modelMatrixVirus158, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus159 = glm::translate(modelMatrixVirus159, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus160 = glm::translate(modelMatrixVirus160, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus161 = glm::translate(modelMatrixVirus161, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus162 = glm::translate(modelMatrixVirus162, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus163 = glm::translate(modelMatrixVirus163, glm::vec3(-0.7f, 0.0f, -0.0f));
		modelMatrixVirus164 = glm::translate(modelMatrixVirus164, glm::vec3(0.7f, 0.0f, -0.0f));
		modelMatrixVirus165 = glm::translate(modelMatrixVirus165, glm::vec3(-0.7f, 0.0f, -0.0f));

		advanceCountVirus3 += 0.7;
		if (advanceCountVirus3 > maxAdvanceVirus3) {
			advanceCountVirus3 = 0;
			stateVirus3 = 1;
		}
		break;
	default:
		break;
	}

		glfwSwapBuffers(window);
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}
