/**
* corelib
*
* @category		Condition Lib
* @package	
* @author		Created by Lu Jianfeng ( lujf1978@163.com ), 2011
*/
#ifndef __IPROPERTYOPERATOR__H__
#define __IPROPERTYOPERATOR__H__

#include <ace/Assert.h>

enum PROPERTYOPERATOR_VALUETYPE
{
	PROPERTYOPER_VT_INT =0,
	PROPERTYOPER_VT_FLOAT,
	PROPERTYOPER_VT_STR,
};

class PropertyOperatorValue
{
public:
	PropertyOperatorValue():value_type_(PROPERTYOPER_VT_INT){
		value_.int_ =0;
	}

	void set_int( int v){
		value_.int_ =v;
		value_type_ =PROPERTYOPER_VT_INT;
	}
	int get_int(){
		ACE_ASSERT( value_type_ == PROPERTYOPER_VT_INT);
		return value_.int_;
	}

	void set_float( float v){
		value_.float_ =v;
		value_type_ =PROPERTYOPER_VT_FLOAT;
	}
	float get_float(){
		ACE_ASSERT( value_type_ == PROPERTYOPER_VT_FLOAT);
		return value_.float_;
	}

	void set_str( const char* v){
		str_ =v;
		value_type_ =PROPERTYOPER_VT_STR;
	}

	const NS_STL::string get_str(){
		ACE_ASSERT( value_type_ == PROPERTYOPER_VT_STR);
		return str_;
	}

	bool operator > ( const PropertyOperatorValue& v) const{
		ACE_ASSERT( !((value_type_ == PROPERTYOPER_VT_STR || v.value_type_ == PROPERTYOPER_VT_STR) && value_type_ != v.value_type_));
		switch( value_type_)
		{
		case PROPERTYOPER_VT_INT:
			return value_.int_ > (int)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_FLOAT:
			return value_.float_ > (float)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_STR:
			return str_ > v.str_;
		default:
			ACE_ASSERT( false && "PropertyOperatorValue not support value type");
			return false;
		}
	}

	bool operator >= ( const PropertyOperatorValue& v) const{
		ACE_ASSERT( !((value_type_ == PROPERTYOPER_VT_STR || v.value_type_ == PROPERTYOPER_VT_STR) && value_type_ != v.value_type_));
		switch( value_type_)
		{
		case PROPERTYOPER_VT_INT:
			return value_.int_ >= (int)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_FLOAT:
			return value_.float_ >= (float)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_STR:
			return str_ >= v.str_;
		default:
			ACE_ASSERT( false && "PropertyOperatorValue not support value type");
			return false;
		}
	}

	bool operator < ( const PropertyOperatorValue& v) const{
		ACE_ASSERT( !((value_type_ == PROPERTYOPER_VT_STR || v.value_type_ == PROPERTYOPER_VT_STR) && value_type_ != v.value_type_));
		switch( value_type_)
		{
		case PROPERTYOPER_VT_INT:
			return value_.int_ < (int)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_FLOAT:
			return value_.float_ < (float)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_STR:
			return str_ < v.str_;
		default:
			ACE_ASSERT( false && "PropertyOperatorValue not support value type");
			return false;
		}
	}

	bool operator <= ( const PropertyOperatorValue& v) const{
		ACE_ASSERT( !((value_type_ == PROPERTYOPER_VT_STR || v.value_type_ == PROPERTYOPER_VT_STR) && value_type_ != v.value_type_));
		switch( value_type_)
		{
		case PROPERTYOPER_VT_INT:
			return value_.int_ <= (int)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_FLOAT:
			return value_.float_ <= (float)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_STR:
			return str_ <= v.str_;
		default:
			ACE_ASSERT( false && "PropertyOperatorValue not support value type");
			return false;
		}
	}

	bool operator == ( const PropertyOperatorValue& v) const{
		ACE_ASSERT( !((value_type_ == PROPERTYOPER_VT_STR || v.value_type_ == PROPERTYOPER_VT_STR) && value_type_ != v.value_type_));
		switch( value_type_)
		{
		case PROPERTYOPER_VT_INT:
			return value_.int_ == (int)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_FLOAT:
			return value_.float_ == (float)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_STR:
			return str_ == v.str_;
		default:
			ACE_ASSERT( false && "PropertyOperatorValue not support value type");
			return false;
		}
	}

	bool operator != ( const PropertyOperatorValue& v) const{
		ACE_ASSERT( !((value_type_ == PROPERTYOPER_VT_STR || v.value_type_ == PROPERTYOPER_VT_STR) && value_type_ != v.value_type_));
		switch( value_type_)
		{
		case PROPERTYOPER_VT_INT:
			return value_.int_ != (int)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_FLOAT:
			return value_.float_ != (float)( v.value_type_ == PROPERTYOPER_VT_INT? v.value_.int_:v.value_.float_);
		case PROPERTYOPER_VT_STR:
			return str_ != v.str_;
		default:
			ACE_ASSERT( false && "PropertyOperatorValue not support value type");
			return false;
		}
	}

public:
	union
	{
		int		int_;
		float	float_;
	}value_;
	NS_STL::string	str_;

	PROPERTYOPERATOR_VALUETYPE	value_type_;
};

/**
* @class IPropertyOperator
* 
* @brief
**/
class IPropertyOperator
{
public:
	virtual PropertyOperatorValue get_property( const char* propname) =0;

};

#endif	//__IPROPERTYOPERATOR__H__
