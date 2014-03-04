#ifndef RENDERER_H
#define RENDERER_H

enum TRANSFORM_TYPE : UINT
{
    TRANSFORM_WORLD,
    TRANSFORM_PROJECTION,
    TRANSFORM_VIEW,
};

enum SHADER_TYPE
{
    SHADER_TYPE_NONE = 0,
    SHADER_TYPE_COLOR,
    SHADER_TYPE_POINT_SPRITE,
    SHADER_TYPE_TEXTURE,
};

class Renderer
{
    public:
		Renderer(void);
		~Renderer();

		bool init(void);
		void Render(void);
};
#endif
