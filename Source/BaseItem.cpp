/*
  ==============================================================================

    BaseItem.cpp
    Created: 28 Oct 2016 8:04:25pm
    Author:  bkupe

  ==============================================================================
*/

#include "BaseItem.h"
#include "BaseItemEditor.h"
#include "ScriptManager.h"

BaseItem::BaseItem(const String &name, bool _canBeDisabled, bool _canHaveScripts) :
	ControllableContainer(name),
	canBeDisabled(_canBeDisabled),
	canHaveScripts(_canHaveScripts)
{
	saveAndLoadName = true;

	if (canBeDisabled)
	{
		enabled = addBoolParameter("Enabled", "Enable / Disable this component", true);
		enabled->hideInOutliner = true;
	}

	nameParam = addStringParameter("Name", "Name of the component", niceName);
	nameParam->hideInEditor = true;
	nameParam->hideInOutliner = true;
	nameParam->isTargettable = false;

	if (canHaveScripts)
	{
		scriptManager = new ScriptManager();
		addChildControllableContainer(scriptManager);
	}
	
}

BaseItem::~BaseItem()
{
	clear();
}

void BaseItem::remove()
{
	baseItemListeners.call(&BaseItem::Listener::askForRemoveBaseItem, this);
}

void BaseItem::onContainerParameterChanged(Parameter * p)
{
	if (p == nameParam)
	{
		setNiceName(nameParam->stringValue());
	}

	onContainerParameterChangedInternal(p);
}

void BaseItem::onContainerNiceNameChanged()
{
	nameParam->setValue(niceName);
}

InspectableEditor * BaseItem::getEditor(bool isRoot)
{
	return ControllableContainer::getEditor(isRoot);// new BaseItemEditor(this, isRoot);
}
