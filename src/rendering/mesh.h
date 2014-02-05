#pragma once

#include "quad.h"
#include <vector>

class Mesh
{
public:
	void push_back(const Quad& q);
	void concatenate(const Mesh& m);

	void clear();

	size_t size() const;

	void draw_with_color() const;
	void draw_without_color() const;

private:
	std::vector<Quad> _quads;
};