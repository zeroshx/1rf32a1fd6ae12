#ifndef __DIALOG_DELEGATE_H__
#define __DIALOG_DELEGATE_H__

class Dialog;

class DialogDelegate
{
public:

	virtual void onClickPositiveButton(Dialog* pDialog, int index) = 0;
	virtual void onClickNegativeButton(Dialog* pDialog, int index) = 0;
};

#endif // __DIALOG_DELEGATE_H__