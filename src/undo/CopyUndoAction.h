/*
 * Xournal++
 *
 * Undo action for page copy
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __COPYUNDOACTION_H__
#define __COPYUNDOACTION_H__

#include "UndoAction.h"
#include <XournalType.h>

class CopyUndoAction : public UndoAction
{
public:
	CopyUndoAction(PageRef pageref, int pageNr);
	virtual ~CopyUndoAction();

public:
	virtual bool undo(Control* control);
	virtual bool redo(Control* control);

	virtual String getText();

private:
	XOJ_TYPE_ATTRIB;

	int pageNr;
};

#endif
