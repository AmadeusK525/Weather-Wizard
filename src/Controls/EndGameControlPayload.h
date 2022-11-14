#ifndef ENDGAMECONTROLPAYLOAD_H_
#define ENDGAMECONTROLPAYLOAD_H_

#pragma once

namespace ww
{
	struct EndGameControlPayload
	{
		bool bShouldRestartGame;

		EndGameControlPayload(bool bShouldRestartGame) : bShouldRestartGame(bShouldRestartGame) {}
	};
}

#endif // ENDGAMECONTROLPAYLOAD_H_