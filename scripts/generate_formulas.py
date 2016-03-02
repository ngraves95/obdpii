#!/usr/bin/python

from bs4 import BeautifulSoup

INFILE="OBD-II_PIDs"

byte_coding = {'A' : 0, 'B' : 1, 'C' : 2, 'D' : 3}
operators = '+-/*'

def declare_var(byte, arg_name ):

    if byte not in byte_coding:
        return ""

    return "int {0} = ({1} >> (8 * {2})) & 0xFF;".format(byte, arg_name, byte_coding[byte])


with open(INFILE, 'r') as raw_html:
    soup = BeautifulSoup(raw_html, 'html.parser')
    tables = soup.find_all('table')
    mode01_table = tables[2]
    arg_name = "packed"
    function_names = []
    # contents[1] is the header of the table.
    # need to increment by 2 to get the next row.
    for i in range(1, len(mode01_table.contents), 2):
        row = mode01_table.contents[i]
        col = row.find_all('td')
        if (len(col) > 0):

            formula = col[6].text.strip().replace(",", "");
            fn = "pid"+col[0].tt.text+"_handler"
            function_names.append(fn)
            generated_func_body = "static int " + fn + "(int " + arg_name + ")\n{\n"
            find_flag = False
            for byte in byte_coding:
                i = formula.find(byte)
                if i >= 0 and (i >= len(formula) - 1
                                 or formula[i + 1] in operators
                                 or formula[i - 1] in operators):
                        find_flag = True
                        generated_func_body += "\t" + declare_var(byte, arg_name) + "\n"

            if find_flag:
                generated_func_body += "\treturn " + "(" + formula.replace("\n", ") / (") + ");\n"
            else:
                generated_func_body += "\treturn packed;\n"

            generated_func_body += "}"
            print (generated_func_body)

    # declare array that will hold these function pointers
    arr = "const pid_handler pid_formulas[] = {\n        " + ",\n        ".join(function_names) + "\n};"
    print (arr)
