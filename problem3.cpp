#include <glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <time.h>
#include <stdbool.h>
#include <iostream>
#include <vector>

class GeometricObjectInterface
{
public:

	virtual void draw() = 0;
};

const int width = 1024;
const int height = 768;
double xpos, ypos;
float* pixels = new float[width*height * 3];


void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawLine2(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{

	if (i0 == i1)
	{
		for (int i = j0; i <= j1; i++)
		{
			drawPixel(i0, i, red, green, blue);
		}
	}
	if (j0 == j1)
		for (int i = i0; i <= i1; i++)
		{
			drawPixel(i, j0, red, green, blue);
		}
}


template<class T_HOW_TO_DRAW>
class GeometricObject : public GeometricObjectInterface
{
public:
	
	void draw()
	{
		T_HOW_TO_DRAW operation;
		operation.draw();
	}
};


class Box
{
public:

	void draw()
	{
		int x = 200;
		int y = 200;
		int r = 60;
		float q = 1.0f;
		float w = 0.0f;
		float e = 0.0f;
		drawLine2(x - r, y - r, x - r, y + r, q, w, e);
		drawLine2(x - r, y + r, x + r, y + r, q, w, e);
		drawLine2(x - r, y - r, x + r, y - r, q, w, e);
		drawLine2(x + r, y - r, x + r, y + r, q, w, e);
	}
};


class Circle
{
public:

	void draw()
	{
		int x = 400;
		int y = 400;
		int r = 60;
		float q = 0.0f;
		float w = 0.0f;
		float e = 1.0f;

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if ((j - y)*(j - y) + (i - x)*(i - x) <= r*r)
				{
					drawPixel(i, j, q, w, e);
				}
				if ((j - y)*(j - y) + (i - x)*(i - x) < r*r - (r*r / 5))
				{
					drawPixel(i, j, 1.0f, 1.0f, 1.0f);
				}
			}
		}


	}
};


void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background
	
	std::vector<class GeometricObjectInterface*> obj_list;
	obj_list.push_back(new GeometricObject<Circle>);
	obj_list.push_back(new GeometricObject<Box>);

	for (auto itr : obj_list)
	{

		itr->draw();
	}
}




int main(void)
{
	GLFWwindow* window;

	

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop unt il the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);
		glfwGetCursorPos(window, &xpos, &ypos);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	delete[] pixels;

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}