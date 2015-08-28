/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Defines.h
* Description : Declaration file to holds structs, enums and various containers/variables to be shared
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

#pragma once

#if !defined(__DEFINES_H__)
#define __DEFINES_H__

// Library Includes
#include <windows.h>

// Enumerators
enum eImage
{
	IMAGE_BLANK,
	IMAGE_1,
	IMAGE_2,
	IMAGE_3,
	IMAGE_4,
	IMAGE_5,
	IMAGE_6,
	IMAGE_7,
	IMAGE_8,
	IMAGE_9,

};

#define VALIDATE(a) if (!a) return (false)

#endif //__DEFINES_H__
