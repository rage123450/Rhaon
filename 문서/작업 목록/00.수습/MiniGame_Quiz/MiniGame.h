#pragma once
#include "gameui/TRUserInterface.h"

namespace MINIGAME
{
	class CMiniGame
	{
	public:
		enum EGameStep
		{
			GS_START_BEFORE,
			GS_START_AFTER,
			GS_SELECT_BEFORE,
			GS_SELECT_AFTER,
			GS_RESULT_BEFORE,
			GS_RESULT_AFTER,
			GS_RESULT_FINAL,
			GS_END
		};

		enum ERoundResult
		{
			RR_WIN,
			RR_LOSE,
			RR_DRAW,
			RR_END
		};

	private:
		EGameStep m_eGameStep;
		std::array<std::function<void(void)>, EGameStep::GS_END> m_arrayUpdate;

	protected:
		std::vector<std::function<bool(void)>> m_vecWinCondition;
		std::vector<std::function<bool(void)>> m_vecLoseCondition;
		std::tuple<int, int, int> m_tupleRoundReward;

	public:
		CMiniGame();
		virtual ~CMiniGame();

	protected:
		virtual void Init_WinCondition() abstract;
		virtual void Init_LoseCondition() abstract;

		virtual void Update_StartBefore() abstract;
		virtual void Update_StartAfter() abstract;
		virtual void Update_SelectBefore() abstract;
		virtual void Update_SelectAfter() abstract;
		virtual void Update_ResultBefore() abstract;
		virtual void Update_ResultAfter() abstract;
		virtual void Update_ResultFinal() abstract;

	public:
		inline void ChangeGameStep(EGameStep _eNextStep)
		{
			m_eGameStep = _eNextStep;
			m_arrayUpdate[m_eGameStep]();
		}

	public:
		EGameStep GetGameStep()const { return m_eGameStep; }
		int GetWin()const { return get<ERoundResult::RR_WIN>(m_tupleRoundReward); }
		int GetLose()const { return get<ERoundResult::RR_LOSE>(m_tupleRoundReward); }
		int GetDraw()const { return get<ERoundResult::RR_DRAW>(m_tupleRoundReward); }
	};
}
