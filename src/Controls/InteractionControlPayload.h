#ifndef INTERACTIONCONTROLLERPAYLOAD_H_
#define INTERACTIONCONTROLLERPAYLOAD_H_

#pragma once

#include <optional>

namespace ww
{
	struct InteractionControllerPayload
	{
		std::optional<Season> newSeason;
		std::optional<Season> newWandSelectionIndex;
	};
}

#endif // INTERACTIONCONTROLLERPAYLOAD_H_