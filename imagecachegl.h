#pragma once
#include "imagecache.h"
#include <glew-1.9.0\include\GL\glew.h>
#include <glfw-3.0.3\include\GLFW\glfw3.h>
#include <glm-0.9.4.0\glm\glm.hpp>

using namespace glm;

namespace program
{
	class imagecachegl
	{
	public:
		imagecachegl() {}
		~imagecachegl() {}
		void draw(imgcontext, size_t, vector2d);
		pair<imgcontext, size_t> add(bitmap);
		void init();
		void setmode(imgcontext);
		void unlock();
		void clearcache(imgcontext);
	private:
		map<imgcontext, map<size_t, GLuint>> cache;
		imgcontext imgcon;
		mutex modelock;
	};
}

