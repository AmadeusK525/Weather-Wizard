#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#pragma once

namespace ww
{
	class Collectable
	{
	public:
		virtual ~Collectable() {}

		virtual int GetPoints() const = 0;
	};
}

#endif // COLLECTABLE_H_