/*
   File name	: impulse_seq.cpp
   Author	: Karan K. Bhat
   Description	: This code prints input impulse sequence, and allows left, right shift.
		  Print is done in binary fashion.
*/

#include <iostream>
#include <cstdint>
#include <bitset>

using namespace std;

class impulse_seq
{
	private:	
		union impulse_seq_buf
		{
			uint32_t stream;
			uint8_t bytes[4];	// can be used for individually modifying bytes	
		}impulse;
				
	public:
		bool store(const uint32_t stream);
		bool shift_left(const uint8_t shift_val);
		bool shift_right(const uint8_t shift_val);		
		bool display(void);
};

bool impulse_seq::store(const uint32_t stream)
{
	impulse.stream = stream;
	return true;
}

bool impulse_seq::display(void)
{
	cout << bitset<32>{impulse.stream} << endl ;
	return true;
}

bool impulse_seq::shift_left(const uint8_t shift_val)
{
	impulse.stream = impulse.stream << shift_val;
	return true;
}

bool impulse_seq::shift_right(const uint8_t shift_val)
{
	impulse.stream = impulse.stream >> shift_val;
	return true;
}

int main(int argc, char *argv[])
{
	impulse_seq input_val;		// class input_val
	
	input_val.store(0x8000);
	input_val.display();
	input_val.shift_right(0x05);	// Shifts impulse sequence to right by 5 indeces
	input_val.display();	
	input_val.shift_left(0x03);	// Shifts impulse sequence to left by 3 indeces
	input_val.display();
		
	return 0;
}
