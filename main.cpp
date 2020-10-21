#include <iostream>
#include <fstream>
#include <string>	
#include <cmath>
#include "Biginteger.h"
using namespace std;

int main(){
	BigInteger integers =  BigInteger();
	integers.createBigInt("input.txt");	//Read
	integers.runapplication(); //Calculate
	//integers.update(key,string input)
	integers.save_to_file("output.txt"); // Save
	return 0;
}

