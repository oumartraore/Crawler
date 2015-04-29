//
//  Title.cpp
//  
//
//  Created by Oumar TRAORE on 06/06/2014.
//
//

#include "Title.h"

Title::Title()
{
  rank = 0;
}

Title::~Title()
{
}

string Title::getContent()
{
  return content;
}

void Title::setContent(string element)
{
  content = element;
}

int Title::getRank()
{
  return rank;
}

void Title::setRank()
{
  if(content.size() < 30)
    rank++;
}