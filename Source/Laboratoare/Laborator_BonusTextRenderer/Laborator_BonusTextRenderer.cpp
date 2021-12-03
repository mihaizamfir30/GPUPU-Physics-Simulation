#include "Laborator_BonusTextRenderer.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator_BonusTextRenderer::Laborator_BonusTextRenderer()
{
}

Laborator_BonusTextRenderer::~Laborator_BonusTextRenderer()
{
}

void Laborator_BonusTextRenderer::Init()
{

	// Create a shader program for drawing face polygon with the color of the normal
	shader = new Shader("ShaderLab9");
	shader->AddShader("Source/Laboratoare/Laborator9/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
	shader->AddShader("Source/Laboratoare/Laborator9/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

	// Set shader uniforms	
	glUseProgram(shader->program);

	GLint loc_light_position1 = glGetUniformLocation(shader->program, "lightPosition1");
	glUniform3fv(loc_light_position1, 1, glm::value_ptr(lightPosition1));

	GLint loc_light_color1 = glGetUniformLocation(shader->program, "lightColor1");
	glUniform3fv(loc_light_color1, 1, glm::value_ptr(lightColor1));

	GLint loc_light_position2 = glGetUniformLocation(shader->program, "lightPosition2");
	glUniform3fv(loc_light_position2, 1, glm::value_ptr(lightPosition2));

	GLint loc_light_color2 = glGetUniformLocation(shader->program, "lightColor2");
	glUniform3fv(loc_light_color2, 1, glm::value_ptr(lightColor2));

	// Set up culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Create meshes
	{
		cubeMesh = new Mesh("cube");

		int noVertices;
		int noIndices;

		glm::vec3* vertices;
		glm::vec3* normals;
		unsigned short* indices;

		Helper::CreateCubeMesh(&vertices, &normals, &indices, &noVertices, &noIndices);

		std::vector<glm::vec3> vec_vertices(vertices, vertices + noVertices);
		std::vector<glm::vec3> vec_normals(normals, normals + noVertices);
		std::vector<unsigned short> vec_indices(indices, indices + noIndices * 3);

		cubeMesh->InitFromData(vec_vertices, vec_normals, vec_indices);
		meshes[cubeMesh->GetMeshID()] = cubeMesh;
	}

	{
		sphereMesh = new Mesh("sphere");

		int noVertices;
		int noIndices;

		glm::vec3* vertices;
		glm::vec3* normals;
		unsigned short* indices;

		Helper::CreateSphereMesh(&vertices, &normals, &indices, &noVertices, &noIndices);

		std::vector<glm::vec3> vec_vertices(vertices, vertices + noVertices);
		std::vector<glm::vec3> vec_normals(normals, normals + noVertices);
		std::vector<unsigned short> vec_indices(indices, indices + noIndices * 3);

		sphereMesh->InitFromData(vec_vertices, vec_normals, vec_indices);
		meshes[sphereMesh->GetMeshID()] = sphereMesh;
	}

	{
		cylinderMesh = new Mesh("cylinder");

		int noVertices;
		int noIndices;

		glm::vec3* vertices;
		glm::vec3* normals;
		unsigned short* indices;

		Helper::CreateCylinderMesh(&vertices, &normals, &indices, &noVertices, &noIndices);

		std::vector<glm::vec3> vec_vertices(vertices, vertices + noVertices);
		std::vector<glm::vec3> vec_normals(normals, normals + noVertices);
		std::vector<unsigned short> vec_indices(indices, indices + noIndices * 3);

		cylinderMesh->InitFromData(vec_vertices, vec_normals, vec_indices);
		meshes[cylinderMesh->GetMeshID()] = cylinderMesh;
	}

	{
		boxMesh = new Mesh("box");

		int noVertices;
		int noIndices;

		glm::vec3* vertices;
		glm::vec3* normals;
		unsigned short* indices;

		Helper::CreateBoxMesh(&vertices, &normals, &indices, &noVertices, &noIndices);

		std::vector<glm::vec3> vec_vertices(vertices, vertices + noVertices);
		std::vector<glm::vec3> vec_normals(normals, normals + noVertices);
		std::vector<unsigned short> vec_indices(indices, indices + noIndices * 3);

		boxMesh->InitFromData(vec_vertices, vec_normals, vec_indices);
		meshes[boxMesh->GetMeshID()] = boxMesh;
	}

	// Create Game Objects

	GameObject::worldSize = worldSize;
	GameObject::topStartingSpeed = topStartingSpeed;

	noSpheres = scenarioId == 1 ? noSpheres1 : scenarioId == 2 ? noSpheres2 : scenarioId == 3 ? noSpheres3 : 0;
	noCubes = scenarioId == 1 ? noCubes1 : scenarioId == 2 ? noCubes2 : scenarioId == 3 ? noCubes3 : 0;
	noCylinders = scenarioId == 1 ? noCylinders1 : scenarioId == 2 ? noCylinders2 : scenarioId == 3 ? noCylinders3 : 0;

	noGameObjects = noSpheres + noCubes + noCylinders;

	gameObjects.reserve(noGameObjects);

	// Seed rng
	srand(time(NULL));

	// Initialize spheres
	for (size_t i = 0; i < noSpheres; i++)
	{
		GameObject* go = new GameObject();
		go->mesh = sphereMesh;
		go->shader = shader;
		go->type = 0;
		go->radius = 0.5f;
		go->color = colors[0];
		go->Initialize();
		gameObjects.push_back(go);
	}

	// Initialize cubes
	for (size_t i = 0; i < noCubes; i++)
	{
		GameObject* go = new GameObject();
		go->mesh = cubeMesh;
		go->shader = shader;
		go->type = 1;
		go->radius = 1.0f;
		go->color = colors[1];
		go->Initialize();
		gameObjects.push_back(go);
	}

	// Initialize cylinders
	for (size_t i = 0; i < noCylinders; i++)
	{
		GameObject* go = new GameObject();
		go->mesh = cylinderMesh;
		go->shader = shader;
		go->type = 2;
		go->radius = 1.0f;
		go->color = colors[2];
		go->Initialize();
		gameObjects.push_back(go);
	}

	// Box mesh matrix
	box_model_matrix = glm::mat4(1);
	box_model_matrix = glm::translate(box_model_matrix, glm::vec3(0, -0.5f, 0));
	box_model_matrix = glm::scale(box_model_matrix, glm::vec3(worldSize + 0.5f));

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box1");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Default fill objects
	polygonMode = GL_FILL;

	// Text renderer
	glm::ivec2 resolution = window->GetResolution();
	Text = new TextRenderer(resolution.x, resolution.y);

	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 18);
}

void Laborator_BonusTextRenderer::drawHud()
{

	glm::ivec2 resolution = window->GetResolution();

	/*
	Text->RenderText("Spheres " + std::to_string(noSpheres), resolution.x - 150.0f, 5.0f, 1.25f, glm::vec3(0.5, 0.5, 0.5));
	Text->RenderText("Cubes " + std::to_string(noCubes), resolution.x - 150.0f, 25.0f, 1.25f, glm::vec3(0.5, 0.5, 0.5));
	Text->RenderText("Cylinders " + std::to_string(noCylinders), resolution.x - 150.0f, 45.0f, 1.25f, glm::vec3(0.5, 0.5, 0.5));
	Text->RenderText("Framerate " + std::to_string(framerate), resolution.x - 200.0f, 65.0f, 1.50f, glm::vec3(0.5, 0.5, 0.5));
	*/

	Text->RenderText("Spheres " + std::to_string(noSpheres), 5.0f, 5.0f, 1.25f, glm::vec3(0.5, 0.5, 0.5));
	Text->RenderText("Cubes " + std::to_string(noCubes), 5.0f, 25.0f, 1.25f, glm::vec3(0.5, 0.5, 0.5));
	Text->RenderText("Cylinders " + std::to_string(noCylinders), 5.0f, 45.0f, 1.25f, glm::vec3(0.5, 0.5, 0.5));
	Text->RenderText("Framerate " + std::to_string(framerate), 5.0f, 65.0f, 1.50f, glm::vec3(0.5, 0.5, 0.5));

}

void Laborator_BonusTextRenderer::ResetSpeed() {
	for (go_it1 = gameObjects.begin(); go_it1 != gameObjects.end(); ++go_it1) {
		(*go_it1)->ResetSpeed();
	}
}

void Laborator_BonusTextRenderer::AddSphere() {
	GameObject* go = new GameObject();
	go->mesh = sphereMesh;
	go->shader = shader;
	go->type = 0;
	go->radius = 0.5f;
	go->color = colors[0];
	go->Initialize();
	gameObjects.push_back(go);

	noSpheres += 1;
}

void Laborator_BonusTextRenderer::AddCube() {
	GameObject* go = new GameObject();
	go->mesh = cubeMesh;
	go->shader = shader;
	go->type = 1;
	go->radius = 1.0f;
	go->color = colors[1];
	go->Initialize();
	gameObjects.push_back(go);

	noCubes += 1;
}

void Laborator_BonusTextRenderer::AddCylinder() {
	GameObject* go = new GameObject();
	go->mesh = cylinderMesh;
	go->shader = shader;
	go->type = 2;
	go->radius = 1.0f;
	go->color = colors[2];
	go->Initialize();
	gameObjects.push_back(go);

	noCylinders += 1;
}

void Laborator_BonusTextRenderer::FrameStart()
{

	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

}

void Laborator_BonusTextRenderer::UpdateFramerate(float deltaTimeSeconds) {

	noFrames += 1;
	frameRateTimer -= deltaTimeSeconds;

	if (frameRateTimer < 0) {

		framerate = noFrames;

		frameRateTimer = 1.0 - frameRateTimer;
		noFrames = 0;
	}

}

void Laborator_BonusTextRenderer::Update(float deltaTimeSeconds)
{

	UpdateFramerate(deltaTimeSeconds);

	glUseProgram(shader->program);

	// Update objects
	for (go_it1 = gameObjects.begin(); go_it1 != gameObjects.end(); ++go_it1) {
		(*go_it1)->Update(deltaTimeSeconds);
	}

	vector<pair<GameObject*, GameObject*>> vecCollidingPairs;

	// Static collisions, i.e. overlap
	for (go_it1 = gameObjects.begin(); go_it1 != gameObjects.end(); ++go_it1) {

		for (go_it2 = gameObjects.begin(); go_it2 != gameObjects.end(); ++go_it2) {

			if (go_it1 == go_it2) {
				continue;
			}

			if ((*go_it1)->IsColliding(*go_it2) == false) {
				continue;
			}

			GameObject* go1 = *go_it1;
			GameObject* go2 = *go_it2;

			// Collision has occured
			vecCollidingPairs.push_back({ go1, go2 });

			// Distance between objects
			float fDistance = go1->GetDistance(go2);

			// Calculate displacement required
			float fOverlap = 0.5f * (fDistance - go1->radius - go2->radius);

			// Displace Current GO away from collision
			go1->p.x -= fOverlap * (go1->p.x - go2->p.x) / fDistance;
			go1->p.y -= fOverlap * (go1->p.y - go2->p.y) / fDistance;
			go1->p.z -= fOverlap * (go1->p.z - go2->p.z) / fDistance;

			// Displace Target GO away from collision
			go2->p.x += fOverlap * (go1->p.x - go2->p.x) / fDistance;
			go2->p.y += fOverlap * (go1->p.y - go2->p.y) / fDistance;
			go2->p.z += fOverlap * (go1->p.z - go2->p.z) / fDistance;
		}
	}


	// Now work out dynamic collisions
	for (auto c : vecCollidingPairs)
	{

		GameObject* b1 = c.first;
		GameObject* b2 = c.second;

		// Distance between balls

		float fDistance = b1->GetDistance(b2);

		// Normal
		float nX = (b2->p.x - b1->p.x) / fDistance;
		float nZ = (b2->p.z - b1->p.z) / fDistance;

		// Tangent
		float tX = -nZ;
		float tZ = nX;

		// Dot Product Tangent
		float dpTan1 = b1->v.x * tX + b1->v.z * tZ;
		float dpTan2 = b2->v.x * tX + b2->v.z * tZ;

		// Dot Product Normal
		float dpNorm1 = b1->v.x * nX + b1->v.z * nZ;
		float dpNorm2 = b2->v.x * nX + b2->v.z * nZ;

		// Conservation of momentum in 1D
		float m1 = (dpNorm1 * (b1->mass - b2->mass) + 2.0f * b2->mass * dpNorm2) / (b1->mass + b2->mass);
		float m2 = (dpNorm2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpNorm1) / (b1->mass + b2->mass);

		// Update ball velocities
		b1->v.x = tX * dpTan1 + nX * m1;
		b1->v.z = tZ * dpTan1 + nZ * m1;
		b2->v.x = tX * dpTan2 + nX * m2;
		b2->v.z = tZ * dpTan2 + nZ * m2;
	}

	// Draw objects

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	for (go_it1 = gameObjects.begin(); go_it1 != gameObjects.end(); ++go_it1) {
		(*go_it1)->Draw();
	}

	// Draw box

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(box_model_matrix));

	// Bind color
	GLint loc_object_color = glGetUniformLocation(shader->program, "objectColor");
	glUniform3fv(loc_object_color, 1, glm::value_ptr(colors[3]));

	// Get mesh
	Mesh* mesh = meshes["box"];

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);


	return;

	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box1"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box1"], glm::vec3(-1, 0.5f, 0));

}

