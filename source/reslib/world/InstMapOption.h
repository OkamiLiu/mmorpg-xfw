/**
* reslib
*
* @category		副本配置
* @package		
* @author		Created by Lu Jianfeng ( lujf1978@163.com ), 2011
*/
#ifndef __INSTMAPOPTION__H__
#define __INSTMAPOPTION__H__

#include <corelib/corelibdef.h>
#include <string>

class TiXmlElement;

/**
* @class InstMapOption
* 
* @brief 副本地图相关配置
* 
**/
class InstMapOption
{
public:
	InstMapOption();

	/**
	* 加载和副本相关的配置选项
	* @param e
	**/
	S_BOOL	load_instmapopt( TiXmlElement* e);

public:
	//副本状态控制实现
	NS_STL::string ctrl_classname_;
};

#endif	//__INSTMAPOPTION__H__
