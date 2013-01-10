#ifndef _IMAC2GL3_CUBE_HPP_
#define _IMAC2GL3_CUBE_HPP_

#include <GL/glew.h>
#include <vector>

#include "common.hpp"

namespace imac2gl3 {


class Cube {
    static const GLint POSITION_NUM_COMPONENTS = 3;
    static const GLint NORMAL_NUM_COMPONENTS = 3;
    static const GLint TEXCOORDS_NUM_COMPONENTS = 2;
    
    static const GLsizei POSITION_OFFSET = 0;
    static const GLsizei NORMAL_OFFSET = POSITION_NUM_COMPONENTS * sizeof(GLfloat);
    static const GLsizei TEX_COORDS_OFFSET = (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS) * sizeof(GLfloat);
    
    static const GLsizei VERTEX_BYTE_SIZE = 
        (POSITION_NUM_COMPONENTS + NORMAL_NUM_COMPONENTS + TEXCOORDS_NUM_COMPONENTS) * sizeof(GLfloat);    
        
    // Pointeur vers les données du tableau
    ShapeVertex m_pDataPointer[36]; 

    // Alloue et construit les données (implantation dans le .cpp)
    void build(GLfloat size);
    
    
    Cube& operator =(const Cube& cube) {
        return *this;
    }
    
public:
    // Constructeurs: allouent le tableau de données et construit les attributs des vertex
    Cube(){
        build(1.0f); // Construction (voir le .cpp)
    }
    
    Cube(GLfloat size){
        build(size); // Construction (voir le .cpp)
    }

    // Destructeur: désalloue le tableau de données
    ~Cube() {
    }

    // Renvoit le pointeur vers les données
    const GLvoid* getDataPointer() const {
        return m_pDataPointer;
    }
    
    // Renvoit le nombre de vertex
    GLsizei getVertexCount() const {
        return 36;
    }

    // Renvoit la taille du tableau en octets
    GLsizeiptr getByteSize() const {
        return getVertexCount() * VERTEX_BYTE_SIZE; // Nombre de sommet * taille d'un sommet
    }
    
    // Renvoit le nombre de composantes de l'attribut position
    GLint getPositionNumComponents() const {
        return POSITION_NUM_COMPONENTS;
    }
    
    // Renvoit le nombre de composantes de l'attribut normale
    GLint getNormalNumComponents() const {
        return NORMAL_NUM_COMPONENTS;
    }
    
    // Renvoit le nombre de composantes de l'attribut coordonnées de texture
    GLint getTexCoordsNumComponents() const {
        return TEXCOORDS_NUM_COMPONENTS;
    }
    
    // Renvoit la taille d'un vertex en octets
    GLsizei getVertexByteSize() const {
        return VERTEX_BYTE_SIZE;
    }
    
    // Renvoit l'offset de l'attribut position
    const GLvoid* getPositionOffset() const {
        return reinterpret_cast<const GLvoid*>(POSITION_OFFSET);
    }
    
    // Renvoit l'offset de l'attribut normale
    const GLvoid* getNormalOffset() const {
        return reinterpret_cast<const GLvoid*>(NORMAL_OFFSET);
    }
    
    // Renvoit l'offset de l'attribut coordonnées de texture
    const GLvoid* getTexCoordsOffset() const {
        return reinterpret_cast<const GLvoid*>(TEX_COORDS_OFFSET);
    }
    
    // Renvoit le type OpenGL d'une composante d'attribut
    GLenum getDataType() const {
        return GL_FLOAT;
    }
};
    
}

#endif
