#include <iostream>

int main(void)
{
	int num=0,i=0;
	
	int A[100] = {};
	
	std::cin >> num;
	if (num > 100) {return -1;}					// constraint num E {1,100}
	
	for(i;i<num;i++){
		std::cin >> A[i];
		if(1000 < A[i]) {std::cout << true; return -1;}	// constraint A[i] E {0, 1E3}
		else if  (-1 > A[i]) {std::cout << true; return -1;}
		else {asm("nop");
		}
	}
	
	// Print in reverse
	for(i=num-1;i>-1;i--)
		std::cout << A[i] << std::endl;

	return 0;
}