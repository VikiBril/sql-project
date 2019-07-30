// Coded with blood swet and tear by Viki Brill - 207129446, and Or Ilani - 307934406

#include "pch.h"
#include "DB_all.h"

using namespace std;


int main() {

	DataBase DB("demoUser", "demo");

	if (DB.Con_to_DB() == -1) {
		cout << "Error while trying to connect" << endl;
		exit(-1);
	}
	cout << "Connected !" << endl;

	if (DB.Initial_DB_tbl() == -1) {
		cout << "DB initial Error ! (Tables)" << endl;
		exit(-1);
	}
	cout << "DB initial ! (Tables)" << endl;

	if (DB.Initial_DB_data() == -1) {
		cout << "Data initial Error" << endl;
		exit(-1);
	}
	cout << "Data initial !" << endl;

	bool flag = true;
	string s1, s2, temp;

	cout << "Welcome to Viki & Or Music_Company Course Project\n" << endl;

	int query = 0;
	 while (flag){

		cout << "\tchoose the number of the question:" << endl;
        cout << "\t1) Count of albums between dates" << endl;
        cout << "\t2) Count of different song record by musician between dates" << endl;
        cout << "\t3) Count of different albums to musician" << endl;
        cout << "\t4) Most popular Instrument" << endl;
        cout << "\t5) Instrument in Album" << endl;
        cout << "\t6) Popular Producer between dates" << endl;
        cout << "\t7) Popular Manufacture" << endl;
        cout << "\t8) Count of Musicians record through years" << endl;
        cout << "\t9) Most collab Musician" << endl;
        cout << "\t10) Popular music Genre " << endl;
        cout << "\t11) Tech-Guy work on Most Track between dates" << endl;
        cout << "\t12) First Album" << endl;
        cout << "\t13) List of Tracks in 2 Albums or more" << endl;
        cout << "\t14) List of Tech-Guy work on full album" << endl;
        cout << "\t15) Most Diverse Musician by Genre" << endl;
        cout << "\t16) Quit ! " << endl;

		cout << "Choose Your Query: >";
		cin >> query;

		switch (query)
		{
		case 1:
			cout << "Enter the two dates ( Year-Month-Day )" << endl;
			cin >> s1 >> s2;
			cout << endl;
			if (DB.q1(s1, s2) == -1)
				cout << "SQL Query Failed!" << endl;
			break;

		case 2:{
				cout << "Enter musician name" << endl;
				getline(cin, temp);
				getline(cin, s1);
				if (DB.q2(s1) != 2)
					break;
			}
			break;

		case 3:
				cout << "Enter musician name" << endl;
				getline(cin, temp);
				getline(cin, s1);
				if (DB.q3(s1) != 2)
					break;

			break;

		case 4:
			if (DB.q4() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 5:
				cout << "Enter Album name" << endl;
				getline(cin, temp);
				getline(cin, s1);
				if (DB.q5(s1) != 2)
					break;
			break;

		case 6:
			cout << "Enter two dates ( Year-Month-Day )" << endl;
			cin >> s1 >> s2;
			cout << endl;
			if (DB.q6(s1, s2) == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 7:
			if (DB.q7() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 8:
			if (DB.q8() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 9:
			if (DB.q9() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 10:
			if (DB.q10() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 11:
			cout << "Enter two dates ( Year-Month-Day )" << endl;
			cin >> s1 >> s2;
			if (DB.q11(s1, s2) == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 12:
			if (DB.q12() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 13:
			if (DB.q13() == -1) {
				cout << "SQL Query Failed!" << endl;
			}

			break;

		case 14:
			if (DB.q14() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 15:
			if (DB.q15() == -1) {
				cout << "SQL Query Failed!" << endl;
			}
			break;

		case 16:
			flag = false;
			cout << "See You Later" << endl;
			break;

		default:
			cout << "Incorect Input, Try Again" << endl;
			break;
		}

	}

	return 0;
}
