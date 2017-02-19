#!/usr/bin/env python3
# -*- coding: utf-8 -*-

MODE = 1
SPECIAL = ['!', '%', '$']
REPLACEMENTS = {'kyr' : 'I', 'k' : 'I',
                'fat' : 'B', 'f' : 'B',
                'undr' : 'U', 'u' : 'U',
                'zach' : 'S', 'z' : 'S',
                'up' : 'SUP', 'up' : 'SUP',
                'down' : 'SUB', 'down' : 'SUB',
                'parag' : 'P', 'p' : 'P',
                '~' : '~'
                }
KEY_WORDS = ['B', 'I', 'U', 'S', 'SUP', 'SUB', 'P', '+', '-']
FONT_TAG_KEY_WORDS = ['color', 'clr', 'c=']

def get_word(string, start_index, finish_symb):
    word = ''
    for i in range(start_index, len(string)):
        if string[i] == finish_symb:
            break
        word = word + string[i]
    return word


def handle_spec(spec):
    global fout
    if spec == 'n':
        print('<BR>\n', end='', file=fout)
    if spec == 'h':
        print('\n<HR>\n', end='', file=fout)
    return 0


def handle_misc_variable(string):
    global to_print_end
    string = string.split('=')
    if string[0] in ['color', 'clr', 'c']:
        print('<FONT color=', string[1], '>', sep='', end='', file=fout)
        to_print_end = to_print_end  + '</FONT>'



def handle_tag(tag):
    for misc_word in FONT_TAG_KEY_WORDS:
        if misc_word in tag:
            handle_misc_variable(tag)
            return ''

    if MODE < 2:
        for rep in REPLACEMENTS:
            if rep in tag:
                tag = tag.replace(rep, REPLACEMENTS[rep])
    if MODE < 1:
        if tag not in KEY_WORDS:
            print('WRONG TAG')
            return ''

    if tag[0] == '-':
        to_print = '</'
    else:
        to_print = '<'
    if tag[0] == '+' or tag[0] == '-':
        tag = tag[1:]

    tag = tag.capitalize()
    to_print = to_print + tag + '>'
    #print(to_print, end='', file=fout)
    return to_print
        

def handle_tag_args(string):
    string = string.split('|')
    tag = string[0]
    string = string[1:]
    to_print = handle_tag(tag)
    to_print = to_print[:len(to_print) - 1]

    for i in range(len(string)):
        try:
            arg_name, arg_value = string[i].split('=')
            to_print = to_print + ' ' + arg_name + '=' + arg_value
        except:
            print('failed transforming', string, 'into tag with args')
            return ''

    to_print = to_print + '>'
    return to_print



def handle_string(string):
    string = list(string)
    global to_print_end
    to_print_end = ''

    try:
        if string[-1] != '!' and string[-2] != '%':
            string.append(' ')
    except:
        print('print more words on one line, pleas')
    to_print = ''
    to_miss = 0

    for symb_index in range(len(string)):
        symb = string[symb_index]
        if to_miss:
            to_miss = max(to_miss - 1, 0)
            continue

        if symb not in SPECIAL:
            print(symb, end='', file=fout)
            continue

        if symb == '!':
            try:
                tag = get_word(string, symb_index + 1, '!')
            except:
                pass

            if len(tag) == 0:
                print('!', end='', file=fout)
            if len(tag) < 1:
                print('Invalid tag on index', symb_index)
            to_miss = len(tag) + 1

            if tag[0] == '$':
                print(handle_tag_args(tag[1:]), end='', file=fout)
            else:
                print(handle_tag(tag), end='', file=fout)

        if symb == '%':
            spec = string[symb_index + 1]
            handle_spec(spec)
            to_miss = 1
    print(to_print_end, file=fout)
    to_print_end = ''
    return 0



def main():
    bgcolor = "'" + input('BackGround color (HEX): ') + "'"
    if bgcolor == "''":
        bgcolor = "'skyblue'"
    body_args = input('Body args: ')

    print("write !help! if you don't know, how to use me\n!stop! to stop")

    global fout
    global help_file
    help_file = open('auto_html_help.txt', 'r')
    help_text = help_file.read()
    fout = open('ouput.html', 'w')

    print('<HTML>\n<HEAD>\n<TITLE>', file=fout)
    print(input('TITLE: '), file=fout)
    print('</TITLE>\n</HEAD>\n<BODY BGCOLOR=', bgcolor, ' ', body_args, '>',
          sep='', file=fout)

    string = ''
    while True:
        string = input()
        if string == '!stop!':
            break
        if string == '!help!':
            print(help_text)
        handle_string(string)

    print('\n</BODY>\n</HTML>', file=fout)
    fout.close()


if __name__ == "__main__":
    main()
