/*
 * Xournal++
 *
 * Part of the PDF export
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __UPDATEREF_H__
#define __UPDATEREF_H__

#include "poppler/XojPopplerDocument.h"

class UpdateRef
{
public:
	UpdateRef(int objectId, XojPopplerDocument doc);
	virtual ~UpdateRef();

public:
	static void destroyDelete(UpdateRef* data);

public:
	XOJ_TYPE_ATTRIB;

	int objectId;
	bool wroteOut;

	Object object;
	XojPopplerDocument doc;
};

#endif /* __UPDATEREF_H__ */
