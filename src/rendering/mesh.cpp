#include "mesh.h"

#include <GLFW/glfw3.h>

#include <algorithm>
#include <functional>

void Mesh::push_back(const Quad& q)
{
	_quads.push_back(q);
}

void Mesh::concatenate(const Mesh& m)
{
	_quads.insert(_quads.end(), m._quads.begin(), m._quads.end());
}

void Mesh::clear()
{
	_quads.clear();
}

void Mesh::draw_with_color() const
{
	if(_quads.size() == 0)
		return;

	glBegin(GL_QUADS);
	const auto first = _quads.begin();
	first->draw_with_color();

	const auto second = first+1;
	std::for_each(second, _quads.end(), [](const Quad& q){q.draw_with_color();});
	glEnd();
}

void Mesh::draw_without_color() const
{
	if (_quads.size() == 0)
		return;

	glBegin(GL_QUADS);
	const auto first = _quads.begin();
	first->draw_without_color();

	const auto second = first + 1;
	std::for_each(second, _quads.end(), [](const Quad& q){q.draw_without_color(); });
	glEnd();
}