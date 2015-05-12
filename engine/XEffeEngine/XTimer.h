#ifndef _JIA_XTIMER_
#define _JIA_XTIMER_

#include "XOSDefine.h"
#include "SDL.h"
#include <string>
namespace XE{

class XSimpleTimer
{
private:
	int m_timer;
	int m_stepTime;
public:
	XSimpleTimer()
		:m_timer(0)
		,m_stepTime(0)
	{}
	XSimpleTimer(int stepTime)
		:m_timer(0)
		,m_stepTime(stepTime)
	{}
	void setStepTime(int stepTime){m_stepTime = stepTime;}
	int getStepTime() const {return m_stepTime;}
	bool update(int stepTime)
	{
		if(m_stepTime <= 0) return true;
		m_timer += stepTime;
		if(m_timer >= m_stepTime)
		{
			m_timer -= m_stepTime;
			return true;
		}
		return false;
	}
};

class XTimer
{
public:
    XTimer();
	~XTimer(){}

    void start();
    void end();
    double getElapsedTime();
    double getElapsedTimeInSec();
    double getElapsedTimeInMilliSec();
    double getElapsedTimeInMicroSec();

	double getUpElapsedTime();
	double getCurrentTime();
private:
	double m_upTime;
    double m_startTime;
    double m_endTime;
#ifdef XEE_OS_WINDOWS
	double m_perFreq;
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_startCount;
    LARGE_INTEGER m_endCount;
	LARGE_INTEGER m_upCount;
	LARGE_INTEGER m_curCount;
#else
    timeval m_startCount;
    timeval m_endCount;
	timeval m_upCount;
	timeval m_curCount;
#endif
    bool m_stopped;
};
inline void XTimer::start()
{
    m_stopped = false;
#ifdef XEE_OS_WINDOWS
    QueryPerformanceCounter(&m_startCount);
#else
    gettimeofday(&m_startCount,NULL);
#endif
}
inline void XTimer::end()
{
    m_stopped = true;
#ifdef XEE_OS_WINDOWS
    QueryPerformanceCounter(&m_endCount);
#else
    gettimeofday(&m_endCount,NULL);
#endif
}
inline double XTimer::getElapsedTimeInMilliSec()
{
    return getElapsedTimeInMicroSec() * 0.001;
}
inline double XTimer::getElapsedTimeInSec()
{
    return getElapsedTimeInMicroSec() * 0.000001;
}
inline double XTimer::getElapsedTime()
{
    return getElapsedTimeInSec();
}
inline double XTimer::getCurrentTime()
{
#ifdef XEE_OS_WINDOWS
    QueryPerformanceCounter(&m_curCount);
    return m_curCount.QuadPart * m_perFreq * 0.001;
#else
	gettimeofday(&m_curCount,NULL);
	return (m_curCount.tv_sec * 1000000.0) + m_curCount.tv_usec;
#endif
}
struct XSystemTime
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
    XSystemTime()
        :year(0)
        ,month(0)
        ,day(0)
        ,hour(0)
        ,minute(0)
        ,second(0)
        ,millisecond(0)
    {}
    XSystemTime(int y,int m,int d)
        :year(y)
        ,month(m)
        ,day(d)
        ,hour(0)
        ,minute(0)
        ,second(0)
        ,millisecond(0)
    {}
};
#define MILLISECOND_IN_ONE_DAY (24 * 60 * 60 * 1000)
#define DAY_IN_ONE_LEAP_YEAR (366)
namespace XTime
{
	inline bool isLeapYear(int year)
	{

		return (((year & 0x03) == 0 && year % 100 != 0) || year % 400 == 0);
	}

	inline long getCurrentTicks()
	{
#ifdef CREATE_WINDOW_WITH_SDL
		return SDL_GetTicks();
#else
	#if WITH_64BIT_SUPPLY
		return GetTickCount64();
	#else
		return GetTickCount();
	#endif
#endif
	}
	extern bool getDateIsCorrect(const XSystemTime &t);
	extern void getTimeMs(XSystemTime &t);
	inline XSystemTime getTimeMs()
	{
		XSystemTime tmp;
		getTimeMs(tmp);
		return tmp;
	}
	extern bool isBefore(const XSystemTime &t1,const XSystemTime &t2);
	extern long getElapsedTime(const XSystemTime &ts,const XSystemTime &te);
	extern const int dayInMonth[12];

	inline int getMsInThisYear(const XSystemTime &t)
	{
		if(!getDateIsCorrect(t)) return 0;
		int ret = t.hour * 60 * 60 * 1000 + t.minute * 60 * 1000 + t.second * 1000 + t.millisecond;
		if(t.month <= 2) return (dayInMonth[t.month - 1] + t.day) * MILLISECOND_IN_ONE_DAY + ret;
		if(isLeapYear(t.year))
			return (dayInMonth[t.month - 1] + t.day) * MILLISECOND_IN_ONE_DAY + ret;
		else
			return (dayInMonth[t.month - 1] - 1 + t.day) * MILLISECOND_IN_ONE_DAY + ret;
	}

	inline int getDateDaysInYear(const XSystemTime &t)
	{
		if(t.month <= 2) return dayInMonth[t.month - 1] + t.day;
		if(isLeapYear(t.year)) return dayInMonth[t.month - 1] + t.day;
		else return dayInMonth[t.month - 1] - 1 + t.day;
	}

	inline int getTotalDays(const XSystemTime &t)
	{
		int tmpY = t.year - 1;
		int tmp = 365 * tmpY + getDateDaysInYear(t);

		tmp += (tmpY >> 2);
		tmpY /= 100;
		tmp += (tmpY >> 2) - tmpY;
		return tmp;
	}

	inline int getDataWeek(const XSystemTime &t)
	{
		return getTotalDays(t) % 7;
	}

	extern void getDateData(int year,int day,XSystemTime &t,int &week);

	extern void solar2lunar(const XSystemTime &in,XSystemTime &out);
	extern void lunar2solar(const XSystemTime &in,XSystemTime &out);
	inline std::string sysTime2String(const XSystemTime &in)
	{
		char tmp[20];
		sprintf(tmp,"%04d%02d%02d-%02d%02d%02d-%03d",in.year,in.month,in.day,
			in.hour,in.minute,in.second,in.millisecond);
		return tmp;
	}
	inline XSystemTime string2sysTime(const std::string &str)
	{
		XSystemTime in;
		sscanf(str.c_str(),"%04d%02d%02d-%02d%02d%02d-%03d",&in.year,&in.month,&in.day,
			&in.hour,&in.minute,&in.second,&in.millisecond);
		return in;
	}
}
}
#endif