#include "stdafx.h"
#include "MainGUI.h"

CMainGUI::CMainGUI()
{
}

CMainGUI::~CMainGUI()
{
	closeDialog();
}

bool CMainGUI::onButtonClick()
{
	// Button : ���� ���� �� ��ư�� �����ٸ�...
	// ���� : Ÿ�̸Ӱ� �����ٸ�(Ÿ�̸Ӱ� �������϶� Ŭ���Ǽ� �ȵȴ�.)
	// ���� ���� �� ��ư�� Ŭ���ϸ� �ش� ���� ĳ���Ѵ�.
	// Ȯ�� ��ư�� Ȱ��ȭ�Ѵ�.

	// Button : Ȯ�� ��ư�� �����ٸ�...
	// m_eScissorsRockPaper�� ĳ�̵� ���� ������������ �ƴϴ� == ���� �������� �ʾҴ�.
	if(m_eScissorsRockPaper != SRP_END)
	{
		RequestGameResult(m_eScissorsRockPaper);
	}
	else
	{
		// �ƹ� ó���� ����.
		// ���� ���� �� ��ư�� Ŭ������ ������ �ش� ��ư�� ��Ȱ��ȭ ��ų �Ŷ�.
	}

	return true;
}

void CMainGUI::showDialog()
{
}

void CMainGUI::closeDialog()
{
}

void CMainGUI::InitMent()
{
	m_mapMent.clear();
	map<tuple<int, int>, string>().swap(m_mapMent);

	// ��� ������ �Ľ��ؼ� ĳ���Ѵ�.
	// �Ľ� �Լ��� �׳� �� Ŭ������ �����Ѵ�.
	//m_mapMent.insert(make_pair(make_tuple(1, 1), ""));

	// ������� �����ߴٸ� �� Ŭ������ ��Ʈ ��θ� ĳ���� ���¿��� �Ѵ�.
	// �ʿ��ϸ� �ٷ� ������ �� �� �ְԲ�
	// �� �Լ��� Ŭ���� ������ �ѹ��� ȣ��Ǿ� �Ѵ�.
}

void CMainGUI::UpdateRewardItem()
{
	// ĳ�̵� ���� ������ ��� ������ ������ ó���Ѵ�.
	
	// ���� ������ ����� �����Ѵ�.
	for(auto& i : m_arrayImage)
	{
		// ���⼭ ������ �̸�, �̹��� �̷� �͵��� �����Ѵ�.
	}
}

void CMainGUI::UpdateRewardSparkle(int& _nRewardLevel)
{
	// ���� ���� ������ ��¦�Ÿ��� ȿ���� ���ش�.
	m_arrayImage[m_nCurRewardLevel].OffSparkle();

	// ���� ���� ���� ���� �����Ѵ�.
	m_nCurRewardLevel = _nRewardLevel;

	// �¸��� �ش� �ܰ��� ���� �������� ��¦�̴� ó���� �Ѵ�.
	m_arrayImage[m_nCurRewardLevel].OnSparkle();
}

void CMainGUI::ReceiveRewardItemInfo()
{
	// ���� ������ ����� �޴´�.
	// ���� ������ ����� ������� ���� �װ� �����صд�.
	// �׷��� ���� ĳ�̵� ����� ���� �ٽ� ĳ���Ѵ�.

	// ���� ������ ��� ���� �Լ��� ȣ���Ѵ�.
	UpdateRewardItem();
}

void CMainGUI::RequestItemInfo()
{
	// ���� ������ ����� ��û�Ѵ�.
}

void CMainGUI::ReceiveGameResult(int _nResult)
{
	// _nResult : ���� �º� ��� ��
	switch(_nResult)
	{
	case CMainGUI::RR_WIN:
		m_nCurRewardLevel += m_nCurRewardLevel < ERewardLevel::RL_3 ? 1 : 0;
		UpdateRewardSparkle(m_nCurRewardLevel);
		break;

	case CMainGUI::RR_LOSE:
		// �й� ȭ���� ����Ѵ�.
		// ���� ���� â�� ����.
		break;

	case CMainGUI::RR_DRAW:
		break;

	default:
		// ���� ó��
		break;
	}

	
	
	// ���� ����� �޴´�.

	// ���� ���� ������ ���� ĳ�̵� ���� �����̶� ���ٸ�?
	// ���º��̹Ƿ�

	// ���� ���� ���� > ���� ĳ�̵� ���� ����
	// �̰����Ƿ� ���󷹺��� �ٽ� ĳ���Ѵ�.
	int nRewardLevel = 0;
	// ��������� ��¦�Ÿ��� �ٽ� �����Ѵ�.
	UpdateRewardSparkle(nRewardLevel);

	// �й��ߴٸ�...
	// 
}

void CMainGUI::RequestGameResult(EScissorsRockPaper m_eScissorsRockPaper)
{
	// ���������� ����� ��û�Ѵ�.
	// �Ƹ� �������״� int �������� ������ �ҰŴ�.(0,1,2 �̷�������)
}
