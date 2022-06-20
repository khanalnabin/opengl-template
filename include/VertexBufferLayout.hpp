#pragma once

#include <glad/glad.h>

#include <vector>

#include "VertexBufferElement.hpp"

class VertexBufferLayout {
  private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;

  public:
	VertexBufferLayout();
	void AddFloat(unsigned int count);
	void AddUnsignedInt(unsigned int count);
	void AddUnsignedByte(unsigned int count);

	const std::vector<VertexBufferElement> GetElements() const;
	unsigned int GetStride() const;

  private:
	void Push(unsigned int type, unsigned int count, unsigned char normalized);
};
