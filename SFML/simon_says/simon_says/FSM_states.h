#pragma once

// Defining FSM states
enum class FSMStates
{
	GENERATE_SEQUENCE,
	NEXT_SEQUENCE,
	SHOW_SEQUENCE,
	CHECK_INPUT,
	WRONG_INPUT,
	CORRECT_INPUT,
	DONE
};