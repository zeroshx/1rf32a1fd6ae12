#include "TextureLoadingManager.h"

TextureLoadingManager::TextureLoadingManager()
{
	_textureCount = 0;
	_textureList.clear();
}
TextureLoadingManager::~TextureLoadingManager()
{
}
TextureLoadingManager* TextureLoadingManager::getInstance()
{
	static TextureLoadingManager ins;
	return &ins;
}
void TextureLoadingManager::init()
{
	_isRunning = false;
	_textureCount = 0;
	_textureList.clear();
	_delegate = nullptr;
}
void TextureLoadingManager::setDelegate(TextureLoadingDelegate* pDelegate)
{
	_delegate = pDelegate;
}
void TextureLoadingManager::addTexture(const std::string& textureName, const std::string& plistName)
{
	_textureList.insert(make_pair(textureName, plistName));
}
void TextureLoadingManager::begin()
{		
	auto tc = _textureCache;

	_isRunning = true;

	_textureCount = _textureList.size();

	_delegate->onTextureLoadingBegan(this);

	for (auto& iter : _textureList){
		
		tc->addImageAsync(iter.first, CC_CALLBACK_1(TextureLoadingManager::TextureLoadingCallback, this, iter.second));		
	}	
}
void TextureLoadingManager::TextureLoadingCallback(Texture2D *texture, const std::string& plistName)
{	
	if (plistName != "None"){
		auto sfc = SpriteFrameCache::getInstance();
		sfc->addSpriteFramesWithFile(plistName, texture);
	}

	_textureCount--;
	_delegate->onTextureLoaded(this);

	if (_textureCount == 0){
		_delegate->onTextureLoadingEnded(this);
		_isRunning = false;
	}
}