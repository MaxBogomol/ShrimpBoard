#pragma once

#include "ButtonMatrix.h"

class Keyboard {
    private:
        ButtonMatrix* buttonMatrix;

    public:
        void setButtonMatrix(ButtonMatrix* buttonMatrix);

        ButtonMatrix& getButtonMatrix();

        bool isTwoLinkedButtonPress(int row1, int collumn1, int row2, int collumn2);
        bool isTwoLinkedButtonPressed(int row1, int collumn1, int row2, int collumn2);
        bool isTwoLinkedButtonRelease(int row1, int collumn1, int row2, int collumn2);
        bool isShiftPressed();
        bool isFNPress();
        bool isFNPressed();
        bool isFNReleased();
        bool isEscPress();
        bool isEnterPress();
        bool isSpacePress();
        bool isLeftPress();
        bool isRightPress();
        bool isUpPress();
        bool isDownPress();
        bool isWPress();
        bool isAPress();
        bool isSPress();
        bool isDPress();
        bool isEscPressed();
        bool isEnterPressed();
        bool isSpacePressed();
        bool isLeftPressed();
        bool isRightPressed();
        bool isUpPressed();
        bool isDownPressed();
        bool isWPressed();
        bool isAPressed();
        bool isSPressed();
        bool isDPressed();
};