 #ifndef SALES_ITEM_H
#define SALES_ITEM_H

// Handwrtitten code all understood.
// Difference between class and struct is the default access modifier.
// That is, controlling what can be run anywhere and what can only be run inside the function.
// By default, struct sets everything to public, and class, to private.
// By doing this, the abstract data type can have an encapsulated iplementation with a public interface.
// Which is the idea behind abstract data types.

#include <string>
#include <iostream>

class sales_data {
	// Uses constructors. They act as a way to pass args to instances of classes
	// if no args passed, default values are used as stated by sales_data() = default; and 	std::string bookNo; unsigned units_sold = 0; double revenue = 0.0;
	
public:
	sales_data() = default; // allows for default constructing if other constructors dont accomdate specific data members.
	sales_data(const std::string &s): bookNo(s) { } 
	sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n) { } 
	sales_data(std::istream &); 

	// Function declarations
	std::string isbn() const {return bookNo;}
	sales_data& combine(const sales_data&);

private:
	double avg_price() const;
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;

friend sales_data add(const sales_data&, const sales_data&);
friend std::ostream &print(std::ostream&, const sales_data&);
friend std::istream &read(std::istream&, sales_data&);
};

double sales_data::avg_price() const { // Function Definitions, (not declarations) VVV"
	if (units_sold){
		return revenue/units_sold;
	}
	else{
		return 0;
	}
}

sales_data& sales_data::combine(const sales_data &rhs){ 
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

std::ostream& print(std::ostream &os, const sales_data &item){ // outputs data
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
	return os;
}

std::istream& read(std::istream &is, sales_data &item){ // reads data 
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

sales_data::sales_data(std::istream &is){ 
	read(is, *this);					 
}

sales_data add(const sales_data &lhs, const sales_data &rhs){
	sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

#endif