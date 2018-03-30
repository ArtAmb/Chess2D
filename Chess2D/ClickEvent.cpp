#include "ClickEvent.h"
#include "LayoutView.h"

ClickEvent::ClickEvent()
{
}


ClickEvent::~ClickEvent()
{
}

void ClickEvent::setView(LayoutView* view) {
	this->view = view;
}

LayoutView* ClickEvent::getView() {
	return view;
}
