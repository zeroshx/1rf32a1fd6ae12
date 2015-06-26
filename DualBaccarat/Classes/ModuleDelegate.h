#ifndef __MODULE_DELEGATE_H__
#define __MODULE_DELEGATE_H__

class ModuleDelegate
{
public:

	virtual void onModuleInit() = 0;
	virtual void onModuleBegan() = 0;
	virtual void onModuleWorking() = 0;
	virtual void onModuleEnded() = 0;
};

#endif // __MODULE_DELEGATE_H__
