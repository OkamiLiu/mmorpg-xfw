﻿/**
* gts application
*
* @category		core
* @package		
* @author		Created by Lu Jianfeng ( lujf1978@163.com ), 2009
*/
#include <ace/OS_NS_stdio.h>

#include <corelib/log/logmacro.h>

#if defined (ACE_WIN32)

//exception
LONG WINAPI exception_filter( struct _EXCEPTION_POINTERS* ExceptionInfo)
{
	MODULE_LOG_ERROR( MODULE_SYSTEM, "exp code:%08X", ExceptionInfo->ExceptionRecord->ExceptionAddress);

	switch(ExceptionInfo->ExceptionRecord->ExceptionInformation[0])
	{
	case 0:
		MODULE_LOG_ERROR( MODULE_SYSTEM, "Read Error:%08X", ExceptionInfo->ExceptionRecord->ExceptionInformation[1]);
		break;
	case 1:
		MODULE_LOG_ERROR( MODULE_SYSTEM, "Write Error:%08X", ExceptionInfo->ExceptionRecord->ExceptionInformation[1]);
		break;
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

#endif	//ACE_WIN32

#include "GTSModule.h"

int ACE_TMAIN(int argc, ACE_TCHAR **argv) 
{
#if defined (ACE_WIN32)
	//挂接异常记录filter
	::SetUnhandledExceptionFilter( (LPTOP_LEVEL_EXCEPTION_FILTER)exception_filter);
#endif

	MODULE_LOG_INIT("gts.properties")

	MODULE_LOG_WARN( MODULE_BOOT, "========gts server starting-------------------------------------------");

	if( GTSMODULE->init( argc, argv) != 0)
		return 1;

	MODULE_LOG_WARN( MODULE_BOOT, "========gts server start end------------------------------------------");

	MODULE_LOG_WARN( MODULE_BOOT, "========gts server begin main loop------------------------------------");

	//进入主循环
	GTSMODULE->main_loop();

	//释放资源
	GTSMODULE->fini();

	MODULE_LOG_WARN( MODULE_BOOT, "========gts server end main loop-------------------------------------");

	MODULE_LOG_SHUTDOWN

#if defined (ACE_WIN32)
	::SetUnhandledExceptionFilter( NULL);
#endif
	return 0;
}

#include <corelib/script/ScriptContext.h>

namespace app { namespace script {

bool ScriptContext::regist_bindclass()
{
	return true;
}

}}
