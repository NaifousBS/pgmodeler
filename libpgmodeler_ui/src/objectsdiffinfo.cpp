/*
# PostgreSQL Database Modeler (pgModeler)
#
# Copyright 2006-2014 - Raphael Araújo e Silva <raphael@pgmodeler.com.br>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

#include "objectsdiffinfo.h"

const unsigned ObjectsDiffInfo::CREATE_OBJECT=0;
const unsigned ObjectsDiffInfo::DROP_OBJECT=1;
const unsigned ObjectsDiffInfo::ALTER_OBJECT=2;
const unsigned ObjectsDiffInfo::NO_DIFFERENCE=3;

ObjectsDiffInfo::ObjectsDiffInfo(void)
{
	object=nullptr;
	diff_type=NO_DIFFERENCE;
}

ObjectsDiffInfo::ObjectsDiffInfo(unsigned diff_type, BaseObject *object)
{
	this->diff_type=diff_type;
	this->object=object;
}

unsigned ObjectsDiffInfo::getDiffType(void)
{
	return(diff_type);
}

QString ObjectsDiffInfo::getInfoMessage(void)
{
	QString msg=QT_TR_NOOP("Object `%1' `(%2)' will be %3"), obj_name;
	TableObject *tab_obj=dynamic_cast<TableObject *>(object);

	if(tab_obj)
	 obj_name=tab_obj->getParentTable()->getName(true) + "." + tab_obj->getName(true);
	else
	 obj_name=object->getName(true);

	if(diff_type==DROP_OBJECT)
	{
		return(msg.arg(obj_name)
							.arg(object->getTypeName())
							.arg("<font color='#e00000'><strong>dropped</strong></font>"));
	}
	else if(diff_type==CREATE_OBJECT)
	{
		return(msg.arg(obj_name)
							.arg(object->getTypeName())
							.arg("<font color='#008000'><strong>created</strong></font>"));
	}
	else if(diff_type==ALTER_OBJECT)
	{
		return(msg.arg(obj_name)
							.arg(object->getTypeName())
							.arg("<font color='#ff8000'><strong>changed</strong></font>"));
	}

	return("");
}

BaseObject *ObjectsDiffInfo::getObject(void)
{
	return(object);
}