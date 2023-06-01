#include <iostream>
#include <string>
#include "Screen.h"
#include "TicketBox.h"
using namespace std;

int main() {
	TUKoreaTBox tBox;
	Screen* screen = NULL;
	bool bScreenMenu = true;
	int select = 0;
	tBox.Initialize(); // 3개의 스크린 객체 생성

	while (1) {
		if (bScreenMenu) {
			screen = tBox.selectMenu();
			bScreenMenu = false;
			if (!screen) return 0;
		}
		screen->showMovieMenu();
		cout << "메뉴를 선택하세요: ";
		cin >> select; cout << endl;
		switch (select) {
		// 영화 정보
		case 1: 
			screen->showMovieInfo();
			break;
		// 좌석 현황
		case 2: 
			screen->showSeatMap();
			break;
		// 예약 하기
		case 3:
			screen->reserveTicket();
			break;
		// 결제 하기
		case 4:
			screen->Payment();
			break;
		// 스크린 메인 메뉴
		case 7: 
			bScreenMenu = true;
			break;
		}
	}
	return 0;
}