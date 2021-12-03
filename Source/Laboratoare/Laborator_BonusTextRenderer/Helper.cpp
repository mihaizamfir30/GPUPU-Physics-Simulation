#include "Helper.h"

void Helper::CreateCubeMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int *noVertices, int * noIndices) {

	int vertexIndex = 0;
	int triangleIndex = 0;

	int faces = 6;

	*noVertices = faces * 4;
	*noIndices = faces * 2;

	glm::vec3* vertices = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));
	glm::vec3* normals = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));
	unsigned short* indices = (unsigned short*)malloc(*noIndices * 3 * sizeof(unsigned short));

	unsigned int* trianglesPerVertex = (unsigned int*)malloc(*noVertices * sizeof(unsigned int));
	trianglesPerVertex = (unsigned int*)memset(trianglesPerVertex, 0, *noVertices * sizeof(unsigned int));

	glm::vec3 position = glm::vec3(0, 0, 0);

	// Front face
	position = glm::vec3(-.5f, -.5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, -.5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, .5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, .5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	// Back face
	position = glm::vec3(-.5f, -.5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, -.5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, .5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, .5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	// Left face
	position = glm::vec3(-.5f, -.5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, -.5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, .5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, .5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	// Right face
	position = glm::vec3(.5f, -.5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, -.5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, .5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, .5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	// Bottom face
	position = glm::vec3(-.5f, -.5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, -.5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, -.5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, -.5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	// Top face
	position = glm::vec3(-.5f, .5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, .5f, -.5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-.5f, .5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(.5f, .5f, .5f);
	addVertex(&position, vertices, &vertexIndex);

	// Triangles
	addTriangle(0, 1, 2, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(1, 3, 2, indices, trianglesPerVertex, &triangleIndex);

	addTriangle(4, 6, 5, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(5, 6, 7, indices, trianglesPerVertex, &triangleIndex);

	addTriangle(8, 9, 10, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(9, 11, 10, indices, trianglesPerVertex, &triangleIndex);

	addTriangle(12, 14, 13, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(13, 14, 15, indices, trianglesPerVertex, &triangleIndex);

	addTriangle(16, 17, 18, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(17, 19, 18, indices, trianglesPerVertex, &triangleIndex);

	addTriangle(20, 22, 21, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(21, 22, 23, indices, trianglesPerVertex, &triangleIndex);

	calculateNormals(vertices, normals, indices, trianglesPerVertex, *noVertices, *noIndices);

	*vertices_ptr = vertices;
	*normals_ptr = normals;
	*indices_ptr = indices;
}

void Helper::CreateSphereMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices) {

	int vertexIndex = 0;
	int triangleIndex = 0;

	int resolutionX = 16;
	int resolutionY_half = 16;

	int resolutionY = resolutionY_half * 2 + 1;

	*noVertices = resolutionX * resolutionY + 2;
	*noIndices = 2 * resolutionX * resolutionY;

	glm::vec3 *vertices = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));
	glm::vec3* normals = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));
	unsigned short *indices = (unsigned short*)malloc(*noIndices * 3 * sizeof(unsigned short));

	unsigned int* trianglesPerVertex = (unsigned int*)malloc(*noVertices * sizeof(unsigned int));
	trianglesPerVertex = (unsigned int*)memset(trianglesPerVertex, 0, *noVertices * sizeof(unsigned int));

	float heightMax = .5, heightMin = -.5;

	// Vertices

	// Bottom pole
	glm::vec3 position = glm::vec3(0, heightMin, 0);
	addVertex(&position, vertices, &vertexIndex);

	for (size_t y = 0; y < resolutionY; y++)
	{

		float height = (y + 1) * ((heightMax - heightMin) / (resolutionY + 1)) - (heightMax - heightMin) / 2;

		float a = abs(int(y) - resolutionY_half) / float(resolutionY_half + 1) * (heightMax - heightMin) / 2;
		float c = (heightMax - heightMin) / 2;
		float b = sqrt(c * c - a * a);

		float radius = b;

		for (size_t x = 0; x < resolutionX; x++)
		{
			float angle = (360.0f / resolutionX) * (x - 1);
			position = glm::vec3(sin(glm::radians(angle)) * radius, height, cos(glm::radians(angle)) * radius);

			addVertex(&position, vertices, &vertexIndex);
		}
	}

	// Top pole
	position = glm::vec3(0, heightMax, 0);
	addVertex(&position, vertices, &vertexIndex);

	// Triangles

	// Bottom
	int k;
	for (k = 0; k < resolutionX - 1; k++)
	{
		addTriangle(0, k + 2, k + 1, indices, trianglesPerVertex, &triangleIndex);
	}
	addTriangle(0, 1, k + 1, indices, trianglesPerVertex, &triangleIndex);

	// Quads
	for (size_t i = 0, k = 1; i < resolutionY - 1; i++)
	{
		for (size_t j = 0; j < resolutionX - 1; j++, k++)
		{
			addTriangle(k, k + 1, k + 1 + resolutionX, indices, trianglesPerVertex, &triangleIndex);
			addTriangle(k, k + 1 + resolutionX, k + resolutionX, indices, trianglesPerVertex, &triangleIndex);
		}

		addTriangle(k, k + 1 - resolutionX, k + 1, indices, trianglesPerVertex, &triangleIndex);
		addTriangle(k, k + 1, k + resolutionX, indices, trianglesPerVertex, &triangleIndex);

		k++;
	}

	// Top
	k = (resolutionY - 1) * resolutionX + 1;
	for (size_t i = 0; i < resolutionX - 1; i++, k++)
	{
		addTriangle(k, k + 1, resolutionX * resolutionY + 1, indices, trianglesPerVertex, &triangleIndex);
	}

	addTriangle(k, k - resolutionX + 1, resolutionX * resolutionY + 1, indices, trianglesPerVertex, &triangleIndex);

	calculateNormals(vertices, normals, indices, trianglesPerVertex, *noVertices, *noIndices);

	*vertices_ptr = vertices;
	*normals_ptr = normals;
	*indices_ptr = indices;
}

void Helper::CreateCylinderMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices) {

	int vertexIndex = 0;
	int triangleIndex = 0;

	int resolution = 32;

	*noVertices = 2 * 2 * resolution + 2;
	*noIndices = 4 * resolution;

	glm::vec3* vertices = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));
	glm::vec3* normals = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));

	unsigned short* indices = (unsigned short*)malloc(*noIndices * 3 * sizeof(unsigned short));

	unsigned int* trianglesPerVertex = (unsigned int*)malloc(*noVertices * sizeof(unsigned int));
	trianglesPerVertex = (unsigned int*)memset(trianglesPerVertex, 0, *noVertices * sizeof(unsigned int));

	glm::vec3 position = glm::vec3(0, 0, 0);

	float heightMax = .5f, heightMin = -.5f;
	float radius = (heightMax - heightMin) / 2;

	for (size_t x = 0, y = 0; x < 2; x++) {

		// Center of circle
		float height = x == 0 ? -.5 : .5;
		position = glm::vec3(0, height, 0);
		addVertex(&position, vertices, &vertexIndex);

		int circleCenterIndex = vertexIndex - 1;

		for (size_t k = 0; k < 2; k++, y++)
		{

			for (size_t i = 0; i < resolution; i++) {

				float angle = (360.0f / resolution) * (i - 1);
				position = glm::vec3(sin(glm::radians(angle)) * radius, height, cos(glm::radians(angle)) * radius);
				
				addVertex(&position, vertices, &vertexIndex);

				if (y % 2 == 0) {

					if (y == 0) {
						// Bottom circle
						if (i < resolution - 1) {
							addTriangle(
								circleCenterIndex, circleCenterIndex + i + 2, circleCenterIndex + i + 1,
								indices, trianglesPerVertex, &triangleIndex
							);
						}
						else {
							addTriangle(
								circleCenterIndex, circleCenterIndex + 1, circleCenterIndex + i + 1,
								indices, trianglesPerVertex, &triangleIndex
							);
						}
					}
					else {
						// Top circle
						if (i < resolution - 1) {
							addTriangle(
								circleCenterIndex, circleCenterIndex + i + 1, circleCenterIndex + i + 2,
								indices, trianglesPerVertex, &triangleIndex
							);
						}
						else {
							addTriangle(
								circleCenterIndex, circleCenterIndex + i + 1, circleCenterIndex + 1,
								indices, trianglesPerVertex, &triangleIndex
							);
						}
					}
				}

				// Cylinder body
				if (y == 1) {

					if (i < resolution - 1) {

						addTriangle(
							circleCenterIndex + resolution * k + i + 1,
							circleCenterIndex + resolution * k + i + 2,
							circleCenterIndex + 3 * resolution * k + i + 3,
							indices, trianglesPerVertex, &triangleIndex
						);
						addTriangle(
							circleCenterIndex + resolution * k + i + 1,
							circleCenterIndex + 3 * resolution * k + i + 3,
							circleCenterIndex + 3 * resolution * k + i + 2,
							indices, trianglesPerVertex, &triangleIndex
						);

					}
					else {

						addTriangle(
							circleCenterIndex + resolution * k + i + 1,
							circleCenterIndex + resolution * k + i + 2 - resolution,
							circleCenterIndex + 2 * resolution * k + i + 3,
							indices, trianglesPerVertex, &triangleIndex
						);
						addTriangle(
							circleCenterIndex + resolution * k + i + 1,
							circleCenterIndex + 2 * resolution * k + i + 3,
							circleCenterIndex + 3 * resolution * k + i + 2,
							indices, trianglesPerVertex, &triangleIndex
						);

					}
				}
			}
		}
	}

	calculateNormals(vertices, normals, indices, trianglesPerVertex, *noVertices, *noIndices);

	*vertices_ptr = vertices;
	*normals_ptr = normals;
	*indices_ptr = indices;
}

void Helper::CreateBoxMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices) {
	
	int vertexIndex = 0;
	int triangleIndex = 0;

	int faces = 5;

	*noVertices = faces * 4;
	*noIndices = faces * 2;

	glm::vec3* vertices = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));
	glm::vec3* normals = (glm::vec3*)malloc(*noVertices * sizeof(glm::vec3));

	unsigned short* indices = (unsigned short*)malloc(*noIndices * 3 * sizeof(unsigned short));

	unsigned int* trianglesPerVertex = (unsigned int*)malloc(*noVertices * sizeof(unsigned int));
	trianglesPerVertex = (unsigned int*)memset(trianglesPerVertex, 0, *noVertices * sizeof(unsigned int));

	glm::vec3 position = glm::vec3(0, 0, 0);

	// Front face
	position = glm::vec3(-1.0f, 0.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 0.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-1.0f, 2.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 2.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	// Back face
	position = glm::vec3(-1.0f, 0.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 0.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-1.0f, 2.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 2.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	// Left face
	position = glm::vec3(-1.0f, 0.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-1.0f, 0.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-1.0f, 2.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-1.0f, 2.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	// Right face
	position = glm::vec3(1.0f, 0.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 0.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 2.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 2.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	// Bottom face
	position = glm::vec3(-1.0f, 0.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 0.0f, -1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(-1.0f, 0.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);

	position = glm::vec3(1.0f, 0.0f, 1.0f);
	addVertex(&position, vertices, &vertexIndex);


	//http://www.songho.ca/math/quaternion/quaternion.html


	/*
	// Front
	addTriangle(0, 1, 2, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(1, 3, 2, indices, trianglesPerVertex, &triangleIndex);

	// Back
	addTriangle(4, 6, 5, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(5, 6, 7, indices, trianglesPerVertex, &triangleIndex);

	// Left
	addTriangle(8, 9, 10, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(9, 11, 10, indices, trianglesPerVertex, &triangleIndex);

	// Right
	addTriangle(12, 14, 13, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(13, 14, 15, indices, trianglesPerVertex, &triangleIndex);

	// Bottom
	addTriangle(16, 17, 18, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(17, 19, 18, indices, trianglesPerVertex, &triangleIndex);
	
	*/

	// Triangles
	// Front
	addTriangle(0, 2, 1, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(1, 2, 3, indices, trianglesPerVertex, &triangleIndex);

	// Back
	addTriangle(4, 5, 6, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(5, 7, 6, indices, trianglesPerVertex, &triangleIndex);

	// Left
	addTriangle(8, 10, 9, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(9, 10, 11, indices, trianglesPerVertex, &triangleIndex);

	// Right
	addTriangle(12, 13, 14, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(13, 15, 14, indices, trianglesPerVertex, &triangleIndex);

	// Bottom
	addTriangle(16, 18, 17, indices, trianglesPerVertex, &triangleIndex);
	addTriangle(17, 18, 19, indices, trianglesPerVertex, &triangleIndex);

	calculateNormals(vertices, normals, indices, trianglesPerVertex, *noVertices, *noIndices);

	*vertices_ptr = vertices;
	*normals_ptr = normals;
	*indices_ptr = indices;

}

void Helper::addVertex(glm::vec3* position, glm::vec3* vertices, int* vertexIndex) {
	vertices[*vertexIndex] = *position;
	(*vertexIndex)++;
}

void Helper::addTriangle(unsigned int a, unsigned int b, unsigned int c, unsigned short* indices, unsigned int* trianglesPerVertex, int* triangleIndex) {
	indices[*triangleIndex * 3 + 0] = a;
	indices[*triangleIndex * 3 + 1] = b;
	indices[*triangleIndex * 3 + 2] = c;

	(*triangleIndex)++;

	trianglesPerVertex[a] += 1;
	trianglesPerVertex[b] += 1;
	trianglesPerVertex[c] += 1;
}

void Helper::calculateNormals(glm::vec3* vertices, glm::vec3* normals, unsigned short* indices, unsigned int* trianglesPerVertex, int noVertices, int noIndices) {

	for (size_t i = 0; i < noVertices; i++)
	{
		normals[i] = glm::vec3(0);
	}

	for (size_t i = 0; i < noIndices; i++)
	{
		unsigned int i0 = indices[i * 3 + 0];
		unsigned int i1 = indices[i * 3 + 1];
		unsigned int i2 = indices[i * 3 + 2];

		glm::vec3 p0 = vertices[i0];
		glm::vec3 p1 = vertices[i1];
		glm::vec3 p2 = vertices[i2];

		glm::vec3 normal = glm::cross(p1 - p0, p2 - p0);

		normals[i0] += normal;
		normals[i1] += normal;
		normals[i2] += normal;
	}

	for (size_t i = 0; i < noVertices; i++) {

		normals[i] /= trianglesPerVertex[i];

		float magnitude = sqrt(
			normals[i].x * normals[i].x +
			normals[i].y * normals[i].y +
			normals[i].z * normals[i].z
		);

		normals[i] /= magnitude;
	}

}