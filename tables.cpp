// Coded with blood swet and tear by Viki Brill - 207129446, and Or Ilani - 307934406

#include "pch.h"
#include "tables.h"

using namespace std;

Musician::Musician(mysqlx_row_t* row) {
	int64_t x;
	char temp1[256] = { 0 };
	char temp2[256] = { 0 };
	char temp3[256] = { 0 };
	char temp4[256] = { 0 };
	size_t s = 0;

	s = sizeof(temp1);

	mysqlx_get_sint(row, 0, &x);
	this->musician_id = x;

	mysqlx_get_bytes(row, 1, 0, temp1, &s);
	this->name = temp1;

	s = sizeof(temp2);
	mysqlx_get_bytes(row, 2, 0, temp2, &s);
	this->address = temp2;

	s = sizeof(temp3);
	mysqlx_get_bytes(row, 3, 0, temp3, &s);
	this->phone = temp3;

	s = sizeof(temp4);
	mysqlx_get_bytes(row, 4, 0, temp4, &s);
	this->expert = temp4;
}
Album::Album(mysqlx_row_t* row) {
	int64_t x;
	char temp1[256] = { 0 };
	char temp2[256] = { 0 };
	char temp3[256] = { 0 };
	size_t s = 0;

	s = sizeof(temp1);

	mysqlx_get_sint(row, 0, &x);
	this->album_id = x;

	s = sizeof(temp1);
	mysqlx_get_bytes(row, 1, 0, temp1, &s);
	this->name = temp1;

	s = sizeof(temp2);
	mysqlx_get_bytes(row, 2, 0, temp2, &s);
	this->start_date = temp2;

	s = sizeof(temp3);
	mysqlx_get_bytes(row, 3, 0, temp3, &s);
	this->end_date = temp3;

	mysqlx_get_sint(row, 4, &x);
	this->tracks_num = x;
}
Track::Track(mysqlx_row_t * row) {
	int64_t x;
	int64_t y;
	char temp1[256] = { 0 };
	char temp2[256] = { 0 };
	char temp3[256] = { 0 };
	char temp4[256] = { 0 };
	char buff5[256] = { 0 };
	char buff6[256] = { 0 };

	size_t s = 0;

	s = sizeof(temp1);

	mysqlx_get_sint(row, 0, &x);
	this->track_id = x;

	s = sizeof(temp1);
	mysqlx_get_bytes(row, 1, 0, temp1, &s);
	this->name = temp1;

	s = sizeof(temp2);
	mysqlx_get_bytes(row, 2, 0, temp2, &s);
	this->M_creator = temp2;

	mysqlx_get_sint(row, 3, &y);
	this->length = x;

	s = sizeof(temp3);
	mysqlx_get_bytes(row, 4, 0, temp3, &s);
	this->L_creator = temp3;

	s = sizeof(temp4);
	mysqlx_get_bytes(row, 5, 0, temp4, &s);
	this->date = temp4;

	s = sizeof(buff5);
	mysqlx_get_bytes(row, 6, 0, buff5, &s);
	this->genre = buff5;

	s = sizeof(buff6);
	mysqlx_get_bytes(row, 7, 0, buff6, &s);
	this->tech_guy = buff6;

}
Instrument::Instrument(mysqlx_row_t* row) {
	int64_t x;
	char temp1[256] = { 0 };
	char temp2[256] = { 0 };

	size_t s = 0;

	s = sizeof(temp1);

	mysqlx_get_sint(row, 0, &x);
	this->instrument_id = x;

	mysqlx_get_bytes(row, 1, 0, temp1, &s);
	this->brand = temp1;

	s = sizeof(temp2);
	mysqlx_get_bytes(row, 2, 0, temp2, &s);
	this->type = temp2;
}
Producer::Producer(mysqlx_row_t* row) {
	int64_t x;
	char temp1[256] = { 0 };
	size_t s = 0;

	s = sizeof(temp1);

	mysqlx_get_sint(row, 0, &x);
	this->id = x;

	mysqlx_get_bytes(row, 1, 0, temp1, &s);
	this->name = temp1;
}


ostream& operator<<(ostream& os, const Musician& obj) {
	os << obj.Print();
	return os;
}
ostream& operator<<(ostream& os, const Album& obj) {
	os << obj.Print();
	return os;
}
ostream& operator<<(ostream& os, const Track& obj) {
	os << obj.Print();
	return os;
}
ostream& operator<<(ostream& os, const Instrument& obj) {
	os << obj.Print();
	return os;
}
ostream& operator<<(ostream& os, const Producer& obj) {
	os << obj.Print();
	return os;
}

