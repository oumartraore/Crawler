//
//  DbaLink.h
//  
//
//  Created by Oumar TRAORE on 06/06/2014.
//
//

#ifndef _DbaLink_h
#define _DbaLink_h

#include <mysql_connection.h>
#include <mysql/mysql.h>
#include <cstdlib>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "../ModelClasse/ListLink.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <string>
#include <sstream>

using namespace std;
using namespace sql;

class DbaLink
{
  private:
    //
    MYSQL mysql;
    
    MYSQL_FIELD *field;
    
    MYSQL_STMT *stmG;
    MYSQL_BIND bind[5];
    MYSQL_RES *res;
    
    MYSQL_BIND bindUpdate[2];
    
    vector<string> urlDejaCraw;
    int numb_fields;
    
  public:
    DbaLink();
    ~DbaLink();
    
    void setCrawl(ListLink linkC);
    void setStartLink(ListLink *crawler);
    
    void closeConnection();
    void doUpdateCrawl();
};

#endif
