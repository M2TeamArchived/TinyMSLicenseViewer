// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
// 编译器优化可能出现的警告（去除未引用函数并适当对一些函数使用内联）
#pragma warning(disable:4505) // 未引用的本地函数已移除(等级 4)
#pragma warning(disable:4710) // 函数未内联(等级 4)
#endif

#ifndef _DEBUG
#include <_msvcrt.h>
#endif 

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

// 为编译通过而禁用的警告
#if _MSC_VER >= 1200
#pragma warning(push)
// 微软SDK存在的警告
#pragma warning(disable:4365) // 有符号/无符号不匹配(等级 4)
#pragma warning(disable:4820) // 字节填充添加在数据成员后(等级 4)
#pragma warning(disable:4986) // 异常规范与前面的声明不匹配(MSDN未标明警告级别，默认禁用该警告)
#endif

#include <comdef.h>

#if _MSC_VER >= 1200
#pragma warning(pop)
#endif

#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
