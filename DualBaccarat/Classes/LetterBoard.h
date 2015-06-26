#ifndef __LETTER_BOARD_H__
#define __LETTER_BOARD_H__

#include "PublicApi.h"

#define LETTERBOARD_WIDTH		DESIGN_WIDTH
#define LETTERBOARD_HEIGHT		80
#define LETTER_SIZE				50
#define LETTER_SPEED			5				// the higher value, the slower speed will be.

USING_NS_CC;

class LetterBoard : public ClippingRectangleNode
{
public:

	LetterBoard();
	~LetterBoard();
	
	static LetterBoard* create();
	virtual bool init();
	void setSentence(const std::string& sentence);
	void run();
	void run(const std::string& sentence);
	void stop();
	void onMoveEnded();

private:

	MODULE_STATE _state;
	Label *_label;
	Sprite *_background;
};

#endif // __LETTER_BOARD_H__
