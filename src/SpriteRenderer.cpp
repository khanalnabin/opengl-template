#include "../include/SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Shader &shader) : m_Shader(shader) {
	InitRenderData();
}

SpriteRenderer::~SpriteRenderer() { glDeleteVertexArrays(1, &m_QuadVAO); }

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position,
                                glm::vec2 size, float rotate, glm::vec3 color) {
	m_Shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));
	model =
	    glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model =
	    glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model =
	    glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	m_Shader.SetMat4("model", model);

	m_Shader.SetVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(m_QuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
void SpriteRenderer::InitRenderData() {
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
	    // pos      // tex
	    0.0f, 1.0f, 0.0f, 1.0f, // one
	    1.0f, 0.0f, 1.0f, 0.0f, // two
	    0.0f, 0.0f, 0.0f, 0.0f, // three
	    0.0f, 1.0f, 0.0f, 1.0f, // one
	    1.0f, 1.0f, 1.0f, 1.0f, // two
	    1.0f, 0.0f, 1.0f, 0.0f  // three
	};

	glGenVertexArrays(1, &m_QuadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(m_QuadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
	                      (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
