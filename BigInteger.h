#define MAX_NUM 5
#include "dll.h"
//Used DoublyLinkedList provided by the lab assisstants and added extra functions to it
class BigInteger {
public:
    void createBigInt(string input); //Reads from an input file to store tokens and integers in a linkedlist format
    void updateBigInt(int number, string input); //Overloaded Version for the User(copies contents of input.txt to a bigint)
    void freeBigInt(); //Frees the internal data structure of the BigInteger
	void runapplication();	//Runs the calculations	
    void save_to_file(string input); // aves the result to a provided txt file
	void addBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2, DoublyLinkedList <int>  &save_bigint); //Addition
	void subBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2, DoublyLinkedList <int>  &save_bigint); //Substraction
	void multiplyBigInt	(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2); // Multiplication
private:
	DoublyLinkedList <char> tokens;							//Store the tokens for calculation
	DoublyLinkedList <int> *integers[MAX_NUM];				//Store the numbers in an DoublyLinkedList array
	void updateBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2); //Private version of UpdateBigInt (copies contents of bigint2 to bigint)
    DLLNode<int>* gettail(DoublyLinkedList <int> &dll)  { 
        return dll.gettail();
    }
    DLLNode<int>* gethead(DoublyLinkedList <int> &dll)  {
        return dll.gethead();
    }
};

void BigInteger::createBigInt(string input){		
char temp_char;
int index = 0;										
integers[index] = new DoublyLinkedList<int>();	
ifstream myFile;	
myFile.open(input.c_str(), ios::in);
	while (!myFile.eof() ) {
		myFile.get(temp_char);		
		if (temp_char == ' '){
			continue;
		}
		else if (temp_char == '\n'){
			break;
		}
		else if (temp_char == '*' || temp_char == '+'|| temp_char == '-' ){ 
			tokens.addToDLLTail(temp_char);
			index++;											
			integers[index] = new DoublyLinkedList<int>();		
		}
		else{
			integers[index]->addToDLLTail(temp_char-48);	
		}	
	}

}

void BigInteger::updateBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2){	
	bigint.clear();
	DLLNode<int> *tmp_tail_2 = gettail(bigint2);
	for (int i=0 ; i < bigint2.size() ; i++){	
		bigint.addToDLLHead(tmp_tail_2->info);
		tmp_tail_2 = tmp_tail_2->prev;
	}
}


void BigInteger::updateBigInt(int number, string input){	
	unsigned int tokensize = tokens.size();	
	unsigned int temp_num = number;
	if (temp_num > tokensize || temp_num < 0){
		cout << "Update Error\n"; 
		return;
	}
	DoublyLinkedList<int> *tmp =  integers[number];
	tmp->clear();
	unsigned int sizeim = input.size();	
	for (unsigned int i = sizeim-1 ; i < sizeim ; i--){
		tmp->addToDLLHead(input[i] - 48);
	}
}

void BigInteger::freeBigInt(){
	for(int i=0;i<MAX_NUM;i++){
		integers[i]->~DoublyLinkedList();
	}
}
void BigInteger::addBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2, DoublyLinkedList <int>  &save_bigint){
	int difference = bigint.size()-bigint2.size();
	int abosulutediff = abs(bigint.size()-bigint2.size());
	int sum,remainder = 0;
	for (int i=0 ; i < abosulutediff ; i++){					//Fill the smaller number's left side with 0s for easier calc
		if (difference > 0){	
			bigint2.addToDLLHead(0);	
		}	
		else {	
			bigint.addToDLLHead(0);	
		}
	}
	DLLNode<int> *tmp_tail_1 = gettail(bigint);
	DLLNode<int> *tmp_tail_2 = gettail(bigint2);
	for (int i=0 ; i < bigint.size() ; i++){		
		sum = tmp_tail_1->info + tmp_tail_2->info + remainder;
		if (sum >= 10){
			sum = sum - 10; remainder =1;
		}
		else{
			remainder = 0;
		}
		tmp_tail_1 = tmp_tail_1->prev;
		tmp_tail_2 = tmp_tail_2->prev;	
		save_bigint.addToDLLHead(sum);
	}
	if (remainder == 1){	
		save_bigint.addToDLLHead(remainder);	
	}	
	for (int i=0 ; i < abosulutediff ; i++){					
		if (difference > 0){
			bigint2.deleteFromDLLHead();
		}	
		else {	
			bigint.deleteFromDLLHead();	
		}
	}
	
}

