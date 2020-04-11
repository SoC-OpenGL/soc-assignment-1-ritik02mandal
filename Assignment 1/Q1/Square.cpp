#include "GL_Framework/gl_framework.hpp"
#include "Shader/shader_util.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

float points[]={
                 0.8f,0.8f,0.0f,
		             0.8f,-0.8f,0.0f,
     	          -0.8f,-0.8f,0.0f,
		            -0.8f,0.8f,0.0f,
     	          -0.8f,-0.8f,0.0f,
		             0.8f,0.8f,0.0f
	             };

GLuint shaderProgram;
GLuint vbo, vao;

void initShadersGL(void)
{
  std::string vertex_shader_file("Shader/simple_vs.glsl");
  std::string fragment_shader_file("Shader/window_simple_fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(opengl::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(opengl::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = opengl::CreateProgramGL(shaderList);

}

void initVertexBufferGL(void)
{
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, 18* sizeof (float), points, GL_STATIC_DRAW);

  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray (vao);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(int argc, char** argv)
{
  GLFWwindow* window;

  glfwSetErrorCallback(opengl::error_callback);

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "A SQUARE", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  glfwSetKeyCallback(window, opengl::key_callback);
  glfwSetFramebufferSizeCallback(window, opengl::framebuffer_size_callback);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  opengl::initGL();
  initShadersGL();
  initVertexBufferGL();

  while (glfwWindowShouldClose(window) == 0)
    {
       
      renderGL();

      glfwSwapBuffers(window);
      
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}