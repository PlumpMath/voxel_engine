#pragma once

#include <Windows.h>

#include "camera.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Renderer
{
public:
	static void clear_screen()
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	template<typename T>
	inline static void render(const Camera& c, const T& objectOfInterest)
	{
		render(c, objectOfInterest.get_model_matrix(), objectOfInterest.get_mesh());
	}

	static void render(const Camera& camera, const glm::mat4& modelMatrix, const Mesh& mesh)
	{
		glPolygonMode(GL_FRONT, GL_FILL);
		setup_matrices(camera.get_projection_matrix(), camera.get_view_matrix(), modelMatrix);
	}

	template<typename T>
	inline static void render_wireframe(const Camera& camera, const Color& color, const T& objectOfInterest)
	{
		render_wireframe(camera, objectOfInterest.get_model_matrix(), color, objectOfInterest.get_mesh());
	}

	static void render_wireframe(const Camera& camera, const glm::mat4& modelMatrix, const Color& color, const Mesh& mesh)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonOffset(-1.0f, -1.0f);
		glLineWidth(1);
		glColor3ub(color.get_red(), color.get_green(), color.get_blue());

		setup_matrices(camera.get_projection_matrix(), camera.get_view_matrix(), modelMatrix);

		glDisable(GL_POLYGON_OFFSET_LINE);
		glPolygonMode(GL_FRONT, GL_FILL);
	}

private:
	static inline void setup_matrices(const glm::mat4& projection, const glm::mat4& view, const glm::mat4& model)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMultMatrixf(glm::value_ptr(projection*view*model));
	}
};