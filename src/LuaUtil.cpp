/*
 * LuaUtil.cpp
 *
 *  Created on: 2017年11月29日
 *      Author: cplusplus
 */

#include "LuaUtil.h"
#include "string.h"

namespace CommonUtils
{

static LuaType Convert2LuaType(int type)
{
	switch(type)
	{
	case LUA_TNIL:
		return LuaType::_nil;
	case LUA_TNUMBER:
		return LuaType::_number;
	case LUA_TBOOLEAN:
		return LuaType::_boolean;
	case LUA_TSTRING:
		return LuaType::_string;
	case LUA_TTABLE:
		return LuaType::_table;
	case LUA_TFUNCTION:
		return LuaType::_function;
	case LUA_TUSERDATA:
		return LuaType::_userdata;
	case LUA_TTHREAD:
		return LuaType::_thread;
	case LUA_TLIGHTUSERDATA:
		THROW(LuaException,"wrong lua type");
	}

	return  LuaType::_nil;
}

LuaUtil::LuaUtil()
:m_luaState(nullptr)
{
	m_luaState = luaL_newstate();
}
LuaUtil::~LuaUtil()
{
	if(nullptr != m_luaState)
	{
		lua_close(m_luaState);
		m_luaState = nullptr;
	}
}

void LuaUtil::LoadLuaFile(std::string luaFile)
{

}

void LuaUtil::LoadLuaString(std::string luaString)
{

}

void LuaUtil::SetLuaEnvPath(std::string evnPath)
{

}

void LuaUtil::CallFunc(std::string funcName, const char* signString , ...)
{
	va_list vl;
	int iArgc = 0;
	va_start(vl , signString);
	///把函数地址压入栈中
	lua_getglobal(m_luaState , funcName.c_str());
	///压入参数
	const char *p = signString;
	while(*p)
	{
		switch(*p++)
		{
			case 'd':
				lua_pushnumber(m_luaState , va_arg(vl , double));
				break;
			case 'i':
				lua_pushnumber(m_luaState , va_arg(vl , int));
				break;
			case 's':
				lua_pushstring(m_luaState , va_arg(vl , char*));
				break;
			case '>':
				goto ENDWHILE;
			default:
			{
				THROW(LuaException , "调用函数参数类型不支持");
			}
		}
		++iArgc;
		luaL_checkstack(m_luaState , 1  , "too many argment.\n");
	}
ENDWHILE:
	int retCnt = strlen(p);
	int tmpCnt = retCnt;
	///do the call  ;  remove the function and argement
	if(0 != lua_pcall(m_luaState , iArgc , retCnt , 0))
	{
		THROW(LuaException , "call function:" + funcName + lua_tostring(m_luaState , -1));
	}

	retCnt = -1*retCnt;
	while(*p)
	{
		switch(*p++)
		{
			case 'd':
				if(lua_isnumber(m_luaState , retCnt))
				{
					THROW(LuaException , "wrong result type");
				}
				*va_arg(vl , double*) = lua_tonumber(m_luaState , retCnt);
				break;
			case 'i':
				if(lua_isnumber(m_luaState , retCnt))
				{
					THROW(LuaException , "wrong result type");
				}
				*va_arg(vl , int*) = lua_tonumber(m_luaState , retCnt);
				break;
			case 's':
				if(lua_isstring(m_luaState, retCnt))
				{
					THROW(LuaException , "wrong result type");
				}
				strcpy( *va_arg(vl , char**) , lua_tostring(m_luaState , retCnt) );
				break;
			default:
				THROW(LuaException , "wrong result type");

		}
		++retCnt;
	}

	if(tmpCnt > 0)
	{
		////结果取完后，把所有结果弹出栈
		lua_pop(m_luaState , tmpCnt);
	}

}

LuaUtil& LuaUtil::NewTable()
{
	lua_newtable(m_luaState);
	return *this;
}

LuaUtil& LuaUtil::Insert2Tab(int key , std::string value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushnumber(m_luaState, key);
	lua_pushstring(m_luaState , value.c_str());
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(int key , int value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushnumber(m_luaState, key);
	lua_pushnumber(m_luaState , value);
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(int key , long value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushnumber(m_luaState, key);
	lua_pushnumber(m_luaState , value);
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(int key , double value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushnumber(m_luaState, key);
	lua_pushnumber(m_luaState , value);
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(int key , void* value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushnumber(m_luaState, key);
	lua_pushlightuserdata(m_luaState , value);
	lua_settable(m_luaState, -3);  //table　index
	return *this;
}

LuaUtil& LuaUtil::Insert2Tab(std::string key , std::string value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushstring(m_luaState, key.c_str());
	lua_pushstring(m_luaState , value.c_str());
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(std::string key , int value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushstring(m_luaState, key.c_str());
	lua_pushnumber(m_luaState , value);
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(std::string key , long value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushstring(m_luaState, key.c_str());
	lua_pushnumber(m_luaState, value);
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}
LuaUtil& LuaUtil::Insert2Tab(std::string key , double value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushstring(m_luaState, key.c_str());
	lua_pushnumber(m_luaState , value);
	lua_settable(m_luaState , -3);  //table　index
	return *this;
}

LuaUtil& LuaUtil::Insert2Tab(std::string key , void* value)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}
	lua_pushstring(m_luaState, key.c_str());
	lua_pushlightuserdata(m_luaState , value);
	lua_settable(m_luaState, -3);  //table　index
	return *this;
}

std::string LuaUtil::GetTableData4String(int key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushnumber(m_luaState, key);
	lua_gettable(m_luaState, -2); /* get tab[key] */

	std::string result(lua_tostring(m_luaState, -1));
	Pop(1); /* remove result  from stack*/

	return result;
}
int LuaUtil::GetTableData4Int(int key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushnumber(m_luaState, key);
	lua_gettable(m_luaState, -2); /* get tab[key] */

	int result = lua_tointeger(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}
long LuaUtil::GetTableData4Long(int key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushnumber(m_luaState, key);
	lua_gettable(m_luaState, -2); /* get tab[key] */

	long result = lua_tointeger(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}
double LuaUtil::GetTableData4Double(int key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushnumber(m_luaState, key);
	lua_gettable(m_luaState, -2); /* get tab[key] */

	long result = lua_tonumber(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}
void* LuaUtil::GetTableData4Ptr(int key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushnumber(m_luaState, key);
	lua_gettable(m_luaState, -2); /* get tab[key] */

	void *result = lua_touserdata(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}

std::string LuaUtil::GetTableData4String(std::string key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushstring(m_luaState, key.c_str());
	lua_gettable(m_luaState, -2); /* get tab[key] */

	std::string result(lua_tostring(m_luaState, -1));
	Pop(1); /* remove result  from stack*/

	return result;
}
int LuaUtil::GetTableData4Int(std::string key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushstring(m_luaState, key.c_str());
	lua_gettable(m_luaState, -2); /* get tab[key] */

	int result = lua_tointeger(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}
long LuaUtil::GetTableData4Long(std::string key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushstring(m_luaState, key.c_str());
	lua_gettable(m_luaState, -2); /* get tab[key] */

	long result = lua_tointeger(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}
double LuaUtil::GetTableData4Double(std::string key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushstring(m_luaState, key.c_str());
	lua_gettable(m_luaState, -2); /* get tab[key] */

	double result = lua_tonumber(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}
void* LuaUtil::GetTableData4Ptr(std::string key)
{
	if(IsTable(-1))
	{
		THROW(LuaException , "stack top is not table.");
	}

	lua_pushstring(m_luaState, key.c_str());
	lua_gettable(m_luaState, -2); /* get tab[key] */

	void* result = lua_touserdata(m_luaState, -1);
	Pop(1); /* remove result  from stack*/

	return result;
}




void LuaUtil::SetGlobalVar(std::string globalName)
{
	lua_setglobal(m_luaState , globalName.c_str());
}
LuaType LuaUtil::GetGlobalVar(std::string globalName)
{
	return Convert2LuaType(lua_getglobal(m_luaState ,globalName.c_str()));
}

void LuaUtil::Pop(int count)
{
	lua_pop(m_luaState,count);
}


bool LuaUtil::IsBoolean(int index)
{
	return 1 == lua_isboolean(m_luaState,index)?true : false;
}

bool LuaUtil::IsFunction(int index)
{
	return 1 == lua_isfunction(m_luaState,index)?true : false;
}

bool LuaUtil::IsInteger(int index)
{
	return 1 == lua_isinteger(m_luaState,index)?true : false;
}

bool LuaUtil::IsLightUserData(int index)
{
	return 1 == lua_islightuserdata(m_luaState,index)?true : false;
}

bool LuaUtil::IsNil(int index)
{
	return 1 == lua_isnil(m_luaState,index)?true : false;
}

bool LuaUtil::IsNone(int index)
{
	return 1 == lua_isnone(m_luaState,index)?true : false;
}

bool LuaUtil::IsNumber(int index)
{
	return 1 == lua_isnumber(m_luaState,index)?true : false;
}

bool LuaUtil::IsString(int index)
{
	return 1 == lua_isstring(m_luaState,index)?true : false;
}

bool LuaUtil::IsTable(int index)
{
	return 1 == lua_istable(m_luaState,index)?true : false;
}

bool LuaUtil::IsThread(int index)
{
	return 1 == lua_isthread(m_luaState,index)?true : false;
}


bool LuaUtil::IsUserData(int index)
{
	return 1 == lua_isuserdata(m_luaState,index)?true : false;
}

int LuaUtil::Length(int index)
{
	lua_len(m_luaState,index);
	int len = lua_tointeger(m_luaState,-1);
	Pop(1);
	return len;
}

}


