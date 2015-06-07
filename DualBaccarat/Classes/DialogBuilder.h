#ifndef __DIALOG_BUILDER_H__
#define __DIALOG_BUILDER_H__

#include "Dialog.h"

class DialogBuilder
{
public:	

	static const int BUILD_TYPE_LOGIN_FAILURE = 0;
	static const int BUILD_TYPE_DATA_FETCH_FAILURE = 1;
	static const int BUILD_TYPE_UNLINK_FAILURE = 2;
	static const int BUILD_TYPE_INTERNAL_ERROR = 3;

	DialogBuilder();
	~DialogBuilder();

	Dialog* build(int type);

private:

	
};

#endif // __DIALOG_BUILDER_H__