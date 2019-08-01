#ifndef database_hpp
#define database_hpp

#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>


using namespace sql;
using namespace std;
    
#define DB_NAME "albums_scheme"
#define DB_HOST "tcp://127.0.0.1/"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_PASS "root"

class Database {
private:
    // singleton instance
    static Database *instance;
    
    Driver *driver;
    ConnectOptionsMap connection_properties;
    
    // private CTOR (singleton)s
    Database();
public:
    static Database& getInstance();
    Connection *getConnection();
    
    virtual ~Database() {}


    /* Menu Options Functions */

    //Option 1
    void PrintAlbumsDate();
    //Option 2
    void PrintSingerDate();
    //Option 3
    void PrintMusicianDate();
    //Option 4
    void PrintPopularInstrument();
    //Option 5
    void PrintInstrumentsInAlbum();
    //Option 6
    void PrintEffectiveProducer();
    //Option 7
    void PrintEffectiveCreator();
    // Option 8
    void PrintAllMusicians();
    // Option 9
    void PrintFriendlyMusician();
    // Option 10
    void PrintPopularGenre();
    // Option 11
    void PrintEffectiveTechnician();
    //Option 12
    void PrintFirstAlbum();
    //Option 13
    void PrintSameSong();
    //Option 14
    void PrintAllTechnician();
    //Option 15
    void PrintCreativeMusician();


};


#endif /* database_hpp */
