#include "Statistics.h"
#include"Screen.h"

int Statistics::totalRevenue(Screen* pScreen)
{
	int count = 0, total = 0;
	int i = 0, j = 0;
	Ticket** pseatArray = pScreen->getTicketArray();

	for (i = 0; i < pScreen->getRowMax(); i++) {
		for (j = 0; j < pScreen->getColMax(); j++) {
			if (pseatArray[i][j].getCheck() == SEAT_COMPLETION_MARK) {
				total += pseatArray[i][j].getPayAmount();
			}
		}
	}
	
	return total;
}

int Statistics::totalSalesCount(Screen* pScreen)
{
	int count = 0;
	int i = 0, j = 0;
	Ticket** pseatArray = pScreen->getTicketArray();

	for (i = 0; i < pScreen->getRowMax(); i++) {
		for (j = 0; j < pScreen->getColMax(); j++) {
			if (pseatArray[i][j].getCheck() == SEAT_COMPLETION_MARK) {
				count++;
			}
		}
	}

	return count;
}
