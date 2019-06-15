/*  @Daniel Fróes - 10255956
 *  @Augusto Paulo Silva - 9266639
*/


#include <cg_window.hpp>
#include <transform_lib.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "cpp_src/OBJ_Loader.h"
#include <shader.hpp>
#include <stb_image.hpp>

using namespace transform_lib;
using namespace std;

class Demo : public cgicmc::Window { //herdando de Window (cpp_src/cg_window.hpp)

  public:

    Demo() : cgicmc::Window() {} // Construtor da classe Demo igual ao da classe Window

    /*  @Gerencia os inputs do usuário;
        @Parâmetros: translateOffset - coordenadas do próximo deslocamento;
                    angularVel - velocidade em que o catavento irá girar;
                    rotateAble - habilita ou desabilita a rotação dos polígonos;
        @Retorno: void;
    */
    void inputTranslate(vec3* translateOffset )
    {
      /* Inputs para fechar a janela
      */
      if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
      
      /* Inputs para translação
      */
      if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        translateOffset->y += 0.01;
      if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        translateOffset->y -= 0.01;
      if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        translateOffset->x -= 0.01;
      if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        translateOffset->x += 0.01;
      
    }
      /*
      * @inputRotate: gerencia os inputs para a rotação;
      * @PARAMETROS:  rotDir = controla a direção da rotação; rotationAngle - controla as rotações nas 3 dimensões;
      * @RETURN: VOID;
      */
    void inputRotate( int* rotDir, objl::Vector3* rotationAngle )
    {
      //Rotaciona em Z
      if(glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS && glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
            rotationAngle->Z -= 0.1f;
      else if (glfwGetKey(_window, GLFW_KEY_Z) == GLFW_PRESS)
        rotationAngle->Z += 0.1f;
      
      //Rotaciona em Y
      if(glfwGetKey(_window, GLFW_KEY_Y) == GLFW_PRESS && glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
            rotationAngle->Y -= 0.1f;
      else if (glfwGetKey(_window, GLFW_KEY_Y) == GLFW_PRESS)
        rotationAngle->Y += 0.1f;
      
      //Rotaciona em X
      if(glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS && glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
            rotationAngle->X -= 0.1f;
      else if (glfwGetKey(_window, GLFW_KEY_X) == GLFW_PRESS)
        rotationAngle->X += 0.1f;
      
      
      //Muda direção da rotação  
      if(glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        *rotDir *= -1;

    }

      /*
      * @inputScale: controla os inputs da escala;
      * @PARAMETROS: scalefactor - fator de escala;
      * @RETORNO: VOID;
      */  
    void inputScale(vec3* scalefactor)
    {
      //aumenta o modelo
      if(glfwGetKey(_window, GLFW_KEY_M) == GLFW_PRESS)
      {
        scalefactor->x += 0.001; scalefactor->y += 0.001; scalefactor->z += 0.001;
      }

      //diminui o modelo
      if(glfwGetKey(_window, GLFW_KEY_N) == GLFW_PRESS)
      {
        scalefactor->x -= 0.001; scalefactor->y -= 0.001; scalefactor->z -= 0.001;
      }
    }


   /*  @Função do loop de renderização;
    *  @Parâmetros: void;
    *  @Retorno: void;
    */    
    void run() override 
    { 
      vec3 translateOffset = vec3(0,0,0);
      vec3 scaleFactor = vec3(1, 1, 1);
      objl::Vector3 rotationAngle = objl::Vector3 (0.0, 0.0, 0.0);
      int rotDir = 1;


      while (!glfwWindowShouldClose(_window)) // loop de renderização
      { 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Comandos de entrada do teclado
        inputTranslate(&translateOffset);
        inputRotate (&rotDir, &rotationAngle);
        inputScale(&scaleFactor);


        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection    = glm::mat4(1.0f);
        // Comandos de renderizacao vao aqui
        glClearColor(0.5, 0.5f, 1.0f, 1.0f); //seta a cor de fundo da janela
        glClear(GL_COLOR_BUFFER_BIT);

        //Matriz de tranformação inicializa com a identidade
        float model[][MatDim] = {1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 1.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 1.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 1.0f};

        /*Adiciona as transformações a seguir na ordem na matriz de tranformação
        */

        //Translação pelos inputs
        transform_lib::addTranslate(model, translateOffset, false);


        //Translação para a origem
        addTranslate(model, translateOffset, true);

        //Rotação nos eixos
        transform_lib::addRotate(model, rotationAngle.Z, 'z');
        transform_lib::addRotate(model, rotationAngle.Y, 'y');
        transform_lib::addRotate(model, rotationAngle.X, 'x');
 
        //Escala o modelo
        addScale(model, scaleFactor);

        //volta para a origem
        addTranslate(model, translateOffset, false);

        /* Passa a matriz de transformação para o shader
        */
        _shader.useShader(); //Usa o shader program

        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "model") , 1, GL_FALSE, &model[0][0]); 

        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(_shader.getId(), "projection"), 1, GL_FALSE, &projection[0][0]);


        /*
        * Desenha o modelo na janela
        */
        glBindTexture(GL_TEXTURE_2D, _textureBuffer);
        glBindVertexArray(_VAO);
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(_window);
        glfwPollEvents();

      }
    }



     /*
      * @setupMesh: Configura os buffers do openGL;
      * @PARAMETROS: VOID;
      * @RETORNO: VOID;
      */
    void setupBuffers()
    {      
      glGenVertexArrays(1, &_VAO);
      glGenBuffers(1, &_vertVBO);
      glGenBuffers(1, &_EBO);
      glGenBuffers(1, &_texCoordVBO);


    
      glBindVertexArray(_VAO);
        
      glBindBuffer(GL_ARRAY_BUFFER, _vertVBO);
      glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(objl::Vertex), &_vertices[0], GL_STATIC_DRAW);  

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), 
                  &_indices[0], GL_STATIC_DRAW);


      
      // vertex positions
      glEnableVertexAttribArray(0);	
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)0);

      // vertex normals
      // glEnableVertexAttribArray(1);	
      // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)offsetof(objl::Vertex, Normal));
      

      //Texture Coordinates
      glEnableVertexAttribArray(2);	
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)offsetof(objl::Vertex, TextureCoordinate));

      // Parametros da textura
      glGenTextures(1, &_textureBuffer);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, _textureBuffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      float borderColor[] = {0.3, 0.45, 0.18, 1.0};
      glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


      //carrega imagem  
      int width, height, channels;
      unsigned char *image;
      char path[] = "../assets/3d_models/Dog_diffuse.jpg";

      stbi_set_flip_vertically_on_load(true);
      image = stbi_load(path, &width, &height, &channels, 0);
      if (image) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                    GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
      }
      stbi_image_free(image);



      glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      glEnable(GL_DEPTH_TEST);


      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }  

    

     /*
      * @init: inicia as variáveis da mesh;
      * @PARAMETROS: mesh - mesh do modelo;
      * @RETORNO: VOID;
      */
    void init(objl::Mesh mesh)
    {
      _vertices = mesh.Vertices;
      _indices = mesh.Indices;
      for(int i = 0; i < _vertices.size(); i++)
      {
        _vertexTexture.emplace_back(_vertices[i].TextureCoordinate);
      } 
    }

  
   
      /*
       * @loadShaders: Carrega os shaders;
       * @PARAMETROS: VOID;
       * @RETORNO: VOID;
       */ 
    void loadShaders()
    {
      _shader.loadVertexShader("../assets/shaders/texture.vert");
      _shader.loadFragmentShader("../assets/shaders/texture.frag");
    }

     /*
      * @normalize: Normaliza os vertices na janela;
      * @PARAMETROS: VOID;
      * @RETORNO: VOID;
      */
    void normalize()
    {
      objl::Vector3 Max, Min;
      objl::Vector3 vMax,vMin;
      objl::Vector3 scale, t, dist;
      float distMax;
      float wMin, wMax;

      Max = objl::Vector3(_vertices[0].Position.X, _vertices[0].Position.Y, _vertices[0].Position.Z);
      Min = objl::Vector3(_vertices[0].Position.X, _vertices[0].Position.Y, _vertices[0].Position.Z);

      /*
       *Pega as coordenadas maximas e minimas do modelo;
       */
      for (int j = 0; j < _vertices.size(); j++)
      {
        
        //pega as coords maximas
        if(_vertices[j].Position.X>Max.X)
          Max.X = _vertices[j].Position.X;

        if(_vertices[j].Position.Y>Max.Y)
          Max.Y = _vertices[j].Position.Y;

        if(_vertices[j].Position.Z>Max.Z)
          Max.Z = _vertices[j].Position.Z;

        

        //Pega os as coords mínimas
        if(_vertices[j].Position.X<Min.X)
          Min.X = _vertices[j].Position.X;

        if(_vertices[j].Position.Y<Min.Y)
          Min.Y = _vertices[j].Position.Y;
        
        if(_vertices[j].Position.Z<Min.Z)
          Min.Z = _vertices[j].Position.Z;
      }

      //Calcula as distancias da caixa do mundo
      dist = objl::Vector3(abs(Max.X-Min.X), abs(Max.Y-Min.Y), abs(Max.Z-Min.Z));
      
      //Calcula qual é a dimensão mais larga do modelo
      if(dist.X>=dist.Y && dist.X>=dist.Z)
      {
        wMin = Min.X;
        wMax = Max.X;
      }
      else if(dist.Y >= dist.Z)
      {
        wMin = Min.Y;
        wMax = Max.Y;
      }
      else
      {
        wMin = Min.Z;
        wMax = Max.Z;
      }

      //Inicializa a view box
      vMax = objl::Vector3(1.0f, 1.0f, 1.0f);
      vMin = objl::Vector3(-1.0f, -1.0f, -1.0f);
     

      //Calcula a escala e a translação necessária para normalização 
      scale = objl::Vector3((vMax.X - vMin.X)/(wMax - wMin), (vMax.Y - vMin.Y)/(wMax - wMin), (vMax.Z - vMin.Z)/(wMax - wMin) );
      t = objl::Vector3(((wMax*vMin.X) - (wMin*vMax.X))/(wMax - wMin), (scale.Y*Max.Y + scale.Y*Min.Y)/2, (scale.Z*Max.Z + scale.Z*Min.Z)/2);
        

      //Normaliza a bounding box, aplicando as transformações em cada vertice
      for (int j = 0; j < _vertices.size(); j++)
      {
        _vertices[j].Position.X = (scale.X* _vertices[j].Position.X) + t.X;
        _vertices[j].Position.Y = (scale.Y* _vertices[j].Position.Y) - t.Y;
        _vertices[j].Position.Z = (scale.Z* _vertices[j].Position.Z) - t.Z;
      }

 }

  protected:
    cgicmc::Shader _shader; 
    std::vector<objl::Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<objl::Vector2> _vertexTexture;
    unsigned int _vertVBO, _VAO, _EBO, _textureVBO, _texCoordVBO,  _textureBuffer;
};






int main(int argc, char const *argv[])
{
  Demo window;
  window.createWindow(); //Cria a janela
  window.loadShaders(); //Configura os shaders

  objl::Loader Loader;
  //"../assets/3d_models/newdog.obj"

  //carrega o modelo;  
  bool loadout = Loader.LoadFile(argv[1]);

  if(loadout)
  {
    window.init(Loader.LoadedMeshes[0]);
    window.normalize();
    window.setupBuffers();
    window.run();
  }
  else
  {
    printf("erro ao carregar mesh");
    return 1;
  }
  

  
}
