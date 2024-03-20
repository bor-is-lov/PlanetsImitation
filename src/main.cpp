#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "RegularPoly.hpp"

int main(void) {
	// OpenGL part
	if (!glfwInit())
	{
		std::cout << "GLFW Error: failed to initialize the library\n";
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(480, 480, "Planets imitation v2", NULL, NULL);
	if (!window) {
		std::cout << "GLFW Error: failed to create window\n";
		glfwTerminate();
		return 2;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	unsigned int err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "GLEW Error: " << glewGetErrorString(err) << '\n';
		return 3;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			int min = width < height ? width : height;
			glViewport(0, 0, min, min);
		});

	// Planets
	const size_t SIZE = 3;
	unsigned int indices_size = 0;
	RegularPoly planets[SIZE]
	{
		{
			{0.0f, 0.0f},
			0.2f, 12
		},
		{
			{0.5f, 0.0f},
			0.1f, 6
		},
		{
			{0.7f, 0.0f},
			0.05f, 3
		}
	};
	const size_t INDICES_SIZE = RegularPoly::GetIndicesSize(planets, SIZE);
	unsigned int* indices = new unsigned int[INDICES_SIZE];
	RegularPoly::SetIndicesArray(indices, planets, SIZE);

	const size_t POSITIONS_SIZE = RegularPoly::GetPositionsSize(planets, SIZE);
	// (As I understand) I can't pass dynamic array to OpenGL buffer, so I have to allocate like this:
	Position2D* positions = (Position2D*)alloca(sizeof(Position2D) * POSITIONS_SIZE);
	RegularPoly::SetPositionsArray(positions, planets, SIZE);

	// OpenGL part
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, POSITIONS_SIZE * sizeof(Position2D), positions, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Position2D), 0);
	glEnableVertexAttribArray(0);

	// Render
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, INDICES_SIZE, GL_UNSIGNED_INT, indices);

		// I know it's wrong to rotate these while rendering, but I just didn't learned yet how to do it else
		// TODO: move rotation from here to game loop

		planets[0].Rotate(-0.005f);

		// rotation around planets[0]
		planets[1].Rotate(planets[0].GetCenter(), 0.005f);
		// rotation around itself
		planets[1].Rotate(0.01f);

		// to rotate arond planets[1], it first has to rotate
		// around planets[0] the smae way as planets[1] do
		planets[2].Rotate(planets[0].GetCenter(), 0.005f);
		planets[2].Rotate(planets[1].GetCenter(), -0.035f);

		RegularPoly::SetPositionsArray(positions, planets, SIZE);
		glBufferData(GL_ARRAY_BUFFER, POSITIONS_SIZE * sizeof(Position2D), positions, GL_DYNAMIC_DRAW);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete[] indices;
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
