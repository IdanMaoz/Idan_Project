

#include "timerContainer.h"
#include <cstring>
timerContainer::timerContainer() {
	memset(_timerTasks,0,20);
	_counter = 0;

}
void timerContainer::add(TimerTask* timerTask)
{
	 for(int i=0;i<_counter;i++){
		if(_timerTasks[i]== timerTask){
			return;
		}
	 }
	_timerTasks[_counter] = timerTask;
	_counter++;
}

void timerContainer::remove(TimerTask* timerTask)
{
	 for(int i=0;i<_counter;i++){
		if(_timerTasks[i]== timerTask){
			_timerTasks[i] = _timerTasks[_counter-1];
			_counter--;
			return;
		}
	}
}


void timerContainer::timeInterrupt()
{
	for(int i=0;i<_counter;i++){
		_timerTasks[i]->timerFunc();
	}

}
