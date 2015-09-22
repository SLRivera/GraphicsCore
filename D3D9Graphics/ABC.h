
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

		inline D3DXVECTOR3& getPosition();
		inline D3DXVECTOR3& getVelocity();
		inline int getHealth();
		inline int getModelId();
		inline int getTextureId();
		inline ObjType getObjectType();
		inline bool isEnabled();
		inline void setPosition(const D3DXVECTOR3& pos);
		inline void setVelocity(const D3DXVECTOR3& velo);
		inline void setFixedRotation(const D3DXVECTOR3& rot);
		inline void setHealth(const int health);
		inline void toggleEnabled();
		inline void setEnabled(const bool enabled);
		inline void setObjectType(ObjType e);

		ABC();
		ABC(const ABC&);
		virtual ~ABC() = 0;

	protected:
		D3DXVECTOR3		position;
		D3DXVECTOR3		velocity;
		D3DXVECTOR3		fixedRotation;

		ObjType		eType;

		int		nHealth;
		int		nTextureId;
		int		nModelId;
		int		nObjectId;

		bool bEnabled;
	};

	D3DXVECTOR3& ABC::getPosition()	{ return position; }
	D3DXVECTOR3& ABC::getVelocity() { return velocity; }
	ABC::ObjType ABC::getObjectType() { return eType; }
	int ABC::getHealth() { return nHealth; }
	int ABC::getModelId()	{ return nModelId; }
	int ABC::getTextureId() { return nTextureId; }
	bool ABC::isEnabled()	{ return bEnabled; }
	void ABC::setPosition(const D3DXVECTOR3& pos)		{ position = pos; }
	void ABC::setVelocity(const D3DXVECTOR3& velo)	{ velocity = velo; }
	void ABC::setFixedRotation(const D3DXVECTOR3& rot)	{ fixedRotation = rot; }
	void ABC::setHealth(const int health)		{ nHealth = health; }
	void ABC::toggleEnabled()		{ bEnabled = !bEnabled; }
	void ABC::setEnabled(const bool enabled)		{ bEnabled = enabled; }
	void ABC::setObjectType(ObjType e)	{ eType = e; }
}