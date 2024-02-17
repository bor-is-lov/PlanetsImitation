#include "RegularPoly.hpp"

RegularPoly::RegularPoly(const Position2D& center, float r, size_t positions_size)
	: INDICES_SIZE((positions_size - 2) * 3), POSITIONS_SIZE(positions_size)
{
	positions = new Position2D[POSITIONS_SIZE];
	for (size_t i = 0; i < POSITIONS_SIZE; i++)
	{
		positions[i].x = center.x + r * cos(2 * M_PI / POSITIONS_SIZE * i - M_PI);
		positions[i].y = center.y + r * sin(2 * M_PI / POSITIONS_SIZE * i - M_PI);
	}
	indices = new unsigned int[INDICES_SIZE];
	for (size_t i = 0, j = 1; i < INDICES_SIZE / 3; i++, j++)
	{
		indices[i * 3]     = 0;
		indices[i * 3 + 1] = j;
		indices[i * 3 + 2] = j + 1;
	}
}

void RegularPoly::Rotate(float x, float y, float speed)
{
	for (size_t i = 0; i < POSITIONS_SIZE; i++)
		positions[i].Rotate(x, y, speed);
}

void RegularPoly::Rotate(Position2D center, float speed) { Rotate(center.x, center.y, speed); }

void RegularPoly::Rotate(float speed) { Rotate(GetCenter(), speed); }

Position2D RegularPoly::GetCenter()
{
	float x = 0, y = 0;
	for (size_t i = 0; i < POSITIONS_SIZE; i++)
	{
		x += positions[i].x;
		y += positions[i].y;
	}
	x /= POSITIONS_SIZE;
	y /= POSITIONS_SIZE;
	return { x, y };
}

void RegularPoly::SetIndicesArray(unsigned int* indices, RegularPoly polygons[], size_t size)
{
	size_t index = 0, positions_size = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < polygons[i].INDICES_SIZE; j++)
			indices[index++] = polygons[i].indices[j] + positions_size;
		positions_size += polygons[i].POSITIONS_SIZE;
	}
}

void RegularPoly::SetPositionsArray(Position2D* positions, RegularPoly polygons[], size_t size)
{
	size_t size_total = 0;
	for (size_t i = 0; i < size; i++)
		size_total += polygons[i].GetPositionsSize();
	size_t index = 0;
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < polygons[i].POSITIONS_SIZE; j++)
			positions[index++] = polygons[i].positions[j];
}

Position2D* RegularPoly::GetPositions() { return positions; }

size_t RegularPoly::GetPositionsSize() { return POSITIONS_SIZE; }

size_t RegularPoly::GetIndicesSize() { return INDICES_SIZE; }

size_t RegularPoly::GetPositionsSize(RegularPoly polygons[], size_t size)
{
	size_t size_total = 0;
	for (size_t i = 0; i < size; i++)
		size_total += polygons[i].GetPositionsSize();
	return size_total;
}
size_t RegularPoly::GetIndicesSize(RegularPoly polygons[], size_t size)
{
	size_t size_total = 0;
	for (size_t i = 0; i < size; i++)
		size_total += polygons[i].GetIndicesSize();
	return size_total;
}

RegularPoly::~RegularPoly()
{
	delete[] indices;
	delete[] positions;
}