/*
 * LuaUtil.h
 *
 *  Created on: 2017年11月29日
 *      Author: cplusplus
 */

#ifndef INCLUDE_LUAUTIL_H_
#define INCLUDE_LUAUTIL_H_

#include <string>
#include <map>
#include "TplUtil.h"
#include "Exception.h"
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}



namespace CommonUtils
{

DECLARE_EXCEPTION(LuaException, Exception);

enum class LuaType
{
	_nil,
	_boolean,
	_number,
	_string,
	_function,
	_userdata,
	_thread,
	_table
};

class LuaUtil
{
public:
	LuaUtil();
	~LuaUtil();
	static std::unique_ptr<LuaUtil> newInstance();
	/**
	 * 加载ｌｕａ文件
	 */
	void LoadLuaFile(std::string luaFile);
	/**
	 * 加载ｌｕａ串
	 */
	void LoadLuaString(std::string luaString);

	/**
	 * 设置ｌｕａ环境路径
	 */
	void SetLuaEnvPath(std::string evnPath);

	/*调用lua函数
	 *param:
	 *      strFunc--入参， 调用的函数名
	 *      strSign--入参， 入参>出参；  如：  ddssii>ssdd  ；  ‘>' 用于分隔入参出参
	 */
	void CallFunc(std::string funcName, const char* signString, ...);

	/**
	 *
	 */
	void CallFunc(std::string funcName, const std::map<std::string,std::string>& tabIn , std::map<std::string,std::string> &tabOut);

	/**
	 * 创建ｌｕａｔａｂｌｅ
	 */
	LuaUtil& NewTable();

	/**
	 * 插入数据到ｔａｂｌｅ
	 */
	LuaUtil& Insert2Tab(int key , std::string value);
	LuaUtil& Insert2Tab(int key , int value);
	LuaUtil& Insert2Tab(int key , long value);
	LuaUtil& Insert2Tab(int key , double value);
	LuaUtil& Insert2Tab(int key , void* value);
	LuaUtil& Insert2Tab(std::string key , std::string value);
	LuaUtil& Insert2Tab(std::string key , int value);
	LuaUtil& Insert2Tab(std::string key , long value);
	LuaUtil& Insert2Tab(std::string key , double value);
	LuaUtil& Insert2Tab(std::string key , void* value);

	/**
	 * 获取ｔａｂｌｅ内元素
	 */
	std::string GetTableData4String(int key);
	int GetTableData4Int(int key);
	long GetTableData4Long(int key);
	double GetTableData4Double(int key);
	void* GetTableData4Ptr(int key);

	std::string GetTableData4String(std::string key);
	int GetTableData4Int(std::string key);
	long GetTableData4Long(std::string key);
	double GetTableData4Double(std::string key);
	void* GetTableData4Ptr(std::string key);

	/**
	 * 弹出栈顶元素同时把值设置为指定变量的值
	 */
	void SetGlobalVar(std::string globalName);

	/**
	 * 把全局变量放入栈顶，同时返回变量类型
	 */
	LuaType GetGlobalVar(std::string globalName);

	/**
	 * 弹出指定数量的元素
	 */
	void Pop(int count);

	/**
	 * 栈指定位置是否为Boolean类型
	 */
	bool IsBoolean(int index);

	/**
	 * 栈指定位置是否为Function类型
	 */
	bool IsFunction(int index);

	/**
	 * 栈指定位置是否为Integer类型
	 */
	bool IsInteger(int index);

	/**
	 * 栈指定位置是否为LightUserData类型
	 */
	bool IsLightUserData(int index);

	/**
	 * 栈指定位置是否为Nil类型
	 */
	bool IsNil(int index);

	/**
	 * 栈指定位置是否无效
	 */
	bool IsNone(int index);

	/**
	 * 栈指定位置是否为数字或可以转换为数字的字符串
	 */
	bool IsNumber(int index);

	/**
	 * 栈指定位置是否String
	 */
	bool IsString(int index);

	/**
	 * 栈指定位置是否Table
	 */
	bool IsTable(int index);

	/**
	 * 栈指定位置是否Thread
	 */
	bool IsThread(int index);


	/**
	 * 栈指定位置是否UserData
	 */
	bool IsUserData(int index);

	/**
	 * 指定元素的长度
	 */
	int Length(int index);

	/**
	 * 遍历ｔａｂｌｅ元素
	 */
	void TraverseTable(std::map<std::string,std::string > &result);
private:
	LuaUtil(const LuaUtil &lu) = delete;
	LuaUtil& operator = (const LuaUtil &lu ) = delete;

	lua_State* m_luaState;
};


}



#endif /* INCLUDE_LUAUTIL_H_ */
