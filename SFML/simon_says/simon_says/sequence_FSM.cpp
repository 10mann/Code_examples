#include "sequence_FSM.h"


// ================ Constructors ================
SequenceFSM::SequenceFSM(int difficulty)
{
	this->started = false;
	this->currentStep = 0;
	this->difficulty = difficulty;
	this->state = FSMStates::GENERATE_SEQUENCE;
	this->rng = std::mt19937(this->random_device());
	this->getRandomNumber = std::uniform_int_distribution<std::mt19937::result_type>(0, 8);
	this->grid = nullptr;
	this->inputButtons = nullptr;
	this->score = nullptr;
}

// ================ Functions ================

// Attach grid to the FSM
void SequenceFSM::setGrid(SequenceGrid* grid)
{
	this->grid = grid;
}

// Attach input panel to the FSM
void SequenceFSM::setInputPanel(ButtonPanel* inputButtons)
{
	this->inputButtons = inputButtons;
}

// Attach score to the FSM
void SequenceFSM::setLightCluster(LightCluster* score)
{
	this->score = score;
}

// Starts a thread to run the FSM, and sets the default state
void SequenceFSM::start()
{
	printf("Starting FSM\n");
	this->started = true;
	this->state = FSMStates::GENERATE_SEQUENCE;

	this->FSMThread = std::thread(&SequenceFSM::FSM, this);
	FSMThread.detach();
}

// Stops the FSM
void SequenceFSM::stop()
{
	printf("Stopping FSM\n");
	this->started = false;
}

void SequenceFSM::restart()
{
	this->state = FSMStates::GENERATE_SEQUENCE;
	if (!this->started)
		this->start();
}

// A simple FSM to check user input and control the game
void SequenceFSM::FSM()
{
	if (this->grid == nullptr)
		this->stop();

	bool correctInput = true;
	int pressedButton = -1;
	int sequenceCheckIndex = 0;

	while(this->started)
	{
		switch (this->state)
		{
			// Sets up default values, then sets the next state of the FSM
			case FSMStates::GENERATE_SEQUENCE:
				printf("Setting default values\n");
				this->grid->reset();
				this->currentStep = 0;
				this->sequence.clear();
				sequenceCheckIndex = 0;
				this->score->setActive(this->currentStep);
				printf("Generating sequence\n");
				this->sequence.push_back(this->getRandomNumber(this->rng));

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				this->state = FSMStates::SHOW_SEQUENCE;
				break;

			// In this state the sequence is shown on screen with a set delay
			case FSMStates::SHOW_SEQUENCE:
				printf("Showing sequence\n");

				printf("Sequence: ");
				for (int i = 0; i < this->sequence.size(); i++)
				{
					this->grid->setBoxState(this->sequence[i], true);
					printf("%i ", this->sequence[i]);
					std::this_thread::sleep_for(std::chrono::milliseconds(800));
					this->grid->setBoxState(this->sequence[i], false);
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
				}

				printf("\n");
				sequenceCheckIndex = 0;
				this->state = FSMStates::CHECK_INPUT;
				break;

			// Checks which button was pressed and compares the sequence to the pressed button
			case FSMStates::CHECK_INPUT:
				//printf("Checking input\n");
				//printf("Step %i/%i\n", this->currentStep, this->difficulty);
				correctInput = true;

				pressedButton = this->inputButtons->getButtonPressedIndex();
					
				if(pressedButton != -1)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
					printf("Seqence number: %i, pressed index: %i, index: %i\n", this->sequence[sequenceCheckIndex], pressedButton, sequenceCheckIndex);
					if (pressedButton != this->sequence[sequenceCheckIndex])
					{
						correctInput = false;
						this->state = FSMStates::WRONG_INPUT;
					}

					else
					{
						if (++sequenceCheckIndex == this->sequence.size())
						{
							this->currentStep++;
							this->state = FSMStates::CORRECT_INPUT;
						}
					}
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				break;

			// If the correct button was pressed, the game proceeds
			case FSMStates::CORRECT_INPUT:
				printf("Correct!\n");
				this->score->setActive(this->currentStep);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				
				if (this->currentStep == this->difficulty)
				{
					printf("Done\n");
					this->state = FSMStates::DONE;
				}
				else
				{
					this->state = FSMStates::NEXT_SEQUENCE;
				}
				break;

			// Chooses the next index of the sequence
			case FSMStates::NEXT_SEQUENCE:
				this->sequence.push_back(this->getRandomNumber(this->rng));

				this->state = FSMStates::SHOW_SEQUENCE;
				break;

			// If the wrong button is pressed, the game restarts
			case FSMStates::WRONG_INPUT:
				printf("Wrong!\n");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				this->state = FSMStates::GENERATE_SEQUENCE;
				break;

			// if the sequence is correct, the game end and the player won
			case FSMStates::DONE:
				printf("You win!\n");
				this->stop();
				break;
		}
	}

	printf("Thread done\n");
}