void BigInteger::subBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2, DoublyLinkedList <int>  &save_bigint){
	int difference = bigint.size()-bigint2.size();
	int abosulutediff = abs(bigint.size()-bigint2.size());
	int subtract,remainder = 0;
	
	for (int i=0 ; i < abosulutediff ; i++){			
		if (difference > 0){
			bigint2.addToDLLHead(0);
		}	
		else {	
			bigint.addToDLLHead(0);	
		}
	}
	DLLNode<int> *tmp_tail_1 = gettail(bigint);
	DLLNode<int> *tmp_tail_2 = gettail(bigint2);

	for (int i=0 ; i < bigint.size() ; i++){			
		subtract = tmp_tail_1->info - tmp_tail_2->info - remainder;
		if (subtract < 0){
			subtract = subtract + 10; remainder =1;
		}
		else{
			remainder = 0;
		}
		tmp_tail_1 = tmp_tail_1->prev;
		tmp_tail_2 = tmp_tail_2->prev;
		save_bigint.addToDLLHead(subtract);
		
	}

	if (remainder == 1){	
		save_bigint.addToDLLHead(remainder);	
	}	

	for (int i=0 ; i < abosulutediff ; i++){					
		if (difference > 0){
			bigint2.deleteFromDLLHead();
		}	
		else {	
			bigint.deleteFromDLLHead();
		}
	}	
}

void BigInteger::multiplyBigInt(DoublyLinkedList <int> &bigint, DoublyLinkedList <int> &bigint2){
	DoublyLinkedList <int> *cache[50*50*50];	
	DoublyLinkedList <int> temp_bigint;
	updateBigInt(temp_bigint,bigint);
	int mul = 0;
	int remainder = 0;
	DLLNode<int> *tmp_tail_1 = gettail(temp_bigint);
	for (int i=0 ; i < temp_bigint.size() ; i++){	
		cache[i] = new DoublyLinkedList<int>();
		for (int k=0 ; k < i ; k++){	
			cache[i]->addToDLLHead(0); 
		}
		DLLNode<int> *tmp_tail_2 = gettail(bigint2);
		for (int j=0 ; j < bigint2.size() ; j++){	
			mul = (tmp_tail_2->info * tmp_tail_1->info) + remainder;
			remainder = 0;	
			while (mul > 10){	
				mul -= 10; 
				remainder++;
			}
			cache[i]->addToDLLHead(mul);
			tmp_tail_2 = tmp_tail_2->prev;
		}
		tmp_tail_1 = tmp_tail_1->prev;
		cache[i]->addToDLLHead(remainder);								
		remainder = 0; mul = 0; 
	}
	DoublyLinkedList <int> temp_sum;
	for (int i=0; i < temp_bigint.size()-1; i++){						
		addBigInt(*cache[0],*cache[i+1],temp_sum);	
		updateBigInt(*cache[0], temp_sum );							
		temp_sum.clear();													
	}
	updateBigInt(bigint, *cache[0] );				
}
	
void BigInteger::runapplication(){	
	int mult_index = -1;					//To fix the issue of token and number adjancensy
	for (int i=0 ; i < tokens.size() ; i++){
		if (tokens.nth_element(i) == '*'){
				if (mult_index == -1 ) {
					mult_index = i;
				}
				multiplyBigInt(*integers[mult_index],*integers[i+1]);	
				integers[i+1]->clear();									
				integers[i+1]->addToDLLHead(0);
		}
		else{
			mult_index = -1;
		}				
	}	
	
	DoublyLinkedList <int> temp_subtract;
	for (int i=0 ; i < tokens.size() ; i++){			
		if (tokens.nth_element(i) == '-'){
			subBigInt(*integers[0],*integers[i+1],temp_subtract);
			integers[i+1]->clear();	
			updateBigInt(*integers[0], temp_subtract );
			temp_subtract.clear();		
		}
	}
	DoublyLinkedList <int> temp_sum;
	for (int i=0 ; i < tokens.size() ; i++){							
		addBigInt(*integers[0],*integers[i+1],temp_sum);	
		updateBigInt(*integers[0], temp_sum );				
		temp_sum.clear();						
	}	
}

void BigInteger::save_to_file(string input){
	if (gethead(*integers[0])->info == 0){
		integers[0]->deleteFromDLLHead();
	}
	freopen(input.c_str(),"w",stdout);		
    cout << *integers[0];			
}
