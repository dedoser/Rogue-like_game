#include "common.h"
#include "Image.h"
#include "Player.h"
#include "Room.h"
#include "Game.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <unistd.h>

constexpr GLsizei WINDOW_WIDTH = 1440, WINDOW_HEIGHT = 992;
Player *player;
struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	  case GLFW_KEY_ESCAPE:
	  	if (action == GLFW_PRESS)
	  		glfwSetWindowShouldClose(window, GL_TRUE);
		  break;
    case GLFW_KEY_1:
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      break;
    case GLFW_KEY_2:
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      break;
	  default:
		  if (action == GLFW_PRESS)
        Input.keys[key] = true;
		  else if (action == GLFW_RELEASE)
        Input.keys[key] = false;
	}
}

void processPlayerMovement(Player &player)
{
  if (Input.keys[GLFW_KEY_W])
    player.ProcessInput(MovementDir::UP);
  else if (Input.keys[GLFW_KEY_S])
    player.ProcessInput(MovementDir::DOWN);
  else if (Input.keys[GLFW_KEY_A])
    player.ProcessInput(MovementDir::LEFT);
  else if (Input.keys[GLFW_KEY_D])
    player.ProcessInput(MovementDir::RIGHT);
  else if (Input.keys[GLFW_KEY_SPACE])
    player.OpenDoor();
  if (Input.keys[GLFW_KEY_E])
    player.GetKey();
}

int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;

	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback        (window, OnKeyboardPressed);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();
  Game game;
  
  player = game.ret_player();
	Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
  // printf("%d %d\n", screenBuffer.Width(), screenBuffer.Height());
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;

  //game loop
  int tmp = WINDOW_HEIGHT;
  std::cout << "Controls: "<< std::endl;
  std::cout << "W, A, S, D - movement  "<< std::endl;
  std::cout << "E - take key" << std::endl;
  std::cout << "SPACE - open doors" << std::endl;
  std::cout << "press ESC to exit" << std::endl;
	while (!glfwWindowShouldClose(window))
	{
    GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    if (player->NeedChange())
    {
      game.change_room();
    }
    if (game.ret_anim())
    {
      game.disapear(screenBuffer, WINDOW_WIDTH, tmp);
      if (tmp == 0)
        tmp = WINDOW_HEIGHT;
    }
    else
    {
      glfwPollEvents();
      processPlayerMovement(*player);
      player->ChangeText();
      game.draw(screenBuffer);
    }
    // for (int i = 0; i < WINDOW_HEIGHT; ++i)
    //   for (int j = 0; j < WINDOW_WIDTH - 100; ++j)
    //     screenBuffer.PutPixel(j, i, Pixel {.r = 255, .g = 255, .b = 255, .a = 255});
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
    glDrawPixels (WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
