#pragma once
#include <string>
#include <cctype>
#include <algorithm>

enum GridResourceType
{
	Coal,
	Oil,
	Garbage,
	Uranium
};


class GridResource
{
public:
	GridResource(GridResourceType resourceType);
	~GridResource();

	GridResourceType getResourceTypeByName(std::string name);

private:
	GridResourceType m_resourceType;
};