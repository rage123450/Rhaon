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
	// Button : 가위 바위 보 버튼을 누른다면...
	// 조건 : 타이머가 끝났다면(타이머가 진행중일땐 클릭되선 안된다.)
	// 가위 바위 보 버튼을 클릭하면 해당 값을 캐싱한다.
	// 확인 버튼을 활성화한다.

	// Button : 확인 버튼을 누른다면...
	// m_eScissorsRockPaper에 캐싱된 값이 가위바위보가 아니다 == 아직 선택하지 않았다.
	if(m_eScissorsRockPaper != SRP_END)
	{
		RequestGameResult(m_eScissorsRockPaper);
	}
	else
	{
		// 아무 처리가 없다.
		// 가위 바위 보 버튼을 클릭하지 않으면 해당 버튼을 비활성화 시킬 거라서.
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

	// 대사 파일을 파싱해서 캐싱한다.
	// 파싱 함수는 그냥 이 클래스에 구현한다.
	//m_mapMent.insert(make_pair(make_tuple(1, 1), ""));

	// 여기까지 진입했다면 이 클래스는 멘트 모두를 캐싱한 상태여야 한다.
	// 필요하면 바로 가져다 쓸 수 있게끔
	// 이 함수는 클래스 생성시 한번만 호출되야 한다.
}

void CMainGUI::UpdateRewardItem()
{
	// 캐싱된 보상 아이템 목록 정보를 가지고 처리한다.
	
	// 보상 아이템 목록을 갱신한다.
	for(auto& i : m_arrayImage)
	{
		// 여기서 아이템 이름, 이미지 이런 것들을 셋팅한다.
	}
}

void CMainGUI::UpdateRewardSparkle(int& _nRewardLevel)
{
	// 현재 보상 아이템 반짝거리는 효과를 꺼준다.
	m_arrayImage[m_nCurRewardLevel].OffSparkle();

	// 현재 보상 레벨 값을 변경한다.
	m_nCurRewardLevel = _nRewardLevel;

	// 승리시 해당 단계의 보상 아이템이 반짝이는 처리를 한다.
	m_arrayImage[m_nCurRewardLevel].OnSparkle();
}

void CMainGUI::ReceiveRewardItemInfo()
{
	// 보상 아이템 목록을 받는다.
	// 보상 아이템 목록이 어떤식으로 오든 그걸 저장해둔다.
	// 그러면 현재 캐싱된 목록을 비우고 다시 캐싱한다.

	// 보상 아이템 목록 갱신 함수를 호출한다.
	UpdateRewardItem();
}

void CMainGUI::RequestItemInfo()
{
	// 보상 아이템 목록을 요청한다.
}

void CMainGUI::ReceiveGameResult(int _nResult)
{
	// _nResult : 라운드 승부 결과 값
	switch(_nResult)
	{
	case CMainGUI::RR_WIN:
		m_nCurRewardLevel += m_nCurRewardLevel < ERewardLevel::RL_3 ? 1 : 0;
		UpdateRewardSparkle(m_nCurRewardLevel);
		break;

	case CMainGUI::RR_LOSE:
		// 패배 화면을 출력한다.
		// 보상 지급 창을 띄운다.
		break;

	case CMainGUI::RR_DRAW:
		break;

	default:
		// 에러 처리
		break;
	}

	
	
	// 게임 결과를 받는다.

	// 받은 보상 레벨과 현재 캐싱된 보상 레벨이랑 같다면?
	// 무승부이므로

	// 받은 보상 레벨 > 현재 캐싱된 보상 레벨
	// 이겼으므로 보상레벨을 다시 캐싱한다.
	int nRewardLevel = 0;
	// 보상아이템 반짝거림을 다시 갱신한다.
	UpdateRewardSparkle(nRewardLevel);

	// 패배했다면...
	// 
}

void CMainGUI::RequestGameResult(EScissorsRockPaper m_eScissorsRockPaper)
{
	// 가위바위보 결과를 요청한다.
	// 아마 서버한테는 int 형식으로 보내야 할거다.(0,1,2 이런식으로)
}
