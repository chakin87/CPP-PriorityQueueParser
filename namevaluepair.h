#include <string>

using namespace std;


class NameValuePair
{
 public:
  // setter & getters
  inline const string getName() {return m_Name;}
  inline const string getValue() {return m_Value;}
  inline void setName(string data) {m_Name=data;}
  inline void setValue(string data) {m_Value=data;}

 private:
  string m_Name;
  string m_Value;
};
