// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "DxDefine.h"
#include <math.h>
#include <time.h>
#include <sstream>
#include <stdarg.h> 
#include <assert.h>
#include "SpriteBatch.h"
#include "SpriteFont.h"

#include "../Input/InputClass.h"
//#include "../Graphics/TextureClass.h"
#include "../Unit/Object.h"
#include "../Unit/ObjectPool.h"
#include "../Graphics/UI/UI.h"
#include "../Unit/Damage.h"

#include "../Graphics/Background.h"
#include "../Unit/Player/PlayerClass.h"

#include "../Unit/Enemy/EnemyClass.h"
#include "../Unit/Enemy/EnemyTailClass.h"
#include "../Unit/Enemy/EnemyObstacle.h"
#include "../Unit/Enemy/EnemyPoison.h"

#include "../Unit/Collision.h"
