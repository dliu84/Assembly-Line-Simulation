/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 11, 2023
I confirm that I am the only author of this file
and the content was created entirely by me.
+------------------------------------------------------------------------------+*/
#include "Utilities.h"
namespace sdds {   
   char Utilities::m_delimiter{};
   void Utilities::setFieldWidth(size_t newWidth) {
      m_widthField = newWidth;
   }
   size_t Utilities::getFieldWidth() const {
      return m_widthField;
   }
   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
      std::string token{};
      size_t pos {};
      if (str.at(next_pos) == m_delimiter) {
         more = false;
         throw m_delimiter;
      }
      else {               
         pos = str.find(m_delimiter, next_pos);
         if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of(' ') + 1);
            more = true;
            m_widthField = m_widthField < token.length() ? token.length() : m_widthField;
         }
         else {
            token = str.substr(next_pos);
            token.erase(0, token.find_first_not_of(' '));
            token.erase(token.find_last_not_of(' ') + 1);
            more = false;
            m_widthField = m_widthField < token.length() ? token.length() : m_widthField;           
         }
      }
      next_pos = pos + 1;
      return token;
   }
   void Utilities::setDelimiter(char newDelimiter) {
      m_delimiter = newDelimiter;
   }
   char Utilities::getDelimiter() {
      return m_delimiter;
   }
}
