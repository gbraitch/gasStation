/*
Name: Gursewak Braitch and Yuedong (Rick) Cheng
Student #: 21730163 and 24250169
Lab Section: L1A
*/

#ifndef __Customer__
#define __Customer__


#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "C:\\RTExamples\\rt.h"

CSemaphore Queue1("Queue1", 1, 1);
CSemaphore Queue2("Queue2", 1, 1);
CSemaphore Queue3("Queue3", 1, 1);
CSemaphore Queue4("Queue4", 1, 1);

CSemaphore Pump1("Pipe1", 1, 1);
CSemaphore Pump2("Pipe2", 1, 1);
CSemaphore Pump3("Pipe3", 1, 1);
CSemaphore Pump4("Pipe4", 1, 1);

class Customer1 : public ActiveClass
{
private:
	const char * NameArray[6] = { "Joseph Yu      ", "Mark Hamill   ", "Isaac Newton  ", "Jake Smith    ", "Average Joe   ", "Derick Rose   " };	//Array to pull name from
	int CreditArray[6] = {98123,13345,98760,58034,48503,32034 };	//Array to choose credit card number from
	int FuelChoices[4] = {87,89,91,93};

	char MyName[14];	//Name of Customer
	int MyCreditNum;	//What their credit card number is
	int FuelNeed;
	int FuelChoice;
	
public:
	Customer1()	//Initialize pump with its number
	{
		srand(1);
		strcpy(MyName, NameArray[rand() % 5]);
		srand(2);
		MyCreditNum = rand() % 99999;
		srand(3);
		FuelNeed = rand() % 70;
		srand(4);
		FuelChoice = FuelChoices[rand()%3];
	}


	int main(void)
	{
		BOOL RefillStatus = FALSE;
		BOOL CreditValid = FALSE;
		BOOL Dispense = FALSE;
		Queue1.Wait();

		CPipe MyPipe("Pipe1");

		Pump1.Wait();

		MyPipe.Write(&MyName, sizeof(MyName));
		SLEEP(500);

		MyPipe.Write(&MyCreditNum, sizeof(MyCreditNum));
		SLEEP(500);

		Pump1.Signal();
		SLEEP(200);

		Pump1.Wait();
		MyPipe.Read(&CreditValid, sizeof(CreditValid));

		if (CreditValid == FALSE) {
			Pump1.Signal();
			Queue1.Signal();
			return 0;
		}

		MyPipe.Write(&FuelNeed, sizeof(FuelNeed));
		SLEEP(500);
		MyPipe.Write(&FuelChoice, sizeof(FuelChoice));

		Pump1.Signal();
		SLEEP(200);
		Pump1.Wait();
		MyPipe.Read(&Dispense, sizeof(Dispense));

		if (Dispense = FALSE) {
			Pump1.Signal();
			Queue1.Signal();
			return 0;
		}

		Pump1.Signal();
		Sleep(200);
		Pump1.Wait();
		Pump1.Signal();
		Queue1.Signal();

		return 0;
	}

};

class Customer2 : public ActiveClass
{
private:
	const char * NameArray[6] = { "Joseph Yu      ", "Mark Hamill   ", "Isaac Newton  ", "Jake Smith    ", "Average Joe   ", "Derick Rose   " };	//Array to pull name from
	int CreditArray[6] = { 98123,13345,98760,58034,48503,32034 };	//Array to choose credit card number from
	int FuelChoices[4] = { 87,89,91,93 };

	char MyName[14];
	int MyCreditNum;	//What their credit card number is
	int FuelNeed;
	int FuelChoice;

public:
	Customer2()	//Initialize pump with its number
	{
		srand(5);
		strcpy(MyName, NameArray[rand() % 5]);
		srand(222);
		MyCreditNum = rand() % 99999;
		srand(6298);
		FuelNeed = rand() % 70;
		srand(790);
		FuelChoice = FuelChoices[rand() % 3];
	}


	int main(void)
	{
		BOOL RefillStatus = FALSE;
		BOOL CreditValid = FALSE;
		BOOL Dispense = FALSE;
		Queue2.Wait();

		CPipe MyPipe("Pipe2");

		Pump2.Wait();

		MyPipe.Write(&MyName, sizeof(MyName));

		SLEEP(500);

		MyPipe.Write(&MyCreditNum, sizeof(MyCreditNum));
		SLEEP(500);

		Pump2.Signal();
		SLEEP(200);

		Pump2.Wait();
		MyPipe.Read(&CreditValid, sizeof(CreditValid));

		if (CreditValid == FALSE) {
			Pump2.Signal();
			Queue2.Signal();
			return 0;
		}

		MyPipe.Write(&FuelNeed, sizeof(FuelNeed));
		MyPipe.Write(&FuelChoice, sizeof(FuelChoice));

		Pump2.Signal();
		SLEEP(200);
		Pump2.Wait();
		MyPipe.Read(&Dispense, sizeof(Dispense));

		if (Dispense = FALSE) {
			Pump2.Signal();
			Queue2.Signal();
			return 0;
		}

		Pump2.Signal();
		Sleep(200);
		Pump2.Wait();
		Pump2.Signal();
		Queue2.Signal();

		return 0;
	}

};


