#pragma once

#include <thread>
#include <vector>
#include <random>

#include "FSM_states.h"
#include "light_cluster.h"
#include "sequence_grid.h"
#include "button_panel.h"


class SequenceFSM
{
private:
	int difficulty;
	int currentStep;
	FSMStates state;
	bool started = false;
	std::vector<int> sequence;
	std::random_device random_device;
	std::mt19937 rng;
	std::uniform_int_distribution<std::mt19937::result_type> getRandomNumber;

	SequenceGrid* grid;
	ButtonPanel* inputButtons;
	LightCluster* score;

	std::thread FSMThread;

public:
	// ================ Constructors ================
	SequenceFSM(int difficulty);

	// ================ Functions ================
	void setGrid(SequenceGrid* grid);
	void setInputPanel(ButtonPanel* inputButtons);
	void setLightCluster(LightCluster* score);
	void start();
	void stop();
	void restart();

	void FSM();
};