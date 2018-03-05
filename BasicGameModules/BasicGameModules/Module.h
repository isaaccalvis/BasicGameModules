#ifndef __MODULE_H__
#define __MODULE_H__

class Application;

struct GUI_object;
enum GUI_OBJECT_STATE;

class Module
{
public:

	Module() : active(false) {}
	virtual ~Module() {}

	void Init() { active = true; }
	virtual bool Awake() { return true; }
	virtual bool Start() { return true; }
	virtual bool PreUpdate() { return true; }
	virtual bool Update(float dt) { return true; }
	virtual bool PostUpdate() { return true; }
	virtual bool CleanUp() { return true; }
	virtual bool Load() { return true; }
	virtual bool Save() const { return true; }

	virtual void CallBack(GUI_object* object, GUI_OBJECT_STATE state){}

public:

	char*		name;
	bool		active;

};

#endif