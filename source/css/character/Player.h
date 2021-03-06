﻿/**
* css application
*
* @category		player
* @package		
* @author		Created by Lu Jianfeng ( lujf1978@163.com ), 2009
*/
#ifndef __PLAYER__H__
#define __PLAYER__H__

#if !defined (ACE_LACKS_PRAGMA_ONCE) 
#pragma once
#endif

#include "../css_pre.h"

#include <ace/Thread_Mutex.h>
#include <prolib/BasicProtocol.h>
#include <boost/pool/object_pool.hpp>

#include "UnitBase.h"
#include "PlayerData.h"
#include "PlayerActionSelector.h"
#include "UnitEventListener.h"
#include <corelib/condition/IPropertyOperator.h>

class GTSLink;

/**
* @class Player
* 
* @brief 玩家信息
**/
class Player : public UnitBase, public PlayerData, public UnitEventListener, public IPropertyOperator
{
	typedef UnitBase inherit;
public:
	Player();
	virtual ~Player();

	//---------------------------------UnitBase virtual function---------------------------//
	virtual void tick( const ACE_UINT64& tnow);

	/**
	* @see UnitBase::reset()
	**/
	virtual void reset();

	/**
	* @see UnitBase::get_id()
	**/
	virtual int get_id();

	virtual ACTOR_TYPE_ENUM get_actortype(){ return ACTOR_TYPE_PLAYER;}

	bool is_unused(){ return status_ == PLAYERSTATUS_NONE;}

	inline virtual void set_position( float x, float y, float z);
	inline virtual void set_position( coordinate_pointer& p);
	inline virtual void set_positionx( float v);
	inline virtual void set_positiony( float v);
	inline virtual void set_positionz( float v);
	inline virtual coordinate_pointer get_position();
	inline virtual float get_positionx();
	inline virtual float get_positiony();
	inline virtual float get_positionz();
	inline virtual void set_facing( float v);
	inline virtual float get_facing();

	inline bool is_needupdatepos( const ACE_UINT64& tnow);

	/**
	* @see UnitBase::moveto( coordinate_pointer& pos, S_FLOAT_32& face)
	**/
	virtual void moveto( coordinate_pointer& pos, float& face);

	/**
	* 属性加载完成
	* @return
	**/
	virtual bool is_initfinish(){ return status_ > PLAYERSTATUS_REGIST;}

	virtual bool can_beattacked( UnitBase* pattack);

	//-----------------------------------IPropertyOperator virtual function implementation-------------------------------
	virtual PropertyOperatorValue get_property( const char* propname);

public:
	/**
	* 战斗对象相关
	**/
	void set_fighttargetobj( UnitBase* obj);
	UnitBase* get_fighttargetobj(){ return this->fight_target_obj_;}

	virtual void event_unitentity_reset( UnitBase* pobj);

public:
	/**
	* 注册玩家
	* @param uid
	* @param stmp
	* @param chrid
	**/
	void regist( int uid, S_TIMESTAMP stmp, int chrid);
	void regist( int gid, int uid, S_TIMESTAMP stmp, int chrid);
	/**
	* 玩家数据初始化
	**/
	void props_load( PRO::Pro_ChrLoad_ack* ack);
	void regist_fin( PRO::Pro_ChrFin_NTF* fin);

	/**
	* 根据属性计算出完整的属性
	**/
	void calcuate_playerproperty();

	/**
	* 断线保持重发
	**/
	void lnkkeep_reload();

	/**
	* 发送到gts服务器
	* @param p
	**/
	void send_to_gts( BasicProtocol* p);

	/**
	* 脚本系统绑定
	**/
	static void script_regist( lua_State* l);

	/**
	* 构建一个玩家类
	**/
	static Player*	create_player();
	static void		destroy_player( Player* p);

public:
	//-----------------------------------skill对外接口封装函数------------------------------------
	/**
	* 学习一个技能
	* @param skid
	**/
	void skill_study( int skid);

	/**
	* 使用一个技能
	* #引起player状态变化的一个入口
	* @param skid		技能编号
	* @param targetid	目标id
	* @param st			玩家的当前状态
	**/
	void skill_used( int skid, S_INT_64 targetid, CHRSTATE_TYPE_ENUM st);

public:
	//---------------------------------其他函数---------------------------------------------------
	/**
	* 进入副本
	**/
	void begin_entertranscript();
	void end_entertranscript();

public:
	//player state machine
	PlayerActionSelector	action_selector_;

	//玩家状态
	PLAYERSTATUS_TYPE_ENUM	status_;
	//帐号id
	uuid_session	uuid_;
	//关联的gts链接
	GTSLink*		gts_link_;
	//是否正在进入副本
	bool			is_entertranscript_;
	//在副本中
	bool			is_in_inst;

	//上次更新坐标时间
	ACE_UINT64		t_lastupdate_;
	float			lastposx_, lastposy_, lastposz_, lastfacing_;

protected:
	//当前的攻击目标
	UnitBase*	fight_target_obj_;

public:
	//玩家全局索引，系统定义
	int									global_index_;

	//玩家分配pool
	static boost::object_pool<Player>	player_pools_;
	static ACE_Thread_Mutex				pool_mutex_;
};

#include "Player.inl"

#endif	//__PLAYER__H__
