#include "mesh_data.h"

namespace graphics
{

    void PolygonMeshData::AddVertices (const size_t& size, float* data)
    {
        for (uint i=0; i<size;) {
            vec3 vertex;
            vertex.x = data[++i];
            vertex.y = data[++i];
            vertex.z = data[++i];

            vertices.emplace_back (vertex);
        }
    }

    void PolygonMeshData::AddTriangle (const uint& a, const uint& b, const uint& c)
    {
        indices.emplace_back (a);
        indices.emplace_back (b);
        indices.emplace_back (c);
    }

    void OpenGLMeshData::GenBuffers (uint VAOsize, uint VBOsize, uint EBOsize)
    {
        DeleteBuffers ();

        this->VAOsize = VAOsize;
        this->VBOsize = VBOsize;
        this->EBOsize = EBOsize;

        VAOs = new GLuint[VAOsize];
        VBOs = new GLuint[VBOsize];
        EBOs = new GLuint[EBOsize];

        glGenVertexArrays (VAOsize, VAOs);
        glGenBuffers (VBOsize, VBOs);
        glGenBuffers (EBOsize, EBOs);
    }

    void OpenGLMeshData::DeleteBuffers ()
    {
        if (VAOsize > 0) {
            glDeleteVertexArrays (VAOsize, VAOs);
            delete [] VAOs;
            VAOsize = 0;
        }
        if (VBOsize > 0) {
            glDeleteBuffers (VBOsize, VBOs);
            delete [] VBOs;
            VBOsize = 0;
        }
        if (EBOsize > 0) {
            glDeleteBuffers (EBOsize, EBOs);
            delete [] EBOs;
            EBOsize = 0;
        }
    }

    void OpenGLMeshData::AddArraySubData (uint loc, uint size, GLfloat* data)
    {
        glBindBuffer (GL_ARRAY_BUFFER, VBOs[loc]);
        glBufferSubData (GL_ARRAY_BUFFER, 0, size * sizeof (data[0]), data);
        glBindBuffer (GL_ARRAY_BUFFER, 0);
    }

    void OpenGLMeshData::AddElementSubData (uint loc, uint size, GLuint* data)
    {
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBOs[loc]);
        glBufferSubData (GL_ELEMENT_ARRAY_BUFFER, 0, size * sizeof (data[0]), data);
    }

    void OpenGLMeshData::AddArrayBuffer (uint loc, uint size, GLfloat* data, GLuint flag, GLuint type, uint count)
    {
        // Put array data in GPU memory
        glBindBuffer (GL_ARRAY_BUFFER, VBOs[loc]);
        glBufferData (GL_ARRAY_BUFFER, size, data, flag);

        glEnableVertexAttribArray (loc);
        glVertexAttribPointer (loc, count, type, GL_FALSE, count * sizeof (GLfloat), NULL);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGLMeshData::AddElementBuffer (uint loc, uint size, GLuint* data, GLuint flag)
    {
        // Put element data in GPU memory
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBOs[loc]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, size, data, flag);
    }

    void OpenGLMeshData::Draw (GLuint flag)
    {
        OpenGLMeshData::Draw (flag, drawCount, useIndices);
    }

    void OpenGLMeshData::Draw (GLuint flag, GLuint drawCount, bool useIndices)
    {
        for (uint i=0; i<VAOsize; ++i) {
            glBindVertexArray (VAOs[i]);
            if (useIndices) {
                glDrawElements (flag, drawCount, GL_UNSIGNED_INT, 0);
            } else {
                glDrawArrays (flag, 0, drawCount);
            }
        }
        glBindVertexArray (0);
    }

}