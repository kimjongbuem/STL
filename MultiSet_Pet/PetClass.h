#pragma once
#include <string>                                // string Å¬·¡½º
#include <cstring>                               // strcmp()
using std::string;

class Pet {
protected:
	string name{};
public:
	virtual ~Pet() {}
	const string& get_name() const { return name; }

	virtual bool operator<(const Pet& pet) const {
		auto result = std::strcmp(typeid(*this).name(), typeid(pet).name());
		return (result < 0) || ((result == 0) && (name < pet.name));
	}
	friend std::ostream& operator<<(std::ostream& out, const Pet& pet);
};
inline std::ostream& operator<<(std::ostream& out, const Pet& pet) {
	return out << "A " << string{ typeid(pet).name() }.erase(0, 6) << " called " << pet.name;
}

class Dog : public Pet {
public:
	Dog() = default;
	Dog(const string& dog_name) {
		name = dog_name;
	}
};

class Cat : public Pet{
public:
	Cat() = default;
	Cat(const string& cat_name) {
		name = cat_name;
	}
};

class Mouse : public Pet {
public:
	Mouse() = default;
	Mouse(const string& mouse_name) {
		name = mouse_name;
	}
};

