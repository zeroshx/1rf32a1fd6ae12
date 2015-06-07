#ifndef __PUBLIC_API_H__
#define __PUBLIC_API_H__

#define DESIGN_WIDTH	1920
#define DESIGN_HEIGHT	1080

#define _director		Director::getInstance()
#define _textureCache	_director->getTextureCache()
#define _visibleSize	_director->getVisibleSize()
#define _origin			_director->getVisibleOrigin()
#define _center			Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y)

#define _user			AppUser::getInstance()

#define _font			"NanumGothic_Coding.ttf"

#define ANIM_DEALING_TIME	2.0f
#define ANIM_SHUFFLE_TIME	2.0f
#define ANIM_GAMEOVER_TIME	2.0f
//#define DEBUG

enum class Winner
{
	NONE,
	PLAYER,
	BANKER,
	TIE
};

class PublicApi
{
public:   
	
};

#endif // __PUBLIC_API_H__