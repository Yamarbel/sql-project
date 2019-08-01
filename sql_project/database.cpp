
#include "database.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

void clearCin() {
    string temp;
    getline(cin, temp);
}


Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
    connection_properties["hostName"] = DB_HOST;
    connection_properties["port"] = DB_PORT;
    connection_properties["userName"] = DB_USER;
    connection_properties["password"] = DB_PASS;
    connection_properties["OPT_RECONNECT"] = true;
}


Database & Database::getInstance() {
    if (Database::instance == 0) {
        instance = new Database();
    }
    return *instance;
}

Connection * Database::getConnection() {
    try {
        Connection *con = driver->connect(connection_properties);
        con->setSchema(DB_NAME);
        return con;
    }
    catch (SQLException &e) {
        cout << e.what();
    }
    return 0;
}


//Option 1
void Database::PrintAlbumsDate() {
    string temp1, temp2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM albums where start_day >= ? AND end_day <= ?;");

    cout << "\nPlease enter date in this pattern YYYY-MM-DD\n" << endl;
    cout << "Please enter start date:> ";
    clearCin();
    getline(cin, temp1);
    pstmt->setString(1, temp1);
    cout << "Please enter end date:> ";
    getline(cin, temp2);
    pstmt->setString(2, temp2);
    rset = pstmt->executeQuery();

    if (rset->first()) {
        cout << "Number of albums between: " << temp1 << " and " << temp2 << " is: " << rset->rowsCount() << "." << endl;
    }
    else cout << "invalid date or no albums found that were recorded between dates." << endl;


    delete con;
    delete pstmt;
    delete rset;
}

//Option 2
void Database::PrintSingerDate() {
    string temp1, temp2, temp3;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("SELECT * FROM songs_view WHERE musician_name = ? AND song_record_date >= ? AND song_record_date < ?");

    cout << "Please enter musician name:> ";
    clearCin();
    getline(cin, temp1);
    pstmt->setString(1, temp1);
    cout << "\nPlease enter date in this pattern YYYY-MM-DD\n" << endl;
    cout << "Please Enter Start Date:> ";
    getline(cin, temp2);
    pstmt->setString(2, temp2);
    cout << "Please Enter End Date:> ";
    getline(cin, temp3);
    pstmt->setString(3, temp3);
    rset = pstmt->executeQuery();

    if (rset->first()) {
        cout << "Number of songs recorded between " << temp2 << " And " << temp3 << " Is: " << rset->rowsCount() << "." << endl;
    }
    else cout << "Invalid date or no songs found that where ordered between dates." << endl;


    delete con;
    delete pstmt;
    delete rset;
}

//Option 3
void Database::PrintMusicianDate() {
    string temp1, temp2, temp3;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("SELECT DISTINCT(album_id) FROM songs_view WHERE musician_name = ? AND (end_day > ? AND start_day < ?)");
    
    cout << "Please enter musician name:> ";
    clearCin();
    getline(cin, temp1);
    pstmt->setString(1, temp1);
    cout << "\nPlease enter date in this pattern YYYY-MM-DD\n" << endl;
    cout << "Please Enter Start Date:> ";
    getline(cin, temp2);
    pstmt->setString(2, temp2);
    cout << "Please Enter End Date:> ";
    getline(cin, temp3);
    pstmt->setString(3, temp3);
    rset = pstmt->executeQuery();

    if (rset->first()) {
        cout << "Number of albums " << temp1 << " has been part of Between " << temp2 << " And " << temp3 << " Is: " << rset->rowsCount() << "." << endl;
    }
    else cout << "Invalid date or no albums found that where found between dates." << endl;


    delete con;
    delete pstmt;
    delete rset;
}

//Option 4
void Database::PrintPopularInstrument() {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *pstmt = con->createStatement();
    ResultSet *rset = pstmt->executeQuery("select instruments.instrument_type from instruments where instruments.instrument_id = (SELECT instrument_id FROM instruments_song GROUP BY instrument_id ORDER BY COUNT(*) DESC LIMIT 1)");

    rset->first();
    cout << "The most popular instrument is: " << rset->getString("instrument_type");
    cout << endl << endl;

    delete con;
    delete pstmt;
    delete rset;
}

//Option 5
void Database::PrintInstrumentsInAlbum() {
        string temp;
        Connection *con = driver->connect(connection_properties);
        con->setSchema(DB_NAME);
        PreparedStatement *pstmt = con->prepareStatement("select instrument_type from instruments where instruments.instrument_id = any(select instument_id from album_instruments   where  album_id =(select id from  albums where album_name = ? ))");


        cout << "Please Album name: > ";
        cin >> temp;
        pstmt->setString(1, temp);
        ResultSet *rset = pstmt->executeQuery();
        rset->beforeFirst();
        int count = 1;
        cout << "List of all instruments in album " << temp << " :" << endl;
        while (rset->next()) {
            cout << count << ". " << rset->getString("instrument_type") << endl;
            count++;
        }
    
        delete rset;
        delete con;
        delete pstmt;
}

