#ifndef _JIA_XXML_
#define _JIA_XXML_

#include "tinyxml.h"
#include "XOSDefine.h"
#include "XStringFun.h"

namespace XE{
namespace XXml
{

	inline TiXmlNode * getXmlAsInt(TiXmlNode *node,const char * name,int &value)
	{
		if (node == NULL || name == NULL) return NULL;
		TiXmlNode *keyNode = node->FirstChildElement(name);
		if(keyNode == NULL ||
			keyNode->ToElement()->GetText() == NULL) return NULL;
		value = atoi(keyNode->ToElement()->GetText());
		return keyNode;
	}
	inline TiXmlNode * getNextXmlAsInt(TiXmlNode *node,const char * name,int &value)
	{
		if (node == NULL || name == NULL) return NULL;
		TiXmlNode *keyNode = node->NextSiblingElement(name);
		if(keyNode == NULL ||
			keyNode->ToElement()->GetText() == NULL) return NULL;
		value = atoi(keyNode->ToElement()->GetText());
		return keyNode;
	}
	inline TiXmlNode * getXmlAsFloat(TiXmlNode *node,const char * name,float &value)
	{
		if (node == NULL || name == NULL) return NULL;
		TiXmlNode *keyNode = node->FirstChildElement(name);
		if(keyNode == NULL ||
			keyNode->ToElement()->GetText() == NULL) return NULL;
		value = (float)atof(keyNode->ToElement()->GetText());
		return keyNode;
	}
	inline TiXmlNode * getNextXmlAsFloat(TiXmlNode *node,const char * name,float &value)
	{
		if (node == NULL || name == NULL) return NULL;
		TiXmlNode *keyNode = node->NextSiblingElement(name);
		if(keyNode == NULL ||
			keyNode->ToElement()->GetText() == NULL) return NULL;
		value = (float)atof(keyNode->ToElement()->GetText());
		return keyNode;
	}
	extern TiXmlNode * getXmlAsBool(TiXmlNode *node,const char * name,bool &value);
	extern TiXmlNode * getNextXmlAsBool(TiXmlNode *node,const char * name,bool &value);
	inline TiXmlNode * getXmlAsString(TiXmlNode *node,const char * name,std::string &value)
	{
		if (node == NULL || name == NULL) return NULL;
		TiXmlNode *keyNode = node->FirstChildElement(name);
		if(keyNode == NULL ||
			keyNode->ToElement()->GetText() == NULL)  return NULL;
#ifdef UNICODE
		value = XString::UTF82ANSI(keyNode->ToElement()->GetText());
#else
		value = keyNode->ToElement()->GetText();
#endif
		return keyNode;
	}
	inline TiXmlNode * getNextXmlAsString(TiXmlNode *node,const char * name,std::string &value)
	{
		if (node == NULL || name == NULL) return NULL;
		TiXmlNode *keyNode = node->NextSiblingElement(name);
		if(keyNode == NULL ||
			keyNode->ToElement()->GetText() == NULL)  return NULL;
#ifdef UNICODE
		value = XString::UTF82ANSI(keyNode->ToElement()->GetText());
#else
		value = keyNode->ToElement()->GetText();
#endif
		return keyNode;
	}
	inline XBool addLeafNode(TiXmlNode &pElmParent,const char* pszNode,const char* pszText)
	{
		if (pszText == NULL || pszNode == NULL) return XFalse;
		TiXmlElement elmNode(pszNode);
		TiXmlText elmText(pszText);
		return !(elmNode.InsertEndChild(elmText) == NULL ||
			pElmParent.InsertEndChild(elmNode) == NULL);

	}
	inline XBool addComment(TiXmlNode &pElmParent,const char* pszText)
	{
		if (pszText == NULL) return XFalse;
		TiXmlComment elmText(pszText);
		return !(pElmParent.InsertEndChild(elmText) == NULL);
	}
	inline XBool addLeafNode(TiXmlNode &pElmParent,const char* pszNode,const std::string &pszText)
	{
		if (pszNode == NULL) return XFalse;
		return addLeafNode(pElmParent,pszNode,pszText.c_str());
	}
	extern XBool addLeafNode(TiXmlNode &pElmParent,const char* pszNode,bool flag);
}
}
#endif