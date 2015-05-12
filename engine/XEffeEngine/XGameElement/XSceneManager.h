#ifndef _JIA_XSCENEMANAGER_
#define _JIA_XSCENEMANAGER_

#include "XScene.h"
#include <map>
#include "../XSprite.h"
namespace XE{
enum XSceneChangeMode
{
	SCENE_MODE_NULL,
	SCENE_MODE_FADE_IN,
	SCENE_MODE_FADE_OUT,
	SCENE_MODE_BLACK,
	SCENE_MODE_WHITE,

};
class XSceneManager
{
protected:
	XSceneManager();
	XSceneManager(const XSceneManager&);
	XSceneManager &operator= (const XSceneManager&);
	virtual ~XSceneManager(){}
public:
	static XSceneManager& getInstance()
	{
		static XSceneManager m_instance;
		return m_instance;
	}
public:
	void update(float dt);
	void draw();

	bool addScene(XScene* newScene);
	bool goToScene(const std::string &name,XSceneChangeMode mode = SCENE_MODE_NULL,float time = 1.0f);
	bool isChanged()const{return !m_isChange;}

	void input(const XInputEvent &event);
	unsigned int getNumScenes()const{return m_scenes.size();}
	XScene * getCurrentScene(){return m_currentScene;}
	XScene * getScene(const std::string &name);
	std::string getCurrentSceneName()const;

private:
	std::map <std::string,XScene *> m_scenes;

	XScene* m_currentScene;
	XScene* m_futureScene;

	XSceneChangeMode m_changeMode;
	bool m_isChange;
	float m_timer;
	float m_changeSpeed;

	XFBO m_sceneFbo;
	XSprite m_sprite;
};
#if WITH_INLINE_FILE
#include "XSceneManager.inl"
#endif
#define XSManager XSceneManager::getInstance()
}
#endif