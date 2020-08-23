# Gas Station Simulator

Real time simulation of gas station operating in C++
Uses the RT library to have multiple processes and threads running to accomplish parallel programming

## Problem

Customers will be generated randomly and will head to one of four gas pumps. Each customer will:
1) Arrive at the pump and wait in line 
2) Swipe their credit card 
3) Remove the gas hose from the pump 
4) Select a one of four grades of fuel 
5) Dispense the fuel
6) Return the hose to the pump
7) Drive away

There is a gas station attendant which is controlled by 'us', which makes sures that the gas station tank does not run out of fuel. The gas station attendant can 
change the price of fuel and enable/disable pumps. 
The attendant's computer also records each transaction performed at one of the four pumps, recording:
1) Time of purchase
2) Credit card number and name of purchaser
3) Grade of fuel selected
4) Quantity of fuel dispersed

The history of transactions can be displayed on command.

Below is an overview of the architecture
![uml_diagram](https://user-images.githubusercontent.com/8892975/90971165-ee890680-e4c1-11ea-9c03-1748b4256bbd.png)
