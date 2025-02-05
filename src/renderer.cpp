#include "renderer.h"

Renderer::Renderer(int w, int h) : m_width(w), m_height(h)
{
    m_aspect_ratio = static_cast<float>(w) / static_cast<float>(h);
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
    LoadPipeline();
    LoadAssets();
}

void Renderer::Update()
{
}

void Renderer::Render()
{
}

void Renderer::Destroy()
{
}

void Renderer::LoadPipeline()
{
}

void Renderer::LoadAssets()
{
}

void Renderer::PopulateCommandList()
{
}

void Renderer::WaitForPreviousFrame()
{
}
