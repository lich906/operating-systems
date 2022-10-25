import sys
import random

USAGE_HINT = 'Usage:\t machinegen.py machine_type(mealy|moore) number_of_states number_of_inputs number_of_outputs'

STATE_LETTER = 'a'
OUTPUT_LETTER = 'w'
INPUT_LETTER = 'z'

def generate_mealy(num_of_states, num_of_inputs, num_of_outputs):
    def get_rand_transition_str():
        return STATE_LETTER + str(random.randrange(num_of_states)) + '/' + OUTPUT_LETTER + str(random.randrange(num_of_outputs))

    for state_num in range(num_of_states):
        print (';', STATE_LETTER, str(state_num), sep='', end='')
    print()
    for input_num in range(num_of_inputs):
        print(INPUT_LETTER, input_num, sep='', end='')
        for i in range(num_of_states):
            print(';' + get_rand_transition_str(), end='')
        print()

def generate_moore(num_of_states, num_of_inputs, num_of_outputs):
    for i in range(num_of_states):
        print(';', OUTPUT_LETTER, random.randrange(num_of_outputs), sep='', end='')
    print()
    for state_num in range(num_of_states):
        print(';', STATE_LETTER, str(state_num), sep='', end='')
    print()
    for input_num in range(num_of_inputs):
        print(INPUT_LETTER, input_num, sep='', end='')
        for i in range(num_of_states):
            print(';' + STATE_LETTER, random.randrange(num_of_states), sep='', end='')
        print()

def parse_args(argc, argv):
    if argc != 5:
        raise Exception('Invalid number of arguments')
    try:
        return [argv[1]] + [eval(n) for n in argv[2:5]]
    except ValueError:
        raise Exception('Invalid type of arguments')

def main(argc, argv):
    [machine_type, num_of_states, num_of_inputs, num_of_outputs] = parse_args(argc, argv)
    if num_of_states < 0 or num_of_inputs < 0 or num_of_outputs < 0:
        raise Exception('Only positive numbers are allowed')
    if machine_type == 'mealy':
        generate_mealy(num_of_states, num_of_inputs, num_of_outputs)
    elif machine_type == 'moore':
        generate_moore(num_of_states, num_of_inputs, num_of_outputs)
    else:
        raise Exception('Invalid machine type')

argc = len(sys.argv)
try:
    main(argc, sys.argv)
except Exception as e:
    print(e)
    print(USAGE_HINT)
    sys.exit(1)
