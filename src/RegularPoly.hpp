#pragma once
#include "Position.hpp"

class RegularPoly
{
	Position2D* positions;
	unsigned int* indices;
	const size_t INDICES_SIZE, POSITIONS_SIZE;
public:

	RegularPoly(const Position2D& center, float r, size_t positions_size);

	void Rotate(float x, float y, float speed);
	// rotate around itself
	void Rotate(float speed);
	void Rotate(Position2D center, float speed);

	Position2D GetCenter();

	static void SetIndicesArray(unsigned int* indices, RegularPoly polygons[], size_t size);
	static void SetPositionsArray(Position2D* positions, RegularPoly polygons[], size_t size);

	Position2D* GetPositions();
	size_t GetIndicesSize();
	// total amount of indices from an array
	static size_t GetIndicesSize(RegularPoly polygons[], size_t size);
	size_t GetPositionsSize();
	// total amount of positions from an array
	static size_t GetPositionsSize(RegularPoly polygons[], size_t size);

	~RegularPoly();
};