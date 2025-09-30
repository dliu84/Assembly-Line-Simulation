/*+----------------------------------------------------------------------------+
- name          : Di Liu
- student number: 123717159
- email         : dliu84@myseneca.ca
- date          : Mar 29, 2023
I confirm that I am the only author of this file
and the content was created entirely by me.
+------------------------------------------------------------------------------+*/
#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"
namespace sdds {
   class CustomerOrder {
		struct Item{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };
			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name{}; // the name of the customer
		std::string m_product{}; // the name of the product
		size_t m_cntItem{}; // a count of the number of items in the customer's order
		Item** m_lstItem{}; // a dynamically allocated array of pointers. 
		                    // Each element of the array points to a dynamically allocated object of type Item
		static size_t m_widthField;
	public: 
		CustomerOrder(){};
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& order); // throw exception if copy constructor is called
		CustomerOrder& operator=(const CustomerOrder& order) = delete; // copy assingment operator is deleted
		CustomerOrder(CustomerOrder&& order) noexcept;
		CustomerOrder& operator=(CustomerOrder&& order) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& ostr);
		void display(std::ostream& ostr) const;
   };
}
#endif // !SDDS_CUSTOMERORDER_H



