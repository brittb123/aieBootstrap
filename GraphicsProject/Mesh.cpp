#include "Mesh.h"

Mesh::Mesh()
{
	m_transform = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	m_tricount = 0;
	m_vertexArrayObject = 0;
	m_vertexBufferObject = 0;
	m_indexBufferObject = 0;

}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteBuffers(1, &m_indexBufferObject);
}

void Mesh::start()
{

	assert(m_vertexArrayObject == 0);

	// Generate Buffers
	glGenBuffers(1, &m_vertexBufferObject);
	glGenVertexArrays(1, &m_vertexArrayObject);

	// Binds the vertex array
	glBindVertexArray(m_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);



	////Define the vertices for a quad
	//Vertex vertices[6];
	//m_tricount = 2;
	////triangle 0
	//vertices[0].position = { -0.5f, 0.0f, 0.5f, 1.0f };
	//vertices[1].position = { 0.5f, 0.0f, 0.5f, 1.0f };
	//vertices[2].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	////triangle 1
	//vertices[3].position = { 0.5f, 0.0f, 0.5f, 1.0f };
	//vertices[4].position = { -0.5f, 0.0f, -0.5f, 1.0f };
	//vertices[5].position = { 0.5f, 0.0f, -0.5f, 1.0f };

	// Generates the vertices
	unsigned int vertexCount;
	Vertex* vertices = generateVertices(vertexCount, m_tricount);


	// Fill vertex buffer
	glBufferData
	(
		GL_ARRAY_BUFFER,				// The Type of buffer
		sizeof(Vertex) * vertexCount,   // The size in bytes of all vertices
		vertices,						// All vertices
		GL_STATIC_DRAW					// How the data will be updated
	);

	unsigned int memoryPosition = 0u;
	// Enable vertex position as first attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer
	(
		0,							// The attribute index
		4,							// Number of values in attribute
		GL_FLOAT,					// Type of each value
		GL_FALSE,					// Whether to normalize
		sizeof(Vertex),				// Size in bytes of one vertex
		(void*)memoryPosition		// Memory position of the attribute
	);
	memoryPosition += sizeof(Vertex::position);
	// Enables vertex notmsl as second attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer
	(
		1,							// The index of the attribute
		4,							// The number of values within the attribute
		GL_FLOAT,					// Type of each value
		GL_TRUE,					// Determines to normalize
		sizeof(Vertex),				// Size in bytes of one vertex
		(void*)memoryPosition		// Memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::normal);

	//Enabale vertex texture as third attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,							// Attribute index
		2,							// Number of values in attribute
		GL_FLOAT,					// Type of each value
		GL_FALSE,					// Whether to normalize
		sizeof(Vertex),				// Size in byts of one vertex
		(void*)memoryPosition		// Memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::texCoord);

	//Enabale vertex tangent as fourth attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,							// Attribute index
		4,							// Number of values in attribute
		GL_FLOAT,					// Type of each value
		GL_TRUE,					// Whether to normalize
		sizeof(Vertex),				// Size in byts of one vertex
		(void*)memoryPosition		// Memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::tangent);

	//Enabale vertex color as fourth attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4,							// Attribute index
		4,							// Number of values in attribute
		GL_FLOAT,					// Type of each value
		GL_FALSE,					// Whether to normalize
		sizeof(Vertex),				// Size in byts of one vertex
		(void*)memoryPosition		// Memory position of this attribute
	);
	memoryPosition += sizeof(Vertex::color);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	 //Deallocate Vertices
	delete[] vertices;
}

void Mesh::draw(aie::ShaderProgram* shader)
{
	shader->bindUniform("modelMatrix", m_transform);
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, m_tricount * 3);
}