#pragma once
#include "window.h"

namespace program
{
	int window::init()
	{
		if (!glfwInit())
			return -1;

		wnd = glfwCreateWindow(800, 600, "Journey", NULL, NULL);
		if (!wnd)
		{
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(wnd);
		glfwSwapInterval(1);
		//glfwSetKeyCallback(window, key_callback);

		nl::nx::load_all();

		imgcache.init();
		uinterface.init();
		return 0;
	}

	void window::draw()
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(wnd, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		uinterface.draw();
		//glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
		glEnd();
		glfwSwapBuffers(wnd);
		glfwPollEvents();
	}


	window::~window()
	{
	}
}
