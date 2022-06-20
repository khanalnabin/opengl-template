#include "../include/VertexBufferLayout.hpp"

VertexBufferLayout::VertexBufferLayout() : m_Stride(0) {}

void VertexBufferLayout::Push(unsigned int type, unsigned int count,
                              unsigned char normalized) {
	VertexBufferElement vbe{type, count, normalized};
	m_Elements.push_back(vbe);
	m_Stride += count * VertexBufferElement::GetSizeOfType(type);
}

void VertexBufferLayout::AddFloat(unsigned int count) {
	Push(GL_FLOAT, count, GL_FALSE);
}
void VertexBufferLayout::AddUnsignedInt(unsigned int count) {
	Push(GL_UNSIGNED_INT, count, GL_FALSE);
}
void VertexBufferLayout::AddUnsignedByte(unsigned int count) {
	Push(GL_UNSIGNED_BYTE, count, GL_TRUE);
}

const std::vector<VertexBufferElement> VertexBufferLayout::GetElements() const {
	return m_Elements;
}

unsigned int VertexBufferLayout::GetStride() const { return m_Stride; }
