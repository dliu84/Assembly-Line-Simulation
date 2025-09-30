/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I confirm that I am the only author of this file
and the content was created entirely by me.
+------------------------------------------------------------------------------+*/
#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
namespace sdds {
   class Station {
      size_t m_id{}; // the id of the station
      std::string m_name{}; // the name of the item handled by the station
      std::string m_desc{}; // the description of the station
      size_t m_nextSerialNum{}; // the next serial number to be assigned to an item at this station 
      size_t m_quantity{}; // the number of items currently in stock
      static size_t m_widthField; 
      static size_t id_generator; 
   public: 
      Station(const std::string& str);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& ostr, bool full) const;
   };
}
#endif // !SDDS_STATION_H



