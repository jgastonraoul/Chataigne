/*
  ==============================================================================

    SequenceTimelineSeeker.cpp
    Created: 23 Nov 2016 11:31:50pm
    Author:  Ben Kuper

  ==============================================================================
*/

#include "SequenceTimelineSeeker.h"
#include "Style.h"

SequenceTimelineSeeker::SequenceTimelineSeeker(Sequence * _sequence) :
	sequence(_sequence)
{
	addAndMakeVisible(&handle);
	sequence->addAsyncContainerListener(this);
	handle.addMouseListener(this,false);
}

SequenceTimelineSeeker::~SequenceTimelineSeeker()
{
	sequence->removeAsyncContainerListener(this);
}

void SequenceTimelineSeeker::paint(Graphics & g)
{
	g.setColour(BG_COLOR);
	g.fillRoundedRectangle(getLocalBounds().toFloat(),2);
	g.setColour(BG_COLOR.darker());
	g.drawRoundedRectangle(getLocalBounds().toFloat(), 2, 2);
	g.setColour(HIGHLIGHT_COLOR);
	float tx = getXForTime(sequence->currentTime->floatValue());
	g.drawLine(tx, 0, tx, getHeight(), 2);
}

void SequenceTimelineSeeker::resized()
{
	Rectangle<int> r = getLocalBounds();
	r.setLeft(getXForTime(sequence->viewStartTime->floatValue()));
	r.setRight(getXForTime(sequence->viewEndTime->floatValue()));
	handle.setBounds(r);
}

void SequenceTimelineSeeker::mouseDown(const MouseEvent & e)
{
	viewStartAtMouseDown = sequence->viewStartTime->floatValue();
	viewEndAtMouseDown = sequence->viewEndTime->floatValue();
	timeAnchor = getTimeForX(e.getMouseDownPosition().x);
}

void SequenceTimelineSeeker::mouseDrag(const MouseEvent & e)
{
	if (e.originalComponent != &handle) return;
	
	float offsetX = e.getOffsetFromDragStart().x;
	float offsetY = e.getOffsetFromDragStart().y / sequence->totalTime->floatValue();

	/*
	float viewTime = (viewEndAtMouseDown - viewStartAtMouseDown);
	if (viewTime == 0) return;
	float viewTimeFactor = ((viewTime - offsetY) / viewTime);
	if (viewTimeFactor == 0) return;

	float destAnchor = timeAnchor + getTimeForX(offsetX);
	float newViewStart = destAnchor - (timeAnchor-viewStartAtMouseDown)*viewTimeFactor;
	float newViewEnd = destAnchor - (timeAnchor-viewEndAtMouseDown)*viewTimeFactor;
	
	sequence->viewStartTime->setValue(newViewStart);
	sequence->viewEndTime->setValue(newViewEnd);
	*/

	sequence->viewStartTime->setValue(viewStartAtMouseDown + getTimeForX(offsetX));
	sequence->viewEndTime->setValue(viewEndAtMouseDown + getTimeForX(offsetX));
}


int SequenceTimelineSeeker::getXForTime(float time)
{
	return (int)jmap<float>(time, 0, sequence->totalTime->floatValue(), 0, (float)getWidth());
}

float SequenceTimelineSeeker::getTimeForX(int tx)
{
	return jmap<float>((float)tx, 0, (float)getWidth(), 0, sequence->totalTime->floatValue());
}


void SequenceTimelineSeeker::newMessage(const ContainerAsyncEvent & e)
{
	switch (e.type)
	{
	case ContainerAsyncEvent::ControllableFeedbackUpdate:

		if (e.targetControllable == sequence->viewStartTime || e.targetControllable == sequence->viewEndTime)
		{
			resized();
		}
		else if (e.targetControllable == sequence->currentTime)
		{
			repaint();
			resized();
		}
		else if (e.targetControllable == sequence->totalTime)
		{
			repaint();
			resized();
		}
		break;

	default:
		//other events not handled 
		break;
	}
}


void SeekHandle::paint(Graphics & g)
{
	g.setColour(BLUE_COLOR.withAlpha(.3f));
	g.fillRoundedRectangle(getLocalBounds().toFloat(), 2);
	g.setColour(BLUE_COLOR.brighter());
	g.drawRoundedRectangle(getLocalBounds().toFloat(), 2, 2);
}

void SeekHandle::resized()
{
}