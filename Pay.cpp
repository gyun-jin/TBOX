#include<iostream>
#include "Pay.h"

int MobilePay::charge(int amount)
{
	amount = amount + (int)(amount * interest);
	
	return amount;
}

int CardPay::charge(int amount)
{
	amount = amount + (int)(amount * interest);
	
	return amount;
}

int BankTransfer::charge(int amount)
{
	amount = amount + (int)(amount * interest);
	
	return amount;
}
