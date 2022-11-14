#ifndef BOOK_H_
#define BOOK_H_

#pragma once

#include "Collectable.h"

namespace ww
{
	class Book : public Collectable
	{
	public:
		inline virtual int GetPoints() const { return 1; }
	};
}

#endif // BOOK_H_