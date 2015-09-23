#include "imagecachegl.h"

namespace program
{
	void imagecachegl::init()
	{
		imgcon = ict_sys;
	}

	void imagecachegl::setmode(imgcontext ict)
	{
		modelock.lock();
		imgcon = ict;
	}

	void imagecachegl::unlock()
	{
		modelock.unlock();
	}

	void imagecachegl::draw(imgcontext ict, size_t id, vector2d pos)
	{
		if (id > 0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, cache[ict][id]);
			glBegin(GL_TEXTURE_2D);
			glColor4f(1, 1, 1, 1);
			glTexCoord2i(0, 0);
			glVertex2i(0, 0);
			glTexCoord2i(1, 0);
			glVertex2i(800, 0);
			glTexCoord2i(1, 1);
			glVertex2i(800, 600);
			glTexCoord2i(0, 1);
			glVertex2i(0, 600);
			//glDrawArrays(GL_TEXTURE_2D, 0, 1);
			glDisable(GL_TEXTURE_2D);
		}
		/*bitmap bmp = cache[ict][id];
		const void* data = bmp.data();
		if (data)
		{
			glRotatef(2, 0, 1, 1);
			glTranslatef(pos.x(), pos.y(), 1);
			glDrawPixels(bmp.width(), bmp.height(), GL_BGRA, GL_UNSIGNED_BYTE, data);
		}*/
	}

	pair<imgcontext, size_t> imagecachegl::add(bitmap bmp)
	{
		const void* data = bmp.data();
		if (data)
		{
			GLuint texName;
			glGenTextures(1, &texName);
			glBindTexture(GL_TEXTURE_2D, texName);

			glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
			glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
			glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
			glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
			glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
				bmp.width(), bmp.height(), 0,
				GL_BGRA, GL_UNSIGNED_INT_8_8_8_8, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			cache[imgcon][bmp.id()] = texName;
			make_pair(imgcon, bmp.id());
		}
		return make_pair(imgcon, -1);
	}

	void imagecachegl::clearcache(imgcontext ict)
	{
		cache[ict].clear();
	}
}
