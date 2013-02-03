#pragma once
#include "DialogCls.h"

class DialogOwnerCls
{
public:
	DialogOwnerCls(const char *aDeckName);
	void BeginDialog();
	virtual void AddToInventory();
	virtual ~DialogOwnerCls(void);
private:
	DialogCls mDialog;
};

