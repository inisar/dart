/*
 * Copyright (c) 2011-2018, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/master/LICENSE
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_GUI_GLFW_WINDOW_HPP_
#define DART_GUI_GLFW_WINDOW_HPP_

#include <memory>
#include <unordered_map>

#include <Eigen/Dense>
//#include <GLFW/glfw3.h>
#include "dart/gui/LoadOpengl.hpp"

#include "dart/gui/Trackball.hpp"

namespace dart {
namespace gui {
namespace glfw {

class Scene;

class Window
{
public:
  /// Constructor
  Window(
      const std::string& title = "Nonamed Window",
      int width = 640,
      int height = 360,
      bool show = true);

  /// Destructor
  virtual ~Window();

  /// Runs the main loop for all the viewers.
  static void runAllViewers(std::size_t refresh = 50u);

  //----------------------------------------------------------------------------
  /// \{ \name Properties
  //----------------------------------------------------------------------------

  /// Sets the title that will be displayed at the window bar.
  void setTitle(const std::string& title);

  /// Sets the size of this viewer.
  void setSize(const Eigen::Vector2i& size);

  /// Sets the size of this viewer.
  void setSize(int width, int height);

  /// Returns the size of this viewer.
  Eigen::Vector2i getSize() const;

  /// Sets the visibility.
  void setVisible(bool visible);

  /// Returns true if this Viewer is shown.
  bool isVisible() const;

  /// Shows this Viewer. Equivalent to setVisible(true).
  void show();

  /// Hides this Viewer. Equivalent to setVisible(false).
  void hide();

  /// \}

  //----------------------------------------------------------------------------
  /// \{ \name GLFW event handlers
  //----------------------------------------------------------------------------

  /// Windows resize callback function.
  virtual void windowSizeCallback(int width, int height);

  /// Windows resize callback function.
  virtual void framebufferSizeCallback(int width, int height);

  /// Mouse move callback function.
  virtual void cursorPosCallback(double xMouse, double yMouse);

  /// Mouse button callback function.
  virtual void mouseButtonCallback(int button, int action, int mods);

  /// Keyboard callback function.
  virtual void keyboardCallback(int key, int scancode, int action, int mods);

  /// Character callback function, which is called when a Unicode character is
  /// input.
  virtual void charCallback(unsigned int codepoint);

  /// File drop callback of the specified window, which is called when one or
  /// more dragged files are dropped on the window.
  virtual void dropCallback(int count, const char** filenames);

  /// Scroll callback of the specified window, which is called when a scrolling
  /// device is used, such as a mouse wheel or scrolling area of a touchpad.
  virtual void scrollCallback(double xoffset, double yoffset);

  /// \}

protected:
  void render();

  virtual void renderScene();

  virtual void renderGui();

  static Window* findWindow(GLFWwindow* window);

  //----------------------------------------------------------------------------
  /// \{ \name Camera work
  //----------------------------------------------------------------------------

  /// Set the scene position (where the camera needs to look at)
  void setScenePosition(const Eigen::Vector3f& position, float sceneRadius);

  /// Set the camera so that we can view the whole scene
  void resetCameraToViewAll();

  /// Map mouse coordinates to coordinates on the sphere
  bool mapMouseCoordinatesToSphere(
      double xMouse, double yMouse, Eigen::Vector3f& spherePoint) const;

  /// Zoom the camera
  void zoom(float zoomDiff);

  /// Translate the camera
  void translate(int xMouse, int yMouse);

  /// Rotate the camera
  void rotate(int xMouse, int yMouse);

  /// \}

  GLFWwindow* mGlfwWindow;

  bool mIsVisible;

  Eigen::Vector4f mClearColor;

  //----------------------------------------------------------------------------
  /// \{ \name Camera and view angle
  //----------------------------------------------------------------------------

  /// Width of the window in pixels
  int mWindowWidth;

  /// Height of the window in pixels
  int mWindowHeight;

  int mViewportX;
  int mViewportY;
  int mViewportWidth;
  int mViewportHeight;

  Eigen::Vector3f mCenterScene;

  double mLastMouseX;
  double mLastMouseY;

  Eigen::Vector3f mLastPointOnSphere;

  bool mIsLastPointOnSphereValid;

  static const float SCROLL_SENSITIVITY;
  // TODO: make this as an option

  /// \}

private:
  static void startupGlfw();
  static void shutdownGlfw();
  void setCallbacks();
  void initLights();
  static std::unordered_map<GLFWwindow*, Window*> mViewerMap;
  static bool mMainloopActive;
};

} // namespace glfw
} // namespace gui
} // namespace dart

#include "dart/gui/glfw/detail/Viewer.hpp"

#endif // DART_GUI_GLFW_WINDOW_HPP_