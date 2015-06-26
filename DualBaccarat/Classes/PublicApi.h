#ifndef __PUBLIC_API_H__
#define __PUBLIC_API_H__

#include "cocos2d.h"
#include "MessageGuide.h"

#define DESIGN_WIDTH	1920
#define DESIGN_HEIGHT	1080

#define _director		Director::getInstance()
#define _textureCache	_director->getTextureCache()
#define _visibleSize	_director->getVisibleSize()
#define _origin			_director->getVisibleOrigin()
#define _center			Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y)

#define _user			AppUser::getInstance()

#define _font			"NanumGothic_Coding.ttf"

#define ANIM_PREDEALING_TIME 1.5f
#define ANIM_POSTDEALING_TIME 1.0f
#define ANIM_DEALING_TIME	3.0f
#define ANIM_SHUFFLE_TIME	2.0f
#define ANIM_GAMEOVER_TIME	3.0f
//#define DEBUG

namespace BetType
{
	enum BET_TYPE
	{
		PLAYER = 0,
		PLAYER_PAIR,
		PLAYER_NATURAL,
		BANKER,
		BANKER_PAIR,
		BANKER_NATURAL,
		TIE,
		BIG,
		SMALL,
		NONE
	};
};
using BetType::BET_TYPE;

enum class WINNER
{
	NONE,
	PLAYER,
	BANKER,
	TIE
};

enum class EXTRA_WINNER
{
	PLAYER_NATURAL,
	BANKER_NATURAL,
	BIG,
	SMALL,
};

enum class PAIR
{
	NONE,
	PLAYER,
	BANKER,
	BOTH
};

enum class CONTINUATION
{
	NONE,
	KEEP,
	INVERSE
};

enum class REWARD_TYPE
{
	CHIP,
	RP,
	TICKET
};

enum class MISSION_STATE
{
	ONGOING,
	COMPLETE,
	REWARD
};

enum class TIER
{
	UNRANKER,
	BRONZE,
	SILVER,
	GOLD,
	PLATINUM,
	DIAMOND,
	MASTER,
	CHALLENGER
};

enum class MODULE_STATE
{
	IDLE,
	START,
	DONE
};

enum class GAME_STATE
{
	READY,
	SHUFFLE,
	BET,
	DEALING,
	GAMEOVER
};

enum class CARD_NAME
{
	NONE,
	_A_,
	_2_,
	_3_,
	_4_,
	_5_,
	_6_,
	_7_,
	_8_,
	_9_,
	_10_,
	_J_,
	_Q_,
	_K_
};
enum class CARD_SYMBOL
{
	NONE,
	SPADE,
	HEART,
	CLOVER,
	DIAMOND
};

namespace CardOwner
{
	enum CARD_OWNER
	{
		PLAYER1 = 0,
		BANKER1,
		PLAYER2,
		BANKER2,
		PLAYER3,
		BANKER3,
		NONE,
	};
};
using CardOwner::CARD_OWNER;

enum class RECORD_TYPE
{
	PROTOTYPE,
	BASE,
	DIVINATION1TH,
	DIVINATION2ND,
	DIVINATION3RD,
	NEXT_DIV1TH,
	NEXT_DIV2ND,
	NEXT_DIV3RD,
};

namespace DivDepth
{
	enum DIV_DEPTH
	{
		FIRST = 1,
		SECOND,
		THIRD
	};
}
using DivDepth::DIV_DEPTH;

namespace ScoreType
{
	enum SCORE_TYPE
	{
		BANKER = 0,
		PLAYER,
		TIE,
		BANKER_PAIR,
		PLAYER_PAIR,
		TOTAL
	};
}
using ScoreType::SCORE_TYPE;

#define COUNT_BET_TYPE 9
class BettingRecord
{
public:

	int _total;
	int _type[COUNT_BET_TYPE];

	void reset()
	{
		_total = 0;
		for (int i = 0; i < COUNT_BET_TYPE; i++)
		{
			_type[i] = 0;
		}
	}
};

static const std::string stringToMoney(const std::string& str)
{
	std::string src = str;
	std::string dest;
	int cnt = 0;

	while (src.length() > 0)
	{
		dest.insert(dest.begin(), src.back());
		src.pop_back();
		cnt++;
		if (cnt == 3 && src.length() > 0)
		{
			dest.insert(dest.begin(), ',');
			cnt = 0;
		}
	}

	return dest;
}

class PublicApi
{
public:   
	
};

#endif // __PUBLIC_API_H__