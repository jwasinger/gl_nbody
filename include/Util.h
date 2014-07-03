#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

bool checkSDLError(void);

struct RECT
{
	int left, right, top, bottom;
};

struct RECTF
{
	float left, right, top, bottom;
};

#endif // UTIL_H_INCLUDED
