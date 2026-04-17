#include "Transform.h"
#include <GLFW/glfw3.h>

Transform::Transform() : posX(0), posY(0), scaleX(1), scaleY(1), rotation(0) {}

void Transform::SetPosition(float x, float y) {
    posX = x;
    posY = y;
}

void Transform::Translate(float dx, float dy) {
    posX += dx;
    posY += dy;
}

void Transform::ApplyTransform() {
    glPushMatrix();
    glTranslatef(posX, posY, 0);
    glRotatef(rotation, 0, 0, 1);
    glScalef(scaleX, scaleY, 1);
}

void Transform::ResetTransform() {
    glPopMatrix();
}