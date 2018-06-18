#!/usr/bin/env python3
# -*- coding: utf-8 -*-

SPECIAL = ['!', '%', '/']
MISC_KEY_WORDS = ['color=', 'clr=', 'c=', '-c']

def get_word(string, start_index, finish_symb):
    word = ''
    for i in range(start_index, len(string)):
        if string[i] == finish_symb:
            break
        word = word + string[i]
    return word


def handle_spec(string, spec_symb_index):
    global fout
    spec = string[spec_symb_index]

    if spec == 'n':
        if spec_symb_index == len(string):
            print('<BR>', end='', file=fout)
        else:
            print('<BR>\n' + ' ' * TAB_SIZE, end='', file=fout)
    if spec == 'h':
        print('<HR>', end='', file=fout)
    return 0

def handle_tag(tag):
    if len(tag) < 1:
        return ''

    global TAB_SIZE
    if tag[0] == '-':
        TAB_SIZE -= 2
        return '</' + tag[1:].upper() + '>'

    if tag[0] == '+':
        tag = tag[1:]
    tag = tag.split('|')
    output = '<' + tag[0].upper()
    for i in range(1, len(tag)):
        output = output + ' ' + tag[i]
    output = output + '>'
    TAB_SIZE += 2

    return output


def handle_string(string):
    global TAB_SIZE
    global symb_index

    if len(string) < 1:
        print('[empty_string]')
        return 0

    if len(string) > 1 and string[0] == '!' and string[1] == '-':
        print(' ' * (TAB_SIZE - 2), end='', file=fout)
    else:
        print(' ' * TAB_SIZE, end='', file=fout)

    symb_index = 0
    string_len = len(string)

    while symb_index < string_len:
        symb_used = False
        symb = string[symb_index]
        
        if (symb not in SPECIAL or
           symb_index == string_len or
           string[symb_index - 1] == '/'):
            print(symb, end='', file=fout)
            symb_index += 1
            symb_used = True

        if not symb_used and (symb == '!'and string[symb_index - 1] != '/'):
            tag = get_word(string, symb_index + 1, '!')
            symb_index += len(tag) + 2
            to_print = handle_tag(tag)
            print(to_print, end='', file=fout)
            symb_used = True

        if not symb_used and (symb == '%' and string[symb_index - 1] != '/'):
            handle_spec(string, symb_index + 1)
            symb_index += 2
            symb_used = True

    print('\n', end='', file=fout)




TAB_SIZE = 4
def main():
    global fout
    global help_file
    help_file = open('auto_html_help.txt', 'r')
    help_text = help_file.read()
    fout = open('html_page.html', 'w')

    print('<HTML>', file=fout)
    print('  <HEAD>', file=fout)
    print('    <TITLE>', file=fout)
    print('      ' + input('Title: '), file=fout)
    print('    </TITLE>', file=fout)
    print('  <HEAD>', file=fout)
    print('  <BODY BGCOLOR=', end='', file=fout)
    
    bgcolor = "'" + input('Body color (HEX): ') + "'"
    if len(bgcolor) != 8:
        bgcolor = 'skyblue'
    body_args = input('Body args: ')
    if body_args:
        body_args = ' ' + body_args
    print(bgcolor + body_args, end='>\n', file=fout)

    print("--write !help! if you don't know, how to use me")
    print('--!stop! to stop')
    
    while True:
        string = input()
        if string == '!stop!':
            break
        if string == '!help!':
            print(help_text)
        handle_string(string)

    print('  </BODY>', file=fout)
    print('</HTML>', file=fout)
    fout.close()


if __name__ == "__main__":
    main()
