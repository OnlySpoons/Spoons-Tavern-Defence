/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#pragma once
#include <string>

namespace spty {

	//Function to cast between Event types
	template<typename toType, typename fromType>
	toType EventCast( fromType& from ) { return *dynamic_cast< toType* >(&from); }

	template<typename T>
	class Event
	{
	//Variables
	protected:
		T type_;
		std::string name_;
		bool handled_ = false;

	//Functions
	public:
		//Constructors
		Event() {}
		Event(T type, const std::string& name = "") : type_(type), name_(name) {}

		//Destructor
		virtual ~Event() {}

		inline const T type() const { return type_; }
		inline const std::string& getName() const { return name_; }
		virtual bool isHandled() const { return handled_; }
		virtual void handle() { handled_ = true; }
	};
}