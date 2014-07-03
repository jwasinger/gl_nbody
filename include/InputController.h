#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Renderer.h"
#include "Util.h"

namespace gl_nbody
{
	enum CAMERA_MODE
	{
		CAMERA_MODE_STATIC_CAMERA = 0,
		CAMERA_MODE_FPS_CAMERA = 1,
		CAMERA_MODE_KEY_CAMERA = 2,
	};

	enum MOTION_STATE
	{
		MOTION_STATE_STATIONARY = 0,
		MOTION_STATE_FORWARD = 1,
		MOTION_STATE_LEFT = 2,
		MOTION_STATE_BACK = 3,
		MOTION_STATE_RIGHT = 4,
	};

	class InputController
	{
	private:
		Renderer *renderer;
		RECT windowRect;
		int windowWidth, windowHeight;

		CAMERA_MODE cameraMode;
		MOTION_STATE motionState;

		int screenOriginX;
		int screenOriginY;
		int mouseDeltaX;
		int mouseDeltaY;

		float mouseDamping;
		float cameraMoveSpeed;

	public:
		InputController(void);
		InputController(const RECT &windowRect, Renderer *renderer);
		~InputController(void);

		int GetMouseDeltaY(void) const { return this->mouseDeltaY; }
		int GetMouseDeltaX(void) const { return this->mouseDeltaX; }
		CAMERA_MODE GetCameraMode(void) const { return this->cameraMode; }
		MOTION_STATE GetMotionState(void) const { return this->motionState; }

		//void OnWndProc(UINT message, WPARAM wparam, LPARAM lparam);
		void Update(double ms);
		//bool Init(HWND hWnd);

	private:
		//void readRawInput(LPARAM lParam);
		void FPSMouseUpdate(int dx, int dy);
		//void onKeyDown(WPARAM wParam);
		//void onKeyUp(WPARAM wParam);
	};
}

#endif // INPUTCONTROLLER_H
