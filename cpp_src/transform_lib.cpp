/*  @Daniel Fróes - 10255956
 *  @Augusto Paulo Silva - 9266639
*/


#include "transform_lib.hpp"

namespace transform_lib
{   /*  @Construtor da classe vec3;
        @Parâmetros: valores das variáveis x, y, z;
    */
    vec3::vec3(GLfloat _x, GLfloat _y, GLfloat _z)
    {
            x = _x;
            y = _y;
            z = _z;
    }


    /*  @Imprime uma matriz na tela;
        @Parâmetros: m[][MatDim] - matriz quadrada;
        @Retorno: void;
    */
    void printM(GLfloat m[][MatDim])
    {
        for(int i = 0; i < MatDim; i++)
        {
            for(int j = 0; j < MatDim; j++ )
            {
                printf("%.2f ", m[i][j]);
            }
            printf("\n");
        }
    }



    /*  @Multiplica duas matrizes na forma res = m1*m2
        @Parâmetros: res - resultado; m1 - matriz 1; m2 - matriz 2;
        @Return: void;
    */
    void multiply(GLfloat res[][MatDim], GLfloat m1[][MatDim], GLfloat m2[][MatDim])
    {   
        GLfloat elem;
        for(int row = 0; row < MatDim; row++)
        {
            for(int column = 0; column < MatDim; column++)
            {
                elem = 0;
                for(int i = 0; i < MatDim; i++)
                    elem += m1[row][i]*m2[i][column];   
    
                res[row][column] = elem;
            }
        }
    }  



    /*  @Adiciona a transformação de tranlação na matriz de transformação;
        @Parâmetros: transformMat - matriz de transformção; Offset - Deslocamento em cada coordenada;
                     isInverted - se verdadeiro, faz a translação inversa;
        @Return: void;
    */
    void addTranslate(GLfloat transformMat[][MatDim], vec3 Offset, bool isInverted)
    {
        GLfloat result[MatDim][MatDim] = {0};
        
        if(isInverted)
        {
            Offset.x *= -1; Offset.y *= -1; Offset.z *= -1; //inverte os offsets invertendo a transformação;
        }
        
        GLfloat translation[][MatDim] = {1.0f, 0.0f, 0.0f, Offset.x,
                                         0.0f, 1.0f, 0.0f, Offset.y,
                                         0.0f, 0.0f, 1.0f, Offset.z,
                                         0.0f, 0.0f, 0.0f, 1.0f     };
        
        multiply(result, translation, transformMat); //adiciona na matriz de transformação
        for(int i = 0; i < MatDim; i++) //copia resultado para matriz de transformação 
        {
            for(int j = 0; j < MatDim; j++)
                transformMat[i][j] = result[i][j];
        }
    }




    /*  @Adiciona a transformação de rotação na matriz de transformação;
        @Parâmetros: transformMat - matriz de transformção; angle - angulo da rotação em graus;
        @Retorno: void;
    */
    void addRotate(GLfloat transformMat[][MatDim], GLfloat angle, char axis)
    {
        GLfloat result[MatDim][MatDim] = {0};
        angle = angle*PI/180; //tranformando graus para radianos
        
        GLfloat rotation[MatDim][MatDim] = {1.0f, 0.0f, 0.0f, 0.0f,
                                            0.0f, 1.0f, 0.0f, 0.0f,
                                            0.0f, 0.0f, 1.0f, 0.0f,
                                            0.0f, 0.0f, 0.0f, 1.0f};

        if      (axis == 'z')//rotação em torno do eixo z
        {
            rotation[0][0] = (GLfloat)cos(angle); rotation[0][1] = (GLfloat)-sin(angle);
            rotation[1][0] = (GLfloat)sin(angle); rotation[1][1] = (GLfloat)cos(angle);
        }
        else if (axis == 'x')//rotação em torno do eixo x
        {
            rotation[1][1] = cos(angle); rotation[1][2] = -sin(angle);
            rotation[2][1] = sin(angle); rotation[2][2] = cos(angle);
        }
        else if (axis == 'y')//rotação em torno do eixo y
        {
            rotation[0][0] = cos(angle); rotation[0][2] = -sin(angle);
            rotation[2][0] = sin(angle); rotation[2][2] = cos(angle);
        }
        
        multiply(result,  rotation, transformMat);//adiciona na matriz de transformação
        
        for(int i = 0; i < MatDim; i++) //copia resultado para matriz de transformação 
        {
            for(int j = 0; j < MatDim; j++)
                transformMat[i][j] = result[i][j];
        }
        
    }
    



    /*  @Adiciona a transformação de Escala na matriz de transformação;
        @Parâmetros: transformMat - matriz de transformção; angle - angulo da rotação em graus;
        @Retorno: void;
    */
    void addScale(GLfloat transformMat[][MatDim], vec3 scaleFactor)
    {
        GLfloat result[MatDim][MatDim] = {0};
        GLfloat scale[MatDim][MatDim] = {scaleFactor.x, 0.0f,  0.0f, 0.0f,
                                        0.0f, scaleFactor.y  ,  0.0f, 0.0f,
                                        0.0f, 0.0f,scaleFactor.z, 0.0f,
                                        0.0f, 0.0f, 0.0f, 1.0f};
       
         
        multiply(result,  scale, transformMat);//adiciona na matriz de transformação
        
        for(int i = 0; i < MatDim; i++) //copia resultado para matriz de transformação 
        {
            for(int j = 0; j < MatDim; j++)
                transformMat[i][j] = result[i][j];
        }
    }



    /*  @Converte uma matriz em um array
        @Parâmetros: mat - matriz a ser convertida
        @Retorno: Ponteiro para o início do array contendo os dados da matriz;
    */
    GLfloat* matrixToPointer(GLfloat mat[][MatDim])
    {
        GLfloat* array = (GLfloat*) calloc(MatDim*MatDim, sizeof(GLfloat));
        int i=0;
        for(int col = 0; col < MatDim; col++)
        {
            for(int row = 0; row < MatDim; row++)
            {
                array[i] = mat[row][col];
                i++;
            }
        }
        
        return array;
    }
   



}

