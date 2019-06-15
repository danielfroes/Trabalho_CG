/*  @Daniel Fróes - 10255956
 *  @Augusto Paulo Silva - 9266639
*/

#ifndef __TRANSFORM_LIB_HPP__
#define __TRANSFORM_LIB_HPP__

#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>

#define PI 3.14159265 
#define MatDim 4 //Define a dimensão das matrizes

namespace transform_lib
{
    
    class vec3 //classe vec3
    {
        public:
            GLfloat x, y, z;
        
            vec3(GLfloat _x, GLfloat _y, GLfloat _z);
    };
    
    void printM(GLfloat m[][MatDim]);
    void addMultiply(GLfloat m1[][MatDim], GLfloat m2[][MatDim]);
    void addTranslate(GLfloat transformMat[][MatDim], vec3 Offset, bool isInverted);
    void addRotate(GLfloat transformMat[][MatDim], GLfloat angle, char axis);
    void addScale(GLfloat transformMat[][MatDim], vec3 scaleFactor);
    GLfloat* matrixToPointer(GLfloat mat[][MatDim]);
}

#endif
