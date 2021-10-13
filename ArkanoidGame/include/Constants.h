#pragma once

// Window parameters
constexpr int WINDOW_HEIGHT = 720;
constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr int WINDOW_WIDTH = static_cast<int>(WINDOW_HEIGHT * ASPECT_RATIO);

// Update time parameters
constexpr int FPS_TARGET = 30;
constexpr int FRAME_TARGET_TIME = static_cast<int>(1000.0f / FPS_TARGET);