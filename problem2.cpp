#include <iostream>
#include <string.h>

//template class
template<class T>
class Vector
{
public :
	T x_, y_;

	friend std:: ostream& operator<<(std::ostream& os, const Vector& vec)
	{
		os << vec.x_ << " " << vec.y_;
		return os;
	}

	friend  Vector operator + (Vector lhs, const  Vector& rhs) 
	{
		lhs.x_ += rhs.x_;
		lhs.y_ += rhs.y_;

		return lhs;
	}
	
};

//generic function
template<class T_CLASS>
void print(const T_CLASS& i)
{
	std::cout << i << std::endl;
}


int main()
{
	Vector<int> my_vector, my_vector2, my_vector3;
	my_vector.x_ = 1.0f;
	my_vector.y_ = 2.0f;
	my_vector2.x_ = 3.0f;
	my_vector2.y_ = 13.0f;
	my_vector3 = my_vector + my_vector2;
	print(my_vector3);

	return 0;
}