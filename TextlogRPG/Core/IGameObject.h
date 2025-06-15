class IGameObject
{
public:

    virtual ~IGameObject() = default;

public:
    virtual void Init() = 0;

    virtual void Update(float deltaTime) = 0;

    virtual void Render() = 0;

};
    