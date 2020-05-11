#pragma once
#include "gameui/TRUserInterface.h"
#include "TRGuildWorkshop_GUI.h"

#include "TRWorkshopBase.h"

class CTRGuildWorkshop_GuideDlg :
	public CTRCommandTarget,
	public CTRGuildWorkshop_GUI
{
private:
	constexpr static int GUIDEIMG_WIDTH = 512;
	constexpr static int GUIDEIMG_HEIGHT = 156;
	constexpr static int GUIDEIMG_Y01 = 0;
	constexpr static int GUIDEIMG_Y02 = 168;
	constexpr static int GUIDEIMG_Y03 = 336;

private:
	enum EGUIName
	{
		GN_WORKSHOP_GUIDE,
		GN_END
	};

	enum EButtonName
	{
		BN_CLOSE,
		BN_GUIDEBTN1,
		BN_GUIDEBTN2,
		BN_GUIDEBTN3,
		BN_GUIDEBTN4,
		BN_PREVBTN,
		BN_NEXTBTN,
		BN_END
	};

	enum EStaticTextName
	{
		SN_PAGENUM,
		SN_TITLEMENT,
		//SN_INFOMENT,
		SN_END
	};

	enum EFormatedTextName
	{
		FTN_INFOMENT,
		FTN_END
	};

	enum EFrameName
	{
		FN_GUIDEIMG,
		FN_END
	};

	enum EImageCtrlName
	{
		IN_GUIDE01,
		IN_GUIDE02,
		IN_GUIDE03,
		IN_END
	};

private:
	struct SButton
	{
		CGUIButton* pButton;
		function<void(void)> funcEvent;
	};

private:
	array<CGUIDialog*, EGUIName::GN_END> m_arrayDlg = { nullptr, };
	array<SButton, EButtonName::BN_END> m_arrayButton = { nullptr, };
	array<CGUIStaticText*, EStaticTextName::SN_END> m_arrayStaticText = { nullptr, };
	array<CFormatedStaticText*, EFormatedTextName::FTN_END> m_arrayFormatedText = { nullptr, };
	array<CGUIImageCtrl*, EImageCtrlName::IN_END> m_arrayImageCtrl = { nullptr, };
	array<std::string, EImageCtrlName::IN_END> m_arrayImageName;

	map<pair<int, int>, GuildPlantGuideInfo*> m_mapGuideList;
	int m_nCurIndex = 0;
	int m_nCurSubIndex = 0;
	map<int, int> m_mapMaxSubIndex;

	string m_strPageNumSign = " / ";

public:
	CTRGuildWorkshop_GuideDlg();
	virtual ~CTRGuildWorkshop_GuideDlg();

public:
	// CCommandTarget을(를) 통해 상속됨
	virtual bool onButtonClick(CGUIControlID ctrlID, CCommandID cmdID) override;

	// CTRGuildWorkshop_GUI을(를) 통해 상속됨
	virtual void InitName() override;
	virtual void InitGUI() override;
	virtual void InitButton() override;
	virtual void InitStaticText() override;
	virtual void InitImageControl() override;
	virtual void InitFormatedText() override;

	virtual void showDialog() override;
	virtual void closeDialog() override;

public:
	void LoadGuideList(CTRGuildPlanInfoLoader* pLoader);

private:
	void SettingStaticText(EStaticTextName _eStaticText, std::string _strData);
	void SettingGuideImage(pair<int, int> _pairPage);
	void SettingFormatedText(EFormatedTextName _eStaticText, std::string _strData);
};

