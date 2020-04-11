#include "GL_Framework/gl_framework.hpp"
#include "Shader/shader_util.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

Vertex vertices[] =
{
  //Position                    //Color                   //Texcoords
  glm::vec3(0.0f,0.5f,0.f),     glm::vec3(1.f,0.f,0.f),   glm::vec2(0.f,1.f),
  glm::vec3(-0.5f,-0.5f,0.f),   glm::vec3(0.f,1.f,0.f),   glm::vec2(0.f,0.f),
  glm::vec3(0.5f,-0.5f,0.f),    glm::vec3(0.f,0.f,1.f),   glm::vec2(1.f,0.f)
};

unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
  0,1,2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


GLuint shaderProgram;
GLuint vbo, vao, EBO;

void initShadersGL(void)
{
  std::string vertex_shader_file("Shader/simple_vs.glsl");
  std::string fragment_shader_file("Shader/simple_fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(opengl::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(opengl::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = opengl::CreateProgramGL(shaderList);

}

void initVertexBufferGL(void)
{

  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  
  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);


  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray (0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
  glEnableVertexAttribArray(2);
  glBindVertexArray(0);
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray (vao);
  glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

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

  window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Colour Gradient Triangle", NULL, NULL);
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