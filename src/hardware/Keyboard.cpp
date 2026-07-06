#include "Keyboard.h"

void Keyboard::setButtonMatrix(ButtonMatrix* buttonMatrix) {
    this->buttonMatrix = buttonMatrix;
}

ButtonMatrix& Keyboard::getButtonMatrix() {
    return *this->buttonMatrix;
}

bool Keyboard::isTwoLinkedButtonPress(int row1, int collumn1, int row2, int collumn2) {
    return ((getButtonMatrix().isPress(row1, collumn1) && !(getButtonMatrix().isPressed(row2, collumn2))) ||
                    (getButtonMatrix().isPress(row2, collumn2) && !(getButtonMatrix().isPressed(row1, collumn1))));
}

bool Keyboard::isTwoLinkedButtonPressed(int row1, int collumn1, int row2, int collumn2) {
    return (getButtonMatrix().isPressed(row1, collumn1) || getButtonMatrix().isPressed(row2, collumn2));
}

bool Keyboard::isTwoLinkedButtonRelease(int row1, int collumn1, int row2, int collumn2) {
    return ((getButtonMatrix().isRelease(row1, collumn1) && !(getButtonMatrix().isPressed(row2, collumn2))) ||
                    (getButtonMatrix().isRelease(row2, collumn2) && !(getButtonMatrix().isPressed(row1, collumn1))));
}

bool Keyboard::isShiftPressed() {
    return isTwoLinkedButtonPressed(4, 1, 4, 12);
}

bool Keyboard::isFNPress() {
    return getButtonMatrix().isPress(5, 8);
}

bool Keyboard::isFNPressed() {
    return getButtonMatrix().isPressed(5, 8);
}

bool Keyboard::isFNReleased() {
    return getButtonMatrix().isRelease(5, 8);
}

bool Keyboard::isEscPress() {
    return getButtonMatrix().isPress(0, 1);
}

bool Keyboard::isEnterPress() {
    return getButtonMatrix().isPress(3, 13);
}

bool Keyboard::isSpacePress() {
    return isTwoLinkedButtonPress(5, 4, 5, 5);
}

bool Keyboard::isLeftPress() {
    return getButtonMatrix().isPress(5, 10);
}

bool Keyboard::isRightPress() {
    return getButtonMatrix().isPress(5, 12);
}

bool Keyboard::isUpPress() {
    return getButtonMatrix().isPress(4, 13);
}

bool Keyboard::isDownPress() {
    return getButtonMatrix().isPress(5, 11);
}

bool Keyboard::isWPress() {
    return getButtonMatrix().isPress(2, 3);
}

bool Keyboard::isAPress() {
    return getButtonMatrix().isPress(3, 2);
}

bool Keyboard::isSPress() {
    return getButtonMatrix().isPress(3, 3);
}

bool Keyboard::isDPress() {
    return getButtonMatrix().isPress(3, 4);
}

bool Keyboard::isEscPressed() {
    return getButtonMatrix().isPressed(0, 1);
}

bool Keyboard::isEnterPressed() {
    return getButtonMatrix().isPressed(3, 13);
}

bool Keyboard::isSpacePressed() {
    return isTwoLinkedButtonPressed(5, 4, 5, 5);
}

bool Keyboard::isLeftPressed() {
    return getButtonMatrix().isPressed(5, 10);
}

bool Keyboard::isRightPressed() {
    return getButtonMatrix().isPressed(5, 12);
}

bool Keyboard::isUpPressed() {
    return getButtonMatrix().isPressed(4, 13);
}

bool Keyboard::isDownPressed() {
    return getButtonMatrix().isPressed(5, 11);
}

bool Keyboard::isWPressed() {
    return getButtonMatrix().isPressed(2, 3);
}

bool Keyboard::isAPressed() {
    return getButtonMatrix().isPressed(3, 2);
}

bool Keyboard::isSPressed() {
    return getButtonMatrix().isPressed(3, 3);
}

bool Keyboard::isDPressed() {
    return getButtonMatrix().isPressed(3, 4);
}