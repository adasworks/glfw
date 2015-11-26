//========================================================================
// GLFW 3.1 Screen - www.glfw.org
//------------------------------------------------------------------------
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#include "internal.h"

#include <stdlib.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////////
//////                       GLFW internal API                      //////
//////////////////////////////////////////////////////////////////////////

int _glfwPlatformInit(void)
{
    int error;

    error = screen_create_context(&_glfw.screen.context, SCREEN_APPLICATION_CONTEXT);
    if (error)
    {
    	_glfwInputError(GLFW_PLATFORM_ERROR,
    	                        "screen: Failed to create context: %s",
    	                        strerror(error));
    	return GL_FALSE;
    }
    if (!_glfwInitContextAPI())
        return GL_FALSE;

    _glfwInitTimer();
    _glfwInitJoysticks();

    _glfw.screen.event_queue = calloc(1, sizeof(EventQueue));
    _glfwInitEventQueue(_glfw.screen.event_queue);

    error = pthread_mutex_init(&_glfw.screen.event_mutex, NULL);
    if (error)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "screen: Failed to create event mutex: %s",
                        strerror(error));
        return GL_FALSE;
    }

    return GL_TRUE;
}

void _glfwPlatformTerminate(void)
{
    _glfwTerminateContextAPI();
    _glfwTerminateJoysticks();

    _glfwDeleteEventQueue(_glfw.screen.event_queue);

    pthread_mutex_destroy(&_glfw.screen.event_mutex);

    screen_destroy_context(_glfw.screen.context);
}

const char* _glfwPlatformGetVersionString(void)
{
    return _GLFW_VERSION_NUMBER " screen EGL"
#if defined(_POSIX_TIMERS) && defined(_POSIX_MONOTONIC_CLOCK)
        " clock_gettime"
#else
        " gettimeofday"
#endif
#if defined(__linux__)
        " /dev/js"
#endif
#if defined(_GLFW_BUILD_DLL)
        " shared"
#endif
        ;
}

