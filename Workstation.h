/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
+------------------------------------------------------------------------------+*/
#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds {
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;
   class Workstation: public Station {
      std::deque<CustomerOrder> m_orders; 
      Workstation* m_pNextStation{};
   public:
      Workstation(const std::string& str);
      Workstation(const Workstation& workstation) = delete;
      Workstation& operator=(const Workstation& workstation) = delete;
      Workstation(Workstation& workstation) = delete;
      Workstation& operator=(Workstation& workstation) = delete;
      void fill(std::ostream& ostr);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station = nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& ostr) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
   };
}
#endif // !SDDS_WORKSTATION_H



