#include <stdlib.h>
#include <iostream>
#include "database.hpp"

using namespace std;


int main(int argc, char* argv[])
{
	Database &db = Database::getInstance();
	int select = 99;
	while (select != 0) {
		cout << "\n\n"
			<< " Welcome to the great ori and yam albums record database.\n Please choose one of the following\n"
			<< " 1)  Show All albums recorded between dates.\n" 
			<< " 2)  Show recorded song of specific singer between dates.\n"
			<< " 3)  Show albums that muisican been involved between dates.\n"
			<< " 4)  Show the most popular instrument.\n"
			<< " 5)  Show all instruments in a specific album.\n"
			<< " 6)  Show the most effective producer between dates.\n"
			<< " 7)  Show the most producive instrument creator.\n"
			<< " 8)  Show musicians records \n"
			<< " 9)  Show the most friendly musician.\n ***not working***"
			<< " 10) Show the most popular genre.\n"
			<< " 11) Show the most producive thechnician\n"
			<< " 12) Show the first album recorded.\n"
			<< " 13) Show songs that have been recorded in two diffrents albums.\n"
			<< " 14) Show all technician who took part in specific album.\n"
			<< " 15) Show the musician who have the most genres of songs.\n"
			<< " 0) End the program. \n"
			<< "\nYour Choice: ";
		cin >> select;
		switch (select) {

		case 0: {

			cout << "Bye!" << endl;
			exit(EXIT_SUCCESS);
		}

		case 1: {
			db.PrintAlbumsDate();
			string temp1, temp2, temp3, temp4, temp5;
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

		case 2: {
            db.PrintSingerDate();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

		case 3: {
			db.PrintMusicianDate();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

		case 4: {
			db.PrintPopularInstrument();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

		case 5: {
			db.PrintInstrumentsInAlbum();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

		case 6: {
			db.PrintEffectiveProducer();
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}

		case 7: {
			db.PrintEffectiveCreator();
			cin.clear();
			break;
		}

		case 8: {
			db.PrintAllMusicians();
			cin.clear();
			break;
		}

		case 9: {
			db.PrintFriendlyMusician();
			cin.clear();
			break;
		}

		case 10: {
			db.PrintPopularGenre();
			cin.clear();
			break;
		}

		case 11: {
			db.PrintEffectiveTechnician();
			cin.clear();
			break;
		}
		case 12: {
			db.PrintFirstAlbum();
			cin.clear();
			break;
		}

		case 13: {
			db.PrintSameSong();
			cin.clear();
			break;
		}

		case 14: {
			db.PrintAllTechnician();
			cin.ignore(10000, '\n');
			break;
		}

		case 15: {
			db.PrintCreativeMusician();
			cin.clear();
			break;
		}

		default: {
			cout << "\ninvalid choice" << endl;
			select = 42;
			cin.clear();
			cin.ignore(10000, '\n');
			break;
		}




		}

		cout << "\nPress 1 to Return To the Main Menu.\nYour Choice: " << endl;
		select = 0;
		while (select != 1) {
			cin >> select;
			cin.clear();
			cin.ignore(10000, '\n');
		}


	}


	return 0;
}
