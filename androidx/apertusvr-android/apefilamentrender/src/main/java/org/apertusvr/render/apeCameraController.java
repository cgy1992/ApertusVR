/*MIT License

Copyright (c) 2018 MTA SZTAKI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

package org.apertusvr.render;

import android.annotation.SuppressLint;
import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.View;

import com.google.android.filament.Camera;

import org.apertusvr.apeVector3;

public class apeCameraController {

    private enum MotionState {
        MOVE_FORWARD,
        MOVE_BACKWARD,
        STOPPED
    }

    private float mRotateSpeed;
    private float mSpeed;
    private float mHorizontal;
    private float mVertical;

    private apeVector3 mPosition;

    boolean lockAngles = false;

    private final float M_PI = 3.14159265f;

    private MotionState mMotionState;

    @SuppressLint("ClickableViewAccessibility")
    public apeCameraController(apeVector3 position, float horizontal, float vertical,
                               float speed, float rotateSpeed, SurfaceView surfaceView) {
        mPosition = position;
        mHorizontal = horizontal;
        mVertical = vertical;
        mSpeed = speed;
        mRotateSpeed = rotateSpeed;
        mMotionState = MotionState.STOPPED;
        surfaceView.setOnTouchListener(new onTouchListener());
    }

    public void setCameraTransform(Camera camera, float dt) {
        lockAngles = true;

        apeVector3 direction = new apeVector3(
                (float) (Math.cos(mVertical) * Math.sin(mHorizontal)),
                (float) Math.sin(mVertical),
                (float) (Math.cos(mVertical) * Math.cos(mHorizontal))
        );

        apeVector3 right = new apeVector3(
                (float) Math.sin(mHorizontal - M_PI / 2f),
                0f,
                (float) Math.cos(mHorizontal - M_PI / 2f)
        );

        lockAngles = false;

        if(mMotionState == MotionState.MOVE_FORWARD) {
            mPosition = mPosition.add(direction.scale(mSpeed));
        }
        else if (mMotionState == MotionState.MOVE_BACKWARD) {
            mPosition = mPosition.add(direction.scale(-mSpeed));
        }

        apeVector3 up = right.crossProduct(direction);

        camera.lookAt(mPosition.x, mPosition.y, mPosition.z,
                mPosition.x + direction.x, mPosition.y + direction.y, mPosition.z + direction.z,
                up.x,up.y, up.z);
    }

    private float clamp(float x, float a, float b) {
        if(x > b) return b;
        else if (x < a) return a;

        return x;
    }


    class onTouchListener implements View.OnTouchListener {

        float lastX;
        float lastY;

        @SuppressLint("ClickableViewAccessibility")
        @Override
        public boolean onTouch(View v, MotionEvent event) {


            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                lastX = event.getX(0);
                lastY = event.getY(0);
            }
            else if (event.getAction() == MotionEvent.ACTION_MOVE && !lockAngles) {
                mHorizontal += mRotateSpeed * (event.getX(0) - lastX);
                mVertical += mRotateSpeed * (event.getY(0) - lastY);
                mVertical = clamp(mVertical,-M_PI / 2f, M_PI / 2f);

                lastX = event.getX();
                lastY = event.getY();
            }

            if (event.getPointerCount() == 2) {
                if (event.getY(1) < v.getHeight() / 2f) mMotionState = MotionState.MOVE_FORWARD;
                else mMotionState = MotionState.MOVE_BACKWARD;
            }
            else {
                mMotionState = MotionState.STOPPED;
            }


            return true;
        }
    }
}
