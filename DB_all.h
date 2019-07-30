// Coded with blood swet and tear by Viki Brill - 207129446, and Or Ilani - 307934406

#include "tables.h"

using namespace std;

class DataBase
{
private:
	mysqlx_session_t * ses;
	mysqlx_error_t *err;
	char Uname[256];
	char Pass[256];
	
public:
	DataBase(const char *Uname, const char *Pass)
	{
		strncpy_s(this->Uname, Uname, strlen(Uname));
		strncpy_s(this->Pass, Pass, strlen(Pass));

		this->Uname[strlen(Uname)] = '\0';
		this->Pass[strlen(Pass)] = '\0';
	}
	~DataBase() { mysqlx_session_close(this->ses); }

	int Con_to_DB();
	int Initial_DB_tbl();
	int Initial_DB_data();	
	int q1(string start_date, string end_date);		 //Album_Between_Dates
	int q2(string name); 							//Song_From_Musician
	int q3(string name);							//Musician_in_Albums
	int q4();										//PopularInstrument
	int q5(string name);							//Instrument_in_Album
	int q6(string start_date, string end_date);		//Producer_in_album_By_dates
	int q7();										//Popular_Manifactor
	int q8();										//Musician_Years_amount
	int q9();										//Musician_Collab
	int q10();										//PopularGenre
	int q11(string start_date, string end_date);	//TechGuy_Most_Track
	int q12();										//First_Album_Record
	int q13();										//Track_in_Albums
	int q14();										//TechGuy_in_FullAlbum
	int q15(); 										//Diverse_Musician

};