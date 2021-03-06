#include "TextBoxUndoAction.h"
#include "../model/PageRef.h"
#include "../model/Layer.h"
#include "../model/Element.h"
#include "../gui/Redrawable.h"

#include <Rectangle.h>

TextBoxUndoAction::TextBoxUndoAction(PageRef page, Layer* layer,
                                     Element* element,
                                     Element* oldelement) : UndoAction("TextBoxUndoAction")
{
	XOJ_INIT_TYPE(TextBoxUndoAction);

	this->page = page;
	this->layer = layer;
	this->element = element;
	this->oldelement = oldelement;
}

TextBoxUndoAction::~TextBoxUndoAction()
{
	XOJ_CHECK_TYPE(TextBoxUndoAction);

	if (this->undone)
	{
		// Insert was undone, so this is not needed anymore
		if(this->layer->indexOf(element) == -1)
		{
			delete this->element;
		}
		//	we won't be able to delete the old element, as it will
		//	get cleaned up in the next TextBoxUndoAction cleanup.
	}
	else if(this->layer->indexOf(oldelement) == -1)
	{
		delete this->oldelement;
		//if it hasn't been undone we clear out the old element,
		//since that won't be used in the future and isn't drawn.
	}
	this->element = NULL;
	this->oldelement = NULL;

	XOJ_RELEASE_TYPE(TextBoxUndoAction);
}

String TextBoxUndoAction::getText()
{
	XOJ_CHECK_TYPE(TextBoxUndoAction);

	return _("Edit text");
}

bool TextBoxUndoAction::undo(Control* control)
{
	XOJ_CHECK_TYPE(TextBoxUndoAction);

	this->layer->removeElement(this->element, false);
	this->layer->addElement(this->oldelement);

	double x1 = element->getX();
	double y1 = element->getY();
	double x2 = element->getX() + element->getElementWidth();
	double y2 = element->getY() + element->getElementHeight();

	x1 = MIN(x1, oldelement->getX());
	y1 = MIN(y1, oldelement->getY());
	x2 = MAX(x2, oldelement->getX() + oldelement->getElementWidth());
	y2 = MAX(y2, oldelement->getY() + oldelement->getElementHeight());

	Rectangle rect(x1, y1, x2 - x1, y2 - y1);
	this->page->fireRectChanged(rect);

	this->undone = true;

	return true;
}

bool TextBoxUndoAction::redo(Control* control)
{
	XOJ_CHECK_TYPE(TextBoxUndoAction);

	this->layer->removeElement(this->oldelement, false);
	this->layer->addElement(this->element);

	double x1 = oldelement->getX();
	double y1 = oldelement->getY();
	double x2 = oldelement->getX() + oldelement->getElementWidth();
	double y2 = oldelement->getY() + oldelement->getElementHeight();

	x1 = MIN(x1, element->getX());
	y1 = MIN(y1, element->getY());
	x2 = MAX(x2, element->getX() + element->getElementWidth());
	y2 = MAX(y2, element->getY() + element->getElementHeight());

	Rectangle rect(x1, y1, x2 - x1, y2 - y1);
	this->page->fireRectChanged(rect);

	this->undone = false;

	return true;
}
