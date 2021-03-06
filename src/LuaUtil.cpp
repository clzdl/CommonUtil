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
std::unique_ptr<LuaUtil> LuaUtil::newInstance()
{
	return make_unique<LuaUtil>();
}
LuaUtil::LuaUtil()
:m_luaState(nullptr)
{
	m_luaState = luaL_newstate();
	luaL_openlibs(m_luaState);
}
LuaUtil::~LuaUtil()
{
	if(nullptr != m_luaState)
	{
		lua_close(m_luaState);
		m_luaState = nullptr;
	}
}


lua_State* LuaUtil::GetLuaState()
{
    return m_luaState;
}

void LuaUtil::LoadLuaFile(std::string luaFile)
{
	if(luaL_loadfile(m_luaState, luaFile.c_str()) ||  lua_pcall(m_luaState,0,0,0))
	{
		THROW_P1(LuaException,"LoadLuaFile error; %s" , lua_tostring(m_luaState , -1));
	}
}

void LuaUtil::LoadLuaString(std::string luaString)
{
	if(luaL_loadstring(m_luaState, luaString.c_str()) ||  lua_pcall(m_luaState,0,0,0))
	{
		THROW_P1(LuaException,"luaL_loadstring error; %s" , lua_tostring(m_luaState , -1));
	}
}

void LuaUtil::SetLuaEnvPath(std::string evnPath)
{
    lua_getglobal(m_luaState, "package" );
    lua_getfield(m_luaState, -1, "cpath" ); // get field "path" from table at top of stack (-1)
    std::string cur_path = lua_tostring(m_luaState, -1 ); // grab path string from top of stack
    cur_path.append( ";" ); // do your path magic here
    cur_path.append( evnPath );
    lua_pop(m_luaState, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring(m_luaState, cur_path.c_str() ); // push the new one
    lua_setfield(m_luaState, -2, "cpath" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop(m_luaState, 1 ); // get rid of package table from top of stack
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

void LuaUtil::CallFunc(std::string funcName, const std::map<std::string,std::string>& tabIn , std::map<std::string,std::string> &tabOut)
{
		////开始调用lua脚本的转换函数 ,  函数返回结果：  ret_code   ret_table
		GetGlobalVar(funcName.c_str()); ///把函数地址压入栈中
		///生成tab参数
		NewTable();
		for(auto it : tabIn )
			Insert2Tab(it.first, it.second);

		if(LUA_OK != lua_pcall(m_luaState , 1 , 1 , 0))
		{
			THROW_P2(LuaException , "lua_pcall call [%s] return error; %s ",funcName.c_str() ,lua_tostring(m_luaState , -1));
		}
		if(!IsTable(1))
		{
			Pop(lua_gettop(m_luaState));
			THROW(LuaException , "lua_pcall call return not a table");
		}

		TraverseTable(tabOut);
}

LuaUtil& LuaUtil::NewTable()
{
	lua_newtable(m_luaState);
	return *this;
}

void LuaUtil::TraverseTable(std::map<std::string,std::string > &result)
{
	/* table is in the stack at -2 */
	lua_pushnil(m_luaState);  /* first key */
	while (lua_next(m_luaState, -2) != 0)
	{
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		result.insert(std::pair<std::string,std::string>(lua_tostring(m_luaState,-2),lua_tostring(m_luaState,-1)));
		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(m_luaState, 1);
	}
}

LuaUtil& LuaUtil::Insert2Tab(int key , std::string value)
{
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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
	if(!IsTable(-1))
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

void LuaUtil::PushString(std::string value)
{
    lua_pushstring(m_luaState, value.c_str());
}
void LuaUtil::PCall(int inNum, int outNum)
{
    if(0 != lua_pcall(m_luaState, inNum, outNum, 0))
    {
        THROW_P1(LuaException , "error running funcion :%s", lua_tostring(m_luaState, -1));
    }
}

long LuaUtil::ToInteger(int pos)
{
    return lua_tointeger(m_luaState, pos);
}

std::string LuaUtil::ToString(int pos)
{
    const char *value = lua_tostring(m_luaState, pos);
    if(nullptr != value)
    {
        return value;
    }
    return "";
}

int LuaUtil::GetTop()
{
    return lua_gettop(m_luaState);
}

}