//Option 6
void Database::PrintEffectiveProducer() {
    string temp1, temp2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("select producer_name from Producers where producer_id =(select producer_id from(select producer_id ,count(producer_id) as 'count' from (select producer_id from Albums where start_day and end_day between ? and ?) as M group by producer_id order by count DESC limit 1) as T)");

    cout << "\nPlease enter date in this pattern YYYY-MM-DD\n" << endl;
    cout << "Please Enter Start Date:> ";
    clearCin();
    getline(cin, temp1);
    pstmt->setString(1, temp1);
    cout << "Please Enter End Date:> ";
    getline(cin, temp2);
    pstmt->setString(2, temp2);
    rset = pstmt->executeQuery();
    rset->first();

    if (rset->first()) {
        cout << "The most effective producer between: " << temp1 << " And " << temp2 << " Is: " << rset->rowsCount() << "." << endl;
    }
    else cout << "Invalid Date or No Orders Found That Where Ordered Between Dates." << endl;


    delete con;
    delete pstmt;
    delete rset;
}

//Option 7
void Database::PrintEffectiveCreator() {

    string bookName;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *pstmt = con->createStatement();
    ResultSet *rset = pstmt->executeQuery("select instrument_creator from instruments where instrument_id = (SELECT instrument_id FROM instruments_song GROUP BY instrument_id ORDER BY COUNT(*) DESC LIMIT    1)");

    rset->first();
    cout << "The most popular instrument creator: " << rset->getString("instrument_creator");
    cout << endl << endl;

    delete con;
    delete pstmt;
    delete rset;
}

// Option 8
void Database::PrintAllMusicians() {

    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *pstmt = con->createStatement();
    ResultSet *rset = pstmt->executeQuery("SELECT COUNT(distinct musician_id) AS allm FROM musicians");

    rset->first();
    cout << "The number of Musicians: " <<rset->getInt("allm") << endl;

    delete con;
    delete pstmt;
    delete rset;
}

// Option 9
void Database::PrintFriendlyMusician() {
}

// Option 10
void Database::PrintPopularGenre() {

    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *pstmt = con->createStatement();
    ResultSet *rset = pstmt->executeQuery("SELECT song_genre FROM songs GROUP BY song_genre ORDER BY COUNT(*) DESC LIMIT 1; ");

    rset->first();
    cout << "The most popular genre is: " << rset->getString("song_genre");
    cout << endl << endl;


    delete con;
    delete pstmt;
    delete rset;
}

// Option 11
void Database::PrintEffectiveTechnician() {

    string temp1, temp2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("select technician_name from technicians where technician_id = (select technician_id from(select * from songs where song_record_date >= ? and ?)  as o group by technician_id ORDER BY COUNT(*) DESC LIMIT    1)");
    cout << "\nPlease enter date in this pattern YYYY-MM-DD\n" << endl;
    cout << "Please Enter Start Date:> ";
    clearCin();
    getline(cin, temp1);
    pstmt->setString(1, temp1);
    cout << "Please Enter End Date:> ";
    getline(cin, temp2);
    pstmt->setString(2, temp2);
    rset = pstmt->executeQuery();
    rset->first();

    if (rset->first()) {
        cout << rset->getString("technician_name") << " Has recorded "  << "Songss Since " << temp1 << " until "  << temp2 << ". More Than Any Other technician." << endl;
    }
    else cout << "Invalid Date." << endl;

    delete con;
    delete pstmt;
    delete rset;
}

//Option 12
void Database::PrintFirstAlbum() {
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    Statement *pstmt = con->createStatement();
//    ResultSet *rset = pstmt->executeQuery("SELECT MIN(end_day) FROM albums;");
    ResultSet *rset = pstmt->executeQuery("SELECT album_name FROM albums ORDER BY end_day;");

    rset->first();
    cout << "The first album recorded is: " << rset->getString("album_name");
    cout << endl;

    delete con;
    delete pstmt;
    delete rset;
}

//Option 13
void Database::PrintSameSong() {

    string temp1, temp2;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    Statement *stmt = con->createStatement();
    rset = stmt->executeQuery("SELECT COUNT(album_id) AS albums, song_name FROM songs_view GROUP BY song_id HAVING albums > 1");

    rset->beforeFirst();
    cout << "Songs you can find in 2 albums:" << endl;
    
    while (rset->next()) {
        cout << rset->getString("song_name") << endl;
    }

    delete con;
    delete rset;
}

//Option 14
void Database::PrintAllTechnician() {

    string temp1, temp2;
    int counter = 1;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("SELECT DISTINCT (technician_name), album_id, COUNT(song_id) AS songs_counter, songs_count FROM songs_view GROUP BY album_id, technician_name HAVING COUNT(song_id) = songs_count;");

    rset = pstmt->executeQuery();
    rset->beforeFirst();

    cout << "Techinichans who participated an entire album:" << endl;

    while (rset->next()) {
        cout << rset->getString("technician_name") << endl;
    }

    delete con;
    delete pstmt;
    delete rset;
}

//Option 15
void Database::PrintCreativeMusician() {

    string temp;
    Connection *con = driver->connect(connection_properties);
    con->setSchema(DB_NAME);
    ResultSet *rset;
    PreparedStatement *pstmt = con->prepareStatement("SELECT COUNT(song_genre) AS genres, musician_name FROM songs_view GROUP BY musician_id ORDER BY genres DESC LIMIT 1 ;");

    rset = pstmt->executeQuery();
    rset->first();

    if (rset->first()) {
        cout << rset->getString("musician_name") << endl;
    }
    else cout << "Invalid musician." << endl;

    delete con;
    delete pstmt;
    delete rset;

}



