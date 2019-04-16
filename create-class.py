#!/usr/bin/env python3

import os
import argparse
import re

parser = argparse.ArgumentParser('create-class.py')
parser.add_argument('type', choices=['state', 'component'])
parser.add_argument('name', help='Class name')
args = parser.parse_args()

class_type = args.type.capitalize()
class_name = args.name.capitalize()

if class_type == 'State':
    class_name = class_name + 'State'

with open('templates/' + class_type + '.hpp.template', 'r') as file:
    data = file.read()
    data = data.replace('<CAMELCASENAME>', class_name)
    data = data.replace('<UPPERCASENAME>', class_name.upper())
    with open('include/' + class_name + '.hpp', 'w') as header_file:
        header_file.write(data)
        
with open('templates/' + class_type + '.cpp.template', 'r') as file:
    data = file.read()
    data = data.replace('<CAMELCASENAME>', class_name)
    data = data.replace('<UPPERCASENAME>', class_name.upper())
    with open('src/' + class_name + '.cpp', 'w') as header_file:
        header_file.write(data)
