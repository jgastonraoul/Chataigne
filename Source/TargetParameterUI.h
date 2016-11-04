/*
  ==============================================================================

    TargetParameterUI.h
    Created: 2 Nov 2016 5:00:10pm
    Author:  bkupe

  ==============================================================================
*/

#ifndef TARGETPARAMETERUI_H_INCLUDED
#define TARGETPARAMETERUI_H_INCLUDED

#include "TargetParameter.h"
#include "ParameterUI.h"

class TargetParameterUI :
	public ParameterUI,
	public ButtonListener
{
public:
	TargetParameterUI(TargetParameter * parameter, const String &noTargetText = "[Click to select an element]");
	~TargetParameterUI();

	String noTargetText;
	Label label;
	ScopedPointer<ImageButton> targetBT;

	TargetParameter * targetParameter;
	
	void paint(Graphics &g) override;
	void resized() override;

	void updateLabel();
	
	void mouseDown(const MouseEvent &e);

	virtual void buttonClicked(Button * b) override;
protected:
	void valueChanged(const var & v) override;


	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TargetParameterUI)
};



#endif  // TARGETPARAMETERUI_H_INCLUDED
