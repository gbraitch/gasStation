/*
Name: Gursewak Braitch and Yuedong (Rick) Cheng
Student #: 21730163 and 24250169
Lab Section: L1A
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "C:\\Users\\rickc\\Desktop\\School\\CPEN333\\Assignment 1\\Assignment_1\\Assignment_1\\Pump.h"
#include "C:\\Users\\rickc\\Desktop\\School\\CPEN333\\Assignment 1\\Assignment_1\\Assignment_1\\Customer.h"
#include "C:\\Users\\rickc\\Desktop\\School\\CPEN333\\Assignment 1\\Assignment_1\\Assignment_1\\FuelTankMonitor.h"
#include <windows.h>
#include "C:\\RTExamples\\rt.h"

int main(void)
{
	while (1) {
		Pump Pump1(1);
		Pump Pump2(2);
		Pump Pump3(3);
		Pump Pump4(4);
		Pump1.Resume();
		Pump2.Resume();
		Pump3.Resume();
		Pump4.Resume();
		Pump2.WaitForThread();
		Pump3.WaitForThread();
		Pump1.WaitForThread();
		Pump4.WaitForThread();
	}
	return 0;

}