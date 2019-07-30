// Coded with blood swet and tear by Viki Brill - 207129446, and Or Ilani - 307934406

#include "pch.h"
#include "DB_all.h"

using namespace std;


template <typename T>
void VecRel(vector<T *> vec) {
	for (int i = 0; i < vec.size(); ++i)
		delete vec[i];
}
int GetIn(vector<string> &vec, string val) {
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i] == val)
			return i;
	return -1;
}
int FindM(vector<int> &vec) {
	int index = 0;
	int max = vec[0];
	for (int i = 1; i < vec.size(); ++i)
		if (vec[i] > max)
		{
			max = vec[i];
			index = i;
		}
	return index;
}
int IndexI(vector<int> vec, int x) {
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i] == x)
			return i;
	return -1;
}
int DataBase::Con_to_DB() {
	this->ses = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, this->Uname, this->Pass, "", &this->err);
	if (NULL == this->ses){
		cout << mysqlx_error_message(this->err) << "\t" << this->ses << endl;
		return -1;
	}
	return 0;
}
int DataBase::Initial_DB_tbl() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	if (mysqlx_get_schema(ses, "Music_Company", 1)){
		query = mysqlx_sql_new(ses, "DROP database `Music_Company`", MYSQLX_NULL_TERMINATED);
		if ((res = mysqlx_execute(query)) == NULL){
			return -1;
		}
	}

	query = mysqlx_sql_new(ses, "create database `Music_Company`", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	mysqlx_session_close(ses);
	ses = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "demoUser", "demo", "Music_Company", &err);

	if (NULL == ses){
		cout << mysqlx_error_message(err) << "\t" << ses << endl;
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Musician` (\
								`Musician_ID` INT NOT NULL AUTO_INCREMENT,\
								`Name` VARCHAR(256) NOT NULL,\
								`Address` VARCHAR(256) NOT NULL,\
								`Phone` VARCHAR(256) NOT NULL,\
								`Expert` VARCHAR(256) NOT NULL,\
								PRIMARY KEY (`Musician_ID`));", MYSQLX_NULL_TERMINATED);


	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}
	query = mysqlx_sql_new(ses, "CREATE TABLE `Instrument` (\
								`Instrument_ID` INT NOT NULL AUTO_INCREMENT,\
								`Brand` VARCHAR(256) NOT NULL,\
								`Type` VARCHAR(256) NOT NULL,\
								PRIMARY KEY (`Instrument_ID`));", MYSQLX_NULL_TERMINATED);


	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Track` (\
								`Track_ID` INT NOT NULL AUTO_INCREMENT,\
								`Name` VARCHAR(256) NOT NULL,\
								`M_Creator` VARCHAR(256) NULL,\
								`Length` INT NOT NULL,\
								`L_creator` VARCHAR(256) NULL,\
								`Date` VARCHAR(256) NOT NULL,\
								`Genre` VARCHAR(256) NOT NULL,\
								`Tech_Guy` VARCHAR(256) NOT NULL,\
								PRIMARY KEY (`Track_ID`));", MYSQLX_NULL_TERMINATED);


	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Album` (\
								`Album_ID` INT NOT NULL AUTO_INCREMENT,\
								`Name` VARCHAR(256) NOT NULL,\
								`Start_Date` VARCHAR(256) NOT NULL,\
								`End_Date` VARCHAR(256) NOT NULL,\
								`Tracks_Num` INT NOT NULL,\
								PRIMARY KEY (`Album_ID`));", MYSQLX_NULL_TERMINATED);


	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Producer` (\
								`Producer_ID` INT NOT NULL AUTO_INCREMENT,\
								`Name` VARCHAR(256) NOT NULL,\
								PRIMARY KEY (`Producer_ID`));", MYSQLX_NULL_TERMINATED);


	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Musi_VS_Inst` (\
								`mus_ID` INT NOT NULL,\
								`ins_ID` INT NOT NULL,\
								PRIMARY KEY (`ins_ID`, `mus_ID`),\
								FOREIGN KEY (`mus_ID`)\
								REFERENCES `Music_Company`.`Musician` (`Musician_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION,\
								FOREIGN KEY (`ins_ID`)\
								REFERENCES `Music_Company`.`Instrument` (`Instrument_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Musi_VS_Tracks` (\
								`mus_ID` INT NOT NULL,\
								`trac_ID` INT NOT NULL,\
								PRIMARY KEY (`mus_ID`, `trac_ID`),\
								FOREIGN KEY (`mus_ID`)\
								REFERENCES `Music_Company`.`Musician` (`Musician_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION,\
								FOREIGN KEY (`trac_ID`)\
								REFERENCES `Music_Company`.`Track` (`Track_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Album_VS_Tracks` (\
								`trac_ID` INT NOT NULL,\
								`alb_ID` INT NOT NULL,\
								PRIMARY KEY (`trac_ID`, `alb_ID`),\
								FOREIGN KEY (`trac_ID`)\
								REFERENCES `Music_Company`.`Track` (`Track_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION,\
								FOREIGN KEY (`alb_ID`)\
								REFERENCES `Music_Company`.`Album` (`Album_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "CREATE TABLE `Album_VS_Prod` (\
								`alb_ID` INT NOT NULL,\
								`prod_ID` INT NOT NULL,\
								PRIMARY KEY (`alb_ID`, `prod_ID`),\
								FOREIGN KEY (`alb_ID`)\
								REFERENCES `Music_Company`.`Album` (`Album_id`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION,\
								FOREIGN KEY (`prod_ID`)\
								REFERENCES `Music_Company`.`Producer` (`Producer_ID`)\
								ON DELETE NO ACTION\
								ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::Initial_DB_data() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Musician` (`Name`, `Address`, `Phone`, `Expert`) VALUES\
								('Beyonce', 'Houston', '043-9453804', 'Singer') ,\
								('Rihana' ,'Barbadian ', '044-1259402', 'Singer'),\
								('Maroon 5' ,'Los Angeles', '041-3742758', 'Singer + Player'),\
								('Justin Timberlake' ,'tennessee', '042-3382247', 'Singer + Player'),\
								('Drake' ,'Canada', '045-9874502', 'Singer'),\
								('Rita Ora' ,'England', '055-0987654', 'Singer'),\
								('kanye West', 'Atlanta' , '046-2435468', 'Singer + Player'),\
								('Maluma', 'Colombia', '011-9898654', 'Singer + Player'),\
								('Selina Gomez', 'Texas', '047-8675583', 'Singer'),\
								('Ed Shiran', 'England', '055-1234567', 'Singer + Player'),\
								('Natan Gosen', 'Israel', '972-9497404', 'Singer + Player');", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Track` (`Name`, `M_creator`, `Length`, `L_creator`, `Date`, `Genre`, `Tech_Guy`) VALUES\
								('Sorry', 'Beyonce', '353', 'The weekend', '2016-09-09', 'R&B', 'Tom Gioia'),\
								('Talk that talk','Rihana','254','The dream','2011-07-10','R&B','Howie Moscovitch'),\
								('Maps','Maroon 5','310','Adam levin','2014-01-13','Pop','Kim Copeland'),\
								('Cry me a river','Justin timberlake','448','Timberland','2017-06-21','Comedy','Denny Martin'),\
								('One dance','Drake','254','The weekend','2018-01-17','Hip-Hop','Kim Copeland'),\
								('I will never let you down','Rita Ora','323','Rita Ora','2016-12-29','Pop','Howie Moscovitch'),\
								('Corazon','Maluma','306','Alesso','2018-11-25','Rap','Tom Gioia'),\
								('Girls','Justin timberlake','404','Timberland','2014-02-14','R&B','Howie Moscovitch'),\
								('Condena','maluma','352','Alesso','2017-04-04','Pop','Kim Copeland'),\
								('Suger','Maroon 5','331','Adam levin','2015-02-08','Pop','Denny Martin'),\
								('Beautiful people','maluma','259','Alesso','2018-08-09','Regatton','Denny Martin'),\
								('I dont care','maluma','401','Alesso','2018-11-04','Regatton','Kim Copeland'),\
								('Sent it up','Kanye west','258','Kid kari','2015-01-04','R&B','Denny Martin'),\
								( 'Thinking about that','Natan Gosen','217','Natan Gosen','2016-01-23','Pop','Gordi');", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Album` (`Name`, `Start_Date`, `End_Date`, `Tracks_Num`) VALUES\
								('Lemonade', '2015-04-15', '2015-04-29', 1),\
								('Talk that talk', '2017-06-20', '2017-07-01', 2),\
								('V', '2018-01-15', '2018-02-02', 3),\
								('Justified', '2009-09-01', '2009-09-15', 4),\
								('Views', '2016-12-20', '2016-02-20', 5),\
								('Phoenix', '2016-08-04', '2016-09-15', 3),\
								('Yeezus', '2005-01-20', '2005-01-26', 2),\
								('FAME', '2016-05-28', '2016-06-10', 5),\
								('Revivel', '2018-06-06', '2018-07-30', 9),\
								( 'NO6', '2019-06-10', '2019-07-20', 10);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Instrument` (`Brand`, `Type`) VALUES\
								('Yamhaa', 'Trumpet'),\
								('Gibson', 'Guitar'),\
								('Yamhaa', 'Saxophone'),\
								('Fender', 'Bass'),\
								('Jupiter', 'Saxophone'),\
								('Yamahaa', 'Piano'),\
								('Steinbach', 'Violet'),\
								('Mapex', 'Drums'),\
								('Tama', 'Drums'),\
								('Yamahaa', 'Tubas');", MYSQLX_NULL_TERMINATED);


	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Producer` (`Name`) VALUES\
								('Tom Gioia'),\
								('Howie Moscovitch'),\
								('Kim Copeland'),\
								('Denny Martin'),\
								('Gordi'),\
								('Jonas Blue'),\
								('Scoter Brown'),\
								('Pharrell'),\
								('Jay-Z'),\
								('Calvin Harris');", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Musi_VS_Inst` (`mus_ID`, `ins_ID`) VALUES\
								(1,1),\
								(2,9),\
								(3,2),\
								(4,8),\
								(5,1),\
								(6,7),\
								(7,7),\
								(8,10),\
								(9,3),\
								(9,7),\
								(10,4),\
								(4,5),\
								(5,8);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `Musi_VS_Tracks` (`mus_ID`, `trac_ID`) VALUES\
								(1,1),\
								(2,10),\
								(3,10),\
								(8,2),\
								(9,9),\
								(7,3),\
								(10,4),\
								(10,5),\
								(11,6),\
								(11,7),\
								(11,8),\
								(4,6),\
								(6,2),\
								(8,3);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `album_VS_Tracks`(`trac_ID`, `alb_ID`) VALUES\
								(1,1),\
								(4,2),\
								(5,3),\
								(4,4),\
								(5,4),\
								(6,5),\
								(7,5),\
								(8,5),\
								(9,6),\
								(10,7),\
								(3,8),\
								(9,8),\
								(10,8),\
								(3,10),\
								(1,9),\
								(2,9),\
								(3,9),\
								(4,9),\
								(5,9),\
								(6,9),\
								(7,9),\
								(8,9),\
								(9,9),\
								(10,9);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	query = mysqlx_sql_new(ses, "SELECT Music_Company;", MYSQLX_NULL_TERMINATED);
	query = mysqlx_sql_new(ses, "INSERT INTO `album_VS_prod` (`alb_ID`,`prod_ID`) VALUES\
								(1,1),\
								(2,2),\
								(3,2),\
								(3,1),\
								(4,1),\
								(4,2),\
								(4,3),\
								(5,2),\
								(5,6),\
								(6,4),\
								(6,5),\
								(8,4),\
								(8,5),\
								(8,6),\
								(9,1),\
								(9,7),\
								(9,10),\
								(10,9);", MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::q1(string start_date, string end_date) {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT count(*) from album where End_Date > '" + start_date + "' AND End_Date < '" + end_date + "';";

	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);
	if ((res = mysqlx_execute(query)) == NULL){
		return -1;
	}

	mysqlx_row_t *row;
	int64_t x;
	if ((row = mysqlx_row_fetch_one(res)) != NULL) {
		mysqlx_get_sint(row, 0, &x);
		cout << "Albums between " << start_date << " and " << end_date << " are : " << x << endl;
	}else {
		cout << "SQL Query Error." << endl;
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::q2(string Name) {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT * from Musician where Name Like '%" + Name + "%';";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query " << endl;
		return -1;
	}
	int userPick = 1;

	vector<Musician *> v = Arr<Musician>(res);

	if (v.size() == 0){
		cout << "No Musician with that name, try again? b\n";
		char c;
		cin >> c;
		if (c == 'b' || c == 'B')
			return 2;
		else
			return -1;
	}

	if (v.size() > 1){
		for (int i = 0; i < v.size(); ++i){
			cout << i + 1 << " - " << *v[i] << endl;
		}do{
			cout << "Musician index: " << endl;
			cin >> userPick;
			if (userPick < 1 || userPick > v.size())
				cout << "Error try again" << endl;

		}while (userPick < 1 || userPick > v.size());
	}

	string Start_Date;
	string End_Date;
	cout << "Enter Start_Date and End_Date (Year-Month-Day)" << endl;
	cin >> Start_Date >> End_Date;

	qstr = "SELECT count(*) from Track as t join Musi_VS_Tracks as m on \
 			m.trac_ID = t.Track_ID where mus_ID = " +
			to_string(v[userPick - 1]->getID()) + " and t.Date > '" + Start_Date + "' and t.Date < '" + End_Date + "';";

	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	mysqlx_row_t *row;
	int64_t x;

	if ((row = mysqlx_row_fetch_one(res)) != NULL){
		mysqlx_get_sint(row, 0, &x);
		cout << " Tracks  " << v[userPick - 1]->getName() << " recorded between " << Start_Date << " and " << End_Date << " are : " << x << endl
			<< endl
			<< endl;
	}else{
		cout << "SQL Query Error." << endl;
	}

	mysqlx_free(res);
	return 0;
}
int DataBase::q3(string name) {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT * from Musician where Name Like '%" + name + "%';";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	int userPick = 1;
	vector<Musician *> v = Arr<Musician>(res);

	if (v.size() == 0){
		cout << "No Musician with that name,try again? b/n";
		char c;
		cin >> c;
		if (c == 'b' || c == 'B')
			return 2;
		else
			return -1;
	}

	if (v.size() > 1){
		for (int i = 0; i < v.size(); ++i)	{
			cout << i + 1 << " - " << *v[i] << endl;
		}do{
			cout << "Index of Musicain: " << endl;
			cin >> userPick;

			if (userPick < 1 || userPick > v.size())
				cout << "Error" << endl;

		} while (userPick < 1 || userPick > v.size());
	}

	string Start_Date;
	string End_Date;
	cout << "Enter start_date and end_date (Year-Month-Day)" << endl;
	cin >> Start_Date >> End_Date;

	qstr = "SELECT count(*) from Album as alb join (SELECT Alb_ID from( (SELECT * from Album_VS_Tracks) as a INNER JOIN\
 			(SELECT * from Musi_VS_Tracks where Musi_VS_Tracks.mus_ID = " +
			to_string(v[userPick - 1]->getID()) + ") as b\
 			on a.trac_ID = b.trac_ID) group by alb_ID ) as c on alb.Album_id = c.alb_ID where End_Date > '" +
			Start_Date + "' and End_Date < '" + End_Date + "' ;";

	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	mysqlx_row_t *row;
	int64_t x;

	if ((row = mysqlx_row_fetch_one(res)) != NULL){
		mysqlx_get_sint(row, 0, &x);
		cout << "Albums " << v[userPick - 1]->getName() << " released between " << Start_Date << " and " << End_Date << " are : " << x << endl
			<< endl
			<< endl;
	}else{
		cout << "SQL Query Error." << endl;
	}

	mysqlx_free(res);
	return 0;
}
int DataBase::q4() {

	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT * FROM Instrument;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Instrument *> v = Arr<Instrument>(res);
	int Index = -1;
	int Max = -1;

	mysqlx_row_t *row;
	int64_t x;

	for (int i = 0; i < v.size(); ++i){
		qstr = "SELECT count(*) from (\
 				(SELECT * FROM Musi_VS_Inst where ins_ID = " +
				to_string(v[i]->getID()) + ") as a join Musi_VS_Tracks as b \
 				on a.mus_ID = b.mus_ID);";
		int value = -1;

		if ((res = mysqlx_execute(query)) != NULL) {
			if ((row = mysqlx_row_fetch_one(res)) != NULL) {
				value = mysqlx_get_sint(row, 0, &x);
			}else {
				cout << "SQL Query Error." << endl;
			}if (value > Max) {
				Max = value;
				Index = i;
			}
		}
	}

	if (Max == -1 || Index == -1) {
		cout << "SQL Query Error." << endl;
	}
	else{
		cout << "Popular Instrument is:\t" << v[Index]->getBrand() << ", " << v[Index]->getType() << endl;
	}

	mysqlx_free(res);
	return 0;
}
int DataBase::q5(string name) {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT * FROM Album where Name Like '%" + name + "%';";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}
	vector<Album *> album = Arr<Album>(res);

	if (album.size() == 0){
		cout << "No Album with that name, try again? b\n";
		char c;
		cin >> c;
		if (c == 'b' || c == 'B')
			return 2;
		else
			return -1;
	}

	qstr = 		"SELECT * from Instrument as i join\
				(SELECT ins_ID from Musi_VS_Inst as mi join\
 				(SELECT alb_ID from Album_VS_Tracks as at join Musi_VS_Tracks as b on at.trac_ID = b.trac_ID where at.alb_ID = "
				 + to_string(album[0]->getID()) + ")\
				as mb on mi.mus_ID = mb.mus_ID) as b on i.Instrument_ID = b.ins_ID ;";

	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "No Musician with that name" << endl;
		return -1;
	}

	vector<Instrument *> v = Arr<Instrument>(res);

	if (v.size() == 0)
		cout << "No Instruments in " + album[0]->getName() << endl;
	else{
		cout << "Instruments in album :" << endl
			<< endl;
		cout << "Album Name: " + album[0]->getName() << endl
			<< "Index\tID, Brand, Type" << endl;
		for(int i = 0; i < v.size(); ++i)
			cout << i + 1 << ".\t" << *v[i] << endl;
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::q6(string start_date, string end_date) {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT * FROM Producer;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Producer *> vec = Arr<Producer>(res);
	int Index = -1;
	int Max = -1;

	mysqlx_row_t *row;
	int64_t x;

	for (int i = 0; i < vec.size(); ++i) {
		qstr = "SELECT count(*) from (\
 				(SELECT * FROM Album_VS_Prod where prod_ID = " +
				to_string(vec[i]->getID()) + ") as a join Album as b on a.alb_ID = b.Album_id )\
 				where End_Date  > '" +
				start_date + "' and End_Date < '" + end_date + "';";

		query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

		int value = 0;
		if ((res = mysqlx_execute(query)) != NULL){
			if ((row = mysqlx_row_fetch_one(res)) != NULL){
				mysqlx_get_sint(row, 0, &x);
				value = x;
			}else{
				cout << "SQL Query Error." << endl;
			}
			if (value > Max){
				Max = value;
				Index = i;
			}
		}
	}

	if (Max == -1 || Index == -1)
		cout << "SQL Query Error." << endl;
	else
		cout << "Popular Producer: \t" << vec[Index]->getName() << endl;

	mysqlx_free(res);
	return 0;
}
int DataBase::q7() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	vector<string> manufacterers;
	vector<int> count;

	mysqlx_row_t *row;
	int64_t x;

	string qstr = "SELECT * FROM Instrument;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}
	vector<Instrument *> v = Arr<Instrument>(res);

	for (int i = 0; i < v.size(); ++i){
		qstr = "SELECT count(*) from (\
 				(SELECT * FROM Musi_VS_Inst where ins_ID = " +
				to_string(v[i]->getID()) + ") as a join Musi_VS_Tracks as b\
				 on a.mus_ID = b.mus_ID);";

		int value = 0;
		if ((res = mysqlx_execute(query)) != NULL){
			if ((row = mysqlx_row_fetch_one(res)) != NULL){
				value = mysqlx_get_sint(row, 0, &x);
			}else{
				cout << "SQL Query Error" << endl;
			}
			if (GetIn(manufacterers, v[i]->getBrand()) == -1){
				manufacterers.push_back(v[i]->getBrand());
				count.push_back(x);
			}else{
				int index;
				if ((index = GetIn(manufacterers, v[i]->getBrand())) != -1)
					count[index] += x;
			}
		}
	}

	cout << "Popular Manufacterer:" << manufacterers[FindM(count)] << endl;

	mysqlx_free(res);
	return 0;
}
int DataBase::q8() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	string qstr = "SELECT COUNT(*) FROM (SELECT * FROM Musician  JOIN Musi_VS_Tracks ON mus_ID = mus_ID group by mus_ID) AS b;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	mysqlx_row_t *row;
	int64_t x;

	if ((row = mysqlx_row_fetch_one(res)) != NULL) {
		mysqlx_get_sint(row, 0, &x);
		cout << "Musicians recorded through years:\t" << x << endl;
	}else {
		cout << "SQL Query Error." << endl;
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::q9() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	vector<int> Musicians;
	vector<int> count;

	int64_t x;

	string qstr = "SELECT * FROM Track;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL){
		cout << "Error in SQL Query" << endl;
		return -1;
	}
	vector<Track *> v = Arr<Track>(res);

	for (int i = 0; i < v.size(); ++i){
		int64_t value = 0;
		mysqlx_row_t *row;

		qstr = "SELECT count(*) from Musi_VS_Tracks where trac_ID = " + to_string(v[i]->getID()) + " ;";

		query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

		if ((res = mysqlx_execute(query)) != NULL){
			if ((row = mysqlx_row_fetch_one(res)) != NULL)	{
				mysqlx_get_sint(row, 0, &value);
				if (value > 1){
					qstr = "SELECT * from Musi_VS_Tracks where trac_ID = '" + to_string(v[i]->getID()) + "';";
					query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);
					if ((res = mysqlx_execute(query)) != NULL){
						do{
							while ((row = mysqlx_row_fetch_one(res)) != NULL) {
								mysqlx_get_sint(row, 0, &x);
								int index;
								if ((index = IndexI(Musicians, x)) == -1) {
									Musicians.push_back(x);
									count.push_back(value - 1);
								}else {
									count[index] += (value - 1);
								}
							}
						} while (RESULT_OK == mysqlx_next_result(res));
						mysqlx_result_free(res);
					}
				}
			}else{
				cout << "SQL Query Error." << endl;
			}
		}
	}

	if (Musicians.size() == 0) {
		cout << "SQL Query Error." << endl;
	}else {

		qstr = "SELECT * from Musician where Musician_ID = " + to_string(Musicians[FindM(count)]) + ";";
		query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

		if ((res = mysqlx_execute(query)) == NULL) {
			cout << "Error in SQL Query" << endl;
			return -1;
		}

		vector<Musician *> m = Arr<Musician>(res);
		cout << "Musician who collaborated the most: " << m[0]->getName() << endl;
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::q10() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	vector<string> genre;
	vector<int> count;

	mysqlx_row_t *row;
	int64_t x;

	string qstr = "SELECT * FROM Track;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Track *> v = Arr<Track>(res);

	for (int i = 0; i < v.size(); ++i) {
		int index;
		if ((index = GetIn(genre, v[i]->getGenre())) == -1) {
			genre.push_back(v[i]->getGenre());
			count.push_back(1);
		}else {
			count[index]++;
		}
	}

	cout << "The most Popular Genre is :" << genre[FindM(count)] << endl;
	mysqlx_free(res);
	return 0;
}
int DataBase::q11(string start_date, string end_date) {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	vector<string> tech;
	vector<int> count;

	mysqlx_row_t *row;
	int64_t x;

	string qstr = "SELECT * from Track where Date > '" + start_date + "' AND Date < '" + end_date + "';";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}
	vector<Track *> vec = Arr<Track>(res);

	for (int i = 0; i < vec.size(); ++i) {
		int index;

		if ((index = GetIn(tech, vec[i]->getTech_guy())) == -1){
			tech.push_back(vec[i]->getTech_guy());
			count.push_back(1);
		}else {
			count[index]++;
		}
	}
	cout << "Tech_guy that worked on most Tracks :" << tech[FindM(count)] << endl;
	mysqlx_free(res);
	return 0;
}
int DataBase::q12() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	vector<string> genre;
	vector<int> count;

	mysqlx_row_t *row;
	int64_t x;

	string qstr = "SELECT * from Album where End_Date = (SELECT min(End_Date) from album);";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Album *> v = Arr<Album>(res);
	cout << " first album :\t" << v[0]->getName() << endl;
	mysqlx_free(res);
	return 0;
}
int DataBase::q13() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	int64_t x;

	string qstr = "SELECT * FROM Track;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Track *> v = Arr<Track>(res);
	vector<Track *> choosen;

	for (int i = 0; i < v.size(); ++i) {
		int64_t value = 0;
		mysqlx_row_t *row;

		qstr = "SELECT count(*) from Album_VS_Tracks where trac_ID = " + to_string(v[i]->getID()) + ";";
		query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

		if ((res = mysqlx_execute(query)) != NULL) {
			if ((row = mysqlx_row_fetch_one(res)) != NULL) {
				mysqlx_get_sint(row, 0, &value);
				if (value > 1) {
					choosen.push_back(v[i]);
				}
			}else {
				cout << "SQL Query Error." << endl;
			}
		}
	}

	if (choosen.size() == 0) {
		cout << "SQL Query Error." << endl;
	}else {
		cout << "Tracks in 2 Albums or more :" << endl;
		cout << "index\tTrack_ID, Name, M_Creator, Length, L_Craetor, Date, Genre, Tech_Guy" << endl;

		for (int i = 0; i < choosen.size(); ++i) {
			cout << i << "\t" << *choosen[i] << endl;
		}
	}

	mysqlx_free(res);
	return 0;
}
int DataBase::q14() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	vector<string> tech;
	vector<string> choosen;

	int64_t x;

	string qstr = "SELECT * FROM Track;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Track *> v = Arr<Track>(res);

	for (int i = 0; i < v.size(); ++i) {
		if (GetIn(tech, v[i]->getTech_guy()) == -1) {
			tech.push_back(v[i]->getTech_guy());
		}
	}

	qstr = "SELECT * FROM Album;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Album *> a = Arr<Album>(res);

	for (int i = 0; i < a.size(); ++i) {
		int albumLength = a[i]->getTracks();

		for (int j = 0; j < tech.size(); ++j) {
			int64_t value = 0;
			mysqlx_row_t *row;

			qstr = "SELECT count(*) from Track as a  join (SELECT * from Album_VS_Tracks where alb_ID = " + to_string(a[i]->getID()) + ")\
 					as b on a.Track_ID = b.trac_ID\
 					where Tech_Guy = '" +
					tech[j] + "';";
			query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

			if ((res = mysqlx_execute(query)) != NULL) {
				if ((row = mysqlx_row_fetch_one(res)) != NULL) {
					mysqlx_get_sint(row, 0, &value);
					if (value == albumLength) {
						if (GetIn(choosen, tech[j]) == -1) {
							choosen.push_back(tech[j]);
						}
					}
				}
			}
		}
	}

	if (choosen.size() == 0) {
		cout << "SQL Query Error." << endl;
	}else {
		cout << "Tech_guy who work on Full Album:" << endl;
		for (int i = 0; i < choosen.size(); ++i) {
			cout << choosen[i] << endl;
		}
	}
	mysqlx_free(res);
	return 0;
}
int DataBase::q15() {
	mysqlx_stmt_t *query;
	mysqlx_result_t *res;

	int Index = -1;
	int Max = -1;

	string qstr = "SELECT * FROM Musician;";
	query = mysqlx_sql_new(this->ses, qstr.c_str(), MYSQLX_NULL_TERMINATED);

	if ((res = mysqlx_execute(query)) == NULL) {
		cout << "Error in SQL Query" << endl;
		return -1;
	}

	vector<Musician *> v = Arr<Musician>(res);
	mysqlx_row_t *row;

	for (int i = 0; i < v.size(); ++i) {
		int64_t value;
		qstr = "SELECT count(*) from Track as a join (SELECT * from Musi_VS_Tracks where mus_ID = " + to_string(v[i]->getID()) + ") as b on a.trac_ID = b.trac_ID group by Genre;";
		if ((res = mysqlx_execute(query)) != NULL) {
			if ((row = mysqlx_row_fetch_one(res)) != NULL) {
				mysqlx_get_sint(row, 0, &value);
				if (value > Max) {
					Index = i;
					Max = value;
				}
			}else {
				cout << "SQL Query Error." << endl;
			}
		}
	}
	if (Index == -1 || Max == -1) {
		cout << "SQL Query Error." << endl;
	}else {
		cout << "Musician most Diverse Genre:" << v[Index]->getName() << endl;
	}
	return 0;
}
