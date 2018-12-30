#include <iostream>
#include "htmlform.h"

using namespace std;

const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
const char HEX2DEC[256] = 
  {
    /*       0  1  2  3   4  5  6  7   8  9  A  B   C  D  E  F */
    /* 0 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 1 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 2 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 3 */  0, 1, 2, 3,  4, 5, 6, 7,  8, 9,-1,-1, -1,-1,-1,-1,
    
    /* 4 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 5 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 6 */ -1,10,11,12, 13,14,15,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 7 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    
    /* 8 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* 9 */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* A */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* B */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    
    /* C */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* D */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* E */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    /* F */ -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1
  };
    


void HTMLform::debug()
{
  cout << "<hr />";
  cout << "Version 1 from 9/23/15" << endl;
  cout << "we read in [" << m_PostData << "]";
  cout << "<br />Table:<br />";
  cout << "<table border='1'>";
  for (int i=0;i<m_Pairs.size();i++)
  {
    cout << "<tr>";
    cout << "<td>[";
    cout << m_Pairs[i].getName(); 
    cout << "]</td>";
    cout << "<td>[";
    cout << m_Pairs[i].getValue(); 
    cout << "]</td>";
    cout << "</tr>";
  }
  cout << "</table>";

  cout << "<hr />";
}

void HTMLform::getPostData()
{
  getline(cin, m_PostData);
  /// store those lines in m_Pairs
  
  /* format:
  name1=value1&name2=value2&name3=value3...
  */

  string postData = m_PostData;
  string firstPair;
  int pos;
  while (postData.length() > 1)
  {
    //cout << "Debug: postData [" << postData << "]<br />";
    pos = postData.find("&");
    if (pos != string::npos)
    {
      firstPair = postData.substr(0, pos);   
      postData.erase(0, pos+1);
      processPair(firstPair);
    }
    else 
    {
      processPair(postData);
      postData.clear();
    }
  }

}

void HTMLform::processPair(string nvpair)
{
  //cout << "Debug: nvpair [" << nvpair << "]<br />";
  NameValuePair temp;
  string first;
  string second;
  int pos = nvpair.find("=");
  first = nvpair.substr(0,pos);
  second = nvpair.substr(pos+1);  /// until the end
  /// before url decode !!!
  //cout << "Debug: first [" << first << "]<br />";
  //cout << "Debug: second [" << second << "]<br />";
  first = urlDecode(first);
  second = urlDecode(second);
  /// after url decode !!!
  //cout << "Debug: decoded first [" << first << "]<br />";
  //cout << "Debug: decoded second [" << second << "]<br />";

  temp.setName(first);
  temp.setValue(second);
  m_Pairs.push_back(temp);
  //cout << "Debug: pairs stored = [" << m_Pairs.size() << "]<br />";
}

string HTMLform::urlDecode(string &sSrc)
{
  /// turn plus signs into spaces first
  int pos;
  while ( (pos = sSrc.find("+")) != string::npos)
  {
    sSrc[pos]=' ';
  }
  
  /// from http://www.codeguru.com/cpp/cpp/algorithms/strings/article.php/c12759/URI-Encoding-and-Decoding.htm
  
  // Note from RFC1630: "Sequences which start with a percent
  // sign but are not followed by two hexadecimal characters
  // (0-9, A-F) are reserved for future extension"

  const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
  const int SRC_LEN = sSrc.length();
  const unsigned char * const SRC_END = pSrc + SRC_LEN;
  // last decodable '%' 
  const unsigned char * const SRC_LAST_DEC = SRC_END - 2;
  
  char * const pStart = new char[SRC_LEN];
  char * pEnd = pStart;
  
  while (pSrc < SRC_LAST_DEC)
    {
      //      cout << "DECODE: " << *pSrc << "<br />";
      if (*pSrc == '%')
	{
	  char dec1, dec2;
	  if (-1 != (dec1 = HEX2DEC[*(pSrc + 1)])
	      && -1 != (dec2 = HEX2DEC[*(pSrc + 2)]))
	    {
	      *pEnd++ = (dec1 << 4) + dec2;
	      pSrc += 3;
	      continue;
	    }
	}
      
      *pEnd++ = *pSrc++;
    }
  
  // the last 2- chars
  while (pSrc < SRC_END)
    *pEnd++ = *pSrc++;
  
  std::string sResult(pStart, pEnd);
  delete [] pStart;
  //cout << "DECODE DONE: " << sResult << "<br />";

  return sResult;
}



string HTMLform::getField(string field)
{
  string retValue;
  for (int i=0;i<m_Pairs.size();i++)
  {
    if (m_Pairs[i].getName() == field) retValue= m_Pairs[i].getValue(); 
  }
  return retValue;
}
