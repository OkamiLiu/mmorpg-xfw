/**
* css application
*
* @category		transcript service
* @package		
* @author		Created by Lu Jianfeng ( lujf1978@163.com ), 2011
*/
#ifndef __INSTCTRLBASE__H__
#define __INSTCTRLBASE__H__

#if !defined (ACE_LACKS_PRAGMA_ONCE) 
#pragma once
#endif

#include "../css_pre.h"

class InstanceStoryServiceImpl;

#define INSTCTRL_DEFINE( classname)															\
public:																						\
	static const char* get_classname(){														\
		static NS_STL::string s_##classname_name ="##classname";							\
		return s_##classname_name.c_str();													\
	}

#define INSTCTRL_REGIST_BEGIN()																\
	InstCtrlBase* InstCtrlBase::create( const char* cname, InstanceStoryServiceImpl* svr)	\
	{																

#define INSTCTRL_REGIST_IMPL( classname)													\
	if( cname != 0 && stricmp( classname::get_classname(), cname) == 0)						\
		return FRAMEWK_NEW classname( svr)

#define INSTCTRL_REGIST_IMPL_DEFAULT( classname)											\
	return FRAMEWK_NEW classname( svr)

#define INSTCTRL_REGIST_END()																\
	}

/**
* @class InstCtrlBase
* 
* @brief 副本状态控制基类
**/
class InstCtrlBase
{
public:
	/**
	* 根据名字构建控制类
	* @param classname	定义的名称和类名相同
	**/
	static InstCtrlBase* create( const char* classname, InstanceStoryServiceImpl* svr);

public:
	InstCtrlBase( InstanceStoryServiceImpl* iss);
	virtual ~InstCtrlBase();

	virtual void init_ctrl();
	bool	is_initialized(){ return is_initialized_;}

	virtual bool tick( const ACE_UINT64& now_t);

protected:
	InstanceStoryServiceImpl*	inst_service_;

private:
	//完成初始化
	bool	is_initialized_;
};

#endif	//__INSTCTRLBASE__H__
