/*!
* \file test.h
*
* \author Sam Rivera
* \date September 2015
*
* Last Revision: 9/23/15
*/
#pragma once
#include "..\\D3D9Graphics\\abc.h"

namespace GFXCore
{
	class Test : public GSP420::ABC
	{
	public:

		virtual bool init(const int modelId, const int textureId) { nModelId = modelId; return true; }
		virtual void update(const float dt) {}
		virtual void shutdown() {}

		Test(const D3DXVECTOR3& initPos,
			const D3DXVECTOR3& initRot,
			const D3DXVECTOR3& initVelo,
			const D3DXVECTOR3& initScale);

		virtual ~Test()
		{
		}
	};

	Test::Test(const D3DXVECTOR3& initPos, const D3DXVECTOR3& initRot, const D3DXVECTOR3& initVelo, const D3DXVECTOR3& initScale)
	{
		position = initPos;
		fixedRotation = initRot;
		velocity = initVelo;
		scale = initScale;
	}
}