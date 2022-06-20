#include "../include/VertexBufferElement.hpp"

unsigned int VertexBufferElement::GetSizeOfType(unsigned int type) {
	switch (type) {
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_UNSIGNED_INT:
		return sizeof(GLuint);
	case GL_UNSIGNED_BYTE:
		return sizeof(GLbyte);
	}
	return 0;
}
