#include <stdio.h>

class object {
	struct imp;
public:
	static object* create(int d);
	void release();
	void dosomething();
};

struct object::imp : object {
	int data;
	void inc();
};

object * object::create(int d) {
	imp * self = new imp();
	self->data = d;
	return self;
};

#define DESC_SELF imp * self = static_cast<imp *>(this);

void object::release() {
	DESC_SELF
	delete self;
}

void object::dosomething() {
	DESC_SELF
	self->inc();
	printf("%d\n", self->data);
}

void object::imp::inc() {
	DESC_SELF
	++self->data;
}

int main() {
	object *obj = object::create(1);
	obj->dosomething();
	obj->release();
	return 0;
}
