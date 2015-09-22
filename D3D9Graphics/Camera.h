#pragma once

#include "D3DUtils.h"

namespace GFXCore
{
	class Camera
	{
	public:
		const D3DXMATRIX& view() const;
		const D3DXMATRIX& proj() const;
		const D3DXMATRIX& viewProj() const;

		const D3DXVECTOR3& right() const;
		const D3DXVECTOR3& up() const;
		const D3DXVECTOR3& look() const;

		D3DXVECTOR3& pos();

		void lookAt(D3DXVECTOR3& pos, D3DXVECTOR3& target, D3DXVECTOR3& up);
		void setPerspectiveLens(IDirect3DDevice9* device, float fov, float aspect, float nearZ, float farZ);
		void setOrthoLens(IDirect3DDevice9* device, const int width, const int height, const float nearZ, const float farZ);
		void setSpeed(float s);
		void update(float dt, float offsetHeight);
		
		Camera();
		~Camera() {}

	protected:
		D3DXMATRIX	m_view,
			m_proj,
			m_viewProj;

		D3DXVECTOR3	m_posW,
			m_rightW,
			m_upW,
			m_lookW;

		float	m_speed;

		void buildView();
	};
}
//extern Camera* g_camera;