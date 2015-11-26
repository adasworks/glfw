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

#ifndef _glfw3_screen_platform_h_
#define _glfw3_screen_platform_h_

#include <sys/queue.h>
#include <pthread.h>

#include <screen/screen.h>

#include "posix_tls.h"
#include "posix_time.h"
#include "linux_joystick.h"
#include "xkb_unicode.h"

#if defined(_GLFW_EGL)
 #include "egl_context.h"
#else
 #error "The screen backend depends on EGL platform support"
#endif

#define _GLFW_EGL_NATIVE_WINDOW  window->screen.window
#define _GLFW_EGL_NATIVE_DISPLAY EGL_DEFAULT_DISPLAY

#define _GLFW_PLATFORM_WINDOW_STATE         _GLFWwindowScreen  screen
#define _GLFW_PLATFORM_MONITOR_STATE        _GLFWmonitorScreen screen
#define _GLFW_PLATFORM_LIBRARY_WINDOW_STATE _GLFWlibraryScreen screen
#define _GLFW_PLATFORM_CURSOR_STATE         _GLFWcursorScreen  screen


// screen-specific Event Queue
//
typedef struct EventQueue
{
    TAILQ_HEAD(, EventNode) head;
} EventQueue;

// screen-specific per-window data
//
typedef struct _GLFWwindowScreen
{
    screen_window_t window;
} _GLFWwindowScreen;


// screen-specific per-monitor data
//
typedef struct _GLFWmonitorScreen
{
	screen_display_t      display;
	screen_display_mode_t current_mode;
	int current_mode_index;
	int display_id;
	int size[2];
	int position[2];
} _GLFWmonitorScreen;


// screen-specific global data
//
typedef struct _GLFWlibraryScreen
{
    screen_context_t context;
    EventQueue* event_queue;

    pthread_mutex_t event_mutex;
    pthread_cond_t  event_cond;

} _GLFWlibraryScreen;


// screen-specific per-cursor data
// TODO: Only system cursors are implemented in screen atm. Need to wait for support.
//
typedef struct _GLFWcursorScreen
{
} _GLFWcursorScreen;


extern void _glfwInitEventQueue(EventQueue* queue);
extern void _glfwDeleteEventQueue(EventQueue* queue);

#endif // _glfw3_screen_platform_h_
