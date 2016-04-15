#pragma once
#include <string>
using namespace std;

// Incomplete class definitions
class Seat_Row;
class Seat_Section;

class Seat
{
private:
	const Seat_Row* const row;
	const Seat_Section* const section;
	int seat_number;

public:
	Seat(const Seat_Row* const Row, int Seat_Number, const Seat_Section* const Section);
	// Seat() {};

	const Seat_Row* SEAT_ROW() const { return row; };
	const Seat_Section* SEAT_SECTION() const { return section; };

	int SEAT_NUM() const { return seat_number; };
	bool operator>(const Seat& other) const;

	//void Sell();
	void Display() const;
};