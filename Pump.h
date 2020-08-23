/*
Name: Gursewak Braitch and Yuedong (Rick) Cheng
Student #: 21730163 and 24250169
Lab Section: L1A
*/

#ifndef __Pump__
#define __Pump__

#define COST87 1.00
#define COST89 1.05
#define COST91 1.10
#define COST93 1.15


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\RTExamples\rt.h"
#include "Customer.h"
#include "FuelTankMonitor.h"

// Mutexes for printing to the second DOS window
CMutex PumpDOS("PumpDOS");

FuelTank FuelTankMonitor;

// DataPool that has all pump information to be written to the pump status datapool
struct pumpdatapool {
	int pumpNum;
	BOOL Dispense;
	int FuelChoice;
	int MyCreditNum;
	int FuelNeed;
	char MyName[14];
	BOOL CreditValid;
	BOOL refuelComplete;
};

class Pump : public ActiveClass
{
private:
	char MyName[14];
	int pumpNum;
	BOOL Dispense;
	int FuelChoice;
	int MyCreditNum;
	int FuelNeed;
	int add;
	double price; 
	char PumpName[1];

	int main(void);
public:
	Pump(int pumpNumber);
	void printCustInfo();
	void printCustFuelInfo();
	void printRTFuel(int j);
};

Pump::Pump(int pumpNumber) {
	pumpNum = pumpNumber;
	add = 0;
	if (pumpNum == 1)
	{
		add = 0;
	}
	else if (pumpNum == 2)
	{
		add = 35;
	}
	else if (pumpNum == 3)
	{
		add = 70;
	}
	else if (pumpNum == 4)
	{
		add = 105;
	}
	
}

void Pump::printCustInfo() {

	PumpDOS.Wait();
	MOVE_CURSOR(add, 0);
	printf("Cust Name: %s\n", MyName);
	fflush(stdout);
	MOVE_CURSOR(add, 1);
	printf("Cust Credit Card number: %d\n", MyCreditNum);
	fflush(stdout);
	PumpDOS.Signal();

}

void Pump::printCustFuelInfo() {
	PumpDOS.Wait();
	MOVE_CURSOR(add, 2);
	printf("Cust Fuel Need: %d\n", FuelNeed);
	fflush(stdout);
	MOVE_CURSOR(add, 3);
	printf("Cust Fuel Grade Choice: %d\n", FuelChoice);
	fflush(stdout);
	PumpDOS.Signal();
}

void Pump::printRTFuel(int j) {
	PumpDOS.Wait();
	MOVE_CURSOR(add, 4);
	printf("Current Fuel Dispensed: %.3lf\n", j*0.5+0.5);
	fflush(stdout);
	MOVE_CURSOR(add, 5);
	printf("Current Cost of Purchase: %.3lf\n", j*price+price);
	fflush(stdout);
	PumpDOS.Signal();
}

int Pump::main(void) {
	
	sprintf(PumpName, "%d", pumpNum);
	//std::string PumpName = std::to_string(pumpNum);
	Dispense = FALSE;

	// Create datapool to communicate between pump and GSC
	CDataPool pumpstatus("PumpStatus" + string(PumpName), sizeof(struct pumpdatapool));
	struct pumpdatapool *PumpStatusDP = (struct pumpdatapool *)(pumpstatus.LinkDataPool());

	CPipe MyPipe(string("Pipe") + string(PumpName));

	CSemaphore Pump(string("Pipe") + string(PumpName), 1, 1);

	CSemaphore cs(string("CS") + string(PumpName), 0, 1);
	CSemaphore ps(string("PS") + string(PumpName), 1, 1);

	
	while (1) {
		while (MyPipe.TestForData() == NULL) {}

		Pump.Wait();

		MyPipe.Read(&MyName[0], sizeof(MyName));
		MyPipe.Read(&MyCreditNum, sizeof(MyCreditNum));
		
	

		printCustInfo();

		// Send name and credit card number to datapool
		// Producer, consumer problem
		ps.Wait();
		PumpStatusDP->MyCreditNum = MyCreditNum;
		for (int i = 0; i < 14; i++) {
			PumpStatusDP->MyName[i] = MyName[i];
		}

		cs.Signal();

		// CONSUMER (GSC) NEEDS TO WAIT FOR CS AND THEN SIGNAL PS WHEN DONE
		SLEEP(200);
		// Receive OK for credit card and name
		// Pump is consumer, GSC is producer
		cs.Wait();
		MyPipe.Write(&(PumpStatusDP->CreditValid), sizeof(PumpStatusDP->CreditValid));
		SLEEP(200);
		ps.Signal();
		// PRODUCER (GSC) NEEDS TO WAIT ON PS, WRITE TO DATAPOOL, THEN SIGNAL CS

		Pump.Signal();

		SLEEP(200);
		if (PumpStatusDP->CreditValid == FALSE) {
			SLEEP(300);
		}
		else {

			Pump.Wait();
			// Read fuel choice and needed level
			MyPipe.Read(&FuelNeed, sizeof(FuelNeed));
			MyPipe.Read(&FuelChoice, sizeof(FuelChoice));

			switch (FuelChoice) {
			case 87: price = COST87;
			case 89: price = COST89;
			case 91: price = COST91;
			case 93: price = COST93;
			}

			printCustFuelInfo();

			// Pump is producer, gsc is consumer

			PumpStatusDP->FuelNeed = FuelNeed;
			PumpStatusDP->FuelChoice = FuelChoice;
			cs.Signal();
			//	CONSUMER (GSC) NEEDS TO WAIT ON CS AND THEN SIGNAL PS WHEN DONE
			SLEEP(200);

			// Pump is consumer, gsc is producer
			cs.Wait();

			Dispense = PumpStatusDP->Dispense;
			ps.Signal();
			// PRODUCER (GSC) NEEDS TO WAIT ON PS, WRITE TO DATAPOOL, THEN SIGNAL CS SO PUMP CAN READ

			MyPipe.Write(&Dispense, sizeof(Dispense));
			if (Dispense = TRUE) {
				ps.Wait();
				Dispense = FALSE;
				PumpStatusDP->Dispense = Dispense;
				ps.Signal();
				Pump.Signal();
				SLEEP(200);

				Pump.Wait(); // gains access of pipeline while refuelling

				for (int j = 0; j < 2 * FuelNeed; j++) {
					SLEEP(1000);
					printRTFuel(j);
					// CALL FuelTankMonitor.Decrement
					FuelTankMonitor.decrement(FuelChoice);
				}
				// pump writes to datapool that the refuelling is completed.
				ps.Wait();
				PumpStatusDP->refuelComplete = TRUE;
				PumpDOS.Wait();
				MOVE_CURSOR(add, 0);
				printf("              ");
				fflush(stdout);
				MOVE_CURSOR(add,  1);
				printf("			            ");
				fflush(stdout);
				MOVE_CURSOR(add,  2);
				printf("		     	   ");
				fflush(stdout);
				MOVE_CURSOR(add, 3);
				printf("			 	   ");
				fflush(stdout);
				MOVE_CURSOR(add, 4);
				printf("			   	     ");
				fflush(stdout);
				MOVE_CURSOR(add, 5);
				printf("				     ");
				fflush(stdout);
				MOVE_CURSOR(add, 0);
				printf("Customer has left the pump");
				fflush(stdout);
				SLEEP(1000);
				MOVE_CURSOR(add, 0);
				printf("				");
				fflush(stdout);
				PumpDOS.Signal();


				SLEEP(200);
				cs.Signal();
				Pump.Signal(); // signal pipe after refuel done
				SLEEP(500);
			}
			else {
				Pump.Signal();
				SLEEP(500);
			}
		}
		
	}
}

#endif