//========================================================================
// GLFW 3.1 screen - www.glfw.org
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
#include <string.h>
#include <errno.h>


//////////////////////////////////////////////////////////////////////////
//////                       GLFW internal API                      //////
//////////////////////////////////////////////////////////////////////////

void _glfwInitEventQueue(EventQueue* queue)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwDeleteEventQueue(EventQueue* queue)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

//////////////////////////////////////////////////////////////////////////
//////                       GLFW platform API                      //////
//////////////////////////////////////////////////////////////////////////

int _glfwPlatformCreateWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig,
                              const _GLFWctxconfig* ctxconfig,
                              const _GLFWfbconfig* fbconfig)
{
    int rc;
    int nbuffers = fbconfig->doublebuffer ? 2 : 1;
    int format = SCREEN_FORMAT_RGBX8888; // TODO: check fbconfig
    int usage = SCREEN_USAGE_OPENGL_ES2|SCREEN_USAGE_OVERLAY; // TODO: check context config
    int size[2] = { wndconfig->width, wndconfig->height };
    int pos[2] = { 0, 0 };
    int interval = 1;

    if (!_glfwCreateContext(window, ctxconfig, fbconfig))
        return GL_FALSE;

    rc = screen_create_window(&window->screen.window, _glfw.screen.context);
    if (rc)
    {
    	_glfwInputError(GLFW_PLATFORM_ERROR,
    	                    "screen: Error creating window %s", strerror(errno));
    	return GL_FALSE;
    }

    if (wndconfig->monitor)
    {
    	rc = screen_set_window_property_pv(window->screen.window, SCREEN_PROPERTY_DISPLAY, (void**)&wndconfig->monitor->screen.display);
    	if (rc)
    	{
    		_glfwInputError(GLFW_PLATFORM_ERROR,
    	                    "screen: Error set window property %s", strerror(errno));
    		return GL_FALSE;
    	}
    }

    rc = screen_set_window_property_iv(window->screen.window, SCREEN_PROPERTY_FORMAT, &format);
    if (rc) { _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to set format property: %s", strerror(errno)); return GL_FALSE; }
    rc = screen_set_window_property_iv(window->screen.window, SCREEN_PROPERTY_USAGE, &usage);
    if (rc) { _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to set usage property: %s", strerror(errno)); return GL_FALSE; }
    rc = screen_set_window_property_iv(window->screen.window, SCREEN_PROPERTY_SWAP_INTERVAL, &interval);
    if (rc) { _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to set swap interval property: %s", strerror(errno)); return GL_FALSE; }
    rc = screen_set_window_property_iv(window->screen.window, SCREEN_PROPERTY_SIZE, size);
    if (rc) { _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to set size property: %s", strerror(errno)); return GL_FALSE; }
    rc = screen_set_window_property_iv(window->screen.window, SCREEN_PROPERTY_POSITION, pos);
    if (rc) { _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to set position property: %s", strerror(errno)); return GL_FALSE; }
    rc = screen_create_window_buffers(window->screen.window, nbuffers);
    if (rc) { _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to create window buffers: %s", strerror(errno)); return GL_FALSE; }

    return GL_TRUE;
}

void _glfwPlatformDestroyWindow(_GLFWwindow* window)
{
    screen_destroy_window(window->screen.window);
    window->screen.window = NULL;
    _glfwDestroyContext(window);
}

void _glfwPlatformSetWindowTitle(_GLFWwindow* window, const char* title)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetWindowPos(_GLFWwindow* window, int xpos, int ypos)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformGetWindowFrameSize(_GLFWwindow* window,
                                     int* left, int* top,
                                     int* right, int* bottom)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformGetWindowPos(_GLFWwindow* window, int* xpos, int* ypos)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetWindowSize(_GLFWwindow* window, int width, int height)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformGetWindowSize(_GLFWwindow* window, int* width, int* height)
{
	int size[2] = {0};
	int rc = screen_get_window_property_iv(window->screen.window, SCREEN_PROPERTY_SIZE, size);
	if (rc) {
		_glfwInputError(GLFW_PLATFORM_ERROR,
		                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
	} else {
		if (width)
			*width  = size[0];
		if (height)
			*height = size[1];
	}
}

void _glfwPlatformIconifyWindow(_GLFWwindow* window)
{
	_glfwInputError(GLFW_PLATFORM_ERROR,
	                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformRestoreWindow(_GLFWwindow* window)
{
	_glfwInputError(GLFW_PLATFORM_ERROR,
	                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformHideWindow(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformShowWindow(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformUnhideWindow(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

int _glfwPlatformWindowFocused(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
    return GL_FALSE;
}

int _glfwPlatformWindowIconified(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
    return GL_FALSE;
}

int _glfwPlatformWindowVisible(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
    return GL_FALSE;
}

void _glfwPlatformPollEvents(void)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformWaitEvents(void)
{
    _glfwPlatformPollEvents();
}

void _glfwPlatformPostEmptyEvent(void)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformGetFramebufferSize(_GLFWwindow* window, int* width, int* height)
{
	int size[2] = {0};
	int rc = screen_get_window_property_iv(window->screen.window, SCREEN_PROPERTY_BUFFER_SIZE, size);
	if (rc) {
		_glfwInputError(GLFW_PLATFORM_ERROR,
		                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
	} else {
		if (width)
			*width  = size[0];
		if (height)
			*height = size[1];
	}
}

int _glfwPlatformCreateCursor(_GLFWcursor* cursor,
                              const GLFWimage* image,
                              int xhot, int yhot)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);

    return GL_FALSE;
}

int _glfwPlatformCreateStandardCursor(_GLFWcursor* cursor, int shape)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);

    return GL_FALSE;
}

void _glfwPlatformDestroyCursor(_GLFWcursor* cursor)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformGetCursorPos(_GLFWwindow* window, double* xpos, double* ypos)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetCursorPos(_GLFWwindow* window, double xpos, double ypos)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformApplyCursorMode(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetClipboardString(_GLFWwindow* window, const char* string)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

const char* _glfwPlatformGetClipboardString(_GLFWwindow* window)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);

    return NULL;
}