void Laborator_BonusTextRenderer::FrameEnd()
{
	drawHud();
	//DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator_BonusTextRenderer::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (window->KeyHold(GLFW_KEY_W)) {
		GetSceneCamera()->MoveUp(cameraSpeed * deltaTime);
		GetSceneCamera()->Update();
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		GetSceneCamera()->MoveDown(cameraSpeed * deltaTime);
		GetSceneCamera()->Update();
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		GetSceneCamera()->MoveLeft(cameraSpeed * deltaTime);
		GetSceneCamera()->Update();
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		GetSceneCamera()->MoveRight(cameraSpeed * deltaTime);
		GetSceneCamera()->Update();
	}

	if (window->KeyHold(GLFW_KEY_Z)) {
		GetSceneCamera()->MoveBackward(cameraSpeed * deltaTime);
		GetSceneCamera()->Update();
	}

	if (window->KeyHold(GLFW_KEY_X)) {
		GetSceneCamera()->MoveForward(cameraSpeed * deltaTime);
		GetSceneCamera()->Update();
	}
};

void Laborator_BonusTextRenderer::OnKeyPress(int key, int mods)
{

	/*
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
	// add key press event
	if (key == GLFW_KEY_Z) {
		polygonMode = GL_LINE;
	}
	// add key press event
	if (key == GLFW_KEY_X) {
		polygonMode = GL_POINT;
	}
	// add key press event
	if (key == GLFW_KEY_C) {
		polygonMode = GL_FILL;
	}
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
	}
	*/

	if (key == 82) {
		ResetSpeed();
	}

	if (key == 66) {
		AddSphere();
	}
	if (key == 78) {
		AddCube();
	}
	if (key == 77) {
		AddCylinder();
	}
};

void Laborator_BonusTextRenderer::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator_BonusTextRenderer::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	GetSceneCamera()->RotateOY(-(float)deltaX);
	GetSceneCamera()->RotateOX(-(float)deltaY);
	GetSceneCamera()->Update();
};

void Laborator_BonusTextRenderer::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator_BonusTextRenderer::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator_BonusTextRenderer::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator_BonusTextRenderer::OnWindowResize(int width, int height)
{
	// treat window resize event
}
