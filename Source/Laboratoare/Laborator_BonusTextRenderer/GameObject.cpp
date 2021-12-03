#include "GameObject.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

int GameObject::worldSize = 2;
int GameObject::topStartingSpeed = 2;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{

}

void GameObject::Initialize() {

	// Give it random position within world
	p = glm::vec3(
		rand() % (worldSize * 2) - worldSize,
		rand() % worldSize + worldSize,
		rand() % (worldSize * 2) - worldSize
	);

	// Give it random acceleration on the xy plane
	v = glm::vec3(
		rand() % (topStartingSpeed * 2) - topStartingSpeed,
		0,
		rand() % (topStartingSpeed * 2) - topStartingSpeed
	);
}

void GameObject::ResetSpeed() {
	// Give it random acceleration on the xy plane
	v = glm::vec3(
		rand() % (topStartingSpeed * 2) - topStartingSpeed,
		0,
		rand() % (topStartingSpeed * 2) - topStartingSpeed
	);
}

void GameObject::Update(float deltaTimeSeconds) {

	// Add Drag to emulate rolling friction
	a.x = -v.x * 0.2f;
	a.z = -v.z * 0.2f;

	// Update Ball physics
	v.x += a.x * deltaTimeSeconds;
	v.z += a.z * deltaTimeSeconds;

	p.x += v.x * deltaTimeSeconds;
	p.z += v.z * deltaTimeSeconds;

	// Gravity
	p.y -= 9.8 * deltaTimeSeconds;
	if (p.y < 0) {
		p.y = 0;
	}

	// Wrap the balls around screen
	if (p.x < -worldSize) {
		p.x = -worldSize;
		v.x = -v.x;
	}

	if (p.x > worldSize) {
		p.x = worldSize;
		v.x = -v.x;
	}

	if (p.z < -worldSize) {	
		p.z = -worldSize;
		v.z = -v.z;
	}
	
	if (p.z > worldSize) { 
		p.z = worldSize;
		v.z = -v.z;
	}

	// Clamp velocity near zero
	if ((v.x * v.x + v.z * v.z) < 0.1f)
	{
		v.x = 0;
		v.z = 0;
	}

}

void GameObject::Move(float x, float y, float z, float deltaTimeSeconds) {

	/*
	p.x += x * speed * deltaTimeSeconds;
	p.y += y * speed * deltaTimeSeconds;
	p.z += z * speed * deltaTimeSeconds;
	*/

	/*
	v.x = x * speed;
	v.y = y * speed;
	v.z = z * speed;
	*/

	if (p.x > worldSize) {
		p.x = worldSize;
	}
	if (p.x < -worldSize) {
		p.x = -worldSize;
	}

	if (p.y > 2 * worldSize) {
		p.y = 2 * worldSize;
	}
	if (p.y < 0) {
		p.y = 0;
	}

	if (p.z > worldSize) {
		p.z = worldSize;
	}
	if (p.z < -worldSize) {
		p.z = -worldSize;
	}
}

bool GameObject::IsColliding(GameObject* other) {

	if (type == 0) {
		// Sphere-sphere collision
		if (other->type == 0) {
			return GameObject::isSphereSphereCollision(this, other);
		}

		// Cube-sphere collision
		if (other->type == 1) {
			return GameObject::isSphereCubeCollision(this, other);
		}
	}

	if (type == 1) {

		// Cube-sphere collision
		if (other->type == 0) {
			return GameObject::isSphereCubeCollision(other, this);
		}

		// Cube-cube collision
		if (other->type == 1) {
			return GameObject::isCubeCubeCollision(this, other);
		}
	}

	return false;
}

bool GameObject::isSphereSphereCollision(GameObject* go1, GameObject* go2) {
	return glm::length(go1->p - go2->p) <= 1.0f;
}

bool GameObject::isSphereCubeCollision(GameObject* sphere, GameObject* cube) {

	float x = std::max(cube->p.x - 0.5f, std::min(sphere->p.x, cube->p.x + 0.5f));
	float y = std::max(cube->p.y - 0.5f, std::min(sphere->p.y, cube->p.y + 0.5f));
	float z = std::max(cube->p.z - 0.5f, std::min(sphere->p.z, cube->p.z + 0.5f));

	float sqrDistance = (x - sphere->p.x) * (x - sphere->p.x) +
		(y - sphere->p.y) * (y - sphere->p.y) +
		(z - sphere->p.z) * (z - sphere->p.z);

	return sqrDistance <= .25f;
}

bool GameObject::isCubeCubeCollision(GameObject* go1, GameObject* go2) {

	if (
		(abs(go1->p.x - go2->p.x) <= 1.0f) && 
		(abs(go1->p.y - go2->p.y) <= 1.0f) && 
		(abs(go1->p.z - go2->p.z) <= 1.0f)
	) {
		return true;
	}

	return false;
}

float GameObject::GetDistance(GameObject* other) {

	float fDistance = sqrtf(
		(p.x - other->p.x) * (p.x - other->p.x) +
		(p.y - other->p.y) * (p.y - other->p.y) +
		(p.z - other->p.z) * (p.z - other->p.z)
	);

	return fDistance;
}


void GameObject::Draw() {

	// Bind model matrix
	modelMatrix = glm::translate(glm::mat4(1), p);
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind color
	modelMatrix = glm::translate(glm::mat4(1), p);
	GLint loc_object_color = glGetUniformLocation(shader->program, "objectColor");
	glUniform3fv(loc_object_color, 1, glm::value_ptr(color));

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

}

void GameObject::Debug() {
	std::cout << p << std::endl;
}