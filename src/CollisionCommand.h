#ifndef COLLISIONCOMMAND_H_
#define COLLISIONCOMMAND_H_

#pragma once

namespace ww
{
	enum class CollisionCommand
	{
		ALLOW,
		BLOCK,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP
	};
}

#endif // COLLISIONCOMMAND_H_