#include "QuitButtonAction.h"
#include "LayoutView.h"


QuitButtonAction::QuitButtonAction()
{
}


QuitButtonAction::~QuitButtonAction()
{
}

void QuitButtonAction::doAction(ClickEvent* event)
{
	LayoutView* view =  event->getView();
	view->setDisplaying(false);
}
