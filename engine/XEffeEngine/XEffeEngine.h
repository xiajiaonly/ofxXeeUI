#ifndef _JIA_XEFFEENGINE_
#define _JIA_XEFFEENGINE_

#include <stdio.h>
#include <stdlib.h>

#include "XBasicOpenGL.h"

#include "XSprite.h"
#include "XMaskTex.h"
#include "XFrame.h"
#include "XFont/XFont.h"
#include "XFont/XFontUnicode.h"
#include "XBasicWindow.h"
#include "XOSDefine.h"

#include "XFont/XNumber.h"
#include "XFont/XNumberEx.h"
#include "XMedia/XSound.h"
#include "XMedia/XMusic.h"
#include "XNodeLine.h"
#include "XMath/XBezierSpline.h"
#include "XMath/XBezierInterpolation.h"
#include "XLogBook.h"
#include "XString.h"
#include "XParticle/XParticles.h"
#include "XControl/XControls.h"
#include "XPhysics/XPhysicsBasic.h"
#include "XGameElement/XGameElement.h"
#include "XXml.h"
#include "XCommonDefine.h"
#include "XConfigManager.h"
#include "XTimer.h"
#include "XErrorReporter.h"
#include "XThread.h"
#include "XPixelCommon.h"
#include "XInputEventCommon.h"
#include "XWindowCommon.h"
#include "XMath/XPressDataMode.h"

#include "XMedia/XMovieFfmpeg.h"
#include "XMedia/XFfmpegEx.h"

#include "XBmp.h"
#include "XDataBasic.h"
#include "XWindowTitle.h"

#include "XTextureInformation.h"
#include "XFrameEx.h"
#include "XMath/X2DPacker.h"
#include "XResourcePack.h"

#include "XGameBasic.h"
#include "XException.h"
#include "XErrorReporter.h"
#ifdef _DEBUG
#pragma comment(lib, "../../engine/bin/XEffectEngineD.lib")
#else
#pragma comment(lib, "../../engine/bin/XEffectEngine.lib")
#endif

#if WITH_OBJECT_MANAGER
#include "XObjectManager.h"
#endif
#include "XControl/XControlManager.h"

#include "XFrameWork.h"
#endif
