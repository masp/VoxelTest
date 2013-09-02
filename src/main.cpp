#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "world/chunk.hpp"
#include "utils/Resources.hpp"
#include "input/camera.hpp"
#include "utils/GLError.hpp"
#include "renderer/shaders/shader.hpp"
#include "renderer/shaders/program.hpp"
#include "renderer/graphics/texture.hpp"
#include "renderer/renderer.hpp"

using std::cout;
using std::endl;

Renderer renderer;
Texture texture;
Camera camera(glm::vec3(0.0f, 0.0f, 80.0f));


Program program;
Shader vertexShader(GL_VERTEX_SHADER);
Shader fragmentShader(GL_FRAGMENT_SHADER); 

GLint wWidth = 800;
GLint wHeight = 600;

GLuint mvpLocation;
Chunk chunk;

int gameState = 0; // 0 unpaused, 1 paused
void mouseMoved(GLFWwindow* window, double mouseX, double mouseY)
{
	if (gameState == 1) return;	
    if ((int) mouseX == wWidth / 2 && (int) mouseY == wHeight / 2) return;
    double diffX = (mouseX - (wWidth / 2)) / 10.0f;
    double diffY = (mouseY - (wHeight / 2)) / 10.0f;

    camera.changeLook(diffY, diffX);
    program.setUniform("mvp", camera.matrix());
    glfwSetCursorPos(window, wWidth / 2, wHeight / 2);
}

void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, 1);
		if (key == GLFW_KEY_R)
		{
			camera.reset();
			program.setUniform("mvp", camera.matrix());
		}
		else if (key == GLFW_KEY_P)
		{
			if (gameState == 0) gameState = 1; 		
			else if (gameState == 1) gameState = 0;
		}
    }
}

void reshape(GLFWwindow* window, GLint width, GLint height)
{
    wWidth = width;
    wHeight = height;

    glViewport(0, 0, (GLsizei) wWidth, (GLsizei) wHeight);
    
    camera.setAspectRatio((GLfloat) width / (GLfloat) height);
    program.setUniform("mvp", camera.matrix());
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer.renderMesh(chunk.mesh());

    check_gl_error();	
}

void initGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    program.init();
    vertexShader.init();
    fragmentShader.init();

    vertexShader.loadShader(getFileContents("../shaders/vertex.glsl"));		
    fragmentShader.loadShader(getFileContents("../shaders/fragment.glsl"));
    program.attachShader(vertexShader);
    program.attachShader(fragmentShader);

    program.link();
    program.use();

	texture.loadTexture("../resources/crate.png");	
	texture.upload(program, "tex");

    chunk.build();
}

void uninitGL()
{
}

static void error_callback(int error, const char * message)
{
    cout << error << ": " << message << endl;
}


int main()
{
    GLFWwindow* window; 

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
	exit(EXIT_FAILURE);

    window = glfwCreateWindow(wWidth, wHeight, "Makeshift - v0001a", NULL, NULL);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    if (!window)
    {
	glfwTerminate();
	exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, keyPressed);
    glfwSetCursorPosCallback(window, mouseMoved);
    glfwSetFramebufferSizeCallback(window, reshape);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
	return 1;
    }

    glfwGetFramebufferSize(window, &wWidth, &wHeight); 
    initGL();
    reshape(window, wWidth, wHeight);
    glfwSetCursorPos(window, wWidth, wHeight);

    while (!glfwWindowShouldClose(window))
    {
	draw();	
	
	
	glfwSwapBuffers(window);
	glfwPollEvents();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
	    camera.move(camera.forward());
	    program.setUniform("mvp", camera.matrix());
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
	    camera.move(-camera.forward());
	    program.setUniform("mvp", camera.matrix());
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
	    camera.move(camera.right());
	    program.setUniform("mvp", camera.matrix());
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
	    camera.move(-camera.right());
	    program.setUniform("mvp", camera.matrix());
	}
    }

    uninitGL();
    glfwTerminate();
    return 0;
}
