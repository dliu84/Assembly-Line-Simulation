/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
+------------------------------------------------------------------------------+*/
#include "Workstation.h"
namespace sdds {
   std::deque<CustomerOrder> g_pending{};
   std::deque<CustomerOrder> g_completed{};
   std::deque<CustomerOrder> g_incomplete{};
   /*passes it to the Station base class*/
   Workstation::Workstation(const std::string& str) : Station(str) { };
   void Workstation::fill(std::ostream& ostr) {
      if (!m_orders.empty()) 
         m_orders.front().fillItem(*this, ostr);
   }
   /*move the order order at the front of the queue to the next station in the assembly line:*/
   bool Workstation::attemptToMoveOrder() {
      bool result{};
       
      if (!m_orders.empty()) {
         if (m_orders.front().isItemFilled(getItemName())) {
            if (m_pNextStation){
               *m_pNextStation += std::move(m_orders.front());
            }
            else if (m_orders.front().isOrderFilled()) {
               g_completed.push_back(std::move(m_orders.front()));
            }
            else {
               g_incomplete.push_back(std::move(m_orders.front()));
            }
            result = true;
            m_orders.pop_front();
         }
         else if (Station::getQuantity() == 0) {
            if (m_pNextStation) {
               *m_pNextStation += std::move(m_orders.front());
            }
            else {
               g_incomplete.push_back(std::move(m_orders.front()));
            }
            result = true;
            m_orders.pop_front();
         }
      }
      return result;
   }
   void Workstation::setNextStation(Workstation* station) {
      m_pNextStation = station;
   }
   Workstation* Workstation::getNextStation() const {
      return m_pNextStation;
   }
   void Workstation::display(std::ostream& ostr) const {
      if (m_pNextStation)
         ostr << this->getItemName() << " --> " << m_pNextStation->getItemName();
      else
         ostr << this->getItemName() << " --> " << "End of Line";
      ostr << std::endl;
   }
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
      m_orders.push_back(std::move(newOrder));
      return *this;
   }
}
