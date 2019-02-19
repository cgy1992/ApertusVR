#MIT License
#
#Copyright (c) 2016 MTA SZTAKI
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.


# Basic

option(APE_SAMPLES_HelloWorld "APE_SAMPLES_HelloWorld?" ON )
if (${APE_SAMPLES_HelloWorld})
	add_subdirectory (helloWorld)
endif ()

option(APE_SAMPLES_Tester "APE_SAMPLES_Tester?" ON )
if (${APE_SAMPLES_Tester})
	add_subdirectory (tester)
endif ()

option(APE_SAMPLES_InGameBrowser "APE_SAMPLES_InGameBrowser?" OFF )
if (${APE_SAMPLES_InGameBrowser})
	add_subdirectory (inGameBrowser)
endif ()

# Environment Simulation

option(APE_SAMPLES_Environment "APE_SAMPLES_Environment?" OFF )
if (${APE_SAMPLES_Environtment})
	add_subdirectory (environment)
endif ()

# 360

option(APE_SAMPLES_360Image "APE_SAMPLES_360Image?" OFF )
if (${APE_SAMPLES_360Image})
	add_subdirectory (360Image)
endif ()

option(APE_SAMPLES_360Video "APE_SAMPLES_360Video?" OFF )
if (${APE_SAMPLES_360Video})
	add_subdirectory (360Video)
endif ()

# Scene Sharing

option(APE_SAMPLES_MultiPlayer "Use APE_SAMPLES_MultiPlayer?" OFF )
if (${APE_SAMPLES_MultiPlayer})
	add_subdirectory (multiPlayer)
endif ()

# UI

option(APE_SAMPLES_HtmlOverlayUI "APE_SAMPLES_HtmlOverlayUI?" OFF )
if (${APE_SAMPLES_HtmlOverlayUI})
	add_subdirectory (htmlOverlayUI)
endif ()

option(APE_SAMPLES_Presentation "APE_SAMPLES_Presentation?" OFF )
if (${APE_SAMPLES_Presentation})
	add_subdirectory (presentation)
endif ()

option(APE_SAMPLES_Gallery "APE_SAMPLES_Gallery?" OFF )
if (${APE_SAMPLES_Gallery})
	add_subdirectory (gallery)
endif ()

# Video / Voice Chat

option(APE_SAMPLES_VideoChat "APE_SAMPLES_VideoChat?" OFF )
if (${APE_SAMPLES_VideoChat})
	add_subdirectory (videoChat)
endif ()

# Hand Tracking

option(APE_SAMPLES_LeapHandTracking "APE_SAMPLES_LeapHandTracking?" OFF )
if (${APE_SAMPLES_LeapHandTracking})
	add_subdirectory (leapHandTracking)
endif ()

# Head Tracking

option(APE_SAMPLES_FobHeadTracking "APE_SAMPLES_FobHeadTracking?" OFF )
if (${APE_SAMPLES_FobHeadTracking})
	add_subdirectory (fobHeadTracking)
endif ()

# Displays

option(APE_SAMPLES_MultiDisplay "APE_SAMPLES_MultiDisplay?" OFF )
if (${APE_SAMPLES_MultiDisplay})
	add_subdirectory (multiDisplay)
endif ()

option(APE_SAMPLES_CaveSystem "Use APE_SAMPLES_CaveSystem?" OFF )
if (${APE_SAMPLES_CaveSystem})
	add_subdirectory (caveSystem)
endif ()

option(APE_SAMPLES_OculusDK2 "APE_SAMPLES_OculusDK2?" OFF )
if (${APE_SAMPLES_OculusDK2})
	add_subdirectory (oculusDK2)
endif ()

option(APE_SAMPLES_HtcVive "APE_SAMPLES_HtcVive?" OFF )
if (${APE_SAMPLES_HtcVive})
	add_subdirectory (htcVive)
endif ()

# PointCloud

option(APE_SAMPLES_Kinect "APE_SAMPLES_Kinect?" OFF )
if (${APE_SAMPLES_Kinect})
	add_subdirectory (kinect)
endif ()

option(APE_SAMPLES_Zed "APE_SAMPLES_Zed?" OFF )
if (${APE_SAMPLES_Zed})
	add_subdirectory (zed)
endif ()

option(APE_SAMPLES_MixedReality "APE_SAMPLES_MixedReality?" OFF )
if (${APE_SAMPLES_MixedReality})
	add_subdirectory (mixedReality)
endif ()

# Industry / IoT / Controllers / Sensors

option(APE_SAMPLES_Industry40 "APE_SAMPLES_Industry40?" OFF )
if (${APE_SAMPLES_Industry40})
	add_subdirectory (industry40)
endif ()

option(APE_SAMPLES_RobotMonitoring "APE_SAMPLES_RobotMonitoring?" OFF )
if (${APE_SAMPLES_RobotMonitoring})
	add_subdirectory (robotMonitoring)
endif ()

# Others

option(APE_SAMPLES_LinkageDesignerVR "APE_SAMPLES_LinkageDesignerVR?" OFF )
if (${APE_SAMPLES_LinkageDesignerVR})
	add_subdirectory (linkageDesignerVR)
endif ()

option(APE_SAMPLES_Lego "APE_SAMPLES_Lego?" OFF )
if (${APE_SAMPLES_Lego})
	add_subdirectory (lego)
endif ()

option(APE_SAMPLES_TexasEEG "APE_SAMPLES_TexasEEG?" OFF )
if (${APE_SAMPLES_TexasEEG})
	add_subdirectory (texasEEG)
endif ()

option(APE_SAMPLES_Gyor "APE_SAMPLES_Gyor?" OFF )
if (${APE_SAMPLES_Gyor})
	add_subdirectory (gyor)
endif ()

option(APE_SAMPLES_Audi "APE_SAMPLES_Audi?" OFF )
if (${APE_SAMPLES_Audi})
	add_subdirectory (audi)
endif ()

option(APE_SAMPLES_RobotCalibration "APE_SAMPLES_RobotCalibration?" OFF )
if (${APE_SAMPLES_RobotCalibration})
	add_subdirectory (robotCalibration)
endif ()

option(APE_SAMPLES_Polimi "APE_SAMPLES_Polimi?" OFF )
if (${APE_SAMPLES_Polimi})
	add_subdirectory (polimi)
endif ()
