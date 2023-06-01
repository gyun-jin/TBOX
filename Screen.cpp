#include <iostream>
#include <string>
#include "Screen.h"
#include "Pay.h"
using namespace std;

Screen::Screen(string name, int price, int row, int col) {
	strMovieName = name;
	nRowMax = row;
	nColMax = col;
	nTicketPrice = price;
	nCurrentReservedId = 100;
	pSeatArray = new Ticket * [nRowMax];

	for (int r = 0; r < nRowMax; r++) {
		pSeatArray[r] = new Ticket[nColMax];
	}
	for (int i = 0; i < nRowMax; i++) {
		for (int j = 0; j < nColMax; j++) {
			pSeatArray[i][j].setCheck(SEAT_EMPTY_MARK);
		}
	}
}


Screen::~Screen(){
	for (int r = 0; r < nRowMax; r++) {
		delete[] pSeatArray[r];
	}
	delete[] pSeatArray;
}

	// 영화 정보
	void Screen::showMovieMenu()
	{
		cout << "-------------------------------------------" << endl;
		cout << "  메뉴 : " << strMovieName << endl;
		cout << "-------------------------------------------" << endl;
		cout << "1. 상영 영화 정보 " << endl;
		cout << "2. 좌석 예약 현황 " << endl;
		cout << "3. 영화 예약 하기 " << endl;
		cout << "4. 영화 결제 하기 " << endl;
		cout << "7. 메인 메뉴 이동 \n" << endl;
	}

	// 좌석 현황
	void Screen::showSeatMap()
	{
		cout << "\t[ 좌석 예약 현황 ] " << endl;
		cout << "\t";
		for (int j = 0; j < nColMax; j++) {	// 좌석 열 [1] [2] ...
			cout << "[" << j + 1 << "] ";
		}
		cout << endl;
		for (int i = 0; i < nRowMax; i++) {	// 좌석 행 [1]		[-][-]...
			cout << "[" << i + 1 << "]\t";
			for (int j = 0; j < nColMax; j++) {
				cout << "[" << pSeatArray[i][j].getCheck() << "] ";
			}
			cout << endl;
		}
	}

	// 예약 하기
	void Screen::reserveTicket()
	{
		int row, col;
		cout << "  [ 좌석 예약 ]" << endl;
		cout << "좌석 행 번호 입력(1 - " << nRowMax << ") : "; cin >> row;
		if (row > nRowMax || row < 0) {
			printf("없는 좌석입니다.\n\n");
			return;
		}
		cout << "좌석 행 번호 입력(1 - " << nColMax << ") : "; cin >> col;
		if (col > nColMax || col < 0){
			printf("없는 좌석입니다.\n\n"); 
			return;
		}

		if (pSeatArray[row - 1][col - 1].getCheck() == SEAT_RESERVED_MARK || pSeatArray[row - 1][col - 1].getCheck() == SEAT_COMPLETION_MARK) {
			cout << "이미 예약된 자리입니다. " << "\n" << endl;
			return;
		}
		pSeatArray[row - 1][col - 1].setReservedID(nCurrentReservedId);		
		pSeatArray[row - 1][col - 1].setCheck(SEAT_RESERVED_MARK);		// 좌석 예약 완료
		pSeatArray[row - 1][col - 1].setSeat(row, col);
		cout << "행 [" << row << "] 열 [" << col << "] " << pSeatArray[row - 1][col - 1].getReservedID() << "예약 번호로 접수되었습니다. \n" << endl;
		nCurrentReservedId++;
	}

	// 결제 하기
	void Screen::Payment()
	{
		int reservedID, flag = 0, num = 0, i, j, amount = 0;
		string name;

		MobilePay MP(MOBILE_PHONE_INTEREST_RATE);
		BankTransfer BP(BANK_TRANSFER_INTEREST_RATE);
		CardPay CP(CREDIT_CARD_INTEREST_RATE);
		
		cout << "  [ 좌석 예약 결제 ]" << endl;
		cout << "예약 번호 입력 : "; cin >> reservedID;
		for (i = 0; i < nRowMax; i++) {
			for (j = 0; j < nColMax; j++) {
				if (pSeatArray[i][j].getReservedID() == reservedID) {	// 예약 번호 일치
					flag = 1;
					break;
				}
			}
			if (flag == 1) break;
		}

		if (flag == 1) {		// 예약 번호가 존재하면
			if (pSeatArray[i][j].getCheck() == SEAT_COMPLETION_MARK) {	// 이미 결제된 좌석인 경우
				cout << "이미 결제된 좌석입니다. " << endl;
				return;
			}

			cout << "-------------------------------------------" << endl;
			cout << "\t결제 방식 선택 " << endl;
			cout << "-------------------------------------------" << endl;
			cout << "1. 모바일 결제 " << endl;
			cout << "2. 은행 이체 결제 " << endl;
			cout << "3. 카드 결제 \t" << endl;
			cout << " 결제 방식(1~3) : "; cin >> num;

			double number;
			switch (num)
			{
			// 모바일 결제
			case 1:		
				cout << "\t[ 모바일 결제 ]" << endl;
				cout << "핸드폰 번호 입력(11자리수) : "; cin >> number;
				/*if (to_string(number).length() != 11) {
					cout << "잘못된 카드 번호 입력입니다. 다시 시도하세요." << endl;
					return;
				}*/
				cout << "이름 : "; cin >> name;

				amount = MP.charge(getTicketPrice());	// 결제 방식 별 금액
				pSeatArray[i][j].setPayAmount(amount);	// 결제 금액 저장
				cout << "TUKOREA 모바일 결제가 완료되었습니다. : " << pSeatArray[i][j].getPayAmount() << "\n" << endl;

				pSeatArray[i][j].setPayMethod(num);		// 결제 수단 저장
				pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);	
				break;
			
			// 은행 이체 결제
			case 2:		
				cout << "\t[ 은행 이체 결제 ]" << endl;
				cout << "은행 번호 입력(12자리수) : "; cin >> number;
				/*if (to_string(number).length() != 12) {
					cout << "잘못된 카드 번호 입력입니다. 다시 시도하세요." << endl;
					return;
				}*/

				cout << "이름 : "; cin >> name;
				amount = BP.charge(getTicketPrice());	// 결제 방식 별 금액
				pSeatArray[i][j].setPayAmount(amount);	// 결제 금액 저장
				cout << "TUKOREA 은행 결제가 완료되었습니다. : " << pSeatArray[i][j].getPayAmount() << "\n" << endl;

				pSeatArray[i][j].setPayMethod(num);		// 결제 수단 저장
				pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				break;
			
			// 신용카드 결제
			case 3:		
				cout << "\t[ 신용카드 결제 ]" << endl;
				cout << "카드 번호 입력(12자리수) : "; cin >> number;
				/*if (to_string(number).length() != 12) {
					cout << "잘못된 카드 번호 입력입니다. 다시 시도하세요." << endl;
					return;
				}*/
				cout << "이름 : "; cin >> name;

				amount = CP.charge(getTicketPrice());	// 결제 방식 별 금액
				pSeatArray[i][j].setPayAmount(amount);	// 결제 금액 저장
				cout << "TUKOREA 신용카드 결제가 완료되었습니다. : " << pSeatArray[i][j].getPayAmount() << "\n" << endl;

				pSeatArray[i][j].setPayMethod(num);		// 결제 수단 저장
				pSeatArray[i][j].setCheck(SEAT_COMPLETION_MARK);
				break;
			default:
				break;
			}
		}

		else {
			cout << "예약 번호가 존재하지 않습니다. " << endl;
			return;
		}
	}

	// CGV 영화 정보
	void CGVScreen::showMovieInfo()
	{
		cout << "-------------------------------------------" << endl;
		cout << "      [   " << strMovieName << "  ]" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "영화관 : CGV 영화 1관" << endl;
		cout << "주인공 : 빈 디젤, 제이슨 모모아, 제이슨 스타뎀" << endl;
		cout << "줄거리 : 돔(빈 디젤)과 그의 패밀리 앞에 나타난 운명의 적 단테 ... " << endl;
		cout << "가격 : " << nTicketPrice << endl << endl;
	}

	// LotteCinema 영화 정보
	void LotteCinemaScreen::showMovieInfo()
	{
		cout << "-------------------------------------------" << endl;
		cout << "      [   " << strMovieName << "  ]" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "영화관 : 롯데시데마 영화 2관" << endl;
		cout << "주인공 : 스즈메, 소타" << endl;
		cout << "줄거리 : 규슈의 한적한 마을에 살고 있는 소녀 스즈메는 문을 찾아 ... " << endl;
		cout << "가격 : " << nTicketPrice << endl << endl;
	}

	// Megabox 영화 정보
	void MegaboxScreen::showMovieInfo()
	{
		cout << "-------------------------------------------" << endl;
		cout << "      [   " << strMovieName << "  ]" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "영화관 : 메가박스 영화 3관" << endl;
		cout << "주인공 : 라이언 고슬링, 레이첼 맥아담스" << endl;
		cout << "줄거리 : 17살, 노아는 밝고 순수한 앨리를 보고 첫눈에 반한다 ... " << endl;
		cout << "가격 : " << nTicketPrice << endl << endl;
	}
