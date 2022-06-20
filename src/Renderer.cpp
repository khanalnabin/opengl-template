#include "../include/Renderer.hpp"

void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib,
                    const Shader &shader, const unsigned int type) const {
	shader.Use();
	va.Bind();
	ib.Bind();
	glDrawElements(type, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
