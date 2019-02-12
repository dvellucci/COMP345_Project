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