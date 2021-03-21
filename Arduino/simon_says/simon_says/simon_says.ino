/*
    This is a simple version of a Simon says game using an Arduino Uno
    The aim of the game is to enter the sequence output by the system in the correct order
    The sequence is shown on a 3x3 grid of leds and the input consists of a 3x3 grid of buttons
    The first sequence is a single led, then if the correct input is given, the first led will blink again followed by a new addition to the sequence
    This will go on until a wrong input is given and the game restarts
*/
#define MAX_DIFFICULTY 99

// Button input states
enum Input
{
    Correct_input,
    Incorrect_input,
    No_input
};

// Declaring functions
void init_leds();
void init_buttons();
void init_game();
void generate_sequence();
void show_sequence();
void update_led_matrix();
void update_button_input();

void init_display_fsm();
void init_display();
void led_matrix_set_led(int led_index, int value);
void reset_led_matrix();
void reset_button_input();
enum Input check_input();
int get_button_pressed();

// ======================== Leds ========================
    // The display consists of a grid of 3x3 Leds
    // They are configured in a matrix grid to save IO-pins
    // On each row, the leds are connected to eachother via the cathode and then connected to a common output pin via a current limiting resistor
    // The row is enabled when the output pin is set to 0
    // Each column connects the leds via the anode and then to an output pin, the column is enabled when the output pin is 1
    // When the leds are connected in a matrix, in order to turn on a specific led, the correct row needs to be set to 0 and the corresponding column must be 1
    // When enabling multiple leds, the outputs need to be multiplexed in order to only show the correct leds as lit
    // This is done by checking how much time has passed and incrementing the row counter, then disabling the previous row when enabling the current row
    // By doing this, there is only one active led at a time, but this happens so fast that it looks like the leds are on simultaneously
const unsigned int led_rows = 3;
const unsigned int led_cols = 3;
const unsigned int number_of_leds = led_rows * led_cols;
uint8_t led_row_index = 0;
uint8_t led_col_index = 0;
const unsigned int led_row_pins[led_rows] = { 2, 3, 4 };
const unsigned int led_col_pins[led_cols] = { 5, 6, 7 };
const unsigned long led_row_time_ms = 1;
unsigned long led_prev_time = 0;
uint8_t led_matrix[led_rows][led_cols] =
{
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};

// ======================== Buttons ========================
    // The buttons are configured in a matrix orientation in order to save IO-pins
    // The pins connected to each row is set as an output pin and is only set high when that row is checked for input
    // Each column is connected to pins configured as input pins
    // By only enabling one row at a time, the correct button can be identified and is set in the button matrix input grid
const unsigned int button_rows = 3;
const unsigned int button_cols = 3;
uint8_t button_row_index = 0;
const unsigned int button_row_pins[button_rows] = { A0, A1, A2 };
const unsigned int button_col_pins[button_cols] = { 8, 9, 10 };
const unsigned long button_row_time_ms = 10;
unsigned long button_prev_time = 0;
uint8_t button_matrix[button_rows][button_cols] =
{
  0, 0, 0,
  0, 0, 0,
  0, 0, 0
};

// ======================== FSM ========================
    // The FSM controls the state of the game and decides which state is next
enum State
{
    Init_state,
    Start_sequence_state,
    Check_input_state,
    Correct_input_state,
    Incorrect_input_state,
    Next_sequence_state,
    Show_sequence_state,
    Correct_input_wait_state,
    Incorrect_input_wait_state
};

enum State state = Init_state;
enum State next_state = Init_state;

uint8_t sequence[MAX_DIFFICULTY];
unsigned int sequence_index = 0;
const unsigned long show_sequence_time_ms = 300;
unsigned long show_sequence_prev_time = 0;
const unsigned long correct_input_wait_time_ms = 1000;
unsigned long correct_input_wait_prev_time = 0;
const unsigned long incorrect_input_wait_time_ms = 1000;
unsigned long incorrect_input_wait_prev_time = 0;

// ======================== Display FSM ========================
    // The display fsm dictates which state the display is in
