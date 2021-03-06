#ifndef RENDER_DEVICE_GL_H
#define RENDER_DEVICE_GL_H
#include "../gl_utility.h"

namespace jade
{
    class VertexBufferGL
    {
    public:
        VertexBufferGL();
        ~VertexBufferGL();

        GLuint vboID;
    };

    class IndexBufferGL
    {
    public:
        IndexBufferGL();
        ~IndexBufferGL();

        GLuint iboID;
    };

	class Texture2DGL
	{
	public:
		Texture2DGL();
		~Texture2DGL();

		GLuint id;
	};

    typedef VertexBufferGL VertexBufferImpl;
    typedef IndexBufferGL IndexBufferImpl;
	typedef Texture2DGL Texture2DImpl;

}

#endif