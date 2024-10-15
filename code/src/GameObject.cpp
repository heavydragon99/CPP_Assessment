#include "GameObject.h"

#include <iostream>

Sean::String GameObject::getName() const
{
    return mName;
}

void GameObject::printName() const
{
    std::cout << mName << std::endl;
}

void GameObject::printDescription() const
{
    std::cout << mDescription << std::endl;
}

ObjectType GameObject::getType() const
{
    return mType;
}