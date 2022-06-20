#pragma once

#include <glad/glad.h>

class VertexBufferElement {
  public:
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type);
};
