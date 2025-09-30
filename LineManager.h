/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 13, 2023
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
+------------------------------------------------------------------------------+*/
#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <vector>
#include "Workstation.h"
namespace sdds {
   class LineManager {
      std::vector<Workstation*> m_activeLine; // the collection of workstations for the current assembly line.
      size_t m_cntCustomerOrder{}; // the total number of CustomerOrder objects
      Workstation* m_firstStation{}; // points to the first active station on the current line
   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);
      void reorderStations();
      bool run(std::ostream& ostr);
      void display(std::ostream& ostr) const;
   };
}
#endif // !SDDS_LINEMANAGER_H


