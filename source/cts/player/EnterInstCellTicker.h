/**
* cts application
*
* @category		transcript manage
* @package		
* @author		Created by Lu Jianfeng ( lujf1978@163.com ), 2011
*/
#ifndef __ENTERINSTCELLTICKER__H__
#define __ENTERINSTCELLTICKER__H__

#include "../cts_pre.h"
#include <reslib/server/service_define.h>
#include <ace/Basic_Types.h>
#include <prolib/Pro_all.h>

class Player;
class CSSLink;
class InstCellState;

/**
* @class EnterInstCellTicker
* 
* @brief 玩家进入副本的状态节点
* 
**/
class EnterInstCellTicker
{
public:
	enum ENTERINSTCELL_STEP{
		//不处于进入副本状态
		EINSTCELL_ST_NONE =0,
		//main map -> cts -> inst map ->cts(wait cell proxy)
		EINSTCELL_ST_WAITCELLPROXY,
		//gts ->inst map -> cts(wait cell confirm)
		EINSTCELL_ST_WAITCELLCONFIRM
	};

public:
	EnterInstCellTicker();

	void set_owner( Player* p);

	void tick( const ACE_UINT64& t);

	void reset();

	bool is_enterinstcell(){ return tick_state_ != EINSTCELL_ST_NONE;}

	void wait_cellproxy( PRO::Pro_AppEnterIns_req* req, InstCellState* pcell);
	void wait_cellconfirm();
	void finish_cellconfirm();

public:
	//记录的临时状态
	float			posx_, posy_, posz_;

	CSSLink*		css_svr_;
	InstCellState*	inst_cell_;

protected:
	//当前状态
	ENTERINSTCELL_STEP	tick_state_;
	//检测时间点
	ACE_UINT64			tick_time_;

	Player*				owner_;
};

#endif	//__ENTERINSTCELLTICKER__H__
