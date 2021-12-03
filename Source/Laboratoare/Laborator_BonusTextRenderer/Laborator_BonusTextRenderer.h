#pragma once

#include <Component/SimpleScene.h>
#include <TextRenderer/TextRenderer.h>

#include "Helper.h"
#include "GameObject.h"

class Laborator_BonusTextRenderer : public SimpleScene
{
	public:
		Laborator_BonusTextRenderer();
		~Laborator_BonusTextRenderer();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		// Draw the hud
		void drawHud();

		void ResetSpeed();
		void AddSphere();
		void AddCube();
		void AddCylinder();

		float deltaTime;

		Mesh* sphereMesh;
		Mesh* cubeMesh;
		Mesh* cylinderMesh;
		Mesh* boxMesh;

		// Light stuff
		glm::vec3 lightPosition1 = glm::vec3(0, worldSize / 2, 0);
		glm::vec3 lightColor1 = glm::vec3(1, 1, 1);

		glm::vec3 lightPosition2 = glm::vec3(1, 0, 0);
		glm::vec3 lightColor2 = glm::vec3(1, 1, 1);

		glm::vec3 colors[4] = {
			glm::vec3(0.85f, 0.14f, 0.09f),
			glm::vec3(1.00f, 0.84f, 0.00f),
			glm::vec3(0, 0, 1),
			glm::vec3(0.30f, 0.46f, 0.72f)
		};

		int topStartingSpeed = 35.0f;
		float worldSize = 25.0f;
		float cameraSpeed = 10.0f;

		// Scenarios
		int scenarioId = -1;

		int noGameObjects;
		int noSpheres;
		int noCubes;
		int noCylinders;

		// Scenario 1
		int noSpheres1 = 100;
		int noCubes1 = 250;
		int noCylinders1 = 500;

		// Scenario 2
		int noSpheres2 = 250;
		int noCubes2 = 500;
		int noCylinders2 = 1000;

		// Scenario 3
		int noSpheres3 = 500;
		int noCubes3 = 1000;
		int noCylinders3 = 2500;

		Shader* shader;

		int framerate = 123;
		float frameRateTimer = 1.0f;
		int noFrames = 0;

		void UpdateFramerate(float deltaTimeSeconds);

		// GameObjects
		std::vector<GameObject*> gameObjects;
		std::vector<GameObject*>::iterator go_it1;
		std::vector<GameObject*>::iterator go_it2;

		// Game Object radius
		float radius = 0.5f;

		// Box
		glm::mat4 box_model_matrix;

		// The text renderer
		TextRenderer  *Text;

		// Draw primitives mode
		GLenum polygonMode;
};
