#include "GridResource.h"

GridResource::GridResource(GridResourceType resourceType, bool isAvailable, int cost) : m_resourceType(resourceType), 
m_isAvailable(isAvailable), m_cost(cost)
{
}

GridResource::~GridResource()
{
}

void GridResource::setResourceSprite()
{

}

GridResourceType GridResource::getResourceTypeByName(std::string name)
{
	GridResourceType resourceType = Coal;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name == "coal")
		resourceType = Coal;
	else if (name == "oil")
		resourceType = Oil;
	else if (name == "garbage")
		resourceType = Garbage;
	else if (name == "uranium")
		resourceType = Uranium;

	return GridResourceType::Coal;
}
