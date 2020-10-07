#include<SFML\Graphics.hpp>
using namespace sf;
View view;
View getPlayerCoordinateForView(float x, float y)
{
	float tempX = x, tempY = y;
	if (x < 484)
		tempX = 484;
	if (x > 1440)
		tempX = 1440;
	if (y >814)
		tempY = 814;
	if (y < 274)
		tempY = 274;

	view.setCenter(tempX,tempY);
	return view;
}