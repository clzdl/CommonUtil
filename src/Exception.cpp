#include <typeinfo>
#include <stdio.h>
#include "Exception.h"

namespace CommonUtils{



std::ostream & operator << (std::ostream &out, const std::exception &e) {
    out << typeid(e).name() << ": " << e.what();
    return out;
}



const char* Grade::toString(Grade::Type grade) {
	if(grade == Grade::WARNING)
		return "WARNING";
	else if(grade == Grade::MINOR)
		return "MINOR";
	else if(grade == Grade::MAJOR)
		return "MAJOR";
	else if(grade == Grade::CRITICAL)
		return "CRITICAL";
	else 
		return "INDETERMINATE";	
}

std::ostream & operator << (std::ostream & out, const Exception & e) {
    out << "[" << Grade::toString(e.getGrade()) << "] " ;
    out << "[" << e.getFile() << ":" << e.getLine() << "] ";
    out << typeid(e).name() << "-" <<e.getCode() << ": " << e.what()<<std::endl;
    
    if (e.getCause() != 0) {
        out << "Caused by: ";
        const Exception * cause = dynamic_cast < const Exception * > (e.getCause());
        if (cause != 0) {  ///运行时类型转换成功
            out << *cause;
        } 
        else 
        {
            const __std_exception_wrapper *cause1 = dynamic_cast < const __std_exception_wrapper * > (e.getCause());
            if (cause1 != 0) {
                out << *cause1;
            } else {
                out << *e.getCause();
            }
        }
    }
    return out;
}




Exception::Exception(const Exception & e)
:m_file(e.m_file),
 m_line(e.m_line),
 m_grade(e.m_grade),
 m_code(e.m_code),
 m_message(e.m_message),
 m_cause(e.m_cause)
{
}

Exception::Exception(int code, const std::string &msg)
:m_line(-1),
 m_grade(Grade::INDETERMINATE),
 m_code(code),
 m_message(msg)
{
}
    
Exception::Exception(int code, const char *msg, ...)
:m_line(-1),
 m_grade(Grade::INDETERMINATE),
 m_code(code)
{
    ASSIGN_VMESSAGE(Exception::m_message, msg);
}  

Exception::Exception(const std::string &file, int line, Grade::Type grade, int code, const std::string &msg)
:m_file(file),
 m_line(line),
 m_grade(grade),
 m_code(code),
 m_message(msg)
{
}

Exception::Exception(const std::string &file, int line, Grade::Type grade, int code, const char *msg, ...)
:m_file(file),
 m_line(line),
 m_grade(grade),
 m_code(code)
{
    ASSIGN_VMESSAGE(Exception::m_message, msg);    
}


template < typename ECAUSE >
Exception::Exception(const std::string &file, int line, const ECAUSE &cause, Grade::Type grade, int code, const std::string & msg)
:m_file(file),
 m_line(line),
 m_grade(grade),
 m_code(code),
 m_message(msg)
{
    ASSIGN_CAUSE(Exception::m_cause, cause);
}

template < typename ECAUSE >
Exception::Exception(const std::string &file, int line, const ECAUSE &cause, Grade::Type grade, int code, const char*  msg, ...)
:m_file(file),
 m_line(line),
 m_grade(grade),
 m_code(code)
{
    ASSIGN_CAUSE(Exception::m_cause, cause);
    ASSIGN_VMESSAGE(Exception::m_message, msg);
}

/** 析构函数 */
Exception::~Exception() throw() {
}

/** 标准C++异常信息 */
const char * Exception::what() const throw() {
    return m_message.c_str();
}

/** 异常代码 */
Grade::Type Exception::getGrade() const throw() {
    return m_grade;
}

/** 异常代码 */
int Exception::getCode() const throw() {
    return m_code;
}

/** 异常信息 */
const std::string& Exception::getMessage() const throw() {
    return m_message;
}

/** 文件名 */
const std::string& Exception::getFile() const throw() {
    return m_file;
}

/** 行号 */
int Exception::getLine() const throw() {
    return m_line;
}

/** 根原因, 如果没有根原因, 则返回 NULL */
const std::exception* Exception::getCause() const throw() {
    return m_cause.get();
}

/** 克隆当前异常对象 */
Exception * Exception::clone() const throw() {
    return new Exception(* this);
}

std::string Exception::toString() const {
    std::ostringstream buffer;
    buffer << *this;
    return buffer.str();
}

}

