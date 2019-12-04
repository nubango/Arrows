#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "checkML.h"

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void render() const = 0;
	virtual void update() = 0;
};

#endif // !_GAMEOBJECT_H_