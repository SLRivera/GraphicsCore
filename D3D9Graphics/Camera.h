/*!
* \file Camera.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once

#include "D3DUtils.h"

namespace GFXCore
{
	class Camera
	{
	public:
		const D3DXMATRIX& getView() const;
		const D3DXMATRIX& getProj() const;
		const D3DXMATRIX& getViewProj() const;

		const D3DXVECTOR3& getRight() const;
		const D3DXVECTOR3& getUp() const;
		const D3DXVECTOR3& getLook() const;

		D3DXVECTOR3& pos();

		void lookAt(D3DXVECTOR3& pos, D3DXVECTOR3& target, D3DXVECTOR3& up);
		void setPerspectiveLens(IDirect3DDevice9* device, float fov, float aspect, float nearZ, float farZ);
		void setOrthoLens(IDirect3DDevice9* device, const int width, const int height, const float nearZ, const float farZ);
		void setSpeed(float s);
		void update(float dt, float offsetHeight);
		
		Camera();
		~Camera() {}

	protected:
		D3DXMATRIX	viewMat,
							projMat,
							viewProjMat;

		D3DXVECTOR3	vPosWorld,
								vRigthWorld,
								vUpWorld,
								vLlookWorld;

		float	fSpeed;

		void buildView();
	};
}
//extern Camera* g_camera;