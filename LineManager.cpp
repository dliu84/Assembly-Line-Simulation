/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I have done all the coding by myself and only copied the code that my professor
provided to complete my workshops and assignments.
+------------------------------------------------------------------------------+*/
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"
namespace sdds {
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
      Utilities utils;
      std::string::size_type pos{};
      std::ifstream myfile(file);
      std::string line{}, currStationStr{}, nextStationStr{};
      bool more{};
      std::vector<std::string> currStationVector, nextStationVector;
      if (myfile) {
         while (myfile && getline(myfile, line, '\n')) {
            // reuse logic from utilities module to get the current station and next station
            currStationStr = utils.extractToken(line, pos, more);
            // push to current station
            currStationVector.push_back(currStationStr);
            if (more) 
               nextStationStr = utils.extractToken(line, pos, more);                  
            else 
               nextStationStr = "";
            // push to next station
            nextStationVector.push_back(nextStationStr);

            auto first = std::find_if(stations.begin(), stations.end(), [currStationStr](const Workstation* firstworkstation) {
               return currStationStr == firstworkstation->getItemName();
               });

            auto second = std::find_if(stations.begin(), stations.end(), [nextStationStr](const Workstation* firstworkstation) {
               return nextStationStr == firstworkstation->getItemName();
               });

            if (second != stations.end() && first != stations.end())
                (*first)->setNextStation(*second);

            if (first == stations.end()) {
               std::string err {"Error wroking on the first station."};
               throw err;
            }
            else 
               m_activeLine.push_back(*first);
         }
         // loop over m_activeLine vector, identifies the first station in the assembly line and stores its address in the m_firstStation attribute. 
         for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* firstworkstation) {
            auto result = any_of(stations.begin(), stations.end(), [=](Workstation* secondworkstation) {
               if (secondworkstation->getNextStation() == firstworkstation) 
                  return true;
               else 
                  return false;
            });
            if (!result) 
               m_firstStation = firstworkstation;
         });         
         m_cntCustomerOrder = g_pending.size();           
      }
      else {
         std::string err{ "file " + file + " can not be opened." };
         throw err;
      }
   }
   void LineManager::reorderStations(){
      std::vector<Workstation*> activeLine;
      Workstation* nextworkstation{ m_firstStation };
      while (nextworkstation) {
         activeLine.push_back(nextworkstation);
         nextworkstation = nextworkstation->getNextStation();
      }
      m_activeLine = activeLine;
   }
   bool LineManager::run(std::ostream& ostr) {
      static size_t count{};
      bool result{};

      ostr << "Line Manager Iteration: " << ++count << std::endl;
      if(!g_pending.empty()){
         *m_activeLine.front() += std::move(g_pending.front());
         g_pending.pop_front();
      }
      for (size_t i = 0; i < m_activeLine.size(); ++i) {
         m_activeLine[i]->fill(ostr);
      }
      for (size_t i = 0; i < m_activeLine.size(); ++i) {
         m_activeLine[i]->attemptToMoveOrder();
      }
      if(m_cntCustomerOrder == (g_completed.size() + g_incomplete.size())) result = true;
      return result;
   }
   void LineManager::display(std::ostream& ostr) const {
      for (size_t i = 0; i < m_activeLine.size(); ++i) {
         m_activeLine[i]->Workstation::display(ostr);
      }
   }
}
