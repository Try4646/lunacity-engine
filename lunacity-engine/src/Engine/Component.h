// Component.h
#pragma once

class GameObject;  // Forward declaration

class Component {
protected:
    GameObject* owner;

public:
    Component() : owner(nullptr) {}
    virtual ~Component() {}

    virtual void Start() {}
    virtual void Update(float deltaTime) {}
    virtual void Render() {}

    void SetOwner(GameObject* go) { owner = go; }
    GameObject* GetOwner() const { return owner; }
};