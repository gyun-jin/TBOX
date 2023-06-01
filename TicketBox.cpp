#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"

using namespace std;

TUKoreaTBox::TUKoreaTBox()
{
	pCGVScreen = NULL;
	pLotteCinemaScreen = NULL;
	pMegaBoxScreen = NULL;
}

TUKoreaTBox::~TUKoreaTBox()
{
	delete pCGVScreen;
	delete pLotteCinemaScreen;
	delete pMegaBoxScreen;
}

Screen* TUKoreaTBox::selectMenu()
{
	int num;
	cout << "--------------------------------" << endl;
	cout << "     상영관 메인 메뉴           " << endl;
	cout << "--------------------------------" << endl;
	cout << "1. CJ CGV      영화 1관" << endl;
	cout << "2. 롯데시네마  영화 2관" << endl;
	cout << "3. 메가박스    영화 3관" << endl;
	cout << "9. 통계관리            " << endl;
	cout << "\n선택(1~3, 9) 그 외 종료 : "; cin >> num;
	cout << endl;

	switch (num)
	{
	case 1:
		return pCGVScreen;
	case 2:
		return pLotteCinemaScreen;
	case 3:
		return pMegaBoxScreen;
	case 9:
		Manage();
		return NULL;
	default:
		break;
	}
}

// 스크린 객체 생성
void TUKoreaTBox::Initialize() {
	// Screen(영화제목, 티켓가격, 좌석(nRowMax), 좌석(nColMax))
	pCGVScreen = new CGVScreen("분노의 질주: 라이드 오어 다이", 15000, 8, 8);
	pLotteCinemaScreen = new LotteCinemaScreen("스즈메의 문단속", 12000, 10, 10);
	pMegaBoxScreen = new MegaboxScreen("노트북", 20000, 8, 8);
}

void TUKoreaTBox::Manage()
{
	Statistics Static;
	string password;

	cout << "--------------------------------" << endl;
	cout << "     관리자 메뉴           " << endl;
	cout << "--------------------------------" << endl;
	cout << "관리자 비밀번호 입력 : "; cin >> password;

	if (TICKETBOX_MANAGER_PWD == password) {	// 관리자 암호 일치
		cout << "1. CJ CGV 상영관 결제금액 : " << Static.totalRevenue(pCGVScreen) << endl;
		cout << "1. 롯데시네마 상영관 결제금액 : " << Static.totalRevenue(pLotteCinemaScreen) << endl;
		cout << "1. 메가박스 상영관 결제금액 : " << Static.totalRevenue(pMegaBoxScreen) << endl;
		cout << "4. 전제 티켓 판매량 : " << Static.totalSalesCount(pCGVScreen) + Static.totalSalesCount(pLotteCinemaScreen) + Static.totalSalesCount(pMegaBoxScreen) << endl;

		return;
	}
	else
		cout << "비밀번호가 틀렸습니다. " << endl;
}

