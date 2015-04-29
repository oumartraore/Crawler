//
//  DbaLink.cpp
//  
//
//  Created by Oumar TRAORE on 06/06/2014.
//
//

#include "DbaLink.h"

#define INSERT_CRAWL "INSERT INTO results(title, description, keyword, pagerank, url) \
			VALUES (?,?,?,?,?)"
			
#define UPDATE_CRAWL "UPDATE results SET title = \'?\', SET description = \'?\' \
	      SET keyword = \'?\' \
	      SET pagerank = \'?\' \
	      WHERE url = \'?\'"

#define STRING_SIZE 500

DbaLink::DbaLink()
{
  mysql_init(&mysql);
    if( mysql_real_connect(&mysql, "localhost", "root", "root", "moteur", 0, NULL, 0))
      cout << "OK" << endl;

  stmG = mysql_stmt_init(&mysql);
}

DbaLink::~DbaLink()
{
}

void DbaLink::setStartLink(ListLink *crawler)
{
  if(mysql_query(&mysql, "SELECT * from links"))
  {
    // Une erreur est survenu
  }
  
  MYSQL_RES *result = mysql_store_result(&mysql);
  if(result == NULL)
  {
    // Erreur
  }
  
  MYSQL_ROW row;
  
  while((row = mysql_fetch_row(result)))
  {
      // Ajout des liens de départ
      (*crawler).setAllDomaine(row[1]);
  }
  
  mysql_free_result(result);
}


void DbaLink::doUpdateCrawl()
{
  
  if(mysql_query(&mysql, "select * from results"))
  {
    // Une erreur est survenu
  }
  
  
  MYSQL_RES *result = mysql_store_result(&mysql);
  if(result == NULL)
  {
    // Erreur
  }
  
  
  numb_fields = mysql_num_fields(result);
 
  MYSQL_ROW row;
  
  while((row = mysql_fetch_row(result)))
  {
	string content = row[1];
	urlDejaCraw.push_back(content);
  }
  
  mysql_free_result(result);
  
}

void DbaLink::setCrawl(ListLink linkC)
{
  vector<Link> lien = linkC.getlinkDone();
  
  string description;
  string keyword;
  string url;
  string title;
  
  int rank;
  
  unsigned long a;
  
  int linkBase = 0;
  
  
  for(int i = 0; i < (int)lien.size(); i++)
  {
    string domaine = lien[i].getDomaine();
    string url1 = lien[i].getContent();
    
    url = domaine.append(url1);
    
    title = lien[i].getTitle();
    
    vector<Meta> meta = lien[i].getMeta();
    for(int j = 0; j < (int)meta.size(); j++)
    {
      if(j == 0)
	description = meta[0].getContent().c_str();
      if(j == 1)
	keyword = meta[1].getContent().c_str();
      
      rank = lien[i].getRank();
    }
    
   if(stmG)
   {
      int choix = 0;
      
      for(int i = 0; i < (int)urlDejaCraw.size(); i++)
      {
	  string comp = urlDejaCraw[i];
	  
	  if(url.compare(comp) == 0)
	  {
	    choix = 1;
	    linkBase = i;
	  }
      }
   
    // On lie les parametre à la variable bind
    memset(bind, 0, sizeof(bind));
    
    // choix = 0;
     switch(choix)
     {
       case 1:
	 // On fait un Update
	  if(mysql_stmt_prepare(stmG, UPDATE_CRAWL, strlen(UPDATE_CRAWL)))
	  {
	    cout << "Erreur choix 2" << endl;
	  }
	  cout<< "Update Database" << endl;
	 break;
       case 0:
	  // On fait une Insert
	  if(mysql_stmt_prepare(stmG, INSERT_CRAWL, strlen(INSERT_CRAWL)))
	  {
	    cout << "Erreur choix 2" << endl;
	  }
	  cout<< "Insert Database" << endl;
	  break;
     }
        //title (string)
      bind[0].buffer_type = MYSQL_TYPE_STRING;
      bind[0].buffer = (char *)title.c_str();
      bind[0].buffer_length = STRING_SIZE;
      bind[0].is_null = 0;
      a = (unsigned long)url.size();
      bind[0].length = &a;
      
      //description (string)
      bind[1].buffer_type = MYSQL_TYPE_STRING;
      bind[1].buffer = (char *)description.c_str();
      bind[1].buffer_length = STRING_SIZE;
      bind[1].is_null = 0;
      a = (unsigned long)url.size();
      bind[1].length = &a;
      
      //keyword (string)
      bind[2].buffer_type = MYSQL_TYPE_STRING;
      bind[2].buffer = (char *)keyword.c_str();
      bind[2].buffer_length = STRING_SIZE;
      bind[2].is_null = 0;
      a = (unsigned long)url.size();
      bind[2].length = &a;
      
      
      // Pagerank (int)
      bind[3].buffer_type = MYSQL_TYPE_LONG;
      bind[3].buffer = (char *)&rank;
      bind[3].is_null = 0;
      bind[3].length = 0;
      
      //url (string)
      bind[4].buffer_type = MYSQL_TYPE_STRING;
      bind[4].buffer = (char *)url.c_str();
      bind[4].buffer_length = STRING_SIZE;
      bind[4].is_null = 0;
      a = (unsigned long)url.size();
      bind[4].length = &a;
      
      if(mysql_stmt_bind_param(stmG, bind))
      {
	cout << "Erreur 2" << endl;
      } 
      if(mysql_stmt_execute(stmG))
      {
	cout << "Erreur 3" << endl;
      }
      
      
   }  
  }
}


void DbaLink::closeConnection()
{
  mysql_close(&mysql);
}