class Customer3 : public ActiveClass
{
	const char * NameArray[6] = { "Joseph Yu      ", "Mark Hamill   ", "Isaac Newton  ", "Jake Smith    ", "Average Joe   ", "Derick Rose   " };	//Array to pull name from
	int CreditArray[6] = { 98123,13345,98760,58034,48503,32034 };	//Array to choose credit card number from
	int FuelChoices[4] = { 87,89,91,93 };

	char MyName[14];
	int MyCreditNum;	//What their credit card number is
	int FuelNeed;
	int FuelChoice;

public:
	Customer3()	//Initialize pump with its number
	{
		srand(0);
		strcpy(MyName, NameArray[rand() % 5]);
		srand(28);
		MyCreditNum = rand() % 99999;
		srand(200);
		FuelNeed = rand() % 70;
		srand(29);
		FuelChoice = FuelChoices[rand() % 3];
	}


	int main(void)
	{
		BOOL RefillStatus = FALSE;
		BOOL CreditValid = FALSE;
		BOOL Dispense = FALSE;
		Queue3.Wait();

		CPipe MyPipe("Pipe3");

		Pump3.Wait();

		MyPipe.Write(&MyName, sizeof(MyName));

		SLEEP(500);

		MyPipe.Write(&MyCreditNum, sizeof(MyCreditNum));
		SLEEP(500);

		Pump3.Signal();
		SLEEP(200);

		Pump3.Wait();
		MyPipe.Read(&CreditValid, sizeof(CreditValid));

		if (CreditValid == FALSE) {
			Pump3.Signal();
			Queue3.Signal();
			return 0;
		}

		MyPipe.Write(&FuelNeed, sizeof(FuelNeed));
		MyPipe.Write(&FuelChoice, sizeof(FuelChoice));

		Pump3.Signal();
		SLEEP(200);
		Pump3.Wait();
		MyPipe.Read(&Dispense, sizeof(Dispense));

		if (Dispense = FALSE) {
			Pump3.Signal();
			Queue3.Signal();
			return 0;
		}

		Pump3.Signal();
		Sleep(200);
		Pump3.Wait();
		Pump3.Signal();
		Queue3.Signal();

		return 0;
	}

};

class Customer4 : public ActiveClass
{
private:
	const char * NameArray[6] = { "Joseph Yu      ", "Mark Hamill   ", "Isaac Newton  ", "Jake Smith    ", "Average Joe   ", "Derick Rose   " };	//Array to pull name from
	int CreditArray[6] = { 98123,13345,98760,58034,48503,32034 };	//Array to choose credit card number from
	int FuelChoices[4] = { 87,89,91,93 };

	char MyName[14];
	int MyCreditNum;	//What their credit card number is
	int FuelNeed;
	int FuelChoice;

public:
	Customer4()	//Initialize pump with its number
	{
		srand(76);
		strcpy(MyName, NameArray[rand() % 5]);
		srand(229);
		MyCreditNum = rand() % 99999;
		srand(129);
		FuelNeed = rand() % 70;
		srand(15);
		FuelChoice = FuelChoices[rand() % 3];
	}


	int main(void)
	{
		BOOL RefillStatus = FALSE;
		BOOL CreditValid = FALSE;
		BOOL Dispense = FALSE;
		Queue4.Wait();

		CPipe MyPipe("Pipe4");

		Pump4.Wait();

		MyPipe.Write(&MyName, sizeof(MyName));

		SLEEP(500);

		MyPipe.Write(&MyCreditNum, sizeof(MyCreditNum));
		SLEEP(500);

		Pump4.Signal();
		SLEEP(200);

		Pump4.Wait();
		MyPipe.Read(&CreditValid, sizeof(CreditValid));

		if (CreditValid == FALSE) {
			Pump4.Signal();
			Queue4.Signal();
			return 0;
		}

		MyPipe.Write(&FuelNeed, sizeof(FuelNeed));
		MyPipe.Write(&FuelChoice, sizeof(FuelChoice));

		Pump4.Signal();
		SLEEP(200);
		Pump4.Wait();
		MyPipe.Read(&Dispense, sizeof(Dispense));

		if (Dispense = FALSE) {
			Pump3.Signal();
			Queue3.Signal();
			return 0;
		}

		Pump4.Signal();
		Sleep(200);
		Pump4.Wait();
		Pump4.Signal();
		Queue4.Signal();

		return 0;
	}

};


#endif