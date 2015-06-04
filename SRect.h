#pragma once
#include "SVector2.h"

template <typename T> class SRect{
public:
	SRect(){

	}
	SRect(const T& left, const T& top, const T& width, const T& height) 
		: position(left, top)
		, size(width, height){
	}
	SRect(const sf::Rect<T>& rect) 
		: position(sf::Vector2<T>(rect.left, rect.top))
		, size(sf::Vector2<T>(rect.width, rect.height)){

	}
	operator sf::Rect<T>() const{
		return sf::Rect<T>(position, size);
	}
	const T getTop() const{
		return position.y;
	}
	void setTop(const T& top){
		position.y = top;
	}
	const T getLeft() const{
		return position.x;
	}
	void setLeft(const T& left){
		position.x = left;
	}
	const T getWidth() const{
		return size.x;
	}
	void setWidth(const T& width){
		size.x = width;
	}
	const T getHeight() const{
		return size.y;
	}
	void setHeight(const T& height){
		size.y = height;
	}
	
	__declspec (property(get = getTop, put = setTop)) T top;
	__declspec (property(get = getLeft, put = setLeft)) T left;
	__declspec (property(get = getWidth, put = putWidth)) T width;
	__declspec (property(get = getHeight, put = putHeight)) T height;
private:
	SVector2<T> position;
	SVector2<T> size;
};
typedef SRect<float> SFloatRect;
