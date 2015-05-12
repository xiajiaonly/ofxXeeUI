#ifndef _JIA_XMEDIALIST_
#define _JIA_XMEDIALIST_

#include <vector>
namespace XE{

enum XMediaListPlayerMode
{
	PLAY_MODE_SERIAL,
	PLAY_MODE_RAND,
};

struct  XMediaListItem
{
	int m_headDelayTime;
	int m_loopTimes;
	int m_loopHeadDelayTime;
	std::string m_videoFilename;
	int m_loopEndDelayTime;
	int m_endDelayTime;
	bool m_stopAtEnd;
	XMediaListItem()
		:m_headDelayTime(0)
		,m_loopTimes(0)
		,m_loopHeadDelayTime(0)
		,m_videoFilename("")
		,m_loopEndDelayTime(0)
		,m_endDelayTime(0)
		,m_stopAtEnd(false)
	{}
};
#define DEFAULT_PLAY_LIST_FILENAME ("playList.xml")
class XMediaList
{
private:
	std::vector<XMediaListItem> m_playList;
	XMediaListPlayerMode m_playMode;
	int m_loopTimes;
public:
	bool loadFromFile(const char * filename = NULL);
	bool saveToFile(const char * filename = NULL);
	bool checkList(){return true;}
	void addAItem2List(const XMediaListItem & c){m_playList.push_back(c);}
	XMediaListPlayerMode getPlayMode()const{return m_playMode;}
	int getLoopTimes()const{return m_loopTimes;}
	unsigned int getItemSum(){return m_playList.size();}
	const XMediaListItem * getItem(int index)
	{
		if(index < 0 || index >= m_playList.size()) return NULL;
		return &m_playList[index];
	}

	XMediaList()
		:m_loopTimes(0)
		,m_playMode(PLAY_MODE_SERIAL)
	{}
};
}
#endif