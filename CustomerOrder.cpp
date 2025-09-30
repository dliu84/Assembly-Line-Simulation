/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I confirm that I am the only author of this file
and the content was created entirely by me.
+------------------------------------------------------------------------------+*/
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds {
	size_t CustomerOrder::m_widthField{};	
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities utils{};
		size_t pos{};
		bool more{ true };
		size_t counter{};
		m_name = utils.extractToken(str, pos, more);
		m_product = utils.extractToken(str, pos, more);
		char delimiter = Utilities::getDelimiter();
		// find out how many delimiters in the string
		for (size_t i{}; i < str.size(); ++i) {
			counter += (str[i] == delimiter);
		}		
		m_cntItem = counter - 1; // (m_cntItem = number of delimiters (counter) - 2 + 1)
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(utils.extractToken(str, pos, more));
		}
		m_widthField = m_widthField < utils.getFieldWidth() ? utils.getFieldWidth() : m_widthField;
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& order) {
		throw "Copy operation is disabled.";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& order) noexcept {
		operator=(std::move(order));
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& order) noexcept {
		if (this != &order) {
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = order.m_name;
			m_product = order.m_product;
			m_cntItem = order.m_cntItem;
			m_lstItem = order.m_lstItem;
			order.m_name = "";
			order.m_product = "";
			order.m_cntItem = 0;
			order.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		bool filled{true};
		for (size_t i = 0; filled && i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) filled = false;
		}
		return filled;
	}
	/*returns true if all items specified by itemName have been filled. 
	If the item doesn't exist in the order, this query returns true*/
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool filled{};
		size_t duplicateItem{}, filledItem{};
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName) {
				duplicateItem++;
				if (m_lstItem[i]->m_isFilled) 
					filledItem++;
			}			
		}
		if (duplicateItem == filledItem) 
			filled = true;
		return filled;
	}
	/*fills one item in the current order*/
	void CustomerOrder::fillItem(Station& station, std::ostream& ostr) {
		bool filledFirstItem{};
		for (size_t i = 0; i < m_cntItem; ++i) {
			if ((m_lstItem[i]->m_itemName == station.getItemName()) && !filledFirstItem) {
				if (!m_lstItem[i]->m_isFilled) {
					if (station.getQuantity() >= 1) {
						station.updateQuantity();
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						m_lstItem[i]->m_isFilled = true;
						filledFirstItem = true;
						ostr << "    Filled ";
					}
					else
						ostr << "    Unable to fill ";
					ostr << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}				
			}
		}
	}
	void CustomerOrder::display(std::ostream& ostr) const {
		ostr << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			ostr << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') <<
				std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << std::right << "   - ";
			(m_lstItem[i]->m_isFilled) ? ostr << "FILLED" : ostr << "TO BE FILLED";
			ostr << std::endl;
		}
	}
}
