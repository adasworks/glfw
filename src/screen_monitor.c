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
#include <errno.h>

//////////////////////////////////////////////////////////////////////////
//////                       GLFW platform API                      //////
//////////////////////////////////////////////////////////////////////////

_GLFWmonitor** _glfwPlatformGetMonitors(int* count)
{
    int i, found = 0;
    _GLFWmonitor** monitors = NULL;
    *count = 0;

    int rc = 0;

    int display_count = 0;
    rc = screen_get_context_property_iv(_glfw.screen.context, SCREEN_PROPERTY_DISPLAY_COUNT, &display_count);
    if (rc) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to get display count %s", strerror(errno));
        return 0;
    }

    screen_display_t *displays = calloc(sizeof(screen_display_t), display_count);
    rc = screen_get_context_property_pv(_glfw.screen.context, SCREEN_PROPERTY_DISPLAYS, (void**)displays);
    if (rc) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "screen: Failed to get display count %s", strerror(errno));
        free(displays);
        return 0;
    }

    monitors = (_GLFWmonitor**) calloc(sizeof(_GLFWmonitor*), display_count);
    for (i = 0;  i < display_count;  i++) {
        _GLFWmonitorScreen monitor = {0};
        char name[512] = {0};
        int active = 0;
        rc = screen_get_display_property_iv(monitor.display, SCREEN_PROPERTY_ATTACHED, &active);
        if (active) {
            monitor.display = displays[i];
            rc = screen_get_display_property_iv(monitor.display, SCREEN_PROPERTY_PHYSICAL_SIZE, monitor.size);
            rc = screen_get_display_property_iv(monitor.display, SCREEN_PROPERTY_POSITION, monitor.position);
            rc = screen_get_display_property_iv(monitor.display, SCREEN_PROPERTY_ID, &monitor.display_id);
            rc = screen_get_display_property_cv(monitor.display, SCREEN_PROPERTY_PRODUCT, sizeof(name)-1, name);
            rc = screen_get_display_property_pv(monitor.display, SCREEN_PROPERTY_MODE, (void**)&monitor.current_mode);

            monitors[i] = _glfwAllocMonitor(name, monitor.size[0], monitor.size[1]);
            monitors[i]->screen = monitor;
            monitors[i]->modes = _glfwPlatformGetVideoModes(monitors[i], &monitors[i]->modeCount);
            ++found;
        }
    }
    free(displays);
    *count = found;
    return monitors;
}

GLboolean _glfwPlatformIsSameMonitor(_GLFWmonitor* first, _GLFWmonitor* second)
{
    return first->screen.display_id == second->screen.display_id;
}

void _glfwPlatformGetMonitorPos(_GLFWmonitor* monitor, int* xpos, int* ypos)
{
    if (xpos)
        *xpos = monitor->screen.position[0];
    if (ypos)
        *ypos = monitor->screen.position[1];
}

GLFWvidmode _glfwConvertDisplayMode(screen_display_mode_t sm)
{
    GLFWvidmode vm;
    vm.refreshRate = sm.refresh;
    vm.width = sm.width;
    vm.height = sm.height;
    vm.blueBits = 8;
    vm.greenBits = 8;
    vm.redBits = 8;
    return vm;
}

GLFWvidmode* _glfwPlatformGetVideoModes(_GLFWmonitor* monitor, int* found)
{
    int i, modeCount;
    GLFWvidmode* modes = NULL;

    screen_get_display_property_iv(monitor->screen.display, SCREEN_PROPERTY_MODE_COUNT, &modeCount);

    screen_display_mode_t *screenModes = calloc(sizeof(screenModes), modeCount);
    modes = calloc(sizeof(GLFWvidmode), modeCount);

    screen_get_display_modes(monitor->screen.display, modeCount, screenModes);
    // convert screen_display_mode_t to GLFWvidmode
    for (i = 0; i < modeCount; ++i) {
        modes[i] = _glfwConvertDisplayMode(screenModes[i]);
    }
    free(screenModes);
    return modes;
}

void _glfwPlatformGetVideoMode(_GLFWmonitor* monitor, GLFWvidmode* mode)
{
    *mode = _glfwConvertDisplayMode(monitor->screen.current_mode);
}

void _glfwPlatformGetGammaRamp(_GLFWmonitor* monitor, GLFWgammaramp* ramp)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

void _glfwPlatformSetGammaRamp(_GLFWmonitor* monitor, const GLFWgammaramp* ramp)
{
    _glfwInputError(GLFW_PLATFORM_ERROR,
                    "screen: Unsupported function %s", __PRETTY_FUNCTION__);
}