enum Display_state
{
    Init_display_state,
    Set_led_state,
    Light_on_state,
    Light_off_state,
    Next_sequence_index_state,
    Display_done_state
};

enum Display_state display_state = Init_display_state;
enum Display_state next_display_state = Init_display_state;
unsigned int display_sequence_index = 0;
bool display_done = false;

// ======================== Input ========================
unsigned long check_input_index = 0;
enum Input input;

void setup()
{
    // Serial.print is only used for testing and debugging
    Serial.begin(9600);

    // ======================== FSM ========================
    state = Init_state;
    int seed = analogRead(A5); // In order to get a different result from random each time the microcontroller is turned on, the random seed is set by reading a floating analog input
    //Serial.println();
    randomSeed(seed);

    // ======================== Leds ========================
    init_leds();

    // ======================== Buttons ========================
    init_buttons();
}

void loop()
{
    enum Input input;
    switch (state)
    {
        case Init_state:
        {
            init_game();
            next_state = Start_sequence_state;
            break;
        }

        case Start_sequence_state:
        {
            generate_sequence();
            next_state = Show_sequence_state;
            break;
        }

        case Check_input_state:
        {
            input = check_input();

            if (input == Correct_input)
            {
                next_state = Correct_input_state;
            }
            else if (input == Incorrect_input)
            {
                next_state = Incorrect_input_state;
            }
            break;
        }

        case Correct_input_state:
        {
            if (check_input() == No_input)
            {
                if (++check_input_index >= sequence_index)
                {
                    next_state = Correct_input_wait_state;
                    correct_input_wait_prev_time = millis();
                }
                else
                {
                    next_state = Check_input_state;
                }
            }
            break;
        }

        case Incorrect_input_state:
        {
            if (check_input() == No_input)
            {
                check_input_index = 0;
                next_state = Incorrect_input_wait_state;
                incorrect_input_wait_prev_time = millis();
            }
            break;
        }

        case Next_sequence_state:
        {
            generate_sequence();
            next_state = Show_sequence_state;
            break;
        }

        case Show_sequence_state:
        {
            show_sequence();
            check_input_index = 0;
            next_state = Check_input_state;
            break;
        }

        case Correct_input_wait_state:
        {
            if (millis() - correct_input_wait_prev_time >= correct_input_wait_time_ms)
            {
                next_state = Next_sequence_state;
            }
            break;
        }

        case Incorrect_input_wait_state:
        {
            if (millis() - incorrect_input_wait_prev_time >= incorrect_input_wait_time_ms)
            {
                next_state = Init_state;
            }
            break;
        }

        default:
        {
            next_state = Init_state;
            break;
        }
    }

    update_button_input();
    update_led_matrix();
    state = next_state;
}

void init_leds()
{
    // Setting pin mode for all led rows, and setting the pins high to cut the connection to ground
    for (unsigned int i = 0; i < led_rows; ++i)
    {
        pinMode(led_row_pins[i], OUTPUT);
        digitalWrite(led_row_pins[i], 1);
    }

    // Setting pin mode for led columns and setting the pin low to turn the leds off
    for (unsigned int i = 0; i < led_cols; ++i)
    {
        pinMode(led_col_pins[i], OUTPUT);
        digitalWrite(led_col_pins[i], 0);
    }
}

void init_buttons()
{
    // Setting pin mode for button rows and disabling each row
    for (unsigned int i = 0; i < button_rows; ++i)
    {
        pinMode(button_row_pins[i], OUTPUT);
        digitalWrite(button_row_pins[i], 0);
    }

    // Setting pin mode for each button column 
    for (unsigned int i = 0; i < button_cols; ++i)
    {
        pinMode(button_col_pins[i], INPUT_PULLUP);
    }
}

void init_game()
{
    sequence_index = 0;
    reset_led_matrix();
    reset_button_input();
    memset(sequence, 0, MAX_DIFFICULTY * sizeof(sequence[0]));
}

void generate_sequence()
{
    sequence[sequence_index++] = random(number_of_leds);
    //Serial.print("Sequence: ");
    //Serial.println(sequence[sequence_index]);
}

