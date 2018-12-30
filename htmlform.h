#include <string>
#include <vector>
#include "namevaluepair.h"

using namespace std;

class HTMLform
{
 public:
   void debug();
   void getPostData();
   string getField(string);
 private:
   void processPair(string);
   string urlDecode(string&);
   string m_PostData;

   vector<NameValuePair> m_Pairs;
};
