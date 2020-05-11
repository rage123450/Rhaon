#pragma once
#include "gameui/TRUserInterface.h"
#include "TRScissorsRockPaper_Game.h"
//
#include "gameui/TRRewardItemInfoDlg.h"

class CTRScissorsRockPaper_GameAlone;
class CTRScissorsRockPaper_GameGroup;

class CTRScissorsRockPaper_RewardDlg :
	public CTRCommandTarget,
	public CTRScissorsRockPaper_GUI
{
public:	// Name
	enum EGUIName
	{
		GN_REWARD,
		GN_END
	};

	enum EButtonName
	{
		BN_OK,
		BN_END
	};

	enum EStaticTextName
	{
		STN_NAME,
		STN_END
	};

	enum EFormatedTextName
	{
		FTN_DESC,
		FTN_END
	};

	enum EImageCtrlName
	{
		IC_ITEMIMG,
		IC_END
	};

private:	// Link
	std::shared_ptr<CTRScissorsRockPaper_GameAlone> m_pGameAlone = nullptr;
	std::shared_ptr<CTRScissorsRockPaper_GameGroup> m_pGameGroup = nullptr;

private:
	std::array<CGUIDialog*, EGUIName::GN_END> m_arrayDlg = { nullptr, };
	std::array<std::tuple<string, std::function<void(void)>>, EButtonName::BN_END> m_arrayButton;
	std::array<CGUIStaticText*, EStaticTextName::STN_END> m_arrayStaticText = { nullptr, };
	std::array<CFormatedStaticText*, EFormatedTextName::FTN_END> m_arrayFormatedText = { nullptr, };
	CGUIItemImageCtrl* m_pItemImageCtrl = nullptr;

public:
	CTRScissorsRockPaper_RewardDlg();
	virtual ~CTRScissorsRockPaper_RewardDlg();

public:
	// CTRCommandTarget(CCommandTarget)으로부터 상속받음
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID)override;

	// CTRScissorsRockPaper_GUI으로부터 상속받음
	virtual void showDialog()override;
	virtual void closeDialog()override;

	virtual void InitName()override;
	virtual void InitGUI()override;

	virtual void InitButton()override;
	virtual void InitStaticText()override;
	virtual void InitFormatedText()override;
	virtual void InitImageControl()override;

private:
	void UpdateRewardItem();

public:	// Accessor
	inline void SetGameAlone(const std::shared_ptr<CTRScissorsRockPaper_GameAlone>& _pGameAlone) { m_pGameAlone = _pGameAlone; }
	inline void SetGameGroup(const std::shared_ptr<CTRScissorsRockPaper_GameGroup>& _pGameGroup) { m_pGameGroup = _pGameGroup; }
};

