#include "pch.h"
#include "UserManager.h"
#include "AccountManager.h"

void UserManager::ProcessSave()
{
	// account lock
	Account* account = AccountManager::Instance()->GetAccount(100);


	// user lock
	lock_guard<mutex> guard(_mutex);

	
	// todo


}
