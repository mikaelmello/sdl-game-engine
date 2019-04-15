#!/usr/bin/env python3

import os
import argparse
import re

parser = argparse.ArgumentParser('create-state.py')
parser.add_argument('state_name', help='State name')
args = parser.parse_args()

state_name = args.state_name.capitalize() + 'State'

with open('templates/State.hpp.template', 'r') as file:
    data = file.read()
    data = data.replace('<CAMELCASENAME>', state_name)
    data = data.replace('<UPPERCASENAME>', state_name.upper())
    with open('include/' + state_name + '.hpp', 'w') as header_file:
        header_file.write(data)
        
with open('templates/State.cpp.template', 'r') as file:
    data = file.read()
    data = data.replace('<CAMELCASENAME>', state_name)
    data = data.replace('<UPPERCASENAME>', state_name.upper())
    with open('src/' + state_name + '.cpp', 'w') as header_file:
        header_file.write(data)
