#ifndef __LOADING_DELEGATE_H__
#define __LOADING_DELEGATE_H__

class TextureLoadingManager;

class TextureLoadingDelegate
{
public:
	virtual void onTextureLoadingBegan(TextureLoadingManager* tlm) = 0;
	virtual void onTextureLoaded(TextureLoadingManager* tlm) = 0;
	virtual void onTextureLoadingEnded(TextureLoadingManager* tlm) = 0;
};

#endif // __LOADING_DELEGATE_H__
