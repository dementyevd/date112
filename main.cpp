#include "Date.h"

void main() {
	Date d1(28, 2, 1989);
	Date d2(28, 2, 1990);
	std::cout << d1 - d2;
	//d1 < d2 ? std::cout << "yes" : std::cout << "no";
	/*std::cout << d1 << std::endl;
	d1 += 100;
	std::cout << d1 << std::endl;
	d1 -= 1;
	std::cout << d1 << std::endl;*/
}