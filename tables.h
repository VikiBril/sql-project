// Coded with blood swet and tear by Viki Brill - 207129446, and Or Ilani - 307934406

#include "includes.h"
using namespace std;

class Musician {
private:
	int musician_id;
	string name;
	string address;
	string phone;
	string expert;

public:
	Musician(mysqlx_row_t *);
	~Musician() {}

	int getID() const {
		return this->musician_id;
	}
	string getName() const {
		return this->name;
	}
	string getAddress() const {
		return this->address;
	}
	string getPhone() const {
		return this->phone;
	}
	string getexpert() const {
		return this->expert;
	}
	string Print() const {
		stringstream os;
		os << this->musician_id << ", " << this->name << ", " << this->address + ", " << this->phone << ", " << this->expert;
		return os.str();
	}
};

class Instrument {
private:
	int instrument_id;
	string brand;
	string type;

public:
	Instrument(mysqlx_row_t *);
	~Instrument() {}

	int getID() const {
		return this->instrument_id;
	}
	string getBrand() const {
		return this->brand;
	}
	string getType() const {
		return this->type;
	}
	string Print() const {
		stringstream os;
		os << this->instrument_id << ", " << this->brand << ", " << this->type;
		return os.str();
	}

};

class Track {
private:
	int track_id;
	string name;
	string M_creator;
	int length;
	string L_creator;
	string date;
	string genre;
	string tech_guy;

public:
	Track(mysqlx_row_t *);
	~Track() {}

	int getID() const {
		return this->track_id;
	}
	string getName() const {
		return this->name;
	}
	string getM_creator() const {
		return this->M_creator;
	}
	int getLength() const {
		return this->length;
	}
	string getL_creator() const {
		return this->L_creator;
	}
	string getDate() const {
		return this->date;
	}
	string getGenre() const {
		return this->genre;
	}
	string getTech_guy() const {
		return this->tech_guy;
	}

	string Print() const {
		stringstream os;
		os << this->track_id << ", " << this->name << ", " << this->M_creator << ", " << this->length << ", " << this->L_creator << ", " << this->date << ", " << this->genre << ", " << this->tech_guy;
		return os.str();
	}

};

class Album {
private:
	int album_id;
	string name;
	string start_date;
	string end_date;
	int tracks_num;

public:
	Album(mysqlx_row_t *);
	~Album() {}

	int getID() const {
		return this->album_id;
	}
	string getName() const {
		return this->name;
	}
	string getStartDate() const {
		return this->start_date;
	}
	string getEndDate() const {
		return this->end_date;
	}
	int getTracks() const {
		return this->tracks_num;
	}

	string Print() const {
		stringstream os;
		os << this->album_id << ", " << this->name << ", " << this->start_date + ", " << this->end_date << ", " << tracks_num;
		return os.str();
	}

};

class Producer {
private:
	int id;
	string name;

public:
	Producer(mysqlx_row_t *);
	~Producer() {}

	int getID() const { return this->id; }
	string getName() const { return this->name; }

	string Print() const
	{
		stringstream os;
		os << this->id << ", " << this->name;
		return os.str();
	}

};

ostream &operator<<(ostream &os, const Musician &obj);
ostream &operator<<(ostream &os, const Album &obj);
ostream &operator<<(ostream &os, const Track &obj);
ostream &operator<<(ostream &os, const Instrument &obj);
ostream &operator<<(ostream &os, const Producer &obj);

template <typename T>
vector<T *> Arr(mysqlx_result_t *res) {
	vector<T *> vec;

	mysqlx_row_t *row;
	do
	{
		while ((row = mysqlx_row_fetch_one(res)) != NULL)
		{
			vec.push_back(new T(row));
		}
	} while (RESULT_OK == mysqlx_next_result(res));

	return vec;
}