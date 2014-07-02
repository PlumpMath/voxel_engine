#include "ui.h"

#include <Windows.h>
#include <GLFW/glfw3.h>

UI::UI(int width, int height)
:
_width(width),
_height(height),
_pixels((width*height)+2, Color(255, 0, 0)),
_browser("http://google.com", [this](const CefRenderHandler::RectList& dirty, const void* buffer){
	glGenTextures(1, &_textureHandle);
	if (auto error = glGetError())
		throw std::runtime_error("Failed to create texture. Make sure this is called after the gl context has been created.");
	glBindTexture(GL_TEXTURE_2D, _textureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, NULL);
})
{
}

UI::~UI()
{
	glDeleteTextures(1, &_textureHandle);
}

void UI::tick()
{
	_browser.tick();
	glBindTexture(GL_TEXTURE_2D, _textureHandle);
	glLoadIdentity();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(0.0, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void UI::render(const void* buffer)
{
	glBindTexture(GL_TEXTURE_2D, _textureHandle);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, NULL);
}