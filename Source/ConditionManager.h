/*
  ==============================================================================

    ConditionManager.h
    Created: 28 Oct 2016 8:07:18pm
    Author:  bkupe

  ==============================================================================
*/

#ifndef CONDITIONMANAGER_H_INCLUDED
#define CONDITIONMANAGER_H_INCLUDED

#include "Condition.h"

class ConditionManager :
	public BaseManager<Condition>,
	public Condition::ConditionListener,
	public Timer
{
public:
	juce_DeclareSingleton(ConditionManager, true)

	ConditionManager(bool operatorOnSide = false);
	~ConditionManager();
	
	Factory<Condition> factory;

	BoolParameter * isValid;

	enum ConditionOperator { AND, OR };
	EnumParameter * conditionOperator;
	bool operatorOnSide;

	FloatParameter * validationTime;
	FloatParameter * validationProgress;

	bool validationWaiting;
	float prevTimerTime;


	void addItemInternal(Condition *, var data) override;
	void removeItemInternal(Condition *) override;

	void checkAllConditions();

	bool areAllConditionsValid();
	bool isAtLeastOneConditionValid();

	int getNumEnabledConditions();
	int getNumValidConditions();

	bool getIsValid(bool emptyIsValid);

	void dispatchConditionValidationChanged();

	void conditionValidationChanged(Condition *) override;

	void onContainerParameterChanged(Parameter *) override;

	InspectableEditor * getEditor(bool isRoot) override;

	class ConditionManagerListener
	{
	public:
		virtual ~ConditionManagerListener() {}
		virtual void conditionManagerValidationChanged(ConditionManager *) {}
	};


	ListenerList<ConditionManagerListener> conditionManagerListeners;
	void addConditionManagerListener(ConditionManagerListener* newListener) { conditionManagerListeners.add(newListener); }
	void removeConditionManagerListener(ConditionManagerListener* listener) { conditionManagerListeners.remove(listener); }

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConditionManager)


		// Inherited via Timer
		virtual void timerCallback() override;

};


#endif  // CONDITIONMANAGER_H_INCLUDED
