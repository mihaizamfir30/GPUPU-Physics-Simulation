#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

class GameObject
{
	public:
		GameObject();
		~GameObject();

		void Initialize();
		void ResetSpeed();

		void Update(float deltaTimeSeconds);
		void Draw();

		void Move(float x, float y, float z, float deltaTimeSeconds);

		bool IsColliding(GameObject* other);
		float GetDistance(GameObject* other);

		void Debug();

		glm::mat4 modelMatrix;

		Mesh* mesh;
		Shader* shader;

		static int topStartingSpeed;
		static int worldSize;

		int type; // 0 - Sphere, 1 - Cube, 2 - Cylinder

		float mass = 1.0f;
		float radius = 1.0f;

		float speed = 20;

		glm::vec3 color;

		glm::vec3 p;
		glm::vec3 v;
		glm::vec3 a;

	private:
		static bool isSphereSphereCollision(GameObject* go1, GameObject* go2);
		static bool isSphereCubeCollision(GameObject* sphere, GameObject* cube);
		static bool isCubeCubeCollision(GameObject* go1, GameObject* go2);

};
