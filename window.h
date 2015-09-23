#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "nxfile.h"
#include "fontcache.h"
#include "imagecachegl.h"

using namespace glm;

namespace program
{
	class window
	{
	public:
		window() {}
		~window();
		int init();
		void draw();
		ui* getui() { return &uinterface; }
		fontcache* getfonts() { return 0; }
		imagecachegl* getimgcache() { return &imgcache; }
	private:
		GLFWwindow* wnd;
		imagecachegl imgcache;
		ui uinterface;
	};
}

