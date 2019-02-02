#include "GridResource.h"

GridResource::GridResource(GridResourceType resourceType)
{
}

GridResource::~GridResource()
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
