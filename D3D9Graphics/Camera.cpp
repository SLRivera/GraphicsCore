/*!
 * \file Camera.cpp
 *
 * \author Sam Rivera
 * \date 9/27/2015
 *
 * 
 */
#include "DirectInput.h"
#include "Camera.h"

using namespace GFXCore;

//Camera*	g_camera = NULL;

Camera::Camera()
{
	D3DXMatrixIdentity(&viewMat);
	D3DXMatrixIdentity(&projMat);
	D3DXMatrixIdentity(&viewProjMat);

	vPosWorld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vRigthWorld = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vUpWorld = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vLlookWorld = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	
	fSpeed = 50.0f;
}

const D3DXMATRIX& Camera::getView() const
{
	return viewMat;
}

const D3DXMATRIX& Camera::getProj() const
{
	return projMat;
}

const D3DXMATRIX& Camera::getViewProj() const
{
	return viewProjMat;
}

const D3DXVECTOR3& Camera::getRight() const
{
	return vRigthWorld;
}

const D3DXVECTOR3& Camera::getUp() const
{
	return vUpWorld;
}

const D3DXVECTOR3& Camera::getLook() const
{
	return vLlookWorld;
}

D3DXVECTOR3& Camera::pos()
{
	return vPosWorld;
}

void Camera::lookAt(D3DXVECTOR3& pos, D3DXVECTOR3& target, D3DXVECTOR3& up)
{
	D3DXVECTOR3 L = target - pos;
	D3DXVec3Normalize(&L, &L);

	D3DXVECTOR3 R;
	D3DXVec3Cross(&R, &up, &L);
	D3DXVec3Normalize(&R, &R);

	D3DXVECTOR3 U;
	D3DXVec3Cross(&U, &L, &R);
	D3DXVec3Normalize(&U, &U);

	vPosWorld = pos;
	vRigthWorld = R;
	vUpWorld = U;
	vLlookWorld = L;

	buildView();
//	buildWorldFrustumPlanes();

	viewProjMat = viewMat * projMat;
}

void GFXCore::Camera::setPerspectiveLens(IDirect3DDevice9* device, float fov, float aspect, float nearZ, float farZ)
{
 	device->SetTransform(D3DTS_WORLD, &projMat);
  	device->SetTransform(D3DTS_VIEW, &projMat);

	D3DXMatrixPerspectiveFovLH(&projMat, fov, aspect, nearZ, farZ);
	//buildWorldFrustumPlanes();
	device->SetTransform(D3DTS_PROJECTION, &projMat);
	
	buildView();
	viewProjMat = viewMat * projMat;
}

void GFXCore::Camera::setOrthoLens(IDirect3DDevice9* device, const int width, const int height, const float nearZ, const float farZ)
{
	device->SetTransform(D3DTS_WORLD, &projMat);
	device->SetTransform(D3DTS_VIEW, &projMat);

	D3DXMatrixOrthoLH(&projMat, (float)width, (float)height, nearZ, farZ);
	//buildWorldFrustumPlanes();
	device->SetTransform(D3DTS_PROJECTION, &projMat);

	buildView();
	viewProjMat = viewMat * projMat;
}

void Camera::setSpeed(float s)
{
	fSpeed = s;
}

void Camera::update(float dt, float offsetHeight)
{
	// Find the net direction the camera is traveling in (since the
	// camera could be running and strafing).
	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
 	if (gDInput->keyDown(DIK_W))
 		dir += vLlookWorld;
 	if (gDInput->keyDown(DIK_S))
 		dir -= vLlookWorld;
 	if (gDInput->keyDown(DIK_D))
 		dir += vRigthWorld;
 	if (gDInput->keyDown(DIK_A))
 		dir -= vRigthWorld;

	// Move at m_speed along net direction.
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 newPos = vPosWorld + dir*fSpeed*dt;

// 	if (terrain != 0)
// 	{
// 		// New position might not be on terrain, so project the
// 		// point onto the terrain.
// 		newPos.y = terrain->getHeight(newPos.x, newPos.z) + offsetHeight;
// 
// 		// Now the difference of the new position and old (current) 
// 		// position approximates a tangent vector on the terrain.
// 		D3DXVECTOR3 tangent = newPos - m_posW;
// 		D3DXVec3Normalize(&tangent, &tangent);
// 
// 		// Now move camera along tangent vector.
// 		m_posW += tangent*m_speed*dt;
// 
// 		// After update, there may be errors in the camera height since our
// 		// tangent is only an approximation.  So force camera to correct height,
// 		// and offset by the specified amount so that camera does not sit
// 		// exactly on terrain, but instead, slightly above it.
// 		m_posW.y = terrain->getHeight(m_posW.x, m_posW.z) + offsetHeight;
// 	}
// 	else
// 	{
		vPosWorld = newPos;
//	}


	// We rotate at a fixed speed.
	float pitch = gDInput->mouseDY() / 150.0f;
	float yAngle = gDInput->mouseDX() / 150.0f;


	// Rotate camera's look and up vectors around the camera's right vector.
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &vRigthWorld, pitch);
	D3DXVec3TransformCoord(&vLlookWorld, &vLlookWorld, &R);
	D3DXVec3TransformCoord(&vUpWorld, &vUpWorld, &R);


	// Rotate camera axes about the world's y-axis.
	D3DXMatrixRotationY(&R, yAngle);
	D3DXVec3TransformCoord(&vRigthWorld, &vRigthWorld, &R);
	D3DXVec3TransformCoord(&vUpWorld, &vUpWorld, &R);
	D3DXVec3TransformCoord(&vLlookWorld, &vLlookWorld, &R);


	// Rebuild the view matrix to reflect changes.
	buildView();
	//buildWorldFrustumPlanes();

	viewProjMat = viewMat * projMat;
}

void Camera::buildView()
{
	D3DXMatrixLookAtLH(&viewMat, &vPosWorld, &vLlookWorld, &vUpWorld);
	// Keep camera's axes orthogonal to each other and of unit length.
// 	D3DXVec3Normalize(&m_lookW, &m_lookW);
// 
// 	D3DXVec3Cross(&m_upW, &m_lookW, &m_rightW);
// 	D3DXVec3Normalize(&m_upW, &m_upW);
// 
// 	D3DXVec3Cross(&m_rightW, &m_upW, &m_lookW);
// 	D3DXVec3Normalize(&m_rightW, &m_rightW);
// 
// 	// Fill in the view matrix entries.
// 
// 	float x = -D3DXVec3Dot(&m_posW, &m_rightW);
// 	float y = -D3DXVec3Dot(&m_posW, &m_upW);
// 	float z = -D3DXVec3Dot(&m_posW, &m_lookW);
// 
// 	m_view(0, 0) = m_rightW.x;
// 	m_view(1, 0) = m_rightW.y;
// 	m_view(2, 0) = m_rightW.z;
// 	m_view(3, 0) = x;
// 
// 	m_view(0, 1) = m_upW.x;
// 	m_view(1, 1) = m_upW.y;
// 	m_view(2, 1) = m_upW.z;
// 	m_view(3, 1) = y;
// 
// 	m_view(0, 2) = m_lookW.x;
// 	m_view(1, 2) = m_lookW.y;
// 	m_view(2, 2) = m_lookW.z;
// 	m_view(3, 2) = z;
// 
// 	m_view(0, 3) = 0.0f;
// 	m_view(1, 3) = 0.0f;
// 	m_view(2, 3) = 0.0f;
// 	m_view(3, 3) = 1.0f;
}