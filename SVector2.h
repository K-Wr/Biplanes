#pragma once
#include "Header.h"
template <typename T> class SVector2
{
public:
	SVector2(){
	}
	SVector2(const sf::Vector2<T>& sfvect) : screenVector({ sfvect.x / coff.x, sfvect.y / coff.y}){
	}
	SVector2(const T _x, const T _y) : screenVector(_x, _y){

	}
	static void setConversation(const sf::Vector2f& expectedSize, const sf::Vector2f& screenSize){
		coff = { screenSize.x / expectedSize.x, screenSize.y / expectedSize.y };
		isSet = true;
	}
	static void setConversation(const sf::Vector2f& convCoff){
		coff = convCoff;
	}
	//static SVector2<T> convert(const sf::Vector2f& sfvect){
	//	if (!isSet)
	//		throw GameException("Coff not set", "SVector2::convert()");
	//	else
	//		return SVector2<T>(sfvect.x / coff.x, sfvect.y / coff.y);
	//}
	static const sf::Vector2f& getConversation(){
		return coff;
	}
	operator sf::Vector2<T>() const{
		if (isSet)
			return sf::Vector2<T>(screenVector.x * coff.x, screenVector.y * coff.y);
		else
			throw GameException("Conversation for SVector2<T> is not set", "SVector2<T>::operator sf::Vector2<T>()");
	}
	void normalize(const float length = 1.f){
		float realLength = sqrt(x*x + y*y);
		if (!realLength)
			return;
		x /= realLength;
		y /= realLength;
		x *= length;
		y *= length;
	}
	~SVector2(){
	}
	const T getX() const{
		return screenVector.x;
	}
	const T getY() const{
		return screenVector.y;
	}
	void setX(const T nX){
		screenVector.x = nX;
	}
	void setY(const T nY){
		screenVector.y = nY;
	}
	__declspec(property(get = getX, put = setX)) T x;
	__declspec(property(get = getY, put = setY)) T y;
private:
	sf::Vector2<T> screenVector;
	static sf::Vector2f coff;
	static bool isSet;
};
typedef SVector2<float> SVector2f;
typedef SVector2<double> SVector2d;
typedef SVector2<unsigned> SVector2u;
typedef SVector2<int> SVector2i;