// Show the sequence on the display with a defined delay
void show_sequence()
{
    init_display_fsm();

    while (!display_done)
    {
        switch (display_state)
        {
            case Init_display_state:
            {
                init_display();
                break;
            }

            case Set_led_state:
            {
                led_matrix_set_led(sequence[display_sequence_index], 1);
                next_display_state = Light_on_state;
                show_sequence_prev_time = millis();
                break;
            }

            case Light_on_state:
            {
                if (millis() - show_sequence_prev_time >= show_sequence_time_ms)
                {
                    next_display_state = Light_off_state;
                    show_sequence_prev_time = millis();
                    reset_led_matrix();
                }
                break;
            }

            case Light_off_state:
            {
                if (millis() - show_sequence_prev_time >= show_sequence_time_ms)
                {
                    next_display_state = Next_sequence_index_state;
                }
                break;
            }

            case Next_sequence_index_state:
            {
                if (++display_sequence_index >= sequence_index)
                {
                    next_display_state = Display_done_state;
                }
                else
                {
                    next_display_state = Set_led_state;
                }
                break;
            }

            case Display_done_state:
            {
                display_done = true;
                break;
            }
        }

        update_led_matrix();
        display_state = next_display_state;
    }
}

void update_led_matrix()
{
    if (millis() - led_prev_time >= led_row_time_ms)
    {
        led_prev_time = millis();
        for (uint8_t i = 0; i < led_cols; ++i)
        {
            digitalWrite(led_col_pins[i], 0);
        }
        digitalWrite(led_row_pins[led_row_index], 1);
        led_row_index++;
        if (led_row_index >= led_rows)
        {
            led_row_index = 0;
        }

        digitalWrite(led_row_pins[led_row_index], 0);

        for (uint8_t i = 0; i < led_cols; ++i)
        {
            digitalWrite(led_col_pins[i], led_matrix[led_row_index][i]);
        }
    }
}

void update_button_input()
{
    if (millis() - button_prev_time >= button_row_time_ms)
    {
        button_prev_time = millis();
        digitalWrite(button_row_pins[button_row_index], 1);

        button_row_index++;
        if (button_row_index >= button_rows)
        {
            button_row_index = 0;
        }
        
        digitalWrite(button_row_pins[button_row_index], 0);
    }

    for (uint8_t i = 0; i < button_cols; ++i)
    {
        button_matrix[button_row_index][i] = !digitalRead(button_col_pins[i]);
    }

    memcpy(led_matrix, button_matrix, button_rows * button_cols);
}

void init_display_fsm()
{
    display_done = false;
    display_sequence_index = 0;
    display_state = Init_display_state;
}

void init_display()
{
    reset_led_matrix();

    next_display_state = Set_led_state;
}

void led_matrix_set_led(int led_index, int value)
{
    uint8_t x = led_index / led_rows;
    uint8_t y = led_index % led_rows;
    //Serial.print("Led (");
    //Serial.print(x);
    //Serial.print(", ");
    //Serial.print(y);
    //Serial.print(") turned on\n");
    led_matrix[led_index / led_rows][led_index % led_rows] = value;
}

void reset_led_matrix()
{
    memset(led_matrix, 0, led_rows * led_cols * sizeof(led_matrix[0][0]));
}

void reset_button_input()
{
    memset(button_matrix, 0, button_cols * button_rows * sizeof(button_matrix[0][0]));
}

enum Input check_input()
{
    int button_pressed = get_button_pressed();

    if (button_pressed == -1)
    {
        return No_input;
    }

    if (button_pressed == sequence[check_input_index])
    {
        //Serial.println("Correct input");
        return Correct_input;
    }
    else
    {
        //Serial.println("Incorrect input");
        return Incorrect_input;
    }
}

int get_button_pressed()
{
    uint8_t x = 0;
    uint8_t y = 0;

    for (x = 0; x < button_rows; ++x)
    {
        for (y = 0; y < button_cols; ++y)
        {
            if (button_matrix[x][y] == 1)
            {
                return button_rows * x + y;
            }
        }
    }

    return -1;
}