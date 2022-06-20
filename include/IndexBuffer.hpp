#pragma once

#include<glad/glad.h>

class IndexBuffer {
  public:
	IndexBuffer(const unsigned int *indices, const unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const;

  private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
