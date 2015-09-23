#pragma once
namespace GSP420
{
	class ABC
	{
	public:
		enum ObjType {
			BeginObjType = -1,
			LargeAsteroid, 
			SmallAsteroid,
			Enemy1, 
			Enemy2, 
			Enemy3, 
			EnemyBoss, 
			Pickup, 
			PlayerBullet, 
			EnemyBullet, 
			PlayerMissile, 
			EnemyMissile, 
			Player,
			EndObjType
		};

		virtual bool init(const int modelId, const int textureId) = 0;
		virtual void update(const float dt) = 0;
		virtual void shutdown() = 0;

		inline const D3DXVECTOR3& getPosition() const;
		inline const D3DXVECTOR3& getVelocity() const;
		inline const D3DXVECTOR3& getFixedRotation() const;
		inline const D3DXVECTOR3& getScale() const;
		inline int getHealth() const;
		inline int getModelId() const;
		inline int getTextureId() const;
		inline ObjType getObjectType() const;
		inline bool isEnabled() const;
		inline void toggleEnabled();

		ABC();
		ABC(const ABC&);
		virtual ~ABC() = 0;

	private:
		D3DXVECTOR3		position;
		D3DXVECTOR3		velocity;
		D3DXVECTOR3		fixedRotation;
		D3DXVECTOR3		scale;

		ObjType		eType;

		int		nHealth;
		int		nTextureId;
		int		nModelId;
		int		nObjectId;

		bool bEnabled;

// 		inline void setPosition(const D3DXVECTOR3& pos);
// 		inline void setVelocity(const D3DXVECTOR3& velo);
// 		inline void setFixedRotation(const D3DXVECTOR3& rot);
// 		inline void setHealth(const int health);
// 		inline void setEnabled(const bool enabled);
// 		inline void setObjectType(ObjType e);
	};

	const D3DXVECTOR3& ABC::getPosition() const	{ return position; }
	const D3DXVECTOR3& ABC::getVelocity() const { return velocity; }
	const D3DXVECTOR3& ABC::getFixedRotation() const { return fixedRotation; }
	const D3DXVECTOR3& ABC::getScale() const { return scale; }
	ABC::ObjType ABC::getObjectType() const { return eType; }
	int ABC::getHealth() const { return nHealth; }
	int ABC::getModelId() const	{ return nModelId; }
	int ABC::getTextureId() const { return nTextureId; }
	bool ABC::isEnabled() const	{ return bEnabled; }
// 	void ABC::setPosition(const D3DXVECTOR3& pos)		{ position = pos; }
// 	void ABC::setVelocity(const D3DXVECTOR3& velo)	{ velocity = velo; }
// 	void ABC::setFixedRotation(const D3DXVECTOR3& rot)	{ fixedRotation = rot; }
// 	void ABC::setHealth(const int health)		{ nHealth = health; }
// 	void ABC::toggleEnabled()		{ bEnabled = !bEnabled; }
// 	void ABC::setEnabled(const bool enabled)		{ bEnabled = enabled; }
// 	void ABC::setObjectType(ObjType e)	{ eType = e; }
}