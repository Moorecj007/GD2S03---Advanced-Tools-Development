/*
* Bachelor of Software Engineering
* Media Design School 
* Auckland
* New Zealand 
  
* (c) 2005 - 2015 Media Design School 
  
* File Name : Clock.h 
* Description : Header file for the Clock class
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz 
*/

#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

class CClock
{
public:
	// Constructors / Destructors
	CClock();
	~CClock();

	// Prototypes
	bool Initialise();
	void Process();

	// Getters
	float GetDeltaTick();

private:
	//Disallowing copies
	CClock(const CClock& _kr);
	CClock& operator= (const CClock& _kr);

	// Member Variables
protected:
	float m_fTimeElapsed;
	float m_fDeltaTime;
	float m_fLastTime;
	float m_fCurrentTime;
};

#endif // __CLOCK_H__