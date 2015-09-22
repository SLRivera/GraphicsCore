#include "DirectInput.h"
#include "Camera.h"

using namespace GFXCore;

//Camera*	g_camera = NULL;

Camera::Camera()
{
	D3DXMatrixIdentity(&m_view);
	D3DXMatrixIdentity(&m_proj);
	D3DXMatrixIdentity(&m_viewProj);

	m_posW = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rightW = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_upW = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookW = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	
	m_speed = 50.0f;
}

const D3DXMATRIX& Camera::view() const
{
	return m_view;
}

const D3DXMATRIX& Camera::proj() const
{
	return m_proj;
}

const D3DXMATRIX& Camera::viewProj() const
{
	return m_viewProj;
}

const D3DXVECTOR3& Camera::right() const
{
	return m_rightW;
}

const D3DXVECTOR3& Camera::up() const
{
	return m_upW;
}

const D3DXVECTOR3& Camera::look() const
{
	return m_lookW;
}

D3DXVECTOR3& Camera::pos()
{
	return m_posW;
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

	m_posW = pos;
	m_rightW = R;
	m_upW = U;
	m_lookW = L;

	buildView();
//	buildWorldFrustumPlanes();

	m_viewProj = m_view * m_proj;
}

void GFXCore::Camera::setPerspectiveLens(IDirect3DDevice9* device, float fov, float aspect, float nearZ, float farZ)
{
 	device->SetTransform(D3DTS_WORLD, &m_proj);
  	device->SetTransform(D3DTS_VIEW, &m_proj);

	D3DXMatrixPerspectiveFovLH(&m_proj, fov, aspect, nearZ, farZ);
	//buildWorldFrustumPlanes();
	device->SetTransform(D3DTS_PROJECTION, &m_proj);
	
	buildView();
	m_viewProj = m_view * m_proj;
}

void GFXCore::Camera::setOrthoLens(IDirect3DDevice9* device, const int width, const int height, const float nearZ, const float farZ)
{
	device->SetTransform(D3DTS_WORLD, &m_proj);
	device->SetTransform(D3DTS_VIEW, &m_proj);

	D3DXMatrixOrthoLH(&m_proj, (float)width, (float)height, nearZ, farZ);
	//buildWorldFrustumPlanes();
	device->SetTransform(D3DTS_PROJECTION, &m_proj);

	buildView();
	m_viewProj = m_view * m_proj;
}

void Camera::setSpeed(float s)
{
	m_speed = s;
}

void Camera::update(float dt, float offsetHeight)
{
	// Find the net direction the camera is traveling in (since the
	// camera could be running and strafing).
	D3DXVECTOR3 dir(0.0f, 0.0f, 0.0f);
 	if (gDInput->keyDown(DIK_W))
 		dir += m_lookW;
 	if (gDInput->keyDown(DIK_S))
 		dir -= m_lookW;
 	if (gDInput->keyDown(DIK_D))
 		dir += m_rightW;
 	if (gDInput->keyDown(DIK_A))
 		dir -= m_rightW;

	// Move at m_speed along net direction.
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 newPos = m_posW + dir*m_speed*dt;

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
		m_posW = newPos;
//	}


	// We rotate at a fixed speed.
	float pitch = gDInput->mouseDY() / 150.0f;
	float yAngle = gDInput->mouseDX() / 150.0f;


	// Rotate camera's look and up vectors around the camera's right vector.
	D3DXMATRIX R;
	D3DXMatrixRotationAxis(&R, &m_rightW, pitch);
	D3DXVec3TransformCoord(&m_lookW, &m_lookW, &R);
	D3DXVec3TransformCoord(&m_upW, &m_upW, &R);


	// Rotate camera axes about the world's y-axis.
	D3DXMatrixRotationY(&R, yAngle);
	D3DXVec3TransformCoord(&m_rightW, &m_rightW, &R);
	D3DXVec3TransformCoord(&m_upW, &m_upW, &R);
	D3DXVec3TransformCoord(&m_lookW, &m_lookW, &R);


	// Rebuild the view matrix to reflect changes.
	buildView();
	//buildWorldFrustumPlanes();

	m_viewProj = m_view * m_proj;
}

void Camera::buildView()
{
	D3DXMatrixLookAtLH(&m_view, &m_posW, &m_lookW, &m_upW);
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