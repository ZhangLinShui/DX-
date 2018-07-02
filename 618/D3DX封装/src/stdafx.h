// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include<windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO:  在此处引用程序需要的其他头文件

#include <stdio.h>

#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <fstream>
#include <timeapi.h>
using namespace std;

#include<math.h>
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"fmodex_vc.lib")
#include "Singleton.h"
#include "Platform.h"
//#include "ResManager.h"
#include"tinystr.h"
#include"tinyxml.h"
#include "EngineDef.h"