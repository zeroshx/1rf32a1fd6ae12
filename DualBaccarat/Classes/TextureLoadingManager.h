#ifndef __LOADING_MANAGER_H__
#define __LOADING_MANAGER_H__

#include "cocos2d.h"
#include "PublicApi.h"
#include "TextureLoadingDelegate.h"

USING_NS_CC;

class TextureLoadingManager
{
public:
	
	TextureLoadingManager();
	~TextureLoadingManager();

	static TextureLoadingManager* getInstance();

	void setDelegate(TextureLoadingDelegate* pDelegate);
	void init();
	void begin();
	void addTexture(const std::string& textureName, const std::string& plistName = "None");	
	void TextureLoadingCallback(Texture2D *texture, const std::string& plistName);
	
private:

	bool _isRunning;
	int _textureCount;
	std::map<std::string, std::string> _textureList;
	TextureLoadingDelegate* _delegate;

};

#endif // __LOADING_MANAGER_H__
