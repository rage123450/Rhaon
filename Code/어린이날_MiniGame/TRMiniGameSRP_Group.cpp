#include "stdafx.h"
#include "TRMiniGameSRP_Group.h"
//
#include "TRMiniGameQuestion_NpcView.h"
#include "TRMiniGameAnswer_ChoiceSRP.h"

CTRMiniGameSRP_Group::CTRMiniGameSRP_Group()
{
}

CTRMiniGameSRP_Group::~CTRMiniGameSRP_Group()
{
	closeDialog();
}

void CTRMiniGameSRP_Group::showDialog()
{
	closeDialog();

	__super::showDialog();

	if(m_pAnswer != nullptr)
	{
		m_pChoiceSRP = std::dynamic_pointer_cast<CTRMiniGameAnswer_ChoiceSRP>(m_pAnswer);
		m_pChoiceSRP->bindBtn(m_pDlg, "CloseBtn", std::bind(&CTRMiniGameSRP_Group::Func_CloseBtn, this, std::placeholders::_1));
	}

	m_pDlgItem = CTRUserInterface::loadGUI(m_pDlg->getControlID(), "gui/park/RockPaperScissor/RockPaperScissor_ItemDlg2.gui", errmsg);
	if(m_pDlgItem != nullptr)
	{
		m_pDlgItem->setClientPos(m_pDlg->findControl("ItemDlg", GUI_SUB_CONTROL_FRAME)->getClientRect());
	}

	ChangeNPCMent(ENpcMent::NMG_WAIT_START);
}

void CTRMiniGameSRP_Group::closeDialog()
{
	__super::closeDialog();
}

void CTRMiniGameSRP_Group::onOpen()
{
	ChangeNPCMent(ENpcMent::NMG_START_SELECTION_TIMER);
}

void CTRMiniGameSRP_Group::onWait()
{
}

void CTRMiniGameSRP_Group::onReady()
{
}

void CTRMiniGameSRP_Group::onStart()
{
}

void CTRMiniGameSRP_Group::onPlaying()
{
}

void CTRMiniGameSRP_Group::onResult()
{
}

void CTRMiniGameSRP_Group::onEnd()
{
}

void CTRMiniGameSRP_Group::onFrameMove(float fElapsed)
{
	__super::onFrameMove(fElapsed);

	if(m_pQuestion != nullptr)
	{
		m_pQuestion->Update(fElapsed);
	}
}

bool CTRMiniGameSRP_Group::Func_CloseBtn(CGUIControl * _pDlg)
{
	closeDialog();
	return true;
}


bool CTRMiniGameSRP_Group::Func_ScissorsBtn(CGUIControl * _pDlg)
{
	if(m_pChoiceSRP == nullptr)
	{
		return false;
	}

	m_pChoiceSRP->UpdateSelectSRP(m_pChoiceSRP->GetESelectSRPToInt(0));
	return true;
}

bool CTRMiniGameSRP_Group::Func_RockBtn(CGUIControl * _pDlg)
{
	if(m_pChoiceSRP == nullptr)
	{
		return false;
	}

	m_pChoiceSRP->UpdateSelectSRP(m_pChoiceSRP->GetESelectSRPToInt(1));
	return true;
}

bool CTRMiniGameSRP_Group::Func_PaperBtn(CGUIControl * _pDlg)
{
	if(m_pChoiceSRP == nullptr)
	{
		return false;
	}

	m_pChoiceSRP->UpdateSelectSRP(m_pChoiceSRP->GetESelectSRPToInt(2));
	return true;
}

bool CTRMiniGameSRP_Group::Func_StartBtn(CGUIControl * _pDlg)
{
	ChangeState(STATE::STATE_OPEN);

	return true;
}

string CTRMiniGameSRP_Group::GetNPCMent(ENpcMent _eCurNpcMent)
{
	switch(_eCurNpcMent)
	{
	case CTRMiniGameSRP::NMG_WAIT_START:
		// "�ٵ� �𿩺��� ����."
		return m_mapMent[make_tuple(1, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMG_WAIT_END:
		// "��! ����� ���� �� ������<br>�����غ���!!"
		return m_mapMent[make_tuple(1, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMG_START_SELECTION_TIMER:
		// "������ ��ī�ο� Į�� ������" 
		// "������ ���̰� �����ϰԡ�" 
		// "���� ����� ������� ������" 
		// "�̹��� �� ���?<br>������."
		return m_mapMent[make_tuple(1, _eCurNpcMent, CRandomGen::instance.iRandom(0, 3))];

	case CTRMiniGameSRP::NMG_SELECT_TIMER_END:
		// "Ȯ����?<br>�װɷ� �� �ž�?"
		return m_mapMent[make_tuple(1, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMG_WIN_OVER_NPC:
		// "�׷���<br>�� ������ �Ǿ����!"
		return m_mapMent[make_tuple(1, _eCurNpcMent, 0)];

	case CTRMiniGameSRP::NMG_LOSE_OVER_NPC:
		// "���� �̰��?<br>�̾��ؼ� ��¼��?"
		return m_mapMent[make_tuple(1, _eCurNpcMent, 0)];
	}
}



// ==================================================================
// ��ü��
// ==================================================================
void CTRMiniGameSRP_Group::OnGlobalRSPStartNotify(int message_in_str_table, int left_time)
{
}

void CTRMiniGameSRP_Group::OnGlobalRSPEnterAck(eServer_GLOBAL_RSP_ENTER_ACK_TYPE ack, int base_reward, const std::vector<int>& round_rewards, int selection_limit, int time2round_start)
{
}

void CTRMiniGameSRP_Group::OnGlobalRSPCurrentUserNotify(int delta_user, int user_in_playing)
{
}

void CTRMiniGameSRP_Group::OnGlobalRSPGameStartNotify(int left_time_to_input, int current_state)
{
}

void CTRMiniGameSRP_Group::OnGlobalRSPSelectionAck(eServer_GLOBAL_RSP_SELECTION_ACK_TYPE ack, eRSP_SELECTION selection, int left_selection_count, int current_reward_state)
{
}

void CTRMiniGameSRP_Group::OnGlobalRSPSelectionInfoNotify(const int(&selection_count_delta)[eRSP_SELECTION_COUNT], const int(&selection_count)[eRSP_SELECTION_COUNT])
{
}

void CTRMiniGameSRP_Group::OnGlobalRSPSelectionResultNotify(eRSP_SELECTION selection, eRSP_SELECTION_RESULT result, int current_reward_state, int current_state)
{
}
