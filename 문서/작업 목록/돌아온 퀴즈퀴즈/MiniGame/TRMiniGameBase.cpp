#include "stdafx.h"
#include "TRMiniGameBase.h"
//
#include "gui/GUIControlUserValue.h"

void CTRMiniGameBase::onFrameMove(float fElapsed)
{
	switch(m_eGameStep)
	{
	case CTRMiniGameBase::GAMESTEP_BEGIN_BEFORE:
		BeginBefore(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_BEGIN_WHILE:
		BeginWhile(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_BEGIN_AFTER:
		BeginAfter(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_SELECT_BEFORE:
		SelectBefore(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_SELECT_WHILE:
		SelectWhile(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_SELECT_AFTER:
		SelectAfter(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_RESULT_BEFORE:
		ResultBefore(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_RESULT_WHILE:
		ResultWhile(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_RESULT_AFTER:
		ResultAfter(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_EXIT_BEFORE:
		ExitBefore(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_EXIT_WHILE:
		ExitWhile(fElapsed);
		break;

	case CTRMiniGameBase::GAMESTEP_EXIT_AFTER:
		ExitAfter(fElapsed);
		break;
	}
}

void CTRMiniGameBase::BeginBefore(float _fTime)
{
}

void CTRMiniGameBase::BeginWhile(float _fTime)
{
}

void CTRMiniGameBase::BeginAfter(float _fTime)
{
}

void CTRMiniGameBase::SelectBefore(float _fTime)
{
}

void CTRMiniGameBase::SelectWhile(float _fTime)
{
}

void CTRMiniGameBase::SelectAfter(float _fTime)
{
}

void CTRMiniGameBase::ResultBefore(float _fTime)
{
}

void CTRMiniGameBase::ResultWhile(float _fTime)
{
}

void CTRMiniGameBase::ResultAfter(float _fTime)
{
}

void CTRMiniGameBase::ExitBefore(float _fTime)
{
}

void CTRMiniGameBase::ExitWhile(float _fTime)
{
}

void CTRMiniGameBase::ExitAfter(float _fTime)
{
}

void CTRMiniGameBase::SelectGameStep()
{
	switch(m_eGameStep)
	{
	case CTRMiniGameBase::GAMESTEP_BEGIN_BEFORE:
		BeginBefore();
		break;

	case CTRMiniGameBase::GAMESTEP_BEGIN_WHILE:
		BeginWhile();
		break;

	case CTRMiniGameBase::GAMESTEP_BEGIN_AFTER:
		BeginAfter();
		break;

	case CTRMiniGameBase::GAMESTEP_SELECT_BEFORE:
		SelectBefore();
		break;

	case CTRMiniGameBase::GAMESTEP_SELECT_WHILE:
		SelectWhile();
		break;

	case CTRMiniGameBase::GAMESTEP_SELECT_AFTER:
		SelectAfter();
		break;

	case CTRMiniGameBase::GAMESTEP_RESULT_BEFORE:
		ResultBefore();
		break;

	case CTRMiniGameBase::GAMESTEP_RESULT_WHILE:
		ResultWhile();
		break;

	case CTRMiniGameBase::GAMESTEP_RESULT_AFTER:
		ResultAfter();
		break;

	case CTRMiniGameBase::GAMESTEP_EXIT_BEFORE:
		ExitBefore();
		break;

	case CTRMiniGameBase::GAMESTEP_EXIT_WHILE:
		ExitWhile();
		break;

	case CTRMiniGameBase::GAMESTEP_EXIT_AFTER:
		ExitAfter();
		break;
	}
}

void CTRMiniGameBase::SetBtnFunction(CGUIDialog * _pDlg, std::string _btnName, std::function<bool(CGUIControl*)> func)
{
	if(_pDlg == nullptr || _btnName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(_btnName);
	if(pCtrl != nullptr)
	{
		pCtrl->clearButtonClickCmdFunc();
		pCtrl->bindButtonClickCmdFunc(func);
	}
}

void CTRMiniGameBase::SetBtnVisible(CGUIDialog * _pDlg, std::string _btnName, bool _bVisible)
{
	if(_pDlg == nullptr || _btnName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(_btnName);
	if(pCtrl != nullptr)
	{
		pCtrl->setVisible(_bVisible);
	}
}

void CTRMiniGameBase::SetCtrlUserData(CGUIDialog * _pDlg, std::string ctrlName, std::string key, std::string data)
{
	if(_pDlg == nullptr || ctrlName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(ctrlName);
	if(pCtrl != nullptr)
	{
		pCtrl->enableUsingUserData(true)->value.append(key.c_str(), data);
	}
}

void CTRMiniGameBase::SetCtrlUserData(CGUIDialog * _pDlg, std::string ctrlName, std::string key, int data)
{
	if(_pDlg == nullptr || ctrlName.empty())
	{
		return;
	}

	CGUIControl * pCtrl = _pDlg->findControl(ctrlName);
	if(pCtrl != nullptr)
	{
		pCtrl->enableUsingUserData(true)->value.append(key.c_str(), data);
	}
}

void CTRMiniGameBase::InitBar(CGUIFrameImage * _pFrame, CGUIImageCtrl * _pImage)
{
	CRectInfo frameRect = _pFrame->getClientRect();
	get<0>(m_tupleBarFrame) = frameRect;
	get<1>(m_tupleBarFrame) = frameRect.width();
	get<2>(m_tupleBarFrame) = frameRect.height();

	CRectInfo ImgRect;
	_pImage->getSrcRect(ImgRect);
	get<0>(m_tupleBarImage) = ImgRect;
	get<1>(m_tupleBarImage) = ImgRect.width();
	get<2>(m_tupleBarImage) = ImgRect.height();
}

void CTRMiniGameBase::UpdateTimeBar(CGUIFrameImage * _pFrame, CGUIImageCtrl * _pImage, float _fEndTime, float _fElapsed)
{
	_fElapsed = _fEndTime <= _fElapsed ? _fEndTime : _fElapsed;

	CRectInfo frameRect = get<0>(m_tupleBarFrame);
	int nFrameWidth = get<1>(m_tupleBarFrame) * (1.0f - (1.0f / _fEndTime * _fElapsed));
	int nFrameHeight = get<2>(m_tupleBarFrame);
	_pImage->setClientPos(CRectInfo(frameRect.left, frameRect.top, frameRect.left + nFrameWidth, frameRect.top + nFrameHeight));

	CRectInfo ImgRect = get<0>(m_tupleBarImage);
	int nImgWidth = get<1>(m_tupleBarImage) * (1.0f - (1.0f / _fEndTime * _fElapsed));
	int nImgHeight = get<2>(m_tupleBarImage);
	_pImage->setSrcRect(CRectInfo(ImgRect.left, ImgRect.top, ImgRect.left + nImgWidth, ImgRect.top + nImgHeight));
}

void CTRMiniGameBase::UpdateStatisticsBar(CGUIFrameImage * _pFrame, CGUIImageCtrl * _pImage, float _fStart, float _fEnd, float _fTotal, float _fEndTime, float _fElapsed)
{
	_fElapsed = _fEndTime <= _fElapsed ? _fEndTime : _fElapsed;

	CRectInfo frameRect = get<0>(m_tupleBarFrame);
	int nFrameWidth = get<1>(m_tupleBarFrame) * (_fStart / _fTotal) + get<1>(m_tupleBarFrame) * (((_fEnd - _fStart) / _fTotal) / _fEndTime) * _fElapsed;
	int nFrameHeight = get<2>(m_tupleBarFrame);
	_pImage->setClientPos(CRectInfo(frameRect.left, frameRect.top, frameRect.left + nFrameWidth, frameRect.top + nFrameHeight));

	CRectInfo ImgRect = get<0>(m_tupleBarImage);
	int nImgWidth = get<1>(m_tupleBarImage) * (_fStart / _fTotal) + get<1>(m_tupleBarImage) * (((_fEnd - _fStart) / _fTotal) / _fEndTime) * _fElapsed;
	int nImgHeight = get<2>(m_tupleBarImage);
	_pImage->setSrcRect(CRectInfo(ImgRect.left, ImgRect.top, ImgRect.left + nImgWidth, ImgRect.top + nImgHeight));
}

void CTRMiniGameBase::UpdateTimeFunc(std::reference_wrapper<TIME_FUNC> _refTimeFunc, float _fTime)
{
	if(_refTimeFunc.get().bEnd)
	{
		return;
	}

	if(_refTimeFunc.get().fElapsed < _refTimeFunc.get().fLife)
	{
		_refTimeFunc.get().fElapsed += _fTime;
		_refTimeFunc.get().fElapsed = _refTimeFunc.get().fElapsed >= _refTimeFunc.get().fLife ? _refTimeFunc.get().fLife : _refTimeFunc.get().fElapsed;
		_refTimeFunc.get().funcTime(_refTimeFunc.get().fElapsed);
	}
	else
	{
		_refTimeFunc.get().funcTimeEnd(_fTime);
		_refTimeFunc.get().bEnd = true;
	}
}

void CTRMiniGameBase::SetVisible(CGUIControl * _pCtrl, bool _bVisible)
{
	if(_pCtrl)
	{
		_pCtrl->setVisible(_bVisible);
	}
}

void CTRMiniGameBase::SetAnimator(CGUIControl * _pCtrl, CGUIAnimator * _pAnimator, bool _bClearLocalVars)
{
	if(_pCtrl)
	{
		_pCtrl->setAnimator(_pAnimator, _bClearLocalVars);
	}
}

void CTRMiniGameBase::SetText(CGUIControl * _pCtrl, string _strText)
{
	if(_pCtrl)
	{
		_pCtrl->setText(_strText);
	}
}

void CTRMiniGameBase::CloseDialog(CGUIDialog * _pDlg, float _fTimeLength)
{
	if(_pDlg && _pDlg->getControlID().isValid())
	{
		_pDlg->setAnimator(new CGUIAnimatorFadeOutRemove(_fTimeLength));
		_pDlg = nullptr;
	}
}

void CTRMiniGameBase::ToggleDialog(CGUIDialog * _pDlg, bool _bVisible)
{
	if(_pDlg)
	{
		_pDlg->setVisible(_bVisible);
	}
}

int CTRMiniGameBase::GetValueInt(CGUIControl * _pCtrl, string _strName)
{
	if(_pCtrl)
	{
		return _pCtrl->getUserDataValue()->value.asInt(_strName.c_str());
	}

	return -1;
}

std::string CTRMiniGameBase::ReplaceNewLineSTR(std::string _strData)
{
	stringutil::replaceString(_strData, "\\n", "\n");
	return _strData;
}
