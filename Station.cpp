/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I confirm that I am the only author of this file
and the content was created entirely by me.
+------------------------------------------------------------------------------+*/
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
namespace sdds {
   size_t Station::m_widthField = 0;
   size_t Station::id_generator = 0;
   Station::Station(const std::string& str) {
      Utilities utils{};
      size_t pos{};
      bool more{true};
      m_id = ++id_generator;
      m_name = utils.extractToken(str, pos, more);
      m_nextSerialNum = stoi(utils.extractToken(str, pos, more));
      m_quantity = stoi(utils.extractToken(str, pos, more));
      m_widthField = m_widthField > utils.getFieldWidth() ? m_widthField : utils.getFieldWidth();
      m_desc = utils.extractToken(str, pos, more);
   }
   const std::string& Station::getItemName() const {
      return m_name;
   }
   size_t Station::getNextSerialNumber() {     
      return m_nextSerialNum++;
   }
   size_t Station::getQuantity() const {      
      return m_quantity;
   }
   void Station::updateQuantity() {
      if ((m_quantity - 1) >= 0)
         m_quantity -=  1;
   }
   void Station::display(std::ostream& ostr, bool full) const {     
      ostr << std::setw(3) << std::setfill('0') << m_id << std::setfill(' ') << " | " <<
         std::setw(m_widthField) << std::left << m_name << std::right << "  | " <<
         std::setw(6) << std::setfill('0') << m_nextSerialNum << " | ";
      if (!full) ostr << std::endl;
      else ostr << std::setfill(' ') << std::setw(4) << m_quantity << " | " << m_desc << std::endl;
   }
}
