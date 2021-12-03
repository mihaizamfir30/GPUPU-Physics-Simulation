#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include <iostream>

class Helper {

public:

	static void CreateCubeMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices);
	static void CreateSphereMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices);
	static void CreateCylinderMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices);
	static void CreateBoxMesh(glm::vec3** vertices_ptr, glm::vec3** normals_ptr, unsigned short** indices_ptr, int* noVertices, int* noIndices);

	static void addVertex(glm::vec3* position, glm::vec3* vertices, int* vertexIndex);

	static void addTriangle(unsigned int a, unsigned int b, unsigned int c, unsigned short* indices, unsigned int* trianglesPerVertex, int* triangleIndex);

	static void calculateNormals(glm::vec3* vertices, glm::vec3* normals, unsigned short* indices, unsigned int* trianglesPerVertex, int noVertices, int noIndices);

};