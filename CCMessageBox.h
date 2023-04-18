#pragma once

#include "AKSchedulable.h"

namespace CCMessageBoxData {
	extern int messages_sent;
};

class CCMessageBox : public AKSchedulable {
protected:
	const char* message;
public:

	CCMessageBox(const char* msg);

	void update(float delta) override;
};