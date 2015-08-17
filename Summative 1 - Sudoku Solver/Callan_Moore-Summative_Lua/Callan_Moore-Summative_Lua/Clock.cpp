/*
* Bachelor of Software Engineering
* Media Design School
* Auckland
* New Zealand
*
* (c) 2005 - 2015 Media Design School
*
* File Name : Clock.cpp
* Description : Implementaion file for the Clock Class
* Author :	Callan Moore
* Mail :	Callan.Moore@mediadesign.school.nz
*/

// Library Includes
#include <windows.h>

// Local Includes
#include "Clock.h"

/***********************
* CClock: Default Constructor of the Clock Class
* @author: Callan Moore
* @return: void
********************/
CClock::CClock()
{
	m_fTimeElapsed = 0.0f;
	m_fDeltaTime = 0.0f;
	m_fLastTime = 0.0f;
	m_fCurrentTime = 0.0f;
}

/***********************
* ~CClock: Default Destructor of the Clock Class
* @author: Callan Moore
* @return: void
********************/
CClock::~CClock()
{
}

/***********************
* Initialise: Initialises the clock instance
* @author: Callan Moore
* @return: bool: true
********************/
bool CClock::Initialise()
{
	return (true);
}

/***********************
* Process: Updates the member variables, using the current time lapsed from programe start
* @author: Callan Moore
* @return: void
********************/
void CClock::Process()
{
	m_fLastTime = m_fCurrentTime;
	m_fCurrentTime = static_cast<float>(timeGetTime());
	if (m_fLastTime == 0.0f)
	{
		m_fLastTime = m_fCurrentTime;
	}
	m_fDeltaTime = m_fCurrentTime - m_fLastTime;
	m_fTimeElapsed += m_fDeltaTime;
}

/***********************
* GetDeltaTick: Returns the delta tick
* @author: Callan Moore
* @return: float: DeltaTick is how long has it taken to complete a process(the clock update)
********************/
float CClock::GetDeltaTick()
{
	return (m_fDeltaTime / 1000.0f);
}