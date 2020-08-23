/*
Name: Gursewak Braitch and Yuedong (Rick) Cheng
Student #: 21730163 and 24250169
Lab Section: L1A
*/

#ifndef __FuelTank__
#define __FuelTank__

#include "C:\RTExamples\rt.h"
#include <stdio.h>
#include <stdlib.h>


class FuelTank
{
private:
	struct FuelTankStruct {
		double Octane87Level;
		double Octane89Level;
		double Octane91Level;
		double Octane93Level;
	};

	// EACH FUELTANK HAS MAX OF 500L
	CMutex *Octane87Mutex;
	CMutex *Octane89Mutex;
	CMutex *Octane91Mutex;
	CMutex *Octane93Mutex;

	CDataPool *FuelTankDP;

	FuelTankStruct *FuelTankPTR;


public:
	BOOL decrement(int octane);
	void refill(int octane);
	double readLevel(int octane);
	FuelTank();
	~FuelTank();
};

BOOL FuelTank::decrement(int octane) {
	BOOL refill = FALSE;
	// ALWAYS DECREMENT BY 0.5
	// DON'T KNOW IF I NEED TO RETURN A BOOL REFILL BECAUSE GSC ALREADY CHECKS IF FUEL LEVEL IS ENOUGH BEFORE REFUELLING EVEN BEGINS
	if (octane == 87) {
		Octane87Mutex->Wait(); // Wait for resource to be available
		FuelTankPTR->Octane87Level = FuelTankPTR->Octane87Level - 100;
		Octane87Mutex->Signal(); // Signal so resource is available

		refill = TRUE;
	}

	else if (octane == 89) {
		Octane89Mutex->Wait();
		FuelTankPTR->Octane89Level = FuelTankPTR->Octane89Level - 0.5;
		Octane89Mutex->Signal();

		refill = TRUE;
	}

	else if (octane == 91) {
		Octane91Mutex->Wait();
		FuelTankPTR->Octane91Level = FuelTankPTR->Octane91Level - 0.5;
		Octane91Mutex->Signal();

		refill = TRUE;
	}

	else if (octane == 93) {
		Octane93Mutex->Wait();
		FuelTankPTR->Octane93Level = FuelTankPTR->Octane93Level - 0.5;
		Octane93Mutex->Signal();

		refill = TRUE;
	}

	else {
		printf("Error, fuel type does not exist. Returning 0 as fuel level....\n");
	}

	return refill;
}

void FuelTank::refill(int octane) {

	if (octane == 87) {
		Octane87Mutex->Wait(); // Wait for resource to be available
		FuelTankPTR->Octane87Level = 500;
		Octane87Mutex->Signal(); // Signal so resource is available
	}

	else if (octane == 89) {
		Octane89Mutex->Wait();
		FuelTankPTR->Octane89Level = 500;
		Octane89Mutex->Signal();
	}

	else if (octane == 91) {
		Octane91Mutex->Wait();
		FuelTankPTR->Octane91Level = 500;
		Octane91Mutex->Signal();
	}

	else if (octane == 93) {
		Octane93Mutex->Wait();
		FuelTankPTR->Octane93Level = 500;
		Octane93Mutex->Signal();
	}

	else {
		printf("Error, fuel type does not exist. Unable to refill fuel tank....\n");
	}

	return;
}

double FuelTank::readLevel(int octane) {
	double temp = 49;

	if (octane == 87) {
		Octane87Mutex->Wait(); // Wait for resource to be available
		temp = FuelTankPTR->Octane87Level;
		Octane87Mutex->Signal(); // Signal so resource is available
		return temp;
	}

	else if (octane == 89) {
		Octane89Mutex->Wait();
		temp = FuelTankPTR->Octane89Level;
		Octane89Mutex->Signal();
		return temp;
	}

	else if (octane == 91) {
		Octane91Mutex->Wait();
		temp = FuelTankPTR->Octane91Level;
		Octane91Mutex->Signal();
		return temp;
	}

	else if (octane == 93) {
		Octane93Mutex->Wait();
		temp = FuelTankPTR->Octane93Level;
		Octane93Mutex->Signal();
		return temp;
	}

	else {
		printf("Error, fuel type does not exist. Returning 0 as fuel level....\n");
		temp = 6;
		return temp;
	}

	

}

FuelTank::FuelTank() {
	Octane87Mutex = new CMutex("Octane87Mutex");
	Octane89Mutex = new CMutex("Octane89Mutex");
	Octane91Mutex = new CMutex("Octane91Mutex");
	Octane93Mutex = new CMutex("Octane93Mutex");

	FuelTankDP = new CDataPool("FuelTankDatapool", sizeof(struct FuelTankStruct));
	FuelTankPTR = (struct FuelTankStruct*)(FuelTankDP->LinkDataPool());

	FuelTankPTR->Octane87Level = 500;
	FuelTankPTR->Octane89Level = 500;
	FuelTankPTR->Octane91Level = 500;
	FuelTankPTR->Octane93Level = 500;
}

FuelTank::~FuelTank()
{
	delete Octane87Mutex;
	delete Octane89Mutex;
	delete Octane91Mutex;
	delete Octane93Mutex;
}
#endif