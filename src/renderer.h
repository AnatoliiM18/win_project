#pragma once

#include <directx/d3dx12.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

class Renderer {
public:
    Renderer(int w, int h);
    ~Renderer();

private:
    int m_width;
    int m_height;
    float m_aspect_ratio; 

public:
    void Init();
    void Update();
    void Render();
    void Destroy();

private:
    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForPreviousFrame();
